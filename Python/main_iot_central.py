# -------------------------------------------------------------------------
# Copyright (c) G&S Gestion y Sistemas. All rights reserved.
# Licensed under the MIT License. See License.txt in the project root for
# license information.
# inspirado en: https://github.com/Azure/azure-iot-sdk-python/tree/master/azure-iot-device/samples/pnp 
# --------------------------------------------------------------------------
import os
import asyncio
import random
import logging
import json

from azure.iot.device.aio import IoTHubDeviceClient
from azure.iot.device.aio import ProvisioningDeviceClient
from azure.iot.device import constant, Message, MethodResponse
from datetime import date, timedelta, datetime

import serial 
import time

import subprocess
import ctypes

intruso_val = 0
#####################################################
# SERIAL PORT CONFIGURATION
SERIAL_PORT = "COM4" 
ser = serial.Serial(SERIAL_PORT, baudrate = 9600)

logging.basicConfig(level=logging.ERROR)


# This id can change according to the company the user is from
# and the name user wants to call this Plug and Play device
model_id = "dtmi:iotcentralgyslorawan:HandsOnLabDevice346;1"

#####################################################
# COMMAND HANDLERS : User will define these handlers
# depending on what commands the DTMI defines

async def ultrasound_distance_handler(values):
    global intruso_val
    if values:
        print(
            "Devuelve el valor de disntancia asignado  {since}".format(
                since=values
            )
        )
        intruso_val = 0
        
    print("Done generating")

# END COMMAND HANDLERS
#####################################################

#####################################################
# CREATE RESPONSES TO COMMANDS

def create_ultrasound_report_response(values):
    """
    An example function that can create a response to the "getMaxMinReport" command request the way the user wants it.
    Most of the times response is created by a helper function which follows a generic pattern.
    This should be only used when the user wants to give a detailed response back to the Hub.
    :param values: The values that were received as part of the request.
    """
    response_dict = {
        "endTime": datetime.now().isoformat(),
    }
    # serialize response dictionary into a JSON formatted str
    response_payload = json.dumps(response_dict, default=lambda o: o.__dict__, sort_keys=True)
    print(response_payload)
    return response_payload

# END CREATE RESPONSES TO COMMANDS
#####################################################

#####################################################
# TELEMETRY TASKS

async def send_telemetry_iot_central(device_client, telemetry_msg):
    msg = Message(json.dumps(telemetry_msg))
    msg.content_encoding = "utf-8"
    msg.content_type = "application/json"
    print("Sent message")
    await device_client.send_message(msg)

# END TELEMETRY TASKS
#####################################################

#####################################################
# CREATE COMMAND AND PROPERTY LISTENERS

async def execute_command_listener(
    device_client, method_name, user_command_handler, create_user_response_handler
):
    while True:
        if method_name:
            command_name = method_name
        else:
            command_name = None

        command_request = await device_client.receive_method_request(command_name)
        print("Command request received with payload")
        # https://docs.microsoft.com/en-us/python/api/azure-iot-device/azure.iot.device.methodrequest?view=azure-python 
        print(command_request.name)
        print(command_request.payload)
        

        values = {}
        if not command_request.payload:
            print("Payload was empty.")
        else:
            values = command_request.payload

        await user_command_handler(values)

        response_status = 200
        response_payload = create_user_response_handler(values)

        command_response = MethodResponse.create_from_method_request(
            command_request, response_status, response_payload
        )

        try:
            await device_client.send_method_response(command_response)
        except Exception:
            print("responding to the {command} command failed".format(command=method_name))


async def execute_property_listener(device_client):
    ignore_keys = ["__t", "$version"]
    while True:
        patch = await device_client.receive_twin_desired_properties_patch()  # blocking call

        print("the data in the desired properties patch was: {}".format(patch))

        version = patch["$version"]
        prop_dict = {}

        for prop_name, prop_value in patch.items():
            if prop_name in ignore_keys:
                continue
            else:
                prop_dict[prop_name] = {
                    "ac": 200,
                    "ad": "Successfully executed patch",
                    "av": version,
                    "value": prop_value,
                }

        await device_client.patch_twin_reported_properties(prop_dict)


# END COMMAND AND PROPERTY LISTENERS
#####################################################

#####################################################
# An # END KEYBOARD INPUT LISTENER to quit application


def stdin_listener():
    """
    Listener for quitting the sample
    """
    while True:
        selection = input("Press Q to quit\n")
        if selection == "Q" or selection == "q":
            print("Quitting...")
            break


# END KEYBOARD INPUT LISTENER
#####################################################


#####################################################
# PROVISION DEVICE
async def provision_device(provisioning_host, id_scope, registration_id, symmetric_key, model_id):
    provisioning_device_client = ProvisioningDeviceClient.create_from_symmetric_key(
        provisioning_host=provisioning_host,
        registration_id=registration_id,
        id_scope=id_scope,
        symmetric_key=symmetric_key,
    )
    provisioning_device_client.provisioning_payload = {"modelId": model_id}
    return await provisioning_device_client.register()


#####################################################
# MAIN STARTS
async def main():
    switch = "DPS" #os.getenv("IOTHUB_DEVICE_SECURITY_TYPE")
    if switch == "DPS":
        #provisioning_host = (
        #    os.getenv("IOTHUB_DEVICE_DPS_ENDPOINT")
        #    if os.getenv("IOTHUB_DEVICE_DPS_ENDPOINT")
        #    else "global.azure-devices-provisioning.net"
        #)
        
        provisioning_host =  "global.azure-devices-provisioning.net"
        
        #(
        #    "https://iotcentralgyslorawan.azureiotcentral.com"
        #    if "https://iotcentralgyslorawan.azureiotcentral.com"
        #    else "global.azure-devices-provisioning.net"
        #)

        id_scope = "" #ambito del id #os.getenv("IOTHUB_DEVICE_DPS_ID_SCOPE")
        registration_id = "" #os.getenv("IOTHUB_DEVICE_DPS_DEVICE_ID")
        symmetric_key = "" #os.getenv("IOTHUB_DEVICE_DPS_DEVICE_KEY")
        registration_result = await provision_device(
            provisioning_host, id_scope, registration_id, symmetric_key, model_id
        )

        if registration_result.status == "assigned":
            print("Device was assigned")
            print(registration_result.registration_state.assigned_hub)
            print(registration_result.registration_state.device_id)

            device_client = IoTHubDeviceClient.create_from_symmetric_key(
                symmetric_key=symmetric_key,
                hostname=registration_result.registration_state.assigned_hub,
                device_id=registration_result.registration_state.device_id,
                product_info=model_id,
            )
        else:
            raise RuntimeError(
                "Could not provision device. Aborting Plug and Play device connection."
            )

    elif switch == "connectionString":
        conn_str = os.getenv("IOTHUB_DEVICE_CONNECTION_STRING")
        print("Connecting using Connection String " + conn_str)
        device_client = IoTHubDeviceClient.create_from_connection_string(
            conn_str, product_info=model_id
        )
    else:
        raise RuntimeError(
            "At least one choice needs to be made for complete functioning of this sample."
        )

    # Connect the client.
    await device_client.connect()

    ################################################
    # Set and read desired property (target temperature)



    ################################################
    # Register callback and Handle command (reboot)
    print("Listening for command requests and property updates")

    listeners = asyncio.gather(
        execute_command_listener(
            device_client,
            method_name="DistanciaAPersona",
            user_command_handler=ultrasound_distance_handler,
            create_user_response_handler=create_ultrasound_report_response,
        ),
        execute_property_listener(device_client),
    )

    ################################################
    # Send telemetry (current temperature)

    async def send_telemetry():
        global intruso_val 
        print("Sending telemetry for temperature")
        estado_bloqueo = False
        
        notificacion_enviada = True
        
        await device_client.patch_twin_reported_properties({"Intruso": intruso_val})
        last_intruso_val = intruso_val

        while True:
            if last_intruso_val != intruso_val:
                await device_client.patch_twin_reported_properties({"Intruso": intruso_val})
                last_intruso_val = intruso_val

            #####################################################################
            # SERIAL PORT READ
            line = ser.readline()
            print(line)

            line = line.decode("utf-8")[:-3]
            valores = line.split("|")
            print(valores)
            keys = ["Ultrasonido","Temperatura","Humedad", "Ldr", "Potenciometro", "Servo"]
            send_data ={}
            send_data["Notificacion"] =0
            i= 0

            for valor in valores:
                if keys[i][0] == valor[0]:
                    send_data[keys[i]]=float(valor[1:])
                    i+=1
            
            if len(valores) == 6:
                print("verificar ultrasonido")
                #if ctypes.windll.user32.GetForegroundWindow() != 0:

                #####################################################################
                # BLOQUEA PC 60
                if int(send_data["Ultrasonido"]) >= 500 and ctypes.windll.user32.GetForegroundWindow() != 0:
                    # Bloquea computadora
                    #ctypes.windll.user32.LockWorkStation()
                    print("INICIA El bloqueo")
                    if estado_bloqueo != True:
                        estado_bloqueo = True

                #####################################################################
                # NOTIFICA DE UN INTRUSO NUEVO 60
                if int(send_data["Ultrasonido"]) <= 500: #and ctypes.windll.user32.GetForegroundWindow() == 0:

                    if notificacion_enviada==False:
                        print("NOTIFICA Intruso")
                        notificacion_enviada = True
                        send_data["Notificacion"] =1
                        #"""
                        intruso_val = 1  # Initial
                        await device_client.patch_twin_reported_properties({"Intruso": intruso_val})
                        
                else:
                    notificacion_enviada = False




                print(f"Dato a enviar: {notificacion_enviada}", send_data)

                await send_telemetry_iot_central(device_client, send_data)
                        
            await asyncio.sleep(3)
            

    send_telemetry_task = asyncio.create_task(send_telemetry())

    # Run the stdin listener in the event loop
    loop = asyncio.get_running_loop()
    user_finished = loop.run_in_executor(None, stdin_listener)
    # # Wait for user to indicate they are done listening for method calls
    await user_finished

    if not listeners.done():
        listeners.set_result("DONE")

    listeners.cancel()

    send_telemetry_task.cancel()

    # Finally, shut down the client
    await device_client.shutdown()


#####################################################
# EXECUTE MAIN

if __name__ == "__main__":
    asyncio.run(main())

    # If using Python 3.6 or below, use the following code instead of asyncio.run(main()):
    #loop = asyncio.get_event_loop()
    #loop.run_until_complete(main())
    #loop.close()

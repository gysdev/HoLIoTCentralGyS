# IoT Central

En el siguiente documento explicaremos como usar IoT Central desde crear una cuenta hasta conectar hacia un dispositivo 

En caso de que no tengas una cuenta de Microsoft, Outlook o Hotmail puedes seguir los pasos de como crear en la guia: <a href="CrearCuentaOutlook.md" target="_blank">CrearCuentaOutlook.md</a> 

## En la siguiente guía aprenderemos:
* [Acceder a  IoT Central](#acceder-a-iot-central)
* [Crear una aplicacion](#crear-una-aplicacion)
* [Crear plantilla de dispositivos](#crear-plantilla-de-dispositivos)
* [Crear un Modelo y agregar funcionalidad](#crear-un-modelo-y-agregar-funcionalidad)
* [Configuracion de vistas](#configuracion-de-vistas)
* [Publicar](#publicar)
* [Crear un dispositivo](#crear-un-dispositivo)

### Acceder a IoT Central

Para crear una cuenta de IoT Central ingresaremos a la página pricinpal de IoT Central: <a href="https://apps.azureiotcentral.com/" target="_blank">https://apps.azureiotcentral.com/</a> 

Dentro de la pagina seleccionamos el icono del ángulo superior derecha de Iniciar sesión con una cuenta
<p align="center"><img src="./images/iotcentral9.PNG" width="900"\></p>

Ingresamos el correo anteriormente creado u otra cuenta Outlook y click en **siguiente**
<p align="center"><img src="./images/iotcentral10.png" width="400"\></p>

Para poder acceder ingresamos la contraseña, presionar en **Ingresar** o **Sign In**
<p align="center"><img src="./images/iotcentral11.png" width="400"\></p>

Indicamos que queremos mantener la sesión iniciada, presionar en botón de **Sí** o **Yes**
<p align="center"><img src="./images/iotcentral12.png" width="400"\></p>

### Crear una aplicacion 

En la ventana principal de IoT Central dar click en **Compilar** y luego en **Crear una Aplicacion**
<p align="center"><img src="./images/iotcentral14.PNG" \></p>

En la espacio de nueva aplicacion ingresar:
- **Nombre de la aplicacion**: AplicacionDe[Inicial nombre][Inicial apellidos]XX 
- **URL**: Repite el nombre de aplicacion
- **Plantilla de aplicación**: Aplicacion personalizada 
- **Plan de precios**: Gratuito
<p align="center"><img src="./images/iotcentral15.PNG" \></p>

Dar click en **Crear**

<p align="center"><img src="./images/iotcentral16.PNG" width ="700"\></p>

Nos abrirá una nueva ventana donde muestra las características de nuestra aplicación 

<p align="center"><img src="./images/iotcentral17.PNG" width ="1200"\></p>

### Crear plantilla de dispositivos

Para crear una plantilla, en el panel lateral seleccionamos **Plantilla de dispositivo** 
<p align="center"><img src="./images/iotcentral18.png" width ="1200"\></p>

En las opciones seleccionamos **Dispositivos IoT** y luego click en  **Siguiente:Personalizar** 
<p align="center"><img src="./images/iotcentral19.png" width ="1200"\></p>

En **Nombre de la plantilla de dispositivo** escribir *HoL[Inicial Nombre y Apellido]Device[Numero de dispositivo]* Luego dar click en **Siguiente revisión**
<p align="center"><img src="./images/iotcentral20.png" width ="1200"\></p>

Finalmente verificar la información básica y dar click en **Crear**
<p align="center"><img src="./images/iotcentral21.png" width ="1200"\></p>

### Crear un Modelo y agregar funcionalidad
Para crear un modelo tenemos dos opciones, para este laboratorio seleccionaremos **Modelo personzalido**
<p align="center"><img src="./images/iotcentral22.png" width ="1200"\></p>

En la nuevas opciones que aparece debajo de Modelo seleccionamos en el nombre de nuestro dipositivo, en el caso de la imagen inferior **HoLSODevice01**
<p align="center"><img src="./images/iotcentral23.png" width ="1200"\></p>

Para agregar una nueva funcionalidad hacer click en cualquiera de las dos opciones de **+ Agregar funcionalidad**
<p align="center"><img src="./images/iotcentral24.png" width ="1200"\></p>

A continuación en casilleros agregaremos una funcionalidad de **telemetría** con los siguientes datos:
#### Ultrasonido
- **Nombre para mostrar**: Ultrasonido
- **Nombre**: Ultrasonido
- **Tipo de funcionalidad**: Telemetry
- **Tipo semántico**: Distance
<p align="center"><img src="./images/iotcentral25.png" width ="1200"\></p>

Repetir el paso de agregar más funcionalidades para los siguientes:
#### Temperatura
- **Nombre para mostrar**: Temperatura
- **Nombre**: Temperatura
- **Tipo de funcionalidad**: Telemetry
- **Tipo semántico**: Temperatura

#### Humedad
- **Nombre para mostrar**: Humedad
- **Nombre**: Humedad
- **Tipo de funcionalidad**: Telemetry
- **Tipo semántico**: Humidity

#### Servo
- **Nombre para mostrar**: Servo
- **Nombre**: Servo
- **Tipo de funcionalidad**: Telemetry
- **Tipo semántico**: Angle

#### Ldr
- **Nombre para mostrar**: Ldr
- **Nombre**: Ldr
- **Tipo de funcionalidad**: Telemetry
- **Tipo semántico**: Ninguno

#### Potenciometro
- **Nombre para mostrar**: Potenciometro
- **Nombre**: Potenciometro
- **Tipo de funcionalidad**: Telemetry
- **Tipo semántico**: Ninguno
<p align="center"><img src="./images/iotcentral26.png" width ="1200"\></p>

Para agregar un **comando** configuramos de la siguiente manera:
#### Distancia a Persona
- **Nombre para mostrar**: Distancia a Persona
- **Nombre**: DistanciaAPersona
- **Tipo de funcionalidad**: Command

Para este último presionamos en expandir las opciónes de comando (Simbolo de flecha hacia abajo al costado de X)
<p align="center"><img src="./images/iotcentral27.png" width ="1200"\></p>

Dentro de las opciones expandidas de comando solo configuraremos lo siguiente:
- **Solicitud**: Activado
- **Nompre para mostrar**: Distancia
- **Nombre**: Distancia
- **Esquema**: Double
- **Descripción**: Indique las distancia máxima a detectar
<p align="center"><img src="./images/iotcentral27_a.png" width ="1200"\></p>

Por último agregamos una **propiedad**:
#### Alerta de Deteccion
- **Nombre para mostrar**: Alerta de Deteccion
- **Nombre**: AlertaDeDeteccion
- **Tipo de funcionalidad**: Property
- **Tipo semántico**: Ninguno


<p align="center"><img src="./images/iotcentral28.png" width ="1200"\></p>

Una vez terminado de agregar las funcionalidad, damos click en **Guardar**
<p align="center"><img src="./images/iotcentral29.png" width ="1200"\></p>

### Configuracion de vistas

#### 5.1. Vista de último valor conocido (LKV)
Dentro de las opciones de modelo ahora seleccionamos **Vistas**
<p align="center"><img src="./images/iotcentral30.png" width ="1200"\></p>

Existen 3 tipos de vistas a crear, en este caso seleccionamos **Visualización de dispositivo**
<p align="center"><img src="./images/iotcentral31.PNG" width ="1200"\></p>


En el nuevo panel escogemos **Comenzar por un objeto visual**
<p align="center"><img src="./images/iotcentral32.PNG" width ="1200"\></p>

Dentro de las opciones de objetos visuales seleccionamos y arrastramos al espacio en blanco de la derecha  **Último valor conocido (LKV)**
<p align="center"><img src="./images/iotcentral33.png" width ="1200"\></p>


Cerramos el panel presionando en la flecha hacia la izquierda **<**, luego en las opciones al costado de Título predeterminado seleccionamos el simbolo de engranaje o **configuración**
<p align="center"><img src="./images/iotcentral34.png" width ="1200"\></p>

##### LDR
En el panel de la derecha configuramos lo siguiente:
- **Título**: LDR
- **Telemetría**: Click en **+ funcionalidad** y luego seleccionar **Ldr**
- **Tamaño del texto**: 25
- **Decimales**: 2

Una vez agregado y confurado los valores damos click ne **Actualizar**
<p align="center"><img src="./images/iotcentral35.png" width ="1200"\></p>

En visualización con nombre LDR hacer click en la opción que tiene un Cuadro grande y dentro uno pequeño o **Tamaño disponible** y escogemos **1x1**
<p align="center"><img src="./images/iotcentral36.png" width ="800"\></p>

Repetir los pasos de arrastrar **Último valor conocido (LKV)** y luego **Configurar** con las siguientes opciones:

##### Servo
- **Título**: Servo
- **Telemetría**: Click en **+ funcionalidad** y luego seleccionar **Servo**
- **Tamaño del texto**: 25
- **Decimales**: 2
- **Tamaño disponible**: 1x1

##### Potenciometro
- **Título**: Potenciometro
- **Telemetría**: Click en **+ funcionalidad** y luego seleccionar **Potenciometro**
- **Tamaño del texto**: 25
- **Decimales**: 2
- **Tamaño disponible**: 1x1

##### Ultrasonido
- **Título**: Ultrasonido
- **Telemetría**: Click en **+ funcionalidad** y luego seleccionar **Ultrasonido**
- **Tamaño del texto**: 25
- **Decimales**: 2
- **Tamaño disponible**: 1x1

<p align="center"><img src="./images/iotcentral37.png" width ="1200"\></p>

#### 5.2. Vista de Gráfico de líneas

Dentro de las opciones de objetos visuales seleccionamos y arrastramos al espacio en blanco de la derecha  **Gráfico de líneas**
<p align="center"><img src="./images/iotcentral38.png" width ="1200"\></p>

Presionamos en el símbolo de configurar y escogemos lo siguiente:
##### Temperatura
- **Título**: Temperatura
- **Mostrar rango**: Últimos 30 minutos
- **Intervalo**: 1 minuto
- **Telemetría**: Temperatura
 
<p align="center"><img src="./images/iotcentral39.png" width ="1200"\></p>

Luego dar click en **actualizar** de **Tamaño disponible**: 2x2
<p align="center"><img src="./images/iotcentral40.png" width ="400"\></p>

Repetir **Gráfico de líneas** para **Humedad** con las siguientes configuraciones:
##### Humedad
- **Título**: Humedad
- **Mostrar rango**: Últimos 30 minutos
- **Intervalo**: 1 minuto
- **Telemetría**: Humedad
- **Tamaño disponible**: 2x2
<p align="center"><img src="./images/iotcentral41.png" width ="1200"\></p>

Click en el panel de editar vista y cambiar **Nombre de la vista** a *Vista de dispositivos*, luego click en **Guardar** 
<p align="center"><img src="./images/iotcentral42.png" width ="1200"\></p>

### Publicar
Para publicar nuestra plantilla de dispositivo, dar click en **Publicar**
<p align="center"><img src="./images/iotcentral43.png" width ="1200"\></p>

Finalmente mostrará un resúmen de todos los cambios que se realizaron, dar click en **Publicar** para confirmar
<p align="center"><img src="./images/iotcentral45.png" width ="1200"\></p>

### Crear un dispositivo
Para crear un dispositivo en el panel principal de la derecha seleccionamos **Dispositivos** y después **Crear un dispositivo**
<p align="center"><img src="./images/iotcentral46.png" width ="1200"\></p>

Dentro de las opcionas de Crear un dispositivo modificamos:
- **Nombre del dispositivo**: HoL[Inicial nombre y apellido]Device[número de dispositivo]
- **Id. de dispositivo**: Dejamos el valor que nos asignan
- **Plantilla de dispositivo**: Seleccionamos el nombre de nuestra plantilla, en es caso *HoLSODevice01* 
- **¿Quiere simular este dispositivo?**: Dejar la opción en No
<p align="center"><img src="./images/iotcentral47.png" width ="800"\></p>

Una vez finalizado le aparecera en lista el dispositivo que a creado relacionado a la plantilla, dar click sobre el nombre del dispositivo
<p align="center"><img src="./images/iotcentral48.png" width ="800"\></p>

En la nuevas opciones de visualización click en **Conectar**
<p align="center"><img src="./images/iotcentral49.png" width ="800"\></p>

Copiar en un bloc de notas los siguientes datos:
- **Id. de dispositivo**
- **Clave principal**
<p align="center"><img src="./images/iotcentral50.png" width ="800"\></p>
.. Grupo3_Mensajer0 documentation master file, created by
   sphinx-quickstart on Thu Jun 11 17:57:33 2015.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

MensajerO - Grupo 3
============================================

Documentación del proyecto
============================================

Gestión del proyecto
--------------------------------------------

La gestión del proyecto fue mediante un equipo de pares.
Al comienzo del mismo se analizaron los requerimientos y se definio un backlog de tareas que había que realizar para completarlo.
Luego se discutio en el equipo un orden y una organización para esas tareas.
Durante el transcurso del proyecto, se plante el equipo de manera que todo el equipo pueda tomar tareas de cualquier parte del proyecto, por lo que la división de tareas era para asignar un encargado de cada tarea, pero cualquiera podría ayudar o tomar algun issue acerca de dicha funcionalidad.

División de tareas
--------------------------------------------

+ Documentación sobre instalación y librerias: Ramiro Doi
+ Principales funcionalidades del server: Mateo Bosco
+ Otras funcionalidades del server: Uriel Kusnesov
+ Testing y coverage: Matias Capristo
+ CMake: Ramiro Doi
+ Pantalla de contactos y chats abiertos: Uriel Kusnesov
+ Integracion del server con el cliente: Mateo Bosco
+ Pantalla LogIn: Matias Capristo
+ Pantalla de creacion de usuarios: Ramiro Doi
+ Pantalla de conversacion: Uriel Kusnesov
+ Pantalla de perfiles: Mateo Bosco
+ Investigacion de herramientas y testing: Matias Capristo
+ Ubicacion GPS y fotos: Uriel Kusnesov
+ Resolucion de issues y tareas menores: Todo el equipo

Cronograma
--------------------------------------------

El cronograma del proyecto se baso en la división en 3 iteraciones.
El tiempo de estas fue pensado en relación a las entregas y checkpoints del trabajo.

**Primera iteración:**
	Esta incluye la realización de todas las funciones del servidor. 
	Cumplir con los requerimientos del server, realizar tests sobre los mismos.
	Realizar la documentación de instalación del server y sus dependencias.
	El contenido de esta iteración fue estimado para finalizarse el 30/04/2015.

**Segunda iteración:**
	Esta incluye todas las funcionalidades del cliente, a excepcion del check in, el manejo de imagenes (foto de perfil).
	Integración de estas funcionalidades con las ya realizadas del server.
	Correción de issues que surgen tanto del servidor como del cliente.
	El contenido de esta iteración fue estimado para finalizarse el 04/06/2015.

**Tercera iteración:**
	Esta incluye la inclusión de los features de check in y manejo de fotos de perfil.
	Corrección de issues que surgen tanto del servidor como del cliente.
	Realización de la documentación restante y en un formato unificado con el resto de la documentación.
	Preparación de la presentación.
	El contenido de esta iteración fue estimado para finalizarse el 25/06/2015

Control de versiones y workflow
--------------------------------------------

El control de versiones del proyecto fue mediante Github.
Se utilizaron dos repositorios distintos, uno para el proyecto de servidor y otro para el proyecto del cliente.

+ `Servidor <http://github.com/mcapristo/taller_de_prog_2>`_
+ `Cliente <http://github.com/mcapristo/taller_de_prog_2_android>`_

Sistema ticketing
--------------------------------------------

Para el sistema de ticketing, los issues fueron cargados en el mismo github, donde eran asignados a un responsable para su resolución.

Documentacion técnica
============================================

Doc ambiente de desarrollo
--------------------------------------------

Doc de librerias y compilación
--------------------------------------------

Doc de arquitectura/diseño
--------------------------------------------

Doc de clases
--------------------------------------------

Doc de código
--------------------------------------------

Doc de REST API
--------------------------------------------

Doc de pruebas
--------------------------------------------

Manual de usuario del cliente
============================================

Intro general de la app
--------------------------------------------

La aplicación MensajerO es una aplicacón de mensajería instantanea, que nos permite mantener conversaciones con distintos usuarios registrados, mantener información acerca de nuestro perfil, y compartir nuestra ubicación al resto de los contactos.
Podremos diferenciar entre aquellos contactos con los que ya hemos mantenido conversaciones y aquellos con los que no lo hemos hecho.

Features incluidos
--------------------------------------------

Entre los features incluidos podemos encontrar:

+ Eleccion de red
+ Registro de usuarios
+ Servicio de LogIn, con validacion de datos
+ Vista de contactos
	- Tab de contactos con chat abierto
	- Tab de todos los contactos registrados
+ Edicion de perfil
	- Foto de perfil
		+ Elegir foto de la galería del dispositivo
		+ Tomar foto en el momento
	- Nombre para mostrar en lista de contactos
	- Cambio de constraseña
	- Estado
+ Compartir ubicación actual (Tomada por GPS)
+ Visualización del perfil de otros contactos

Instalación y configuracón
--------------------------------------------

Como usarla paso a paso
--------------------------------------------

**Eleccion de red:**

Como primer paso luego de instalar la aplicación y abrirla desde el dispositivo, se mostrara la pantalla de LogIn. Aquí para configurar la red hay que acceder al menu, opcion Configuración IP y se desplegara la pantalla de eleccion de IP de red para poner la IP del servidor en la red en la que se encuentra conectado (Esta puede encontrarse abriendo la consola de comandos y poniendo el comando "ifconfig -a").
Una vez ingresada la IP del servidor en el campo de texto del centro de la pantalla, se procede a presionar el boton "Guardar" y si la carga de la direccion IP es correcta una alerta le indicara que esta se guardo con éxito, por lo que al cerrar la alerta puede presionar el boton "Volver" que lo devolvera a la pantalla de LogIn.

**Registro de usuario:**

Para registrar su usuario, una vez configurada la red, debe presionar el boton "Registrarse" de la pantalla de LogIn y este lo llevara a la pantalla de registro de usuario.
Una vez en ella tendra para completar sus datos, en primer lugar "UserName", en segundo lugar "FullName" y por ultimo "Password", igualmente cada campo tendra un texto provisorio indicando que data debe completar en el mismo.
Cuando termine de completar los datos, puede proceder a presionar el boton "Crear" para que se envíen los datos al servidor, o si no deseaba registrar un nuevo usuario puede presionar "Cancelar" para volver a la pagina anterior.
Al crear un usuario si este se registro correctamente se abrira la pantalla de bienvenida y tocando el boton "Volver" podrá regresar a la pantalla de LogIn.

**LogIn:**

Para iniciar sesión debe tener un usuario registrado. En ese caso en la pantalla de LogIn debe ingresar su username y password en los campos de texto que así lo indican en el centro de la pantalla y luego presionar el boton "Iniciar Sesión".
De haber algun problema en el inicio de sesión una alerta se lo indicara, de lo contrario se iniciara sesión y sera redirigido a la pantalla principal con las listas de contactos para comenzar conversaciones.

**Lista de contactos:**

Al iniciar sesión se abrira una pantalla con dos pestañas.
La primera tendra una lista de contactos con los que alguna vez se ha tenído alguna conversación.
La segunda tendra una lista de todos los contactos registrados en la aplicación.
Para desplazarse entre estas pestañas, puede hacerlo arrastrando la pantalla hacia los lados con el dedo.
Cada contacto va a aparecer listado con su nombre completo y su foto de perfil.

**Conversación:**

Para abrir una conversación es suficiente con tocar con el dedo el registro de un contacto en cualquiera de las listas anteriormente mencionadas.
Una vez hecho esto se abrira la conversación con todos los mensajes previós entre estos contactos (si es que los hubiere) y se pueden ver todos los mensajes si no entran en la pantalla se puede desplazar con el dedo hacia arriba o abajo para visualizar los mismos.
Los mensajes enviados por uno mismo se veran en el lado derecho de la pantalla mientras que los mensajes recibidos se veran del lado izquierdo.
En la parte baja de la pantalla se podra ver un cuadro de texto de color rosado en el que podemos escribir un texto para envíar a nuestro contacto. Para hacer esto, luego de escribir el texto se debe presionar el boton "Enviar" y este se enviara y aparecer como fue dicho, del lado derecho.

**Difusion:**

Para enviar un mensaje a todos los contactos que se encuentren conectados, hay que entrar al menu de la pantalla de contactos, y elegir la opción "Difusion" y se abrira una ventan de conversación con el receptor difusion.
Una vez enviado un mensaje a este se le enviara a todos los contactos conectados.
Vale aclarar que el contacto difusion no guarda el historial de mensajes

**Ver perfil del contacto:**

Para ver el perfil del contacto con el que estamos conversando, se debe abrir desde las listas de contactos el chat con el mismo.
Una vez abierto ingresar al menu y presionar la opción "Ver perfil".
Esto nos redireccionara a la pantalla del perfil del contacto seleccionado.
En esta se podra visualizar la foto de perfil del mismo, junto con su nombre de contacto (el mostrado en la lista) y su nombre de usuario.
Para volver a la conversación se debe presionar la tecla de atras del dispositivo.

**Editar mi perfil:**

Para editar mi propio perfil se debe ingresar al menu desde la lista de contactos y presionar la opción "Editar perfil".
Esta abrira la pantalla con mis datos de perfil, foto, ubicación, nombre, contraseña y estado.
Los textos de nombre y password podran ser editados asi como la foto de perfil.
Para modificar la foto de perfil hay que presionar el boton "Cambiar imagen" y este nos abrira un cuadro con dos opciones. La opcion "Existente" nos llevara a la galería del dispositivo para elegir una foto, la otra opcion "Tomar foto" nos llevara a la camara del dispositivo para tomar una foto en el momento que quede como foto de perfil.
Una vez realizado cualquiera de las dos opciones, aparecera la foto en la pagina del perfil propio.
Luego de que se modificaron los datos de la manera deseada se procede a presionar el boton "Guardar" para guardar los datos y una alerta nos indicara si se guardaron de manera exitosa.
Si no se desean guardar los cambios se debe presionar el boton "Cancelar" y este nos devolvera a la lista de contactos.

**Compartir mi ubicación:**

Para compartir mi ubicación debo entrar a la edición de mi perfil de la manera anteriormente indicada.
En este perfil se debera presionar el boton "Compartir ubicación" y en ese momento el dispositivo buscara mediante GPS la ubicación actual de la manera mas exacta posible (un simbolo de que la aplicación esta buscando la ubicación aparecera en la pantalla para avisar al usuario que se encuentra en proceso su solicitud) y al encontrarla la mostrara en el cuadro de "Última ubicación compartida" y se guardara la misma (una alerta nos indicara que la ubicación se compartio correctamente). Esta ubicación aparecera al resto de los contactos junto a mi nombre completo en sus listas de contactos.
Si se desea no compartir mas la ubicación al resto de los contactos se debe presionar el boton "Dejar de compartir" y el cuadro "Última ubicación compartida" quedará vacío, y la alerta nos indicara que el cambio fue guardado.
Vale aclarar que al presionar compartir o dejar de compartir ubicación el cambio es automaticamente guardado en el perfil del usuario sin necesidad de presionar el boton guardar de la edición de perfil.

Screenshots
--------------------------------------------

Known issues
--------------------------------------------

+ Cuando cambio la foto de perfil por una existente en la galeria, en ciertas ocasiones esta sale rotada esta foto aparece rotada.

Troubleshooting
--------------------------------------------

Documentación de administrador
============================================

Get started
--------------------------------------------

Instalacón y configuración
--------------------------------------------

Forma de uso
--------------------------------------------

Mantenimiento
--------------------------------------------

Known issues
--------------------------------------------

Troubleshooting
--------------------------------------------

.. toctree::
   :maxdepth: 2


# taller_de_prog_2
Tp de 7552 - Taller de programación 2 - 1er cuat 2015 - Proyecto: MensajerO

Instalacón y configuración
--------------------------------------------

**Instalamos CMake**

1. Ejecutar el siguiente comando a partir de una nueva terminal
	a. sudo su
	b. apt-get install cmake


**Instalación de la librería RocksDB**

1. Descargamos los fuentes del RocksDB desde el siguiente link
	a. https://github.com/facebook/rocksdb/archive/master.zip

2. Descomprimir el archivo "rocksdb-master.zip"

3. Ingresar a la carpeta "rocksdb-master" a partir de una nueva terminal

4. Ejecutar el siguiente comando para tener permisos de administrador 
	a. sudo su

5. Ejecutar el siguiente comando 
	a. make all
	b. make install

6. Ejecutar los siguientes comandos
	a. apt-get install libgflags-dev
	b. apt-get install libsnappy-dev
	c. apt-get install zlib1g-dev
	d. apt-get install libbz2-dev


**Instalación de la librería jsoncpp** 

1. Descargamos los fuentes de jsoncpp desde el siguiente link
	a. https://github.com/open-source-parsers/jsoncpp/archive/master.zip

2. Descomprimir el archivo "jsoncpp-master"

3. Ingresar a la carpeta "jsoncpp-master" a partir de una nueva terminal

4. Ejecutar el siguiente comando a partir de una nueva terminal
	a. sudo su

5. Ejecutar los siguientes comandos
	a. mkdir -p build/debug
	b. cd build/debug
	c. cmake -DCMAKE_BUILD_TYPE=debug -DJSONCPP_LIB_BUILD_STATIC=ON -DJSONCPP_LIB_BUILD_SHARED=OFF -G "Unix Makefiles" ../..
	d. make

6. Ingresar a la carpeta "/src/lib_json"

7. Ejecutar el siguiente comando 
	a. cp -a libjsoncpp.a /usr/local/lib


**Instalación de la librería gTest** 

1. Descargamos los fuentes de gTest desde el siguiente link
	a. https://googletest.googlecode.com/files/gtest-1.7.0.zip

2. Descomprimir el archivo "gtest-1.7.0.zip"

3. Ingresar a la carpeta "gtest-1.7.0" a partir de una nueva terminal

4. Ejecutar el siguiente comando para tener permisos de administrador 
	a. sudo su

5. Ejecutar los siguientes comandos
	a. ./configure
	b. make

6. Ejecutar los siguientes comandos
	a. cp -a include/gtest /usr/include
	b. cp -a lib/.libs/* /usr/lib/


Forma de uso
--------------------------------------------

1. Abrimos una nueva terminal

2. Ingresamos a la carpeta "src" donde tengamos los fuentes del Server

3. Ejecutamos el siguiente comando
	a. cmake CMakeLists.txt

4. Ejecutamos el make
	a. make

5. Ejecutamos el server
	a. ./server
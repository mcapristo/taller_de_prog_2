-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
Pasos a seguir para la correcta ejecución del Server.
-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
1. 
Abrir una nueva consola y crear un directorio con el nombre "server"
Comando: mkdir server

2.
Copiar el archivo server.tar.gz a la carpeta copiada recientemente y descomprimirlo.

3. 
Ingresar a la carpeta "server" creada anteriormente
Comando: cd server

4.
Ingresar a la carpeta "src"
Comando: cd src

5. 
Ejecutar el siguiente comando
Comando: cmake CMakeLists.txt

6. 
Ejecutar el siguiente comando
Comando: make

7. 
Ejecutar el server
./server

-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
Intalación de las librerías externas necesarias para la correcta instalación y ejecución del Server.
-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
--------
rocksdb.
--------
1. 
Descomprimir el archivo "rocksdb-master.zip"

2.
Ingresar a la carpeta "rocksdb-master"
Comando: cd rocksdb-master

3. 
Ejecutar el siguiente comando
Comando: make all

4. 
Ejecutar el siguiente comando
Comando: install

5.
Ejecutar los siguientes comandos
Comandos: sudo apt-get install libgflags-dev
		  sudo apt-get install libsnappy-dev
		  sudo apt-get install zlib1g-dev
		  sudo apt-get install libbz2-dev

--------
jsoncpp.
--------
1.
Descomprimir el archivo "jsoncpp-master"

2.
Ingresar a la carpeta "jsoncpp-master"
Comando: cd jsoncpp-master

3.
Ejecutar los siguientes comandos
Comandos: mkdir -p build/debug
    	  cd build/debug
    	  cmake -DCMAKE_BUILD_TYPE=debug -DJSONCPP_LIB_BUILD_STATIC=ON -DJSONCPP_LIB_BUILD_SHARED=OFF -G "Unix Makefiles" ../..
    	  make

4.
Ingresar a la carpeta "/src/lib_json"
Comando: cd src/lib_json

5.
Ejecutar el siguiente comando para tener permisos de administrador
Comando: sudo su

6.
Ejecutar el siguiente comando
Comando: cp -a libjsoncpp.a /usr/local/lib

------
gTest.
------
1.
Descomprimir el archivo "gtest-1.7.0.zip"

2.
Ingresar a la carpeta "gtest-1.7.0"
Comando: cd gtest-1.7.0

3.
Ejecutar los siguientes comandos
Comandos: ./configure
		  make

4.
Ejecutar el siguiente comando para tener permisos de administrador
Comando: sudo su

5.
Ejecutar los siguientes comandos
Comandos: cp -a include/gtest /usr/include
 		  cp -a lib/.libs/* /usr/lib/
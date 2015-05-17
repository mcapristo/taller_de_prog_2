CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Nombre del Proyecto de CM.
PROJECT(CM_server)

# Se activan los flags de compilacion.
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lsnappy")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lgflags")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lz")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lbz2")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Se activa la busqueda de librerias.
INCLUDE(FindPkgConfig)

# Se agregan todas las clases al SOURCE.
SET(SOURCES Loggero.cpp ServiceLayer.h Constants.h Loggero.h ServiceLayer_Test.cpp Conversation.cpp Message.cpp SIGINT_Handler.h Conversation.h Message.h SignalHandler.cpp Conversation_Test.cpp Message_Test.cpp SignalHandler.h Database.cpp mongoose.c testRocks.cpp Database.h mongoose.h User.cpp Database_Test.cpp Proceso.cpp UserFactory.cpp EventHandler.h Proceso.h UserFactory.h holaMundoServer.cpp Server.cpp UserFactory_Test.cpp json/json.h json/json-forwards.h Server.h User.h jsoncpp.cpp ServiceLayer.cpp User_Test.cpp)

# Se crea el make a partir del SOURCE definido.
ADD_EXECUTABLE(server ${SOURCES})

# Se linkean todas las librerias externas necesarias.
TARGET_LINK_LIBRARIES(server /usr/local/lib/librocksdb.a)
TARGET_LINK_LIBRARIES(server /usr/local/lib/libjsoncpp.a)
TARGET_LINK_LIBRARIES(server /usr/lib/libgtest.a)
TARGET_LINK_LIBRARIES(server ${CMAKE_THREAD_LIBS_INIT})
TARGET_LINK_LIBRARIES(server ${ZLIB_LIBRARIES})
TARGET_LINK_LIBRARIES(server ${BZIP2_LIBRARIES})

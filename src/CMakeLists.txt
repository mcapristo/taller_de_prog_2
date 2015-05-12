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
SET(SOURCES jsoncpp.cpp ServiceLayer.cpp Constants.h Loggero.cpp ServiceLayer.h Conversation.cpp Loggero.h ServiceLayer_Test.cpp Conversation.h Message.cpp testRocks.cpp Conversation_Test.cpp Message.h User.cpp Database.cpp Message_Test.cpp UserFactory.cpp Database.h mongoose.c UserFactory.h Database_Test.cpp mongoose.h UserFactory_Test.cpp holaMundoServer.cpp Server.cpp User.h Server.h User_Test.cpp json/json.h json/json-forwards.h)

# Se crea el make a partir del SOURCE definido.
ADD_EXECUTABLE(server ${SOURCES})

# Se linkean todas las librerias externas necesarias.
TARGET_LINK_LIBRARIES(server /usr/local/lib/librocksdb.a)
TARGET_LINK_LIBRARIES(server /usr/local/lib/libjsoncpp.a)
TARGET_LINK_LIBRARIES(server /usr/local/lib/libgtest.a)
TARGET_LINK_LIBRARIES(server ${CMAKE_THREAD_LIBS_INIT})
TARGET_LINK_LIBRARIES(server ${ZLIB_LIBRARIES})
TARGET_LINK_LIBRARIES(server ${BZIP2_LIBRARIES})

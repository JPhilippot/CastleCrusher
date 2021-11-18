QT       += core gui widgets

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#CONFIG += c++11

TARGET = CrusherEngine
TEMPLATE = app

#SOURCES = ./src/*.cpp
#HEADERS = ./src/*.h

SOURCES += ./src/main.cpp \
    ./src/vec3.cpp \
    ./src/object.cpp \
    ./src/entity.cpp \
    ./src/mesh.cpp \
    ./src/mainwidget.cpp \
    ./src/geometryengine.cpp\
     ./src/transformation.cpp

HEADERS += ./src/vec3.h \
    ./src/entity.h \
    ./src/mainwidget.h \
    ./src/geometryengine.h \
    ./src/object.h\
    ./src/mesh.h \
     ./src/transformation.h

RESOURCES += \
    shaders.qrc \
    textures.qrc


# install
target.path = $$[YOUR_PATH]
INSTALLS += target


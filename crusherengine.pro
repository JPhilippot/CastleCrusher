QT       += core gui widgets

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#CONFIG += c++11

TARGET = CrusherEngine
TEMPLATE = app

#SOURCES = ./src/*.cpp
#HEADERS = ./src/*.h

SOURCES += ./src/main.cpp \
    ./src/object.cpp \
    ./src/entity.cpp \
    ./src/mainwidget.cpp \
    ./src/geometryengine.cpp \
    ./src/transformation.cpp\
    ./src/model.cpp\
    ./src/cube.cpp\
    ./src/plane.cpp\
    ./src/sphere.cpp \
    src/collider.cpp \
    src/forces.cpp \
    src/physicsengine.cpp

MODELS +=
HEADERS +=./src/entity.h \
    ./src/mainwidget.h \
    ./src/geometryengine.h \
    ./src/object.h\
     ./src/transformation.h\
     ./src/vec.h\
     ./src/mat.h\
     ./src/model.h\
     ./src/cube.h\
     ./src/plane.h\
     ./src/sphere.h \
    src/collider.h \
    src/forces.h \
    src/physicsengine.h


RESOURCES += \
    shaders.qrc \
    textures.qrc


# install
target.path = $$[YOUR_PATH]
INSTALLS += target


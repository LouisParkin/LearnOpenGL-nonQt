TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++0x

INCLUDEPATH += $$PWD/../../Source \
               $$PWD/../../Include \
               $$PWD/../../Include/assimp \
               $$PWD/../../Include/ATB \
               $$PWD/../../Include/ImageMagick-6

INCLUDEPATH += $$PWD/../../Lib

DEPENDPATH += $$PWD/../../Lib

SOURCES += $$PWD/../../Source/main.cpp\
           $$PWD/../../Common/ogldev_util.cpp \
           $$PWD/../../Common/math_3d.cpp \
           $$PWD/../../Common/pipeline.cpp \
           $$PWD/../../Common/camera.cpp \
           $$PWD/../../Common/ogldev_atb.cpp \
           $$PWD/../../Common/ogldev_backend.cpp \
           $$PWD/../../Common/glut_backend.cpp \
           $$PWD/../../Common/ogldev_glfw_backend.cpp \
           $$PWD/../../Common/ogldev_texture.cpp \
           $$PWD/../../Source/Tutorials.cpp \
           $$PWD/../../Source/Tutorial.cpp

HEADERS  += \
    ../../Source/Tutorials.h \
    ../../Source/Tutorial.h

LIBS += -L$$PWD/../../Lib

LIBS += -lGL -lglut -lGLEW -lAntTweakBar -lglfw -lcurses -lMagickCore -lMagickWand -lMagick++

include(deployment.pri)
qtcAddDeployment()


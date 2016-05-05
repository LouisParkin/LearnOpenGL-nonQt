TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++0x

TUT_VERSION = 23
TUT_DEFINE  = __TUT_VERSION=$$TUT_VERSION
DEFINES += $$TUT_DEFINE

message(TUT_VERSION = $$TUT_VERSION)
message(TUT_DEFINE  = $$TUT_DEFINE )

INCLUDEPATH += \
           $$PWD/../../Source \
           $$PWD/../../Include \
           $$PWD/../../Include/assimp \
           $$PWD/../../Include/ATB \
           $$PWD/../../Common/FreetypeGL \
           $$PWD/../../Include/ImageMagick-6

INCLUDEPATH += \
           $$PWD/../../Lib

DEPENDPATH += \
           $$PWD/../../Lib

SOURCES += \
           $$PWD/../../Common/FreetypeGL/font-manager.c \
           $$PWD/../../Common/FreetypeGL/texture-atlas.c \
           $$PWD/../../Common/FreetypeGL/vector.c \
           $$PWD/../../Common/FreetypeGL/texture-font.c \
           $$PWD/../../Common/FreetypeGL/texture-glyph.c \
           $$PWD/../../Common/FreetypeGL/vertex-buffer.c \
           $$PWD/../../Source/main.cpp\
           $$PWD/../../Common/ogldev_util.cpp \
           $$PWD/../../Common/math_3d.cpp \
           $$PWD/../../Common/pipeline.cpp \
           $$PWD/../../Common/camera.cpp \
           $$PWD/../../Common/ogldev_atb.cpp \
           $$PWD/../../Common/ogldev_backend.cpp \
           $$PWD/../../Common/glut_backend.cpp \
           $$PWD/../../Common/ogldev_glfw_backend.cpp \
           $$PWD/../../Common/ogldev_texture.cpp \
           $$PWD/../../Common/ogldev_app.cpp \
           $$PWD/../../Common/ogldev_basic_lighting.cpp \
           $$PWD/../../Common/technique.cpp \
           $$PWD/../../Common/FreetypeGL/freetypeGL.cpp \
           $$PWD/../../Common/FreetypeGL/font_shader.cpp \
           $$PWD/../../Source/Tutorials.cpp \
           $$PWD/../../Source/Tutorial.cpp



message(Building for Tutorials 4-14 and $$TUT_VERSION)
FILE_EXT = ".cpp"
greaterThan(TUT_VERSION,16) {

lessThan(TUT_VERSION,22){

message(adding version specific source file: Source/lighting_technique$$FILE_EXT)
  SOURCES += $$PWD/../../Source/lighting_technique.cpp

}

greaterThan(TUT_VERSION,21){

message(adding version specific source file: Source/mesh$$FILE_EXT)
  SOURCES += $$PWD/../../Source/mesh.cpp

greaterThan(TUT_VERSION,22){
message(adding version specific source file: Source/Tutorial$$TUT_VERSION/shadow_map_technique$$FILE_EXT)
message(adding version specific source file: Common/ogldev_shadow_map_fbo$$FILE_EXT)
SOURCES += $$PWD/../../Source/Tutorial$$TUT_VERSION/shadow_map_technique.cpp \
           $$PWD/../../Common/ogldev_shadow_map_fbo.cpp
}

}

message(adding version specific source file: Tutorial$$TUT_VERSION/Tutorial$$TUT_VERSION$$FILE_EXT)
    SOURCES += $$PWD/../../Source/Tutorial$$TUT_VERSION/Tutorial$$TUT_VERSION$$FILE_EXT
}

HEADERS  += \
           $$PWD/../../Source/Tutorials.h \
           $$PWD/../../Source/Tutorial.h \
           $$PWD/../../Source/lighting_technique.h \
           $$PWD/../../Common/ogldev_app.cpp

LIBS +=  -L$$PWD/../../Lib

LIBS += -lGL -lglut -lGLEW -lAntTweakBar -lglfw -lcurses -lMagickCore -lMagickWand -lMagick++ -lfontconfig -lfreetype -lassimp

include(deployment.pri)
qtcAddDeployment()


TEMPLATE = app
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -Ofast

SOURCES += main.cpp \
    rubik.cpp \
    scene.cpp \
    cube.cpp \
    sticker.cpp \
    vao.cpp \
    texture.cpp \
    minicube.cpp \
    object.cpp \
    light.cpp \
	object2d.cpp

HEADERS += \
    rubik.h \
    scene.h \
    cube.h \
    sticker.h \
	vao.h \
    texture.h \
    minicube.h \
    object.h \
    light.h \
    object2d.h

DISTFILES += \
    README.md


INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

LIBS += -L$$PWD/lib/ -lSOIL -lGL -lGLU -lGLEW -lglut

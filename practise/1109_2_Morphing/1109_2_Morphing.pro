QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS += -lopengl32

SOURCES += \
    BallModel.cpp \
    Camera.cpp \
    ConeModel.cpp \
    CubeModel.cpp \
    Light.cpp \
    LightModel.cpp \
    Model.cpp \
    MyOpenGLWidget04.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    BallModel.h \
    Camera.h \
    ConeModel.h \
    CubeModel.h \
    Light.h \
    LightModel.h \
    Model.h \
    MyOpenGLWidget04.h \
    foxmath.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

#windows
win32{
    contains(QT_ARCH, i386){
        #32bit
        LIBS += -L$$PWD/freeimage/x32/ -lFreeImage
        INCLUDEPATH += $$PWD/freeimage/x32
        DEPENDPATH += $$PWD/freeimage/x32
    }
    contains(QT_ARCH, x86_64){
        #64bit
        LIBS += -L$$PWD/freeimage/x64/ -lFreeImage
        INCLUDEPATH += $$PWD/freeimage/x64
        DEPENDPATH += $$PWD/freeimage/x64
    }
}


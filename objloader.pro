QT       += core gui
LIBS += -lopengl32 -lglu32
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++17
DEFINES += QT_DEPRECATED_WARNINGS
SOURCES += \
    main.cpp \
    objloader.cpp \
    widget.cpp

HEADERS += \
    objloader.h \
    widget.h
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

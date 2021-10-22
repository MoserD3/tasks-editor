TEMPLATE= app
LANGUAGE = C++
QT += core gui
CONFIG = qt uic warn_on thread resources debug
win32:CONFIG += windows embed_manifest_exe

UI_DIR = tmp/ui
MOC_DIR = tmp/moc
RCC_DIR = tmp/rcc

debug {
    DESTDIR = ../../debug
    OBJECTS_DIR = tmp/debug
}
release {
    DESTDIR = ../../release
    OBJECTS_DIR = tmp/release
}

QMAKE_LIBDIR = $$DESTDIR
unix:QMAKE_LFLAGS += -Wl,-rpath-link,$$DESTDIR

INCLUDEPATH += ../..

LIBS += \
    -llibdb-core \
    -llibdb-comm \
    -lconfig \
    -ltrnames

include(tasks-editor.pri)

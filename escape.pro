TEMPLATE = app
TARGET =
DEPENDPATH += .
INCLUDEPATH += .

QT += opengl

QMAKE_CXXFLAGS += -std=c++11

# Input
HEADERS += src/*.h
SOURCES += src/*.cc

# Output
OBJECTS_DIR = build

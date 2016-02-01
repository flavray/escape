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
MOC_DIR = moc
OBJECTS_DIR = build

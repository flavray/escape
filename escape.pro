TEMPLATE = app
TARGET =
DEPENDPATH += .

INCLUDEPATH += . /usr/include/freetype2

QT += opengl

QMAKE_CXXFLAGS += -std=c++11

LIBS += -lfreetype

# Input
HEADERS += game.h laser.h obstacle.h obstacle_manager.h player.h scene.h
SOURCES += game.cc laser.cc main.cc obstacle.cc obstacle_manager.cc player.cc scene.cc

TEMPLATE = app
TARGET =
DEPENDPATH += .
INCLUDEPATH += .

QT += opengl

QMAKE_CXXFLAGS += -std=c++11

# Input
HEADERS += game.h image.h laser.h obstacle.h obstacle_manager.h player.h scene.h
SOURCES += game.cc image.cc laser.cc main.cc obstacle.cc obstacle_manager.cc player.cc scene.cc

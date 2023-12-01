TARGET = town_simulator
CONFIG += c++11

HEADERS += src/Game.h src/view/GraphicsView.h src/application/Application.cpp
SOURCES += main.cpp src/Game.cpp src/view/GraphicsView.cpp src/application/Application.cpp
QT += widgets
    
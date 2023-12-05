TARGET = town_simulator
CONFIG += c++11

HEADERS += src/Game.h src/view/GraphicsView.h src/application/Application.cpp src/image/GraphicsPixmapItem.h src/buildings/building.h src/buildings/field.h src/buildings/shop.h src/buildings/house.h src/struct.h src/info_zone/info_zone.h src/button/button.h src/settings_building/settings.h
SOURCES += main.cpp src/Game.cpp src/view/GraphicsView.cpp src/application/Application.cpp src/image/GraphicsPixmapItem.cpp src/buildings/building.cpp src/buildings/field.cpp src/buildings/shop.cpp src/buildings/house.cpp src/info_zone/info_zone.cpp src/button/button.cpp src/settings_building/settings.cpp
QT += widgets
    
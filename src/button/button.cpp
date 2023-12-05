#include "button.h"

PushButton::PushButton(QString txt, Xy pos, QColor color, Xy size) : QPushButton(txt){
    scene = scene;
    proxy = new QGraphicsProxyWidget();
    proxy->setWidget(this);
    proxy->setPos(pos.x, pos.y);
    //setGeometry(QRect(QPoint(pos.x, pos.y), QSize(size.x, size.y)));
    QPalette palette;
    palette.setColor(QPalette::Button, color);
    this->setPalette(palette);
}

PushButton::~PushButton(){
    delete proxy;
}

void PushButton::remove(){
    scene->removeItem(proxy);
}

void PushButton::add(){
    scene->addItem(proxy);
}
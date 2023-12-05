#ifndef safe_button
#define safe_button

#include <QPushButton>
#include <iostream>
#include <QGraphicsScene>
#include <QString>
#include <QGraphicsProxyWidget>
#include <QRect>
#include <QSize>
#include <QPoint>
#include <QPalette>
#include <QColor>
#include "../struct.h"

class PushButton: public QPushButton{

public:
    PushButton(QString txt, Xy pos, QColor color, Xy size);
    ~PushButton();
    void add();
    void remove();

private:
    QGraphicsScene *scene;
    QGraphicsProxyWidget *proxy;
};

#endif
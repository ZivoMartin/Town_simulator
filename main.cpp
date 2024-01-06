#include <QApplication>
#include "src/Game.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    GraphicsView *view = new GraphicsView();
    Game game(&app, view);
    view->set_game(&game);
    view->showFullScreen();
    view->show();
    return app.exec();
}
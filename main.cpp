#include "src/application/Application.h"

int main(int argc, char *argv[])
{
    Application app(argc, argv);
    GraphicsView *view = new GraphicsView();
    Game *game = new Game(view);
    view->set_game(game);
    view->showFullScreen();
    view->show();
    app.set_game(game);
    return app.exec();
}
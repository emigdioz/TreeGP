#include "mainwindow.h"
#include <QApplication>

class taps{
public:
    taps();
    void jajaja(){};
};

taps::taps()
{

}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    //window.resize(640, 400);
    window.show();

    taps *t=new taps();
    //hola();
    //start_main(argc,argv);

    return app.exec();
}

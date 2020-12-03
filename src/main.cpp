#include "qk8055.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qk8055 w;
    w.show();

    return app.exec();
}


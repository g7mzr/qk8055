#include "qk8055.h"
#include <QApplication>
#include <QTranslator>
#include "gui_debug.h"

int main(int argc, char *argv[])
{
    
    QApplication app(argc, argv);
    
    
    // Load and configure QTranslator
    QTranslator translator;

    bool isTrlsFileLoaded = translator.load("qk8055", ":/translations");
    
    if(!isTrlsFileLoaded) {
        qCDebug(QK8055_GUI) << "Translation File Not Loaded";
    }
    else {
        qCDebug(QK8055_GUI) << "Translation File Loaded";
        qApp->installTranslator(&translator);
    }
    
    qk8055 w;
    w.show();

    return app.exec();
}


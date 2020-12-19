/*
Copyright (C) 2020 by Sandy McNeil <g7mzrdev@gmail.com>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of
the License or (at your option) version 3 or any later version
accepted by the membership of KDE e.V. (or its successor approved
by the membership of KDE e.V.), which shall act as a proxy 
defined in Section 14 of version 3 of the license.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "config.h"
#include "qk8055.h"
#include <QApplication>
#include <QTranslator>
#include "gui_debug.h"
#include <QLibraryInfo>

int main(int argc, char *argv[])
{
    
    QApplication app(argc, argv);
    
    QCoreApplication::setOrganizationName("g7mzr");
    QCoreApplication::setOrganizationDomain("g7mzr.github.io");
    QCoreApplication::setApplicationName(PROJECT_NAME);
    
    // Load and configure QTranslator for application translations
    QTranslator translator;

    bool isTrlsFileLoaded = translator.load("qk8055", ":/translations");
    
    if(!isTrlsFileLoaded) {
        qCDebug(QK8055_GUI) << "qk8055 Translation File Not Loaded";
    }
    else {
        qCDebug(QK8055_GUI) << "qk8055 Translation File Loaded";
        qApp->installTranslator(&translator);
    }
    

    // Load and configure QTranslator for QT Translations
    QTranslator translatorQT;

    bool isTrlsQTFileLoaded = translatorQT.load(
        QLocale(), 
        QLatin1String("qtbase"), 
        QLatin1String("_"), 
        QLibraryInfo::location(QLibraryInfo::TranslationsPath)
    );
    
    if(!isTrlsQTFileLoaded) {
        qCDebug(QK8055_GUI) << "QT Base Translation File Not Loaded";
    }
    else {
        qCDebug(QK8055_GUI) << "QT Base Translation File Loaded";
        qApp->installTranslator(&translatorQT);
    }
    
    
    qk8055 w;
    w.show();

    return app.exec();
}


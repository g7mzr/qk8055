/*
 * Velleman qk8055 Experimental Board Interface Program USB Bus Scanning Dialog.
 * 
 * Copyright (C) 2020, 2021  Sandy McNeil <g7mzrdev@gmail.com>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "config.h"
#include "qk8055.h"
#include "k8055.h"
#include "ui_qk8055.h"
#include "k8055_guiview.h"
#include "config_dialog.h"
#include "scandevices.h"
#include "gui_debug.h"
#include <QCloseEvent>
//#include <QDebug>
#include <QMessageBox>
#include <QDate>


qk8055::qk8055(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::qk8055)
{
    m_ui->setupUi(this);   
    
    m_k8055_guiView = new k8055_guiView(this);
    setCentralWidget(m_k8055_guiView);
    
    readSettings();
    createStatusBar("Disconnected");
    connect(m_k8055_guiView, SIGNAL(sendStatusBarUpdate(QString)), this, SLOT(createStatusBar(QString)));  

}

qk8055::~qk8055() = default;


void qk8055::closeEvent(QCloseEvent *event)
{
    //if(m_k8055_guiView->m_ui.disconnectButton->isEnabled()) {
    //        
    //}
    qCDebug(QK8055_GUI) << "qk8055::closeEvent()";
    m_k8055_guiView->k8055_disconnect();
    writeSettings();
    event->accept();
}


void qk8055::createStatusBar(QString msg)
{
    qCDebug(QK8055_GUI) << "qk8055::createStatusBar";
    statusBar()->showMessage(msg);
}

void qk8055::on_actionQuit_triggered() {
    qCDebug(QK8055_GUI) << "qk8055::on_actionQuit_triggered()";
    qApp->closeAllWindows();
}


void qk8055::on_actionAbout_triggered()
{
    qCDebug(QK8055_GUI) << "qk8055::on_actionAbout_triggered";
    // QMessageBox::about(this, tr("About K8055 Application"),
    //          tr("The <b>Application</b> example demonstrates how to "
    //             "write modern GUI applications using Qt, with a menu bar, "
    //             "toolbars, and a status bar."));
    
    
    QString translatedTextAboutCaption; 
    translatedTextAboutCaption = QMessageBox::tr(
        "<h3>About %1</h3>"
        "<p>%1 Version %2.</p>"
        "<p>%3</>"
        ).arg(QLatin1String(PROJECT_NAME))
        .arg(QLatin1String(PROJECT_VERSION))
        .arg(QLatin1String(PROJECT_DESCRIPTION));
        
        
    const QString translatedTextAboutText = QMessageBox::tr(
        "<p>%4 is licensed under %7</p>"
        "<p>Please see <a href=\"https://%2/\">%2</a> "
        "for an overview of %4 licensing.</p>"
        "<p>Copyright (C) %1 %5 <a href=\"mailto:%6\">%6</a>.</p>"
        "<p>%4 is developed as an open source "
        "project. See <a href=\"http://%3/\">%3</a> for more information.</p>"
        ).arg(QStringLiteral(COPYRIGHT_YEAR),
              QStringLiteral(PROJECT_LICENSE_URL),
              QStringLiteral(PROJECT_HOMEPAGE),
              QStringLiteral(PROJECT_NAME),
              QStringLiteral(AUTHOR_NAME),
              QStringLiteral(AUTHOR_EMAIL),
              QStringLiteral(PROJECT_LICENSE_NAME));        
        
    QMessageBox *msgBox = new QMessageBox(this);
    msgBox->setAttribute(Qt::WA_DeleteOnClose);
    msgBox->setTextFormat(Qt::RichText);
    msgBox->setWindowTitle(tr("About QK8055"));
    msgBox->setText(translatedTextAboutCaption);
     msgBox->setInformativeText(translatedTextAboutText);
    msgBox->exec();

}

void qk8055::on_actionAboutQT_triggered()
{
    qCDebug(QK8055_GUI) << "qk8055::on_actionAboutQT_triggered";
    QMessageBox::aboutQt(this);    
}


void qk8055::writeSettings()
{
    qCDebug(QK8055_GUI) << "qk8055::writeSettings";
    QSettings settings;

    settings.beginGroup("MainWindow");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.endGroup();
    
    settings.beginGroup("Configuration");
    settings.setValue("frequency", m_k8055_guiView->getPollingTime());
    settings.endGroup();
}

void qk8055::readSettings()
{
    qCDebug(QK8055_GUI) << "qk8055::readSettings";
    QSettings settings;

    settings.beginGroup("MainWindow");
    resize(settings.value("size", QSize(400, 400)).toSize());
    move(settings.value("pos", QPoint(951, 630)).toPoint());
    settings.endGroup();
    
    settings.beginGroup("Configuration");
    m_k8055_guiView->setPollingTime(settings.value("frequency", 250).toInt());
    settings.endGroup();

}


void qk8055::on_actionPreferences_triggered()
{
    qCDebug(QK8055_GUI) << "qk8055::on_actionPreferences_triggered";
    m_config_dialog = new Config_Dialog();
    m_config_dialog->setDialogValues(m_k8055_guiView->getPollingTime());
    int result = m_config_dialog->exec();
    if (result == QDialog::Accepted) {
        qCDebug(QK8055_GUI) << "qk8055::on_actionPreferences_triggered - Dialog Result = Accepted";
        int pollingValue = m_config_dialog->getPollingValue();
        m_k8055_guiView->setPollingTime(pollingValue);
    }

}

void qk8055::on_actionScan_Devices_triggered()
{
    qCDebug(QK8055_GUI) << "qk8055::on_actionScan_Devices_triggered";
    long result = SearchDevices();
    m_scandevices_dialog = new ScanDevices();
    m_scandevices_dialog->loadBoardData(result);
    m_scandevices_dialog->exec();
    
}

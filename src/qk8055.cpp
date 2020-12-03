#include "config.h"
#include "qk8055.h"
#include "ui_qk8055.h"
#include "k8055_guiview.h"
#include <QCloseEvent>
#include <QDebug>
#include <QMessageBox>


qk8055::qk8055(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::qk8055)
{
    m_ui->setupUi(this);   
    
    m_k8055_guiView = new k8055_guiView(this);
    setCentralWidget(m_k8055_guiView);
    
    createStatusBar("Disconnected");
    connect(m_k8055_guiView, SIGNAL(sendStatusBarUpdate(QString)), this, SLOT(createStatusBar(QString)));  

}

qk8055::~qk8055() = default;


void qk8055::closeEvent(QCloseEvent *event)
{
    //if(m_k8055_guiView->m_ui.disconnectButton->isEnabled()) {
    //        
    //}
    qDebug() << "qk8055::closeEvent()";
    m_k8055_guiView->k8055_disconnect();
    event->accept();
}


void qk8055::createStatusBar(QString msg)
{
    
    statusBar()->showMessage(msg);
}

void qk8055::on_actionQuit_triggered() {
    qDebug() << "qk8055::on_actionQuit_triggered()";
    qApp->closeAllWindows();
}


void qk8055::on_actionAbout_triggered()
{
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
    QMessageBox::aboutQt(this);    
}


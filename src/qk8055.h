#ifndef QK8055_H
#define QK8055_H

#include <QMainWindow>
#include <QScopedPointer>

#include "k8055_guiview.h"

#include <QCloseEvent>


namespace Ui {
class qk8055;
}

class qk8055 : public QMainWindow
{
    Q_OBJECT

public:
    explicit qk8055(QWidget *parent = nullptr);
    ~qk8055() override;
    
public Q_SLOTS:
     void createStatusBar(QString msg);
   
private Q_SLOTS:
    void on_actionQuit_triggered();
    void on_actionAbout_triggered();
    void on_actionAboutQT_triggered();
    
    
protected:
    void closeEvent(QCloseEvent *event) override;
    
private:
    QScopedPointer<Ui::qk8055> m_ui;
    k8055_guiView *m_k8055_guiView;
};

#endif // QK8055_H

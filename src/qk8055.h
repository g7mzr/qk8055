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

#ifndef QK8055_H
#define QK8055_H

#include <QMainWindow>
#include <QScopedPointer>
#include <QSettings>

#include "k8055_guiview.h"
#include "config_dialog.h"
#include "scandevices.h"

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
    void on_actionPreferences_triggered();
    void on_actionScan_Devices_triggered();
    
    
protected:
    void closeEvent(QCloseEvent *event) override;
    
private:
    QScopedPointer<Ui::qk8055> m_ui;
    k8055_guiView *m_k8055_guiView;
    Config_Dialog *m_config_dialog;
    ScanDevices *m_scandevices_dialog;
    
    void writeSettings();
    void readSettings();
};

#endif // QK8055_H

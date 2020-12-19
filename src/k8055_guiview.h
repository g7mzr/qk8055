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

#ifndef K8055_GUIVIEW_H
#define K8055_GUIVIEW_H


#include "ui_k8055_guiview.h"

/**
 * This class serves as the main window for k8055_gui.  It handles the
 * menus, toolbars and status bars.
 *
 * @short Main window class
 * @author %{AUTHOR} <%{EMAIL}>
 * @version %{VERSION}
 */
class k8055_guiView : public QWidget
{
    Q_OBJECT
public:
    /**
     * Default Constructor
     */
    explicit k8055_guiView(QWidget *parent);

    /**
     * Default Destructor
     */
    ~k8055_guiView() override;
    
    /**
     * Set timer for reading board data
     */
    void setReadFrequency(int frequency);
    
    /**
     * Get the timeout for reading the board data
     */
    int getReadFrequency();


public Q_SLOTS:
    void k8055_connect();
    void k8055_disconnect();
    void update_analogue1(int i);
    void update_analogue2(int i);
    void timer_timeout();
    void test_timer_timeout();
    void update_dout1(int state);
    void update_dout2(int state);
    void update_dout3(int state);
    void update_dout4(int state);
    void update_dout5(int state);
    void update_dout6(int state);
    void update_dout7(int state);
    void update_dout8(int state);
    void counter1reset();
    void counter2reset();
    void counter1debounce(int id);
    void counter2debounce(int id);
    void setalldigital();
    void clearalldigital();
    void setallanalogue();
    void clearallanalogue();
    void outputtest();
    
Q_SIGNALS:
    void sendStatusBarUpdate(QString msg);


private:
    // this is the name of the root widget inside our Ui file
    // you can rename it in designer and then change it here
    Ui::k8055_guiView m_ui;
    QTimer *timer;
    QTimer *testtimer;
    
    int testoutput = 1;
    int readFrequency = 250;
    
    void enablek8055inputs(bool enabled);
    void checkBoxReadOnly();
};

#endif // K8055_GUIVIEW_H

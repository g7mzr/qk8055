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

#include <string>   

// application headers
#include "k8055_guiview.h"

//#include "k8055_guiSettings.h"
#include "gui_debug.h"

#include "k8055.h"

// KF Headers
#include <QTimer>
//#include <QDebug>

int analogue1 = 0;
int analogue2 = 0;
int digital = 0;
 

k8055_guiView::k8055_guiView(QWidget *parent)
    : QWidget(parent)
{
    m_ui.setupUi(this);
    
    // Connect the "Connect" and "Disconnect" Buttons
    connect(m_ui.connectButton, SIGNAL(clicked()), this, SLOT(k8055_connect()));
    connect(m_ui.disconnectButton, SIGNAL(clicked()), this, SLOT(k8055_disconnect()));
    
    // Connect the two Digital to Analogue Sliders
    connect(m_ui.DA1Slider, SIGNAL(valueChanged(int)), this, SLOT(update_analogue1(int)));
    connect(m_ui.DA2Slider, SIGNAL(valueChanged(int)), this, SLOT(update_analogue2(int)));
    
    // Connect all the output checkboxes
    connect(m_ui.dout1, SIGNAL(stateChanged(int)), this, SLOT(update_dout1(int)));
    connect(m_ui.dout2, SIGNAL(stateChanged(int)), this, SLOT(update_dout2(int)));
    connect(m_ui.dout3, SIGNAL(stateChanged(int)), this, SLOT(update_dout3(int)));
    connect(m_ui.dout4, SIGNAL(stateChanged(int)), this, SLOT(update_dout4(int)));
    connect(m_ui.dout5, SIGNAL(stateChanged(int)), this, SLOT(update_dout5(int)));
    connect(m_ui.dout6, SIGNAL(stateChanged(int)), this, SLOT(update_dout6(int)));
    connect(m_ui.dout7, SIGNAL(stateChanged(int)), this, SLOT(update_dout7(int)));
    connect(m_ui.dout8, SIGNAL(stateChanged(int)), this, SLOT(update_dout8(int)));
    
    // Counter connections
    connect(m_ui.resetcounter1button, SIGNAL(clicked()), this, SLOT(counter1reset()));
    connect(m_ui.resetcounter2button, SIGNAL(clicked()), this, SLOT(counter2reset()));
    connect(m_ui.counter1buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(counter1debounce(int)));
    connect(m_ui.counter2buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(counter2debounce(int)));
     
    // Test button connections
    connect(m_ui.setallDigitalButton, SIGNAL(clicked()), this, SLOT(setalldigital()));
    connect(m_ui.clearalldigitalbutton, SIGNAL(clicked()), this, SLOT(clearalldigital()));
    connect(m_ui.setallanaloguebutton, SIGNAL(clicked()), this, SLOT(setallanalogue()));
    connect(m_ui.clearallanaloguebutton, SIGNAL(clicked()),this, SLOT(clearallanalogue()));
    connect(m_ui.outputtestbutton, SIGNAL(clicked()), this, SLOT(outputtest()));
    
    // Set up timer for reading input data from K8055 Board
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timer_timeout()));
    
    testtimer = new QTimer(this);
    connect(testtimer, SIGNAL(timeout()), this, SLOT(test_timer_timeout()));
    
    enablek8055inputs(false);
    checkBoxReadOnly();
    m_ui.libraryversionlineEdit->setText(Version());
    
}

k8055_guiView::~k8055_guiView()
{
}

void k8055_guiView::k8055_connect()
{
    qCDebug(QK8055_GUI) << "k8055_guiView::k8055_connect()";
    int selectedboard = 0;
    if (m_ui.Board0->isChecked()) {
        selectedboard = 0;
    }
    if (m_ui.Board1->isChecked()) {
        selectedboard = 1;
    }
    if (m_ui.Board2->isChecked()) {
        selectedboard = 2;
    }
    if (m_ui.Board3->isChecked()) {
        selectedboard = 3;
    }
    
    int openResult = OpenDevice((long) selectedboard);
    if (openResult < 0) {
        qCDebug(QK8055_GUI) << "k8055_guiView::k8055_connect() - Unable to open device";
        emit sendStatusBarUpdate(tr("Unable to connect to K8055 Board: ") + QString::number(selectedboard));
        return;
    }
    
    
    m_ui.disconnectButton->setEnabled(true);
    m_ui.connectButton->setEnabled(false);
    m_ui.groupBox->setEnabled(false);

    enablek8055inputs(true);
    counter1debounce(-3);
    counter2debounce(-3);
    m_ui.counter1_2ms->setChecked(true);
    m_ui.counter2_2ms->setChecked(true);
    timer->start(pollingFrequency);
    emit sendStatusBarUpdate(tr("Connected to K8055 Board ") + QString::number(selectedboard));
}

void k8055_guiView::k8055_disconnect()
{
    // Only run this command if the programme is connected to a K8055 Board
    if(m_ui.disconnectButton->isEnabled() == false) {
        return;
    }
        
    qCDebug(QK8055_GUI) << "k8055_guiView::k8055_disconnect()";
    
    timer->stop();
    testtimer->stop();
    m_ui.outputtestbutton->setChecked(false);
    SetAllValues(0, 0, 0);
    ResetCounter(1);
    ResetCounter(2);
    CloseDevice();
    
    // Reset the Analogue Inpots and out puts to 0
    m_ui.AD1lineEdit->setText("0");
    m_ui.AD1ProgressBar->setValue(0);
    m_ui.AD2LineEdit->setText("0");
    m_ui.AD2ProgressBar->setValue(0);
    
    m_ui.DA1Slider->setValue(0);
    m_ui.DA1LineEdit->setText("0");
    m_ui.DA2Slider->setValue(0);
    m_ui.DA2LineEdit->setText("0");
   
    // Set all Digital input displays to unchecked
    m_ui.din1->setChecked(false);
    m_ui.din2->setChecked(false);
    m_ui.din3->setChecked(false);
    m_ui.din4->setChecked(false);
    m_ui.din5->setChecked(false);
    
    // Set all the Digital output displayes to unchecked
    m_ui.dout1->setChecked(false);
    m_ui.dout2->setChecked(false);
    m_ui.dout3->setChecked(false);
    m_ui.dout4->setChecked(false);
    m_ui.dout5->setChecked(false);
    m_ui.dout6->setChecked(false);
    m_ui.dout7->setChecked(false);
    m_ui.dout8->setChecked(false);
    
    // Reset the counters displays
    m_ui.counter1display->setText("0");
    m_ui.counter2display->setText("0");
     
    // Reset the buttopns
    m_ui.disconnectButton->setEnabled(false);
    m_ui.connectButton->setEnabled(true);
    m_ui.groupBox->setEnabled(true);
    
    // Disable all use inputs 
    enablek8055inputs(false);
    
    // Update the status bar
    emit sendStatusBarUpdate(tr("Disconnected"));
}

void k8055_guiView::checkBoxReadOnly()
{
    qCDebug(QK8055_GUI) << "k8055_guiView::checkboxreadonly()";
   m_ui.din1->setAttribute(Qt::WA_TransparentForMouseEvents);
   m_ui.din1->setFocusPolicy(Qt::NoFocus);    
   m_ui.din2->setAttribute(Qt::WA_TransparentForMouseEvents);
   m_ui.din2->setFocusPolicy(Qt::NoFocus);    
   m_ui.din3->setAttribute(Qt::WA_TransparentForMouseEvents);
   m_ui.din4->setFocusPolicy(Qt::NoFocus);    
   m_ui.din4->setAttribute(Qt::WA_TransparentForMouseEvents);
   m_ui.din4->setFocusPolicy(Qt::NoFocus);    
   m_ui.din5->setAttribute(Qt::WA_TransparentForMouseEvents);
   m_ui.din5->setFocusPolicy(Qt::NoFocus);    
}


void k8055_guiView::timer_timeout()
{
    long d;
    long a1;
    long a2;
    long c1;
    long c2;
    
    timer->stop();
    ReadAllValues( &d,&a1,&a2,&c1,&c2); 
    
    m_ui.AD1lineEdit->setText(QString::number(a1));
    m_ui.AD1ProgressBar->setValue(a1);
    m_ui.AD2LineEdit->setText(QString::number(a2));
    m_ui.AD2ProgressBar->setValue(a2);
    
    //m_ui.spinBox_5->setValue(a2);
    
    if(d & 1) {
        m_ui.din1->setChecked(true);
    } else {
        m_ui.din1->setChecked(false);
    }
    if(d & 2) {
        m_ui.din2->setChecked(true);
    } else {
        m_ui.din2->setChecked(false);
    }
    if(d & 4) {
        m_ui.din3->setChecked(true);
    } else {
        m_ui.din3->setChecked(false);
    }
    if(d & 8) {
        m_ui.din4->setChecked(true);
    } else {
        m_ui.din4->setChecked(false);
    }
    if(d & 16) {
        m_ui.din5->setChecked(true);
    } else {
        m_ui.din5->setChecked(false);
    }
    m_ui.counter1display->setText(QString::number(c1));
    m_ui.counter2display->setText(QString::number(c2));
    timer->start(pollingFrequency);
}


void k8055_guiView::enablek8055inputs(bool enabled)
{
    qCDebug(QK8055_GUI) << "k8055_guiView::enablek8055inputs()";
    m_ui.DA1Slider->setEnabled(enabled);
    m_ui.DA2Slider->setEnabled(enabled);
    m_ui.AD1ProgressBar->setEnabled(enabled);
    m_ui.AD2ProgressBar->setEnabled(enabled);
    m_ui.analogueIOgroupbox->setEnabled(enabled);
    m_ui.digitalInputGroup->setEnabled(enabled);
    m_ui.digitalOutputGroup->setEnabled(enabled);
    m_ui.counter1Groupbox->setEnabled(enabled);
    m_ui.counter2groupbox->setEnabled(enabled);
    m_ui.setallDigitalButton->setEnabled(enabled);
    m_ui.clearalldigitalbutton->setEnabled(enabled);
    m_ui.setallanaloguebutton->setEnabled(enabled);
    m_ui.clearallanaloguebutton->setEnabled(enabled);
    m_ui.outputtestbutton->setEnabled(enabled);
}



void k8055_guiView::update_analogue1(int i)
{
    qCDebug(QK8055_GUI) << "k8055_guiView::update_analogue1()";
    SetAllValues(digital, (long) i, analogue2);
    m_ui.DA1LineEdit->setText(QString::number(i));
    analogue1 = i;
}

void k8055_guiView::update_analogue2(int i)
{
    qCDebug(QK8055_GUI) << "k8055_guiView::update_analogue2()";
    SetAllValues(digital, analogue1, (long) i);
    m_ui.DA2LineEdit->setText(QString::number(i));
    analogue2 = i;
    
}

void k8055_guiView::update_dout1(int state)
{
    qCDebug(QK8055_GUI) << "k8055_guiView::updatedout1()";
    long port_no = 1;
    if (state == 0) {
        digital = digital & ~port_no;
    } else {
        digital = digital | port_no;
    }
    SetAllValues(digital, analogue1, analogue2);
}

void k8055_guiView::update_dout2(int state)
{
    qCDebug(QK8055_GUI) << "k8055_guiView::updatedout2()";
    long port_no = 2;
    if (state == 0) {
        digital = digital & ~port_no;
    } else {
        digital = digital | port_no;
    }
    SetAllValues(digital, analogue1, analogue2);
}

void k8055_guiView::update_dout3(int state)
{
    qCDebug(QK8055_GUI) << "k8055_guiView::updatedout3()";
    long port_no = 4;
    if (state == 0) {
        digital = digital & ~port_no;
    } else {
        digital = digital | port_no;
    }
    SetAllValues(digital, analogue1, analogue2);
}

void k8055_guiView::update_dout4(int state)
{
    qCDebug(QK8055_GUI) << "k8055_guiView::updatedout4()";
    long port_no = 8;
    if (state == 0) {
        digital = digital & ~port_no;
    } else {
        digital = digital | port_no;
    }
    SetAllValues(digital, analogue1, analogue2);
}

void k8055_guiView::update_dout5(int state)
{
    qCDebug(QK8055_GUI) << "k8055_guiView::updatedout5()";
    long port_no = 16;
    if (state == 0) {
        digital = digital & ~port_no;
    } else {
        digital = digital | port_no;
    }
    SetAllValues(digital, analogue1, analogue2);
}

void k8055_guiView::update_dout6(int state)
{
    qCDebug(QK8055_GUI) << "k8055_guiView::updatedout6()";
    long port_no = 32;
    if (state == 0) {
        digital = digital & ~port_no;
    } else {
        digital = digital | port_no;
    }
    SetAllValues(digital, analogue1, analogue2);
}

void k8055_guiView::update_dout7(int state)
{
    qCDebug(QK8055_GUI) << "k8055_guiView::updatedout7()";
    long port_no = 64;
    if (state == 0) {
        digital = digital & ~port_no;
    } else {
        digital = digital | port_no;
    }
    SetAllValues(digital, analogue1, analogue2);
}

void k8055_guiView::update_dout8(int state)
{
    qCDebug(QK8055_GUI) << "k8055_guiView::updatedout8()";
    long port_no = 128;
    if (state == 0) {
        digital = digital & ~port_no;
    } else {
        digital = digital | port_no;
    }
    SetAllValues(digital, analogue1, analogue2);
}

void k8055_guiView::counter1reset()
{
    qCDebug(QK8055_GUI) << "k8055_guiView::counter1reset()";
    ResetCounter(1);
}

void k8055_guiView::counter2reset()
{
    qCDebug(QK8055_GUI) << "k8055_guiView::counter2reset()";
    ResetCounter(2);
}

void k8055_guiView::counter1debounce(int id)
{
    qCDebug(QK8055_GUI) << "k8055_guiView::counter1debounce()";
    long debouncetime = 0;
    if (id == -2) {
        debouncetime = 0;
    } else if (id == -3) {
        debouncetime = 2;
    } else if (id == -4) {
        debouncetime = 10;
    } else if (id == -5 ) {
        debouncetime = 1000;
    } else {
       qCDebug(QK8055_GUI) << "k8055_guiView::counter1debounce() -  invalid button";
    }
    SetCounterDebounceTime(1, debouncetime);
}

void k8055_guiView::counter2debounce(int id)
{
    qCDebug(QK8055_GUI) << "k8055_guiView::counter2debounce()";
    long debouncetime = 0;
    if (id == -2) {
        debouncetime = 0;
    } else if (id == -3) {
        debouncetime = 2;
    } else if (id == -4) {
        debouncetime = 10;
    } else if (id == -5 ) {
        debouncetime = 1000;
    } else {
       qCDebug(QK8055_GUI) << "k8055_guiView::counter2debounce() -  invalid button";
    }
    SetCounterDebounceTime(2, debouncetime);
}


void k8055_guiView::setalldigital()
{
    qCDebug(QK8055_GUI) << "k8055_guiView::setalldigital()";
    m_ui.dout1->setChecked(true);
    m_ui.dout2->setChecked(true);
    m_ui.dout3->setChecked(true);
    m_ui.dout4->setChecked(true);
    m_ui.dout5->setChecked(true);
    m_ui.dout6->setChecked(true);
    m_ui.dout7->setChecked(true);
    m_ui.dout8->setChecked(true);
    digital = 255;
    SetAllDigital();
}

void k8055_guiView::clearalldigital()
{
    qCDebug(QK8055_GUI) << "k8055_guiView::clearalldigital()";
    m_ui.dout1->setChecked(false);
    m_ui.dout2->setChecked(false);
    m_ui.dout3->setChecked(false);
    m_ui.dout4->setChecked(false);
    m_ui.dout5->setChecked(false);
    m_ui.dout6->setChecked(false);
    m_ui.dout7->setChecked(false);
    m_ui.dout8->setChecked(false);
    digital = 0;
    ClearAllDigital();
}

void k8055_guiView::setallanalogue()
{
    qCDebug(QK8055_GUI) << "k8055_guiView::setallanalogue()";
    m_ui.DA1Slider->setValue(255);
    m_ui.DA2Slider->setValue(255);
    analogue1 = 255;
    analogue2 = 255;
    SetAllAnalog();
}

void k8055_guiView::clearallanalogue()
{
    qCDebug(QK8055_GUI) << "k8055_guiView::clearallanalogue()";
    m_ui.DA1Slider->setValue(0);
    m_ui.DA2Slider->setValue(0);
    analogue1 = 0;
    analogue2 = 0;
    ClearAllAnalog();
}

void k8055_guiView::outputtest()
{
    qCDebug(QK8055_GUI) << "k8055_guiView::outputtest()";
    
    if (m_ui.outputtestbutton->isChecked()) {
        qCDebug(QK8055_GUI) << "k8055_guiView::outputtest() - Start Timer";
        m_ui.dout1->setChecked(true);
        testoutput = 1;
        testtimer->start(500);
    } else {
        qCDebug(QK8055_GUI) << "k8055_guiView::outputtest() - Stop Timer";
        testtimer->stop();
    }
        
    // Switch on Channel 1
    //WriteAllDigital(1);
    //m_ui.dout1->setChecked(true);
}

void k8055_guiView::test_timer_timeout()
{
    qCDebug(QK8055_GUI) << "k8055_guiView::test_timer_timeout()";
    QStringList myStringList;
    QString name = "dout" + QString::number(testoutput);
    QList<QCheckBox *> list = m_ui.digitalOutputGroup->findChildren<QCheckBox *>();
    foreach (QCheckBox *checkBox, list) {
        if (checkBox->objectName() == name) {
            checkBox->setChecked(false);
        }
    }
    
    testoutput++;
    
    if (testoutput > 8) 
        testoutput = 1;
    
    name = "dout" + QString::number(testoutput);
    foreach (QCheckBox *checkBox2, list) {
        if (checkBox2->objectName() == name)
            checkBox2->setChecked(true);
    }
}


/**
 * Set timer for reading board data
 */
void k8055_guiView::setPollingTime(int period)
{
    pollingFrequency = period;
}


/**
 * Get the timeout for reading the board data
 */
int k8055_guiView::getPollingTime()
{
    return(pollingFrequency);
}

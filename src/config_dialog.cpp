/*
 * Velleman qk8055 Experimental Board Interface Program Configuration Dialog.
 * 
 * Copyright (C) 2020  Sandy McNeil <g7mzrdev@gmail.com>
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

#include "config_dialog.h"
#include "ui_config_dialog.h"
#include "gui_debug.h"
#include "k8055_guiview.h"

/**
 * Constructor
 * 
 * The qk8055 configuration dialog box constructor
 */
Config_Dialog::Config_Dialog()
    : m_ui(new Ui::Config_Dialog)
{
    m_ui->setupUi(this);
    
    // Connect SIGNALS to SLOTS
    connect(m_ui->timerDurationInput, SIGNAL(valueChanged(int)), this, SLOT(updateHZDisplay(int)));
    connect(m_ui->defaultButton, SIGNAL(clicked()), this, SLOT(resetToDefault()));
}

/**
 * Destructor
 * 
 * The qk8055 configuration dialog box destructor
 */
Config_Dialog::~Config_Dialog()
{
}

/**
 * SLOT: updateHZDisplay
 * 
 * Ths SLOT takes the current value in MS from the input spin box and displays it
 * in the HzDisplat Edit box as a frequenct in Hz.
 * 
 * @para int period The number of ms the spinbox is set to.
 * 
 * @return void
 * 
 * @access private
 */
void Config_Dialog::updateHZDisplay(int period)
{
     qCDebug(QK8055_GUI) << "Config_Dialog::updateHZDisplay";
     double hzvalue = 1000.00 / period;
     m_ui->hzEdit->setText(QString::number(hzvalue,'f',2).append(" Hz"));
}

/**
 * SLOT: resetToDefault
 * 
 * This SLOT resets the value to be used by the board polling timer to 250ms or 4Hz. The actual
 * value used is only updated when the input is acepted (OK Button Clicked)
 * 
 * @return void
 * 
 * @access private
 */
void Config_Dialog::resetToDefault()
{
    qCDebug(QK8055_GUI) << "Config_Dialog::resetToDefault";
    m_ui->timerDurationInput->setValue(250);
}

/**
 * FUNCTION: setDialogValues
 * 
 * This function is used to populate the dialof with the current configuration
 * values used by the application
 * 
 * @param int period The polling requenxy for the K8055 board in ms
 * 
 * @return void
 * 
 * @access public
 */
void Config_Dialog::setDialogValues(int period)
{
    qCDebug(QK8055_GUI) << "Config_Dialog::setDialogValues";
    m_ui->timerDurationInput->setValue(period);
    updateHZDisplay(period);
}

/**
 * FUNCTION: getPollingValue
 * 
 * This function retrieves the K8055 Polling frequency in ms from the Configuration
 * Dialog Box as an integer
 *
 * @return int The k8055 Polling frequency in ms
 *
 *@access public
 */ 
int Config_Dialog::getPollingValue()
{
    qCDebug(QK8055_GUI) << "Config_Dialog::getPollingValue";
    return m_ui->timerDurationInput->value();
}

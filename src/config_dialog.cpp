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

Config_Dialog::Config_Dialog()
    : m_ui(new Ui::Config_Dialog)
{
    m_ui->setupUi(this);
    connect(m_ui->timerDurationInput, SIGNAL(valueChanged(int)), this, SLOT(updateHZDisplay(int)));
    connect(m_ui->defaultButton, SIGNAL(clicked()), this, SLOT(resetToDefault()));
}

Config_Dialog::~Config_Dialog()
{
}


void Config_Dialog::updateHZDisplay(int period)
{
     qCDebug(QK8055_GUI) << "Config_Dialog::updateHZDisplay";
     double hzvalue = 1000.00 / period;
     m_ui->hzEdit->setText(QString::number(hzvalue,'f',2).append(" Hz"));
}


void Config_Dialog::resetToDefault()
{
    qCDebug(QK8055_GUI) << "Config_Dialog::resetToDefault";
    m_ui->timerDurationInput->setValue(250);
}

void Config_Dialog::setDialogValues(int period)
{
    qCDebug(QK8055_GUI) << "Config_Dialog::setDialogValues";
    m_ui->timerDurationInput->setValue(period);
    
}

int Config_Dialog::getPollingValue()
{
    qCDebug(QK8055_GUI) << "Config_Dialog::getPollingValue";
    return m_ui->timerDurationInput->value();
}

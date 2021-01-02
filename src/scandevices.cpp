/*
 * Velleman qk8055 Experimental Board Interface Program USB Bus Scanning Dialog.
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

#include "scandevices.h"
#include "ui_scandevices.h"

ScanDevices::ScanDevices()
    : m_ui(new Ui::ScanDevices)
{
    m_ui->setupUi(this);
}

ScanDevices::~ScanDevices()
{
}


/**
 * Load K8055 Board Information
 * 
 * This function loads the ScanDevices Dialog with the list of K8055
 * boards Found.
 * 
 * @param long boardData The list of boards found
 * 
 * @return void
 * 
 * @access public
 */
void ScanDevices::loadBoardData(long boardData)
{
    // Check for board connected as Port 0
    if ((boardData & 1) == 1) { 
        m_ui->port0status->setText("K8055");
    } else {
       m_ui->port0status->setText(tr("Empty")); 
    }

    // Check for board connected as Port 1
    if ((boardData & 2) == 2) { 
        m_ui->port1status->setText("K8055");
    } else {
       m_ui->port1status->setText(tr("Empty")); 
    }
    
    // Check for board connected as Port 2
    if ((boardData & 4) == 4) { 
        m_ui->port2status->setText("K8055");
    } else {
       m_ui->port2status->setText(tr("Empty")); 
    }
    
    // Check for board connected as Port 3
    if ((boardData & 8) == 8) { 
        m_ui->port3status->setText("K8055");
    } else {
       m_ui->port3status->setText(tr("Empty")); 
    }
}

/*
 * Velleman qk8055 Experimental Board Interface Program USB Bus Scanning Dialog.
 * 
 * Copyright (C) 2021  Sandy McNeil <g7mzrdev@gmail.com>
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

#ifndef SCANDEVICES_H
#define SCANDEVICES_H

#include <QDialog>
#include <QScopedPointer>

namespace Ui
{
class ScanDevices;
}

/**
 * @todo write docs
 */
class ScanDevices : public QDialog
{
    Q_OBJECT

public:
    /**
     * Default constructor
     */
    ScanDevices();

    /**
     * Destructor
     */
    ~ScanDevices();
    
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
    void loadBoardData(long boardData);

private:
    QScopedPointer<Ui::ScanDevices> m_ui;
};

#endif // SCANDEVICES_H

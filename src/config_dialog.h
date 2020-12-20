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

#ifndef CONFIG_DIALOG_H
#define CONFIG_DIALOG_H

#include <QDialog>
#include <QScopedPointer>

namespace Ui
{
class Config_Dialog;
}

/**
 * @todo write docs
 */
class Config_Dialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * Constructor
     * 
     * The qk8055 configuration dialog box constructor
     */
    Config_Dialog();

    /**
     * Destructor
     * 
     * The qk8055 configuration dialog box destructor
     */
    ~Config_Dialog();
    
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
    void setDialogValues(int period);
    
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
    int getPollingValue();
    
private Q_SLOTS:
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
    void updateHZDisplay(int period);
    
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
    void resetToDefault();

private:
    // Pointer to the Configuration Dialogbox structure
    QScopedPointer<Ui::Config_Dialog> m_ui;
};

#endif // CONFIG_DIALOG_H

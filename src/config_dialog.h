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
     * Default constructor
     */
    Config_Dialog();

    /**
     * Destructor
     */
    ~Config_Dialog();
    
    /**
     * Set the Dialog Box with the current Values
     */
    void setDialogValues(int period);
    
    /**
     * Read the Frequency Setting
     */
    int getPollingValue();
    
private Q_SLOTS:
    void updateHZDisplay(int period);
    void resetToDefault();

private:
    QScopedPointer<Ui::Config_Dialog> m_ui;
};

#endif // CONFIG_DIALOG_H

/***************************************************************************
 *   Copyright (C) 2003 by Olaf Lueg                                       *
 *   olueg@olsd.de                                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#ifndef CSYSTEMTRAY_H
#define CSYSTEMTRAY_H

#include <ksystemtray.h>

/**
@author Olaf Lueg
*/
class KAction;
class CSystemTray : public KSystemTray
{
Q_OBJECT
public:
    CSystemTray(QWidget *parent = 0, const char *name = 0, WFlags f = 0);

    ~CSystemTray();
protected slots:
	void contextHangup();
private:
	KAction *disconnect;
	KAction *preferences;
signals:
	void hangup();

};

#endif

/***************************************************************************
 *   Copyright (C) 2003 by Olaf Lueg                                       *
 *   olueg@olsd.de                                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#ifndef KDIALER_H
#define KDIALER_H
#include <kmainwindow.h>
#include <kapplication.h>
#include <qwidget.h>

/**
@author Olaf Lueg
*/
class Info;
class KProcess;
class KAction;
class CSystemTray;

class KDialer : public KMainWindow
{
Q_OBJECT
public:
    KDialer(QWidget *parent = 0, const char *name = 0);

    ~KDialer();
	friend class CSystemTray;
	Info *info;
	CSystemTray *tray;
	QString device;
	QString file;
	void dial();
	void init();
private:
	QString dialOut;
	QString profile;
	QString username;
	bool connected;
protected:
	bool queryClose();
protected slots:
	void received( KProcess *proc, char *buff, int len );
	void infoReceived( KProcess *proc, char *buff, int len );
	void disconnect();
	void close();
};

#endif

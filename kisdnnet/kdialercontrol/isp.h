/***************************************************************************
 *   Copyright (C) 2003 by Olaf Lueg                                       *
 *   olueg@olsd.de                                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#ifndef ISP_H
#define ISP_H

#include <qobject.h>

class QListViewItem;
class kdialercontrol;

/**
@author Olaf Lueg
*/
class ISP : public QObject
{
Q_OBJECT
public:
    ISP(QObject *parent = 0, const char *name = 0);
	ISP(QObject *parent = 0, const char *name = 0, const char *file = 0);
    ~ISP();
	friend class kdialercontrol;
	void edit();
protected:
	QString profileName;
	QString username;
	QString sysname;
	QString remoteOut;
	QString remoteIn;
	QString localMSN;
	QString secure;
	QString dialmode;
	QString slave;
	QString pppBind;
	QString pppOptions;
	QString device;
	QListViewItem *item;
	QString fileName;
	QString file;
protected:
	void load( const QString &file );
	void save();
};

#endif

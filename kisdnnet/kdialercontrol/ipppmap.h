/***************************************************************************
 *   Copyright (C) 2003 by Olaf Lueg                                       *
 *   olueg@olsd.de                                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#ifndef IPPPMAP_H
#define IPPPMAP_H

#include <qobject.h>
#include <qdict.h>

/**
@author Olaf Lueg
*/
class IPPPMap : public QObject
{
Q_OBJECT
public:
    IPPPMap(QObject *parent = 0, const char *name = 0);

    ~IPPPMap();
	QDict<QString>providerMap;
	QString getDevice( QString key );

};

#endif

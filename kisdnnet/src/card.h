/***************************************************************************
 *   Copyright (C) 2003 by Olaf Lueg                                       *
 *   olueg@olsd.de                                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#ifndef CARD_H
#define CARD_H

#include <qobject.h>

/**
@author Olaf Lueg
*/
class Card : public QObject
{
Q_OBJECT
public:
    Card(QObject *parent = 0, const char *name = 0);

    ~Card();
	void read( const QString file );
	void edit();
	void save();
private:
	QString fileName;
	QString ID;
	QString module;
	QString type;
	QString membase;
	QString port;
	QString irq;

};

#endif

/***************************************************************************
 *   Copyright (C) 2003 by Olaf Lueg                                       *
 *   olueg@olsd.de                                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#include "ipppmap.h"
#include "kisdnnet.h"

#include <kconfig.h>

#include <qregexp.h>

/*!
	\class IPPPMap ipppmap.h
    \brief The IPPPMap class provides access to the ippp.map file.
	It stores the information from ippp.map in the QDict providerMap
*/


IPPPMap::IPPPMap(QObject *parent, const char *name)
 : QObject(parent, name)
{
	providerMap.setAutoDelete( TRUE );
	QString file = mapPath ; file += "ippp.map";
	KConfig conf( file );
	QString key, *device, provider;
	for( uint i = 0; i <= 10; i++ )
	{
		key = QString("ippp%1").arg( i );
		if( conf.hasKey( key ) ){
			provider = conf.readEntry( key, "" ) ;
			provider = provider.replace( QRegExp("\""), "" );
			device = new QString( key );
			providerMap.insert( provider, device );
			#ifdef DEBUG
			debug( "IPPPMap::IPPPMap() : device=%s, provider=%s",device->latin1(), provider.latin1() );
			#endif
		}
	}
}


IPPPMap::~IPPPMap()
{
	providerMap.clear();
}

QString IPPPMap::getDevice( QString key )
{
	QString *str = providerMap.find( key );
	if( str )
		return str->latin1();
	return QString::null;
}



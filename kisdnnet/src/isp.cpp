/***************************************************************************
 *   Copyright (C) 2003 by Olaf Lueg                                       *
 *   olueg@olsd.de                                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#include "isp.h"
#include "kisdnnet.h"
#include "ispedit.h"

#include <kconfig.h>

#include <qiconview.h>
#include <qregexp.h>
#include <qlabel.h>
#include <qlineedit.h>

ISP::ISP(QObject *parent, const char *name)
 : QObject(parent, name)
{
}

ISP::ISP(QObject *parent, const char *name, const char *file)
 : QObject(parent, name)
{
	load( file );
}


ISP::~ISP()
{
	save();
}

/*! Load the profile settings from the profile \afile
*/
void ISP::load( const QString &file )
{
	fileName = file;
	KConfig conf( file );
	profileName	= conf.readEntry("I4L_PROFILENAME","");
	username	= conf.readEntry("I4L_USERNAME","");
	sysname		= conf.readEntry("I4L_SYSNAME","");
	remoteOut	= conf.readEntry("I4L_REMOTE_OUT","");
	remoteIn	= conf.readEntry("I4L_REMOTE_IN","");
	localMSN	= conf.readEntry("I4L_LOCALMSN","");
	secure		= conf.readEntry("I4L_SECURE","");
	dialmode	= conf.readEntry("I4L_DIALMODE","");
	slave		= conf.readEntry("SLAVE","");
	device		= conf.readEntry("DEVICE","");
	pppBind		= conf.readEntry("I4L_PPPBIND","");
	pppOptions	= conf.readEntry("I4L_PPPOPTIONS","");
	// remove the
	profileName	= profileName.replace( QRegExp("\""), "" );
	username	= username.replace( QRegExp("\""), "" );
	sysname		= sysname.replace( QRegExp("\""), "" );
	remoteOut	= remoteOut.replace( QRegExp("\""), "" );
	remoteIn	= remoteIn.replace( QRegExp("\""), "" );
	localMSN	= localMSN.replace( QRegExp("\""), "" );
	secure		= secure.replace( QRegExp("\""), "" );
	dialmode	= dialmode.replace( QRegExp("\""), "" );
	slave		= slave.replace( QRegExp("\""), "" );
	device		= device.replace( QRegExp("\""), "" );
	pppBind		= pppBind.replace( QRegExp("\""), "" );
	pppOptions	= pppOptions.replace( QRegExp("\""), "" );
}

void ISP::save()
{
	KConfig conf( fileName );
	conf.writeEntry( "I4L_PROFILENAME", "\"" + profileName + "\"" );
	conf.writeEntry( "I4L_USERNAME", "\"" + username + "\"" );
	conf.writeEntry( "I4L_SYSNAME", "\"" + sysname + "\"" );
	conf.writeEntry( "I4L_REMOTE_OUT", "\"" + remoteOut + "\"" );
	conf.writeEntry( "I4L_REMOTE_IN", "\"" + remoteIn + "\"" );
	conf.writeEntry( "I4L_LOCALMSN", "\"" + localMSN + "\"" );
	conf.writeEntry( "I4L_SECURE", "\"" + secure + "\"" );
	conf.writeEntry( "I4L_DIALMODE", "\"" + dialmode + "\"" );
	conf.writeEntry( "SLAVE", "\"" + slave + "\"" );
	conf.writeEntry( "DEVICE","\"" + device + "\"" );
	conf.writeEntry( "I4L_PPPBIND", "\"" + pppBind + "\"" );
	conf.writeEntry( "I4L_PPPOPTIONS", "\"" + pppOptions + "\"" );
}

void ISP::edit()
{
	ISPEdit dlg;
	dlg.profile->setText( profileName );
	dlg.number->setText( remoteOut );
	dlg.msn->setText( localMSN );
	if( dlg.exec() == QDialog::Accepted )
	{

	}
}



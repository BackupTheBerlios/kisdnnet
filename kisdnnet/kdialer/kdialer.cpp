/***************************************************************************
 *   Copyright (C) 2003 by Olaf Lueg                                       *
 *   olueg@olsd.de                                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#include "kdialer.h"
#include "info.h"
#include "dialindlg.h"
#include "csystemtray.h"

#include <qlineedit.h>
#include <qlabel.h>
#include <qregexp.h>

#include <kglobal.h>
#include <kiconloader.h>
#include <kpopupmenu.h>
#include <klocale.h>
#include <kmessagebox.h>
#include <kconfig.h>
#include <kprocess.h>
#include <kaction.h>

KDialer::KDialer(QWidget *parent, const char *name)
 : KMainWindow(parent, name, WDestructiveClose )
{
	info = new Info( this );
	setCentralWidget( info );
	tray = new CSystemTray( this );
	tray->show();
	connect( tray, SIGNAL( hangup() ), this, SLOT( disconnect() ) );
	connect( tray, SIGNAL( quitSelected() ), this, SLOT( close() ) );
	connected = FALSE;
}


KDialer::~KDialer()
{
}

void KDialer::init()
{
	KConfig conf( file );
	profile	= conf.readEntry( "I4L_PROFILENAME", "" );
	dialOut	= conf.readEntry( "I4L_REMOTE_OUT", "");
	username	= conf.readEntry("I4L_USERNAME","");

	profile		= profile.replace( QRegExp("\""),"");
	dialOut		= dialOut.replace( QRegExp("\""),"");
	username	= username.replace( QRegExp("\""),"");
	setCaption( profile );

}

void KDialer::dial()
{
	DialInDlg dlg;
	dlg.profile->setText( dlg.profile->text().arg( profile ) );
	dlg.number->setText( dialOut );
	dlg.user->setText( username );
	if( dlg.exec() == QDialog::Accepted ){
		tray->show();
		KProcess *proc = new KProcess;
		*proc << "/sbin/isdnctrl";
		*proc << "dial" << device;
		connect( proc, SIGNAL( receivedStderr( KProcess *, char *, int ) ),this, SLOT( received( KProcess *, char * , int ) ) );
		proc->start( KProcess::NotifyOnExit, KProcess::AllOutput );
		proc->resume();

		KProcess *proc1 = new KProcess;
		*proc1 << "cat" << "/dev/isdninfo";
		connect( proc1, SIGNAL( receivedStdout( KProcess *, char *, int ) ),this, SLOT( infoReceived( KProcess *, char * , int ) ) );
		proc1->start( KProcess::NotifyOnExit, KProcess::AllOutput );
		proc1->resume();

	}
	else{
		kapp->quit();
	}
}

void KDialer::disconnect()
{
	KProcess *proc = new KProcess;
	*proc << "/sbin/isdnctrl";
	*proc << "hangup" << device;
	connect( proc, SIGNAL( receivedStderr( KProcess *, char *, int ) ),this, SLOT( received( KProcess *, char * , int ) ) );
	proc->start( KProcess::NotifyOnExit, KProcess::AllOutput );
	proc->resume();
}

bool KDialer::queryClose( )
{
	if( connected ){
		return FALSE;
		hide();
	}
	else{
		return TRUE;
	}
}

void KDialer::close()
{
	if( connected )
		disconnect();
	else
		kapp->quit();
}

void KDialer::received( KProcess *proc, char *buff, int len )
{
	QString str = QString::fromLatin1(buff,len);
	KMessageBox::error( this, i18n("isdnctrl returns a message,\rThats not valid. Please report this message to\rMessage: %1").arg( str.latin1() ) );
	kapp->quit();
}

void KDialer::infoReceived( KProcess *proc, char *buff, int len )
{
	QString str = QString::fromLatin1(buff,len);
	if( str.contains( dialOut ) ){
		tray->setPixmap( KGlobal::instance() ->iconLoader() ->loadIcon( "connect_established" , KIcon::NoGroup , KIcon::SizeSmall ) );
		connected = TRUE;
		info->profile->setText( info->profile->text().arg( profile ) );
		// read transfer from /proc/net/dev

	}
	else{
		if( connected ){
			connected = FALSE;
			kapp->quit();
		}
		else
			connected = FALSE;
	}

}



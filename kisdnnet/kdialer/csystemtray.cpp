/***************************************************************************
 *   Copyright (C) 2003 by Olaf Lueg                                       *
 *   olueg@olsd.de                                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#include "csystemtray.h"
#include "kdialer.h"

#include <kaction.h>
#include <klocale.h>
#include <kglobal.h>
#include <kiconloader.h>
#include <kpopupmenu.h>
#include <qpixmap.h>

CSystemTray::CSystemTray(QWidget *parent, const char *name, WFlags f)
 : KSystemTray(parent, name )
{
	setPixmap( KGlobal::instance() ->iconLoader() ->loadIcon( "connect_no" , KIcon::NoGroup , KIcon::SizeSmall ) );
	preferences = new KAction(i18n("Disconnect"), "connect_no", 0, this, SLOT(contextHangup()), actionCollection() );
	preferences->plug( contextMenu() );
}


CSystemTray::~CSystemTray()
{
}

void CSystemTray::contextHangup()
{
	emit hangup();
}



/***************************************************************************
 *   Copyright (C) 2003 by Olaf Lueg                                       *
 *   olueg@olsd.de                                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 ***************************************************************************/
#include "card.h"
#include "kisdnnet.h"
#include "carddialog.h"
#include <qregexp.h>
#include <qlineedit.h>
#include <qcombobox.h>
#include <kconfig.h>

Card::Card(QObject *parent, const char *name)
 : QObject(parent, name)
{
}


Card::~Card()
{
}

void Card::read( const QString file )
{
	fileName = file;
	KConfig config( path + file );
	ID		= config.readEntry( "I4L_ID", "");
	type	= config.readEntry( "I4L_TYPE", "");
	irq		= config.readEntry( "I4L_IRQ", "");
	port	= config.readEntry( "I4L_PORT", "");
	membase	= config.readEntry( "I4L_MEMBASE", "");
	module	= config.readEntry( "I4L_MODULE", "");
	ID		= ID.replace( QRegExp("\""),"") ;
	type	= type.replace( QRegExp("\""),"") ;
	irq		= irq.replace( QRegExp("\""),"") ;
	port	= port.replace( QRegExp("\""),"") ;
	membase	= membase.replace( QRegExp("\""),"") ;
	module	= module.replace( QRegExp("\""),"") ;
}

void Card::edit()
{
	CardDialog dialog;
	dialog.ID->setText( ID );
	dialog.type->setCurrentItem( type.toUInt() -1 );
	dialog.irq->setText( irq );
	dialog.port->setText( port );
	dialog.membase->setText( membase );
	dialog.module->setText( module );
	if( dialog.exec() == QDialog::Accepted )
	{
		type	= dialog.type->currentText();
		type	= type.left(1);
		ID		= dialog.ID->text();
		irq		= dialog.irq->text();
		port	= dialog.port->text();
		membase	= dialog.membase->text();
		module	= dialog.module->text();
		save();
	}
}

void Card::save()
{
	KConfig config( path + fileName );
	config.writeEntry( "I4L_ID", "\"" + ID + "\"" );
	config.writeEntry( "I4L_TYPE", "\"" + type + "\"" );
	config.writeEntry( "I4L_IRQ", "\"" + irq + "\"" );
	config.writeEntry( "I4L_PORT", "\"" + port + "\"" );
	config.writeEntry( "I4L_MEMBASE", "\"" + membase + "\"" );
	config.writeEntry( "I4L_MODULE", "\"" + module + "\"" );
}




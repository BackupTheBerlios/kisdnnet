/*
 * Copyright (C) 2003 Olaf Lueg <olueg@olsd.de>
 */

#include "kisdnnetview.h"
#include "card.h"

#include <qpainter.h>
#include <qlayout.h>
#include <qiconview.h>
#include <qdir.h>
#include <qregexp.h>

#include <klocale.h>
#include <kglobal.h>
#include <kiconloader.h>
#include <kconfig.h>

KISDNnetView::KISDNnetView(QWidget *parent)
    : QWidget(parent),
      DCOPObject("KISDNnetIface")
{
    // setup our layout manager to automatically add our widgets
    QHBoxLayout *top_layout = new QHBoxLayout(this);
    top_layout->setAutoAdd(true);
	view = new QIconView( this );
	connect( view, SIGNAL( doubleClicked( QIconViewItem* ) ), parent, SLOT( itemDoubleClicked( QIconViewItem* ) ) );
}

KISDNnetView::~KISDNnetView()
{
}

QIconViewItem* KISDNnetView::addItem( const QString &name )
{
	return new QIconViewItem( view, name, KGlobal::instance() ->iconLoader() ->loadIcon( "identity" , KIcon::NoGroup , KIcon::SizeMedium ) );
}

#include "kisdnnetview.moc"

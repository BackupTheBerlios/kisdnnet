/*
 * Copyright (C) 2003 Olaf Lueg <olueg@olsd.de>
 */

#ifndef _KISDNNETVIEW_H_
#define _KISDNNETVIEW_H_

#include <qwidget.h>
#include <kisdnnetiface.h>


/**
 * This is the main view class for KISDNnet.  Most of the non-menu,
 * non-toolbar, and non-statusbar (e.g., non frame) GUI code should go
 * here.
 *
 * This kisdnnet uses an HTML component as an example.
 *
 * @short Main view
 * @author Olaf Lueg <olueg@olsd.de>
 * @version 0.1
 */
 class QIconView;
 class QIconViewItem;

class KISDNnetView : public QWidget, public KISDNnetIface
{
    Q_OBJECT
public:
    KISDNnetView(QWidget *parent);
    virtual ~KISDNnetView();
	QIconView *view;
	QIconViewItem* addItem( const QString &name );

};

#endif // _KISDNNETVIEW_H_

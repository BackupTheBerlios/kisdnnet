#include <qlayout.h>
#include <qlistview.h>
#include <qheader.h>
#include <qdir.h>
#include <qregexp.h>
#include <qpoint.h>
#include <qpopupmenu.h>

#include <klocale.h>
#include <kglobal.h>
#include <kiconloader.h>
#include <kconfig.h>
#include <kdesktopfile.h>
#include <kaction.h>

#include "kdialercontrol.h"
#include "kcmwidget.h"
#include "isp.h"
#include "ipppmap.h"

extern "C"
{

    KCModule *create_kdialercontrol(QWidget *parent, const char *name)
    {
        KGlobal::locale()->insertCatalogue("kdialercontrol");
        return new kdialercontrol(parent, "kdialercontrol");
    }
}

kdialercontrol::kdialercontrol(QWidget *parent, const char *name)
    : KCModule(parent, name)
{
    // place widgets here
	profiles.setAutoDelete( TRUE );
	ipppMap = 0;
	QVBoxLayout *layout = new QVBoxLayout( this );
	widget = new KCMWidget( this, "Internet" );
	widget->lv->header()->hide();
    load();
	layout->addWidget( widget);
	popupMenu = new QPopupMenu( widget );
	ispNew = new KAction(i18n("&New Connection"), "monitorin_section", 0, this, SLOT(newISP() ) );
	ispNew->plug( popupMenu );
	connect( widget->lv, SIGNAL( doubleClicked( QListViewItem * ) ), this, SLOT( doubleClicked( QListViewItem * ) ) );
	connect( widget->lv, SIGNAL( currentChanged( QListViewItem * ) ), this, SLOT( currentChanged( QListViewItem * ) ) );
	connect( widget->lv, SIGNAL( contextMenuRequested( QListViewItem *, const QPoint &, int ) ), this, SLOT( contextMenuRequested( QListViewItem *, const QPoint &, int ) ) );
};


kdialercontrol::~kdialercontrol()
{
}


void kdialercontrol::load()
{
    // insert your loading code here...
	if( ipppMap != 0 )
		delete ipppMap;
	profiles.clear();
	widget->lv->clear();
	ipppMap = new IPPPMap( this );
	QDir dir( "/etc/isdn/profile/link", "*" );
    for ( uint i = 0; i < dir.count(); i++ ) {
		if( dir[i] == "." || dir[i] == ".." || dir[i].right(3) == "bak" ){
		}
		else{
			KConfig conf( "/etc/isdn/profile/link/" +dir[i]);
			QString name = conf.readEntry("I4L_PROFILENAME","");
			name = name.replace( QRegExp("\""), "" );
			QListViewItem *item = new QListViewItem( widget->lv, name );
			item->setPixmap(0, KGlobal::instance() ->iconLoader() ->loadIcon( "kppp" , KIcon::NoGroup , KIcon::SizeSmall ) );
			ISP *isp = new ISP( this, name, "/etc/isdn/profile/link/" +dir[i] );
			isp->file = dir[i];
			isp->item = item;
        	profiles.insert( item, isp );
		}
	}
}


void kdialercontrol::defaults()
{
    // insert your default settings code here...
    emit changed(true);
}


void kdialercontrol::save()
{
    // insert your saving code here...
    emit changed(true);
}


int kdialercontrol::buttons()
{
    return KCModule::Default|KCModule::Apply|KCModule::Help;
}


void kdialercontrol::configChanged()
{
    // insert your saving code here...
    emit changed(true);
}


QString kdialercontrol::quickHelp() const
{
    return i18n("Helpful information about the kdialercontrol module.");
}

/*! A item in the listview has double clicked, open edit isp dialog
*/
void kdialercontrol::doubleClicked( QListViewItem *item )
{
	ISP *isp = profiles.find( item );
	isp->edit();
	KDesktopFile *df = new KDesktopFile( "Internet/Internet Connection/" + isp->file + ".desktop", FALSE, "apps" );
	df->setGroup( "Desktop Entry" );
	df->writeEntry( "Name", isp->profileName );
	df->writeEntry( "Icon", "monitoring_section");
	df->writeEntry( "Path", "");
	df->writeEntry( "Terminal", "0");
	df->writeEntry( "TerminalOptions", "");
	df->writeEntry( "Type", "Application");
	df->writeEntry( "X-KDE-SubstituteUID","false");
	df->writeEntry( "Exec", "kdialer " + ipppMap->getDevice( isp->file ) + " " + isp->fileName );
	delete df;
}

/*! update the infos
*/
void kdialercontrol::currentChanged( QListViewItem *item )
{

}

void kdialercontrol::contextMenuRequested( QListViewItem *item, const QPoint &pos, int )
{
	popupMenu->popup( pos );
}

void kdialercontrol::newISP()
{

}

void kdialercontrol::editISP()
{
	QListViewItem *item = widget->lv->currentItem();
	if( item ){
		ISP *isp = profiles.find( item );
		isp->edit();
	}
}

void kdialercontrol::delISP()
{

}


#include "kdialercontrol.moc"

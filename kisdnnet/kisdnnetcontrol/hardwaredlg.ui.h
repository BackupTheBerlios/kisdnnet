/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
#include <kstddirs.h>
#include <kconfig.h>
#include <kiconloader.h>
#include <kglobal.h>

#include <qregexp.h>
#include <qdir.h>

void HardwareDlg::init()
{
	KStandardDirs d;
	QString str = d.findResource( "data", "kisdnnet/cardpool/avm_classic.conf" ).latin1(), desc;
	str = str.replace( QRegExp("avm_classic.conf"),"");
	QDir dir( str );
	  for ( uint i = 0; i < dir.count(); i++ ) {
		if( dir[i].right(4) == "conf" ){
			KConfig config( str + dir[i].latin1() );
			config.setGroup("Global");
			desc = config.readEntry( "Description", "" );
			QListViewItem *item = new QListViewItem( lv, desc );
			item->setPixmap( 0, KGlobal::instance() ->iconLoader() ->loadIcon( "kcmpci" , KIcon::NoGroup , KIcon::SizeSmall ));
		}
	}
}

#include <qlayout.h>
#include <qdir.h>
#include <qpushbutton.h>
#include <qregexp.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qlistview.h>
#include <qpixmap.h>


#include <klocale.h>
#include <kglobal.h>
#include <kstandarddirs.h>
#include <kdebug.h>
#include <kconfig.h>
#include <ksimpleconfig.h>
#include <kiconloader.h>
#include <kprocess.h>
#include <kmessagebox.h>

#include "kisdnnetcontrol.h"
#include "hardwaredlg.h"
#include "kcmwidget.h"

extern "C"
{

    KCModule *create_kisdnnetcontrol(QWidget *parent, const char *name)
    {
        KGlobal::locale()->insertCatalogue("kisdnnetcontrol");
        return new kisdnnetcontrol(parent, "kisdnnetcontrol");
    }
}

kisdnnetcontrol::kisdnnetcontrol(QWidget *parent, const char *name)
    : KCModule(parent, name)
{
    // place widgets here
	QVBoxLayout *layout = new QVBoxLayout( this );
	widget = new KCMWidget( this, "ISDN-CONTROL");
	widget->pic->setPixmap( KGlobal::instance() ->iconLoader() ->loadIcon( "kcmpci" , KIcon::NoGroup , KIcon::SizeMedium ));
	connect( widget->editBtn, SIGNAL( clicked() ), this, SLOT( editClicked() ) );
	QLabel *l = new QLabel( i18n("Please wait..."),this);
	layout->addWidget( l );
    load();
	delete l;
	layout->addWidget( widget );
};


kisdnnetcontrol::~kisdnnetcontrol()
{
}


void kisdnnetcontrol::load()
{
    // insert your loading code here...
	widget->lv->clear();
	QString rName, rValue;
	configFile = findCardConfig();
	if( configFile.isEmpty() ){
		widget->cardInfo->setText( i18n("No installed card found!") );
		return;
	}
	KConfig c_config( configFile );
	type = c_config.readEntry( "I4L_TYPE", "");
	type = type.replace( QRegExp("\""), "") ;
	resourceFile = findResourceFile( );
	if( resourceFile.isEmpty() ){
		widget->cardInfo->setText( i18n("Your installed card is not in the database!") );
		return;
	}
	KConfig r_config( resourceFile );
	r_config.setGroup( "Global");
	widget->cardInfo->setText( r_config.readEntry( "Description","")  );
	QStringList list = r_config.readListEntry( "Resources");
	for( uint i =0; i < list.count(); i++ ){
		r_config.setGroup( list[i] );
		rName = r_config.readEntry( "I4L" );
		rValue = c_config.readEntry( rName );
		rValue = rValue.replace( QRegExp("\""), "");
		rName = r_config.readEntry( "Name" );
		QListViewItem *item =  new QListViewItem( widget->lv, rName, rValue );
		item->setPixmap(0, KGlobal::instance() ->iconLoader() ->loadIcon( "kcmpci" , KIcon::NoGroup , KIcon::SizeSmall ));
		item->setRenameEnabled( 1, TRUE );
		connect( widget->lv, SIGNAL( itemRenamed( QListViewItem *, int ) ), this, SLOT( valueChanged( QListViewItem *, int ) ));
	}
}

QString kisdnnetcontrol::findResourceFile( )
{
	KStandardDirs d;
	QString str = d.findResource( "data", "kisdnnet/cardpool/avm_classic.conf" ).latin1(), _type ;
	str = str.replace( QRegExp("avm_classic.conf"),"");
	QDir dir( str );
	  for ( uint i = 0; i < dir.count(); i++ ) {
		if( dir[i].right(4) == "conf" ){
			KConfig config( str + dir[i].latin1() );
			config.setGroup("Global");
			_type = config.readEntry( "Card Type", "" );
			if( type == _type ){
				return str + dir[i];
			}
		}
	}
	return "";
}

QString kisdnnetcontrol::findCardConfig()
{
	// check for card config file
	QDir dir( widget->path->text().latin1() );
	for ( uint i = 0; i < dir.count(); i++ ) {
		if( dir[i].right(1) != "." && dir[i].right(2) != ".." && dir[i].right(3) != "bak" ){
			return widget->path->text().latin1() + dir[i];
		}
	}
	return "";
}


void kisdnnetcontrol::defaults()
{
    // insert your default settings code here...
    emit changed(true);
}


void kisdnnetcontrol::save()
{
    // insert your saving code here...
	if( createConfig() ){
		KProcess *proc = new KProcess;
		*proc << "/etc/init.d/isdn4linux" << "restart";
		//*proc << "restart";
		connect( proc, SIGNAL( receivedStderr( KProcess *, char *, int ) ),this, SLOT( receivedError( KProcess *, char * , int ) ) );
		connect( proc, SIGNAL( receivedStdout( KProcess *, char *, int ) ),this, SLOT( infoReceived( KProcess *, char * , int ) ) );
		proc->start( KProcess::NotifyOnExit, KProcess::AllOutput );
	}
	else{
		KMessageBox::error( this, i18n("Cannot create the ISDN config file!") );
	}
		//proc->resume();
    //emit changed(true);
}

void kisdnnetcontrol::receivedError( KProcess *, char *buff, int len )
{
	QString str =  QString::fromLatin1(buff,len);
	KMessageBox::information( this, str,"ISDN error" );
}

void kisdnnetcontrol::infoReceived( KProcess *, char *buff, int len )
{
	QString str =  QString::fromLatin1(buff,len);
	//KMessageBox::information( this, str,"bla" );
}


int kisdnnetcontrol::buttons()
{
    return KCModule::Default|KCModule::Apply|KCModule::Help;
}


void kisdnnetcontrol::configChanged()
{
    // insert your saving code here...
    emit changed(true);
}


QString kisdnnetcontrol::quickHelp() const
{
    return i18n("Helpful information about the kisdnnetcontrol module.");
}

void kisdnnetcontrol::editClicked()
{
	HardwareDlg dlg;
	dlg.exec();
}

bool kisdnnetcontrol::createConfig()
{
	QString name, value, i4l_name;
	KSimpleConfig c_config( configFile );
	KConfig r_config( resourceFile );
	r_config.setGroup( "Global" );
	QStringList list = r_config.readListEntry( "Resources");
	c_config.writeEntry( "I4L_ID", "\"" + r_config.readEntry( "Card ID" ) + "\"" );
	c_config.writeEntry( "I4L_TYPE", "\"" + r_config.readEntry( "Card Type" ) + "\"" );
	c_config.writeEntry( "I4L_MODULE", "\"" + r_config.readEntry( "Module" ) + "\"" );
	// write resources
	for( uint i = 0; i < list.count(); i++ ){
		r_config.setGroup( list[i] );
		i4l_name	= r_config.readEntry( "I4L" );
		name		= r_config.readEntry( "Name" );
		QListViewItem *item = widget->lv->findItem( name, 0 );
		if( item ){
			value = item->text( 1 );
			c_config.writeEntry( i4l_name, "\"" + value + "\"" );
		}
		else
			return false;
	}
	return TRUE;
}

void kisdnnetcontrol::valueChanged( QListViewItem *item, int )
{
	if( item->text(1).isEmpty() )
		emit changed( FALSE );
	else
		emit changed( TRUE );
}





#include "kisdnnetcontrol.moc"

#include <qlayout.h>
#include <qdir.h>
#include <qpushbutton.h>


#include <klocale.h>
#include <kglobal.h>
#include <kstandarddirs.h>
#include <kdebug.h>

#include "kisdnnetcontrol.h"
#include "hardwaredlg.h"
#include "kcmwidget.h"

kisdnnetcontrol::kisdnnetcontrol(QWidget *parent, const char *name)
    : KCModule(parent, name)
{
    // place widgets here
	QVBoxLayout *layout = new QVBoxLayout( this );
	widget = new KCMWidget( this, "ISDN-CONTROL");
	layout->addWidget( widget );
	connect( widget->editBtn, SIGNAL( clicked() ), this, SLOT( editClicked() ) );

    load();
};


kisdnnetcontrol::~kisdnnetcontrol()
{
}


void kisdnnetcontrol::load()
{
    // insert your loading code here...
}


void kisdnnetcontrol::defaults()
{
    // insert your default settings code here...
    emit changed(true);
}


void kisdnnetcontrol::save()
{
    // insert your saving code here...
    emit changed(true);
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
	KStandardDirs d;
	QString str = d.findResource( "data", "kisdnnet/cardpool/avm_classic.conf" ).latin1() );
	str = str.replace( QRegExp("avm_classic.conf"),"");
	QDir dir( str );
	  for ( uint i = 0; i < dir.count(); i++ ) {
		if( dir[i].right(4) == "conf" ){

		}
	}


}


extern "C"
{

    KCModule *create_kisdnnetcontrol(QWidget *parent, const char *name)
    {
        KGlobal::locale()->insertCatalogue("kisdnnetcontrol");
        return new kisdnnetcontrol(parent, "kisdnnetcontrol");
    }
}

#include "kisdnnetcontrol.moc"

/*
 * Copyright (C) 2003 Olaf Lueg <olueg@olsd.de>
 */

#include "kisdnnet.h"
#include "pref.h"
#include "isp.h"
#include "ispwizard.h"
#include "ipppmap.h"
#include "card.h"

#include <qdragobject.h>
#include <kprinter.h>
#include <qpainter.h>
#include <qpaintdevicemetrics.h>
#include <qdir.h>
#include <qiconview.h>
#include <qregexp.h>

#include <kglobal.h>
#include <klocale.h>
#include <kiconloader.h>
#include <kmenubar.h>
#include <kstatusbar.h>
#include <kkeydialog.h>
#include <kaccel.h>
#include <kio/netaccess.h>
#include <kfiledialog.h>
#include <kconfig.h>
#include <kurl.h>
#include <kurlrequesterdlg.h>
#include <kmessagebox.h>
#include <kprocess.h>

#include <kedittoolbar.h>

#include <kstdaccel.h>
#include <kaction.h>
#include <kstdaction.h>

KISDNnet::KISDNnet()
    : KMainWindow( 0, "KISDNnet" ),
      m_view(new KISDNnetView(this))
{
    // accept dnd
    setAcceptDrops(true);

    // tell the KMainWindow that this is indeed the main widget
    setCentralWidget(m_view);

    // then, setup our actions
    setupActions();

    // and a status bar
    statusBar()->show();

    // apply the saved mainwindow settings, if any, and ask the mainwindow
    // to automatically save settings if changed: window size, toolbar
    // position, icon size, etc.
    setAutoSaveSettings();

    // allow the view to change the statusbar and caption
    connect(m_view, SIGNAL(signalChangeStatusbar(const QString&)),
            this,   SLOT(changeStatusbar(const QString&)));
    connect(m_view, SIGNAL(signalChangeCaption(const QString&)),
            this,   SLOT(changeCaption(const QString&)));
	readProfiles();

}

KISDNnet::~KISDNnet()
{
	profiles.clear();
}

void KISDNnet::setupActions()
{
    KStdAction::quit(kapp, SLOT(quit()), actionCollection());

    m_toolbarAction = KStdAction::showToolbar(this, SLOT(optionsShowToolbar()), actionCollection());
    m_statusbarAction = KStdAction::showStatusbar(this, SLOT(optionsShowStatusbar()), actionCollection());

    KStdAction::keyBindings(this, SLOT(optionsConfigureKeys()), actionCollection());
    KStdAction::configureToolbars(this, SLOT(optionsConfigureToolbars()), actionCollection());
    KStdAction::preferences(this, SLOT(optionsPreferences()), actionCollection());

    // this doesn't do anything useful.  it's just here to illustrate
    // how to insert a custom menu and menu item
    m_hardware	= new KAction(i18n("&ISDN Hardware"), "hwinfo", 0, this, SLOT(editHardware()), actionCollection(), "hardware");
	m_newISP	= new KAction(i18n("&New Provider"), "kppp", 0, this, SLOT(newISP()), actionCollection(), "newISP");
    createGUI();
}

void KISDNnet::saveProperties(KConfig *config)
{
    // the 'config' object points to the session managed
    // config file.  anything you write here will be available
    // later when this app is restored

}

void KISDNnet::readProperties(KConfig *config)
{
    // the 'config' object points to the session managed
    // config file.  this function is automatically called whenever
    // the app is being restored.  read in here whatever you wrote
    // in 'saveProperties'

}

void KISDNnet::dragEnterEvent(QDragEnterEvent *event)
{
    // accept uri drops only
    event->accept(QUriDrag::canDecode(event));
}

void KISDNnet::dropEvent(QDropEvent *event)
{
    // this is a very simplistic implementation of a drop event.  we
    // will only accept a dropped URL.  the Qt dnd code can do *much*
    // much more, so please read the docs there
    QStrList uri;

    // see if we can decode a URI.. if not, just ignore it
    if (QUriDrag::decode(event, uri))
    {
        // okay, we have a URI.. process it
        QString url, target;
        url = uri.first();

        // load in the file
    }
}

void KISDNnet::fileNew()
{
    // this slot is called whenever the File->New menu is selected,
    // the New shortcut is pressed (usually CTRL+N) or the New toolbar
    // button is clicked

    // create a new window
    (new KISDNnet)->show();
}

void KISDNnet::fileOpen()
{
}

void KISDNnet::fileSave()
{
}

void KISDNnet::fileSaveAs()
{
    // this slot is called whenever the File->Save As menu is selected,
    KURL file_url = KFileDialog::getSaveURL();
    if (!file_url.isEmpty() && !file_url.isMalformed())
    {
        // save your info, here
    }
}


void KISDNnet::optionsShowToolbar()
{
    // this is all very cut and paste code for showing/hiding the
    // toolbar
    if (m_toolbarAction->isChecked())
        toolBar()->show();
    else
        toolBar()->hide();
}

void KISDNnet::optionsShowStatusbar()
{
    // this is all very cut and paste code for showing/hiding the
    // statusbar
    if (m_statusbarAction->isChecked())
        statusBar()->show();
    else
        statusBar()->hide();
}

void KISDNnet::optionsConfigureKeys()
{
    KKeyDialog::configureKeys(actionCollection(), "kisdnnetui.rc");
}

void KISDNnet::optionsConfigureToolbars()
{
    // use the standard toolbar editor
#if defined(KDE_MAKE_VERSION)
# if KDE_VERSION >= KDE_MAKE_VERSION(3,1,0)
    saveMainWindowSettings(KGlobal::config(), autoSaveGroup());
# else
    saveMainWindowSettings(KGlobal::config());
# endif
#else
    saveMainWindowSettings(KGlobal::config());
#endif
}

void KISDNnet::newToolbarConfig()
{
    // this slot is called when user clicks "Ok" or "Apply" in the toolbar editor.
    // recreate our GUI, and re-apply the settings (e.g. "text under icons", etc.)
    createGUI();

#if defined(KDE_MAKE_VERSION)
# if KDE_VERSION >= KDE_MAKE_VERSION(3,1,0)
    applyMainWindowSettings(KGlobal::config(), autoSaveGroup());
# else
    applyMainWindowSettings(KGlobal::config());
# endif
#else
    applyMainWindowSettings(KGlobal::config());
#endif
}

void KISDNnet::optionsPreferences()
{
    // popup some sort of preference dialog, here
    KISDNnetPreferences dlg;
    if (dlg.exec())
    {
        // redo your settings
    }
}

void KISDNnet::changeStatusbar(const QString& text)
{
    // display the text on the statusbar
    statusBar()->message(text);
}

void KISDNnet::changeCaption(const QString& text)
{
    // display the text on the caption
    setCaption(text);
}

void KISDNnet::readProfiles()
{
	card = new Card( this );
	card->read( "mycard" );
	ipppMap = new IPPPMap( this );
	QDir dir( "/etc/isdn/profile/link", "*" );
    for ( uint i = 0; i < dir.count(); i++ ) {
		if( dir[i] == "." || dir[i] == ".." || dir[i].right(3) == "bak" ){
			//do nothing
		}else
		{
			KConfig conf( "/etc/isdn/profile/link/" +dir[i]);
			QString name = conf.readEntry("I4L_PROFILENAME","");
			name = name.replace( QRegExp("\""), "" );
			ISP *isp = new ISP( this, name, "/etc/isdn/profile/link/" +dir[i] );
			isp->file = dir[i];
			isp->item = m_view->addItem( name );
        	profiles.insert( name, isp );
		}
    }
}

void KISDNnet::itemDoubleClicked( QIconViewItem *item )
{
	ISP *isp = profiles.find( item->text() );
	if( isp ){
		//isp->edit();
		QString device = ipppMap->getDevice( isp->file );
		debug( device.latin1() );
		if( device != QString::null ){

		}
	}
}

void KISDNnet::newISP()
{
	ISPWizard wizard;
	wizard.exec();
}

void KISDNnet::editHardware()
{
	card->edit();
}
#include "kisdnnet.moc"

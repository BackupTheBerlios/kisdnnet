/*
 * Copyright (C) 2003 Olaf Lueg <olueg@olsd.de>
 */

#include "kdialer.h"
#include <kapplication.h>
#include <dcopclient.h>
#include <kaboutdata.h>
#include <kcmdlineargs.h>
#include <klocale.h>
#include <kmessagebox.h>

static const char *description =
    I18N_NOOP("A KDE ISDN Dialer");

static const char *version = "0.1";



static KCmdLineOptions options[] =
{
    { "+Device", I18N_NOOP( "Device to open." ), 0 },
	{ "+Profile Path", I18N_NOOP( "Profile to open" ), 0 },
    { 0, 0, 0 }
};

int main(int argc, char **argv)
{
    KAboutData about("kdialer", I18N_NOOP("KDialer"), version, description,
                     KAboutData::License_GPL, "(C) 2003 Olaf Lueg", 0, 0, "olueg@olsd.de");
    about.addAuthor( "Olaf Lueg", 0, "olueg@olsd.de" );
    KCmdLineArgs::init(argc, argv, &about);
    KCmdLineArgs::addCmdLineOptions(options);
    KApplication app;

    // register ourselves as a dcop client
    app.dcopClient()->registerAs(app.name(), false);

    // see if we are starting with session management
    if (app.isRestored())
    {
//        RESTORE(KDialer);
    }
    else
    {
        // no session.. just start up normally
        KCmdLineArgs *args = KCmdLineArgs::parsedArgs();
        if (args->count() != 2 )
        {
           KMessageBox::error( 0, "You cannot call this without any parameters\nCall kdialer --help" );
		   exit(-1);
        }
        else
        {
			KDialer *widget = new KDialer;
			widget->hide();
			widget->device = args->arg(0);
			widget->file = args->arg(1);
			widget->init();
			widget->dial();
        }
        args->clear();
    }

    return app.exec();
}

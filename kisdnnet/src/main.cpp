/*
 * Copyright (C) 2003 Olaf Lueg <olueg@olsd.de>
 */

#include "kisdnnet.h"
#include <kapplication.h>
#include <dcopclient.h>
#include <kaboutdata.h>
#include <kcmdlineargs.h>
#include <klocale.h>

static const char *description =
    I18N_NOOP("A KDE Application");

static const char *version = "0.1";



static KCmdLineOptions options[] =
{
    { "+[URL]", I18N_NOOP( "Document to open." ), 0 },
    { 0, 0, 0 }
};

int main(int argc, char **argv)
{
    KAboutData about("kisdnnet", I18N_NOOP("KISDNnet"), version, description,
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
        RESTORE(KISDNnet);
    }
    else
    {
        // no session.. just start up normally
        KCmdLineArgs *args = KCmdLineArgs::parsedArgs();
        if (args->count() == 0)
        {
            KISDNnet *widget = new KISDNnet;
            widget->show();
        }
        else
        {
            int i = 0;
            for (; i < args->count(); i++)
            {
                KISDNnet *widget = new KISDNnet;
                widget->show();
            }
        }
        args->clear();
    }

    return app.exec();
}

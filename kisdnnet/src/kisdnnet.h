/*
 * Copyright (C) 2003 Olaf Lueg <olueg@olsd.de>
 */

#ifndef _KISDNNET_H_
#define _KISDNNET_H_

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

static char *path =  "/etc/isdn/profile/card/";
static char *mapPath = "/etc/isdn/profile/";

#include <kapplication.h>
#include <kmainwindow.h>
#include <qdict.h>

#include "kisdnnetview.h"

class KToggleAction;
class KAction;
class ISP;
class IPPPMap;
class Card;

/**
 * This class serves as the main window for KISDNnet.  It handles the
 * menus, toolbars, and status bars.
 *
 * @short Main window class
 * @author $AUTHOR <$EMAIL>
 * @version $APP_VERSION
 */
class KISDNnet : public KMainWindow
{
    Q_OBJECT
public:
    /**
     * Default Constructor
     */
    KISDNnet();

    /**
     * Default Destructor
     */
    virtual ~KISDNnet();
protected:
	IPPPMap *ipppMap;
	Card *card;

protected:
    /**
     * Overridden virtuals for Qt drag 'n drop (XDND)
     */
    virtual void dragEnterEvent(QDragEnterEvent *event);
    virtual void dropEvent(QDropEvent *event);

protected:
    /**
     * This function is called when it is time for the app to save its
     * properties for session management purposes.
     */
    void saveProperties(KConfig *);

    /**
     * This function is called when this app is restored.  The KConfig
     * object points to the session management config file that was saved
     * with @ref saveProperties
     */
    void readProperties(KConfig *);

public slots:
	void itemDoubleClicked( QIconViewItem *item );
private slots:
    void fileNew();
    void fileOpen();
    void fileSave();
    void fileSaveAs();
    void optionsShowToolbar();
    void optionsShowStatusbar();
    void optionsConfigureKeys();
    void optionsConfigureToolbars();
    void optionsPreferences();
    void newToolbarConfig();

    void changeStatusbar(const QString& text);
    void changeCaption(const QString& text);

	void newISP();
	void editHardware();

private:
    void setupAccel();
    void setupActions();
	void readProfiles();

private:
    KISDNnetView *m_view;
	KAction *m_hardware;
	KAction *m_newISP;
    KToggleAction *m_toolbarAction;
    KToggleAction *m_statusbarAction;
	QDict<ISP>profiles;
};

#endif // _KISDNNET_H_

#ifndef _KDIALERCONTROL_H_
#define _KDIALERCONTROL_H_

#include <kcmodule.h>
#include <kaboutdata.h>

#include <qptrdict.h>

class KCMWidget;
class QListViewItem;
class QPoint;
class ISP;
class IPPPMap;
class KAction;
class QPopupMenu;

class kdialercontrol: public KCModule
{
    Q_OBJECT

public:
    kdialercontrol( QWidget *parent=0, const char *name=0 );
    ~kdialercontrol();

    virtual void load();
    virtual void save();
    virtual void defaults();
    virtual int buttons();
    virtual QString quickHelp() const;
    virtual const KAboutData *aboutData()
    { return myAboutData; };

public slots:
    void configChanged();
	void doubleClicked( QListViewItem *item );
	void currentChanged( QListViewItem *item );
	void contextMenuRequested( QListViewItem *item, const QPoint &pos, int );
	void newISP();
	void editISP();
	void delISP();

private:
	KAboutData *myAboutData;
	KCMWidget *widget;
	IPPPMap *ipppMap;
	QPtrDict<ISP>profiles;
	QPopupMenu *popupMenu;
	KAction *ispNew;
	KAction *ispEdit;
	KAction *ispDel;
};

#endif

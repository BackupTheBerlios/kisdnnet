#ifndef _KISDNNETCONTROL_H_
#define _KISDNNETCONTROL_H_

#include <kcmodule.h>
#include <kaboutdata.h>

class KCMWidget;
class QListViewItem;

class kisdnnetcontrol: public KCModule
{
    Q_OBJECT

public:
    kisdnnetcontrol( QWidget *parent=0, const char *name=0 );
    ~kisdnnetcontrol();

    virtual void load();
    virtual void save();
    virtual void defaults();
    virtual int buttons();
    virtual QString quickHelp() const;
    virtual const KAboutData *aboutData()
    { return myAboutData; };
protected:
	QString findResourceFile( );
	QString findCardConfig();
	bool createConfig();

public slots:
    void configChanged();
	void editClicked();
	void receivedError( KProcess *, char *buff, int len );
	void infoReceived( KProcess *, char *buff, int len );
	void valueChanged( QListViewItem *item, int );

private:
      KAboutData *myAboutData;
	  KCMWidget *widget;
	  QString type;
	  QString configFile;
	  QString resourceFile;
};

#endif

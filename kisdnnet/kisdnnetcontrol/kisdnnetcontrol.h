#ifndef _KISDNNETCONTROL_H_
#define _KISDNNETCONTROL_H_

#include <kcmodule.h>
#include <kaboutdata.h>

class KCMWidget;

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

public slots:
    void configChanged();
	void editClicked();

private:
      KAboutData *myAboutData;
	  KCMWidget *widget;
};

#endif

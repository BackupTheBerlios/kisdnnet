/*
 * Copyright (C) 2003 Olaf Lueg <olueg@olsd.de>
 */

#ifndef _KISDNNETPREF_H_
#define _KISDNNETPREF_H_

#include <kdialogbase.h>
#include <qframe.h>

class KISDNnetPrefPageOne;
class KISDNnetPrefPageTwo;

class KISDNnetPreferences : public KDialogBase
{
    Q_OBJECT
public:
    KISDNnetPreferences();

private:
    KISDNnetPrefPageOne *m_pageOne;
    KISDNnetPrefPageTwo *m_pageTwo;
};

class KISDNnetPrefPageOne : public QFrame
{
    Q_OBJECT
public:
    KISDNnetPrefPageOne(QWidget *parent = 0);
};

class KISDNnetPrefPageTwo : public QFrame
{
    Q_OBJECT
public:
    KISDNnetPrefPageTwo(QWidget *parent = 0);
};

#endif // _KISDNNETPREF_H_

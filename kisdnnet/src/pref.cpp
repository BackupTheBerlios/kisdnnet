/*
 * Copyright (C) 2003 Olaf Lueg <olueg@olsd.de>
 */

#include "pref.h"

#include <klocale.h>

#include <qlayout.h>
#include <qlabel.h>

KISDNnetPreferences::KISDNnetPreferences()
    : KDialogBase(TreeList, i18n("KISDNnet Preferences"),
                  Help|Default|Ok|Apply|Cancel, Ok)
{
    // this is the base class for your preferences dialog.  it is now
    // a Treelist dialog.. but there are a number of other
    // possibilities (including Tab, Swallow, and just Plain)
    QFrame *frame;
    frame = addPage(i18n("First Page"), i18n("Page One Options"));
    m_pageOne = new KISDNnetPrefPageOne(frame);

    frame = addPage(i18n("Second Page"), i18n("Page Two Options"));
    m_pageTwo = new KISDNnetPrefPageTwo(frame);
}

KISDNnetPrefPageOne::KISDNnetPrefPageOne(QWidget *parent)
    : QFrame(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setAutoAdd(true);

    new QLabel(i18n("Add something here"), this);
}

KISDNnetPrefPageTwo::KISDNnetPrefPageTwo(QWidget *parent)
    : QFrame(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setAutoAdd(true);

    new QLabel(i18n("Add something here"), this);
}
#include "pref.moc"

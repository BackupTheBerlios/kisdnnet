INCLUDES    = $(all_includes)
METASOURCES = AUTO

# Install this plugin in the KDE modules directory
kde_module_LTLIBRARIES = kcm_kisdnnetcontrol.la

kcm_kisdnnetcontrol_la_SOURCES = kisdnnetcontrol.cpp hardwaredlg.ui kcmwidget.ui hardwaredlg.ui.h
kcm_kisdnnetcontrol_la_LIBADD = $(XTESTLIB) $(LIB_KIO)
kcm_kisdnnetcontrol_la_LDFLAGS = -module -avoid-version $(all_libraries) -no-undefined

kisdnnetcontrol_DATA = kisdnnetcontrol.desktop
kisdnnetcontroldir = $(kde_appsdir)/Settings/Peripherals

messages: rc.cpp
	$(XGETTEXT) *.cpp -o $(podir)/kisdnnetcontrol.pot

INCLUDES    = $(all_includes)
METASOURCES = AUTO

# Install this plugin in the KDE modules directory
kde_module_LTLIBRARIES = kcm_kdialercontrol.la

kcm_kdialercontrol_la_SOURCES = kdialercontrol.cpp kcmwidget.ui ipppmap.cpp ipppmap.h isp.cpp ispedit.ui isp.h ispwizard.ui
kcm_kdialercontrol_la_LIBADD = $(XTESTLIB) $(LIB_KIO) 
kcm_kdialercontrol_la_LDFLAGS = -module -avoid-version $(all_libraries) -no-undefined

kdialercontrol_DATA = kdialercontrol.desktop
kdialercontroldir = $(kde_appsdir)/Settings/Network

messages: rc.cpp
	$(XGETTEXT) *.cpp -o $(podir)/kdialercontrol.pot

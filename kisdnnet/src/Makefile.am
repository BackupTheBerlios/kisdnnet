## Makefile.am for kisdnnet

# this is the program that gets installed.  it's name is used for all
# of the other Makefile.am variables
bin_PROGRAMS = kisdnnet

# set the include path for X, qt and KDE
INCLUDES         = $(all_includes)

# the library search path. 
kisdnnet_LDFLAGS = $(KDE_RPATH) $(all_libraries)

# the libraries to link against.
kisdnnet_LDADD   = $(LIB_KFILE) $(LIB_KDEPRINT)

# which sources should be compiled for kisdnnet
kisdnnet_SOURCES = main.cpp kisdnnet.cpp kisdnnetview.cpp 		      pref.cpp kisdnnetiface.skel isp.h isp.cpp card.h card.cpp carddialog.ui ispedit.ui ipppmap.h ipppmap.cpp ispwizard.ui

# these are the headers for your project
noinst_HEADERS = kisdnnet.h kisdnnetview.h pref.h

# let automoc handle all of the meta source files (moc)
METASOURCES = AUTO

messages: rc.cpp
	$(XGETTEXT) *.cpp -o $(podir)/kisdnnet.pot

KDE_ICON = kisdnnet

# this is where the kdelnk file will go 
kdelnkdir   = $(kde_appsdir)/Utilities
kdelnk_DATA = kisdnnet.desktop

# this is where the XML-GUI resource file goes
rcdir = $(kde_datadir)/kisdnnet
rc_DATA = kisdnnetui.rc

INCLUDES = $(all_includes)
bin_PROGRAMS =  kdialer
kdialer_LDFLAGS = $(KDE_RPATH) $(all_libraries)
kdialer_LDADD   = $(LIB_KFILE) $(LIB_KDEPRINT)
kdialer_SOURCES = main.cpp info.ui dialindlg.ui kdialer.cpp csystemtray.cpp

# let automoc handle all of the meta source files (moc)
METASOURCES = AUTO

messages: rc.cpp
	$(XGETTEXT) *.cpp -o $(podir)/kisdnnet.pot

KDE_ICON = kisdnnet


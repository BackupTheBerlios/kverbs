INCLUDES = $(all_includes)

SUBDIRS = .

kde_module_LTLIBRARIES = kverbs_latin.la

kverbs_latin_la_SOURCES = kverbs_latin.cpp
kverbs_latin_la_LIBADD = $(LIB_QT) $(LIB_KDECORE) $(LIB_KDEUI)
kverbs_latin_la_LDFLAGS = $(all_libraries) $(KDE_PLUGIN) -module
METASOURCES = AUTO

lnkdir                    = $(kde_datadir)/kverbs
lnk_DATA                  = latin.desktop

INCLUDES = $(all_includes)

SUBDIRS = .

kde_module_LTLIBRARIES = kverbs_english.la

kverbs_english_la_SOURCES = kverbs_english.cpp
kverbs_english_la_LIBADD = $(LIB_QT) $(LIB_KDECORE) $(LIB_KDEUI)
kverbs_english_la_LDFLAGS = $(all_libraries) $(KDE_PLUGIN) -module
METASOURCES = AUTO

lnkdir                    = $(kde_datadir)/kverbs
lnk_DATA                  = english.desktop

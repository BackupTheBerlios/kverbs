## Makefile.am for kverbs

# this has all of the subdirectories that make will recurse into.  if
# there are none, comment this out
SUBDIRS = . modules pics

# this is the program that gets installed.  it's name is used for all
# of the other Makefile.am variables
bin_PROGRAMS = kverbs

# set the include path for X, qt and KDE
INCLUDES         = $(all_includes)

# the library search path. 
kverbs_LDFLAGS = $(KDE_RPATH) $(all_libraries)

# the libraries to link against.
kverbs_LDADD   = $(LIB_KFILE) -lkdeprint

# which sources should be compiled for kverbs
kverbs_SOURCES =	main.cpp kverbs.cpp

# these are the headers for your project
noinst_HEADERS   = kverbs.h

# let automoc handle all of the meta source files (moc)
METASOURCES = AUTO

messages: rc.cpp
	$(XGETTEXT) *.cpp modules/*/*.cpp -o $(podir)/kverbs.pot

KDE_ICON = kverbs

# this is where the kdelnk file will go 
xdg_apps_data = kverbs.desktop

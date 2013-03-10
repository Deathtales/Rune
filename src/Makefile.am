## Process this file with automake to produce Makefile.in

## Created by Anjuta



AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	$(RUNE_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = rune

rune_SOURCES = \
	main.cc \
	entities/project.cc \
	entities/project.h \
	ui/new-resource-dialog.cc \
	ui/new-resource-dialog.h \
	entities/section.cc \
	entities/section.h \
	entities/scene.cc \
	entities/scene.h \
	ui/main-window.cc \
	ui/main-window.h \
	ui/project-store.cc \
	ui/project-store.h \
	ui/project-tree-view.cc \
	ui/project-tree-view.h \
	ui/project-tree-zone.cc \
	ui/project-tree-zone.h \
	converters/book-converter.cc \
	converters/book-converter.h \
	converters/markdown-converter.cc \
	converters/markdown-converter.h \
	converters/convert-options.cc \
	converters/convert-options.h \
	utils/xml-utils.cc \
	utils/xml-utils.h \
	ui/replacement-table-dialog.cc \
	ui/replacement-table-dialog.h

rune_LDFLAGS = 

rune_LDADD = $(RUNE_LIBS)


EXTRA_DIST = $(ui_DATA)

# Remove ui directory on uninstall
uninstall-local:
	-rm -r $(uidir)
	-rm -r $(pkgdatadir)


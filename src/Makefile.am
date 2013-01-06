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
	ui/edit-window.cc \
	ui/edit-window.h \
	entities/project.cc \
	entities/project.h \
	ui/new-resource-dialog.cc \
	ui/new-resource-dialog.h \
	ui/project-structure.cc \
	ui/project-structure.h \
	ui/structure-view.cc \
	ui/structure-view.h \
	entities/section.cc \
	entities/section.h \
	ui/structure-zone.cc \
	ui/structure-zone.h \
	ui/structure-menu.cc \
	ui/structure-menu.h \
	ui/project-model.cc \
	ui/project-model.h \
	entities/scene.cc \
	entities/scene.h

rune_LDFLAGS = 

rune_LDADD = $(RUNE_LIBS)


EXTRA_DIST = $(ui_DATA)

# Remove ui directory on uninstall
uninstall-local:
	-rm -r $(uidir)
	-rm -r $(pkgdatadir)


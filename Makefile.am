## Process this file with automake to produce Makefile.in
## Created by Anjuta

SUBDIRS = src po

runedocdir = ${prefix}/doc/rune
runedoc_DATA = \
	README\
	COPYING\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS


INTLTOOL_FILES = intltool-extract.in \
	intltool-merge.in \
	intltool-update.in

EXTRA_DIST = $(runedoc_DATA) \
	$(INTLTOOL_FILES)

data_DATA = images/Title.svg \
	images/book.svg \
	images/chapter.svg \
	images/dark-mode.svg \
	images/light-mode.svg \
	images/logo.svg \
	images/new-book.svg \
	images/new-chapter.svg \
	images/new-part.svg \
	images/new-project.svg \
	images/new-scene.svg \
	images/part.svg \
	images/project.svg \
	images/scene.svg \
	images/ReplacementTable.svg

DISTCLEANFILES = intltool-extract \
	intltool-merge \
	intltool-update \
	po/.intltool-merge-cache


# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(runedocdir)

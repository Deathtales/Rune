/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * rune
 * Copyright (C) 2012 Julien SOSTHÈNE <juliensos10@gmail.com>
 * 
 * rune is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * rune is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _EDITION_VIEW_H_
#define _EDITION_VIEW_H_
#include <entities/project.h>
#include <gtkmm/treestore.h>
#include <gtkmm/treeview.h>
#include "ui/project-structure.h"
#include <gtkmm/progressbar.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/cellrenderer.h>
#include <gtkmm/cellrendererprogress.h>
#include <gtkmm/tooltip.h>
#include <iostream>
#include "ui/project-model.h"

class StructureView: public Gtk::TreeView
{
public:
	StructureView(Project* cProject);
	Project* currentProject;
	void updateView(int type, Section* newSec);
	typedef sigc::signal<void,int, Section*> type_signal_section_updated;
	type_signal_section_updated signal_section_updated();
	type_signal_section_updated m_signal_section_updated;
	typedef sigc::signal<void, Section*, GdkEventButton*> type_signal_waiting_menu;
	type_signal_waiting_menu signal_waiting_menu();
	type_signal_waiting_menu m_signal_waiting_menu;
	bool on_button_press_event(GdkEventButton* event);
	typedef sigc::signal<void, Section*> type_signal_section_open;
	type_signal_section_open signal_section_open();
	type_signal_section_open m_signal_section_open;
protected:

private:

    Gtk::TreeModel::iterator selectedRowIter;
	Section* selected;
	ProjectStructure projectStructure;
	Glib::RefPtr<Gtk::TreeStore> refStructure;
	Glib::RefPtr<Gdk::Pixbuf> getPixbuf(int type);
	Glib::RefPtr<Gdk::Pixbuf> bookbuf;
	Glib::RefPtr<Gdk::Pixbuf> partbuf;
	Glib::RefPtr<Gdk::Pixbuf> chapterbuf;
	Glib::RefPtr<Gdk::Pixbuf> scenebuf;
};

#endif // _EDITION_VIEW_H_

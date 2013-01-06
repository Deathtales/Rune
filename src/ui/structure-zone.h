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

#ifndef _STRUCTURE_ZONE_H_
#define _STRUCTURE_ZONE_H_
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/toolbar.h>
#include <gtkmm/menutoolbutton.h>
#include <gtkmm/image.h>
#include <gtkmm/stock.h>
#include "ui/structure-view.h"
#include "entities/project.h"
#include "ui/structure-menu.h"


class StructureZone: public Gtk::VBox
{
public:
	StructureZone(Project *currentProject);
	Project* currentProject;
	StructureView* structureView;
	StructureMenu* structureMenu;
	typedef sigc::signal<void,Section*> type_signal_section_open;
	type_signal_section_open signal_section_open();
	type_signal_section_open m_signal_section_open;
	void on_section_open(Section* sec);
protected:

private:
	void createNewBook();
	void on_menu_waiting(Section* sec, GdkEventButton* event);
};

#endif // _STRUCTURE_ZONE_H_

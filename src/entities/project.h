/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * rune
 * Copyright (C) 2012 Julien SOSTHÈNE <sosthene@Redtouch>
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

#ifndef _PROJECT_H_
#define _PROJECT_H_
#include <glibmm/ustring.h>
#include "entities/section.h"
#include "entities/scene.h"
#include <gtkmm/window.h>
#include <libxml++/document.h>
#include <libxml++/parsers/domparser.h>
#include <gtkmm/recentmanager.h>

class Project : public Section
{
public:
	Project(Glib::ustring name, Glib::ustring desc, Gtk::Window* parent);
	~Project();
	Glib::ustring getPath();
	Gtk::Window* getAssociatedWindow();
	void save();
	void setPath(Glib::ustring uri);
	static Project* createFromRuneFile(Glib::ustring parentPath, Glib::ustring path, Gtk::Window* assocWin);
	bool changesToProject; /**< A boolean showing changes were made in the project tree*/
protected:

private:
	Glib::ustring path;
	Gtk::Window* associatedWindow;

};

#endif // _PROJECT_H_


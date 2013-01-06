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

#ifndef _PROJECT_STRUCTURE_H_
#define _PROJECT_STRUCTURE_H_
#include <gtkmm/treemodelcolumn.h>
#include <gtkmm/image.h>
#include <glibmm/ustring.h>
#include <gtkmm/progressbar.h>
#include <gdkmm/pixbuf.h>
#include <entities/section.h>

class ProjectStructure: public Gtk::TreeModelColumnRecord 
{
public:
	ProjectStructure(){
		add(type);
		add(name);
		add(progress);
		add(section);
		add(description);
	}
	Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf> > type;
	Gtk::TreeModelColumn<Glib::ustring> name;
	Gtk::TreeModelColumn<float> progress;
	Gtk::TreeModelColumn<Section*> section;
	Gtk::TreeModelColumn<Glib::ustring> description;

protected:

private:

};

#endif // _PROJECT_STRUCTURE_H_


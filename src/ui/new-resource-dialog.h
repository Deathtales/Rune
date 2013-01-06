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

#ifndef _NEW_RESOURCE_DIALOG_H_
#define _NEW_RESOURCE_DIALOG_H_
#include <glibmm/ustring.h>
#include <gtkmm/dialog.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/textview.h>
#include <gtkmm/stock.h>
#include "entities/section.h"
#include <iostream>
#include <gtkmm/scrolledwindow.h>

enum SpecificStrings{
	NEWRESOURCE,
	NAMEINFO,
	DESCINFO,
	IMAGEPATH,
	
	NUMBERITEMS
	
};

class NewResourceDialog: public Gtk::Dialog
{
public:
	NewResourceDialog(int type, 
	                  Gtk::Widget* additionnalWidget,
	                  Gtk::Window* parent);
	Glib::ustring getName();
	Glib::ustring getDescription();
	void setName(Glib::ustring name);
	void setDescription(Glib::ustring desc);
protected:

private:
	Glib::RefPtr<Gtk::TextBuffer> descBuffer;
	Glib::ustring getSpecificString(int type, int specString);
	Gtk::Widget* getSpecificWidget(int type);
	Gtk::Box* dialogVBox;
	Gtk::Entry* nameEntry;
	Gtk::TextView* descEntry;
};

#endif // _NEW_RESOURCE_DIALOG_H_

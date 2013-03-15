/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * Rune
 * Copyright (C) 2013 Julien SOSTHÈNE <juliensos10@gmail.com>
 * 
 * Rune is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Rune is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _REPLACEMENT_TABLE_DIALOG_H_
#define _REPLACEMENT_TABLE_DIALOG_H_
#include <glibmm/ustring.h>
#include <gtkmm/dialog.h>
#include <gtkmm/treeview.h>
#include <gtkmm/button.h>
#include <gtkmm/stock.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/treeview.h>
#include <gtkmm/liststore.h>
#include <gtkmm/infobar.h>
#include "utils/user-configuration.h"

class ReplacementTableDialog: public Gtk::Dialog 
{
	public:
		ReplacementTableDialog(Gtk::Window* parent, UserConfiguration* config);
	protected:
		Gtk::Entry* sourceEntry;
		Gtk::Entry* destEntry;
		Gtk::Box* dialogVBox;
		UserConfiguration* userConfig;

		class ModelColumns : public Gtk::TreeModel::ColumnRecord
	{
		public:

			ModelColumns()
		{ add(src); add(dest); }

			Gtk::TreeModelColumn<Glib::ustring> src;
			Gtk::TreeModelColumn<Glib::ustring> dest;
	};

		ModelColumns columns;
		Gtk::TreeView* listView;
		Glib::RefPtr<Gtk::ListStore> refTreeModel;

		void addEntry();
		void removeEntry(GdkEventButton* button);
		private:

};

#endif // _REPLACEMENT_TABLE_DIALOG_H_


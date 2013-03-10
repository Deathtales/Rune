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

#include "replacement-table-dialog.h"


ReplacementTableDialog::ReplacementTableDialog(Gtk::Window* parent): Gtk::Dialog( "Replacement Table", *parent, true),dialogVBox(get_vbox()){

	//Define structure
	Gtk::HBox* entryHBox = Gtk::manage(new Gtk::HBox);
	Gtk::Label* instructions = Gtk::manage(new Gtk::Label("Note: replacement will only occur when you export a book."));
	sourceEntry = Gtk::manage(new Gtk::Entry);
	sourceEntry->set_placeholder_text("Replace This...");
	destEntry = Gtk::manage(new Gtk::Entry);
	destEntry->set_placeholder_text("...with this.");
	Gtk::Button* addButton = Gtk::manage(new Gtk::Button(Gtk::Stock::ADD));
	entryHBox->pack_start(*sourceEntry);
	entryHBox->pack_start(*destEntry);
	entryHBox->pack_start(*addButton);

	Gtk::ScrolledWindow* scrWindow = Gtk::manage(new Gtk::ScrolledWindow);
	listView = Gtk::manage(new Gtk::TreeView);
	scrWindow->add(*listView);
	scrWindow->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	//Create the Tree model:
	refTreeModel = Gtk::ListStore::create(columns);
	listView->set_model(refTreeModel);

	listView->append_column_editable("Replace", columns.src);
	listView->append_column_editable("With", columns.dest);
	dialogVBox->pack_start(*instructions, Gtk::PACK_SHRINK);
	dialogVBox->pack_start(*entryHBox, Gtk::PACK_SHRINK);
	dialogVBox->pack_start(*scrWindow, Gtk::PACK_EXPAND_WIDGET);
	add_button(Gtk::Stock::CLOSE, Gtk::RESPONSE_OK);

	 //Fill the TreeView's model
	Gtk::TreeModel::Row row = *(refTreeModel->append());
	row[columns.src] = "Essai";
	row[columns.dest] = "essai";

	set_size_request(-1,400);
	dialogVBox->show_all();
	addButton->grab_focus();
}

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

/**
 * \file new-resource-dialog.cc
 * \brief Dialog for creating resources
 * \author Julien Sosthène
 *
 * Methods for NewResourceDialog.
 *
 */
#include "new-resource-dialog.h"
NewResourceDialog::NewResourceDialog(int type,
                                     Gtk::Window* parent) :
Gtk::Dialog( getSpecificString(type,NEWRESOURCE), *parent, true),dialogVBox(get_vbox()){
	Gtk::Image* typeImage = 
		Gtk::manage(new Gtk::Image(Gdk::Pixbuf::create_from_file
		                           (getSpecificString(type,IMAGEPATH),
		                            100,100, true)));
	Gtk::HBox* nameHBox = Gtk::manage(new Gtk::HBox);
	Gtk::HBox* typeHBox = Gtk::manage(new Gtk::HBox);
	Gtk::Label* nameLabel = Gtk::manage(new Gtk::Label("Name:"));
	nameEntry = Gtk::manage(new Gtk::Entry);
	nameEntry->set_tooltip_text(getSpecificString(type, NAMEINFO));
	nameHBox->pack_start(*typeImage, Gtk::PACK_SHRINK);

	nameHBox->pack_start(*nameLabel, Gtk::PACK_SHRINK);
	nameHBox->pack_end(*nameEntry);
	dialogVBox->pack_start(*nameHBox, Gtk::PACK_SHRINK);
	Gtk::VBox* descVBox = Gtk::manage(new Gtk::VBox());
	Gtk::Label* descLabel = Gtk::manage(new Gtk::Label("Description: "));
	Glib::RefPtr<Gtk::TextBuffer> descBuffer = Gtk::TextBuffer::create();
	descEntry = Gtk::manage(new Gtk::TextView(descBuffer));
	descEntry->set_editable();
	descEntry->set_wrap_mode(Gtk::WRAP_WORD);
	descEntry->set_justification(Gtk::JUSTIFY_FILL);
	descEntry->set_left_margin(10);
	descEntry->set_right_margin(10);
	descEntry->set_indent(20);
	descEntry->set_border_width(10);
	descEntry->set_tooltip_text(getSpecificString(type, DESCINFO));
	Gtk::ScrolledWindow* descScrolled = 
		Gtk::manage(new Gtk::ScrolledWindow);
	descScrolled->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	descScrolled->add(*descEntry);
	descVBox->pack_start(*descLabel, Gtk::PACK_SHRINK);
	descVBox->pack_end(*descScrolled, Gtk::PACK_EXPAND_WIDGET);
	dialogVBox->pack_start(*descVBox, Gtk::PACK_EXPAND_WIDGET);
	add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	add_button(Gtk::Stock::ADD, Gtk::RESPONSE_OK);

	set_size_request(600,400);
	show_all();
}

Glib::ustring NewResourceDialog::getName(){
	return nameEntry->get_text();
}

Glib::ustring NewResourceDialog::getDescription(){
	return descEntry->get_buffer()->get_text();
}

void NewResourceDialog::setName(Glib::ustring name){
	nameEntry->set_text(name);
}

void NewResourceDialog::setDescription(Glib::ustring desc){
	descEntry->get_buffer()->set_text(desc);
}


Glib::ustring NewResourceDialog::getSpecificString(int type, int specString){

	Glib::ustring spec[NUMBERITEMS];
	switch (type){
		case PROJECT:
			spec[NEWRESOURCE] = "New Project";
			spec[NAMEINFO] = "Name of your project. Will also be the name of the saga";
			spec[DESCINFO] = "Short description of this project. Will be displayed as a tooltip.";
			spec[IMAGEPATH] = "images/project.svg";
			break;
		case BOOK:
			spec[NEWRESOURCE] = "New Book";
			spec[NAMEINFO] = "Title of your book.";
			spec[DESCINFO] = "Short synopsis of this book. Will be displayed as a tooltip.";
			spec[IMAGEPATH] = "images/book.svg";
			break;
		case PART:
			spec[NEWRESOURCE] = "New Part";
			spec[NAMEINFO] = "Title of this part";
			spec[DESCINFO] = "Short synopsis of this part. Will be displayed as a tooltip.";
			spec[IMAGEPATH] = "images/part.svg";
			break;
		case CHAPTER:
			spec[NEWRESOURCE] = "New Chapter";
			spec[NAMEINFO] = "Title of this chapter";
			spec[DESCINFO] = "Short synopsis of this chapter. Will be displayed as a tooltip.";
			spec[IMAGEPATH] = "images/chapter.svg";
			break;
		case SCENE:
			spec[NEWRESOURCE] = "New Scene";
			spec[NAMEINFO] = "Title of this scene. Won't be displayed in output.'";
			spec[DESCINFO] = "Short synopsis of this scene. Will be displayed as a tooltip.";
			spec[IMAGEPATH] = "images/scene.svg";
			break;
		default:
			break;

	}
	return spec[specString];
}
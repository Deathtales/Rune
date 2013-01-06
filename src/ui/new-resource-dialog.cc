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

#include "new-resource-dialog.h"


NewResourceDialog::NewResourceDialog(int type,
                                     Gtk::Widget* specificWidget,
                                     Gtk::Window* parent) :
	Gtk::Dialog( (getSpecificString(type, NEWRESOURCE)), *parent, true),
								dialogVBox(get_vbox()){
	Gtk::Image* typeImage = 
		Gtk::manage(new Gtk::Image(Gdk::Pixbuf::create_from_file(
		                             getSpecificString(type,IMAGEPATH),
		                             100,100, true)));

	Gtk::HBox* nameHBox = Gtk::manage(new Gtk::HBox);
	Gtk::HBox* typeHBox = Gtk::manage(new Gtk::HBox);
	Gtk::Label* nameLabel = Gtk::manage(new Gtk::Label("Nom:"));
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
    descEntry->set_tooltip_text(getSpecificString(type, DESCINFO));
	Gtk::ScrolledWindow* descScrolled = 
		Gtk::manage(new Gtk::ScrolledWindow);
	descScrolled->set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);
	descScrolled->add(*descEntry);
	descVBox->pack_start(*descLabel, Gtk::PACK_SHRINK);
	descVBox->pack_end(*descScrolled, Gtk::PACK_EXPAND_WIDGET);
	dialogVBox->pack_start(*descVBox, Gtk::PACK_EXPAND_WIDGET);
	if(specificWidget != NULL){
		dialogVBox->pack_end(*specificWidget);
	}
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
			spec[NEWRESOURCE] = "Nouveau Projet";
			spec[NAMEINFO] = "Le nom de votre projet. Il servira également de titre à votre série.";
			spec[DESCINFO] = "Courte description qui s'affichera dans une infobulle comme celle-ci.";
			spec[IMAGEPATH] = "images/project.svg";
			break;
		case BOOK:
			spec[NEWRESOURCE] = "Nouveau Livre";
			spec[NAMEINFO] = "Le titre du nouveau livre.";
			spec[DESCINFO] = "Courte description qui s'affichera dans une infobulle comme celle-ci.";
			spec[IMAGEPATH] = "images/book.svg";
			break;
		case PART:
			spec[NEWRESOURCE] = "Nouvelle Partie";
			spec[NAMEINFO] = "OPTIONNEL: Le titre de la nouvelle partie.";
			spec[DESCINFO] = "Courte description qui s'affichera dans une infobulle comme celle-ci.";
			spec[IMAGEPATH] = "images/part.svg";
			break;
		case CHAPTER:
			spec[NEWRESOURCE] = "Nouveau Chapitre";
			spec[NAMEINFO] = "OPTIONNEL: Le titre du nouveau chapitre.";
			spec[DESCINFO] = "Courte description qui s'affichera dans une infobulle comme celle-ci.";
			spec[IMAGEPATH] = "images/chapter.svg";
			break;
		case SCENE:
			spec[NEWRESOURCE] = "Nouvelle Scène";
			spec[NAMEINFO] = "OPTIONNEL: Le titre du nouveau chapitre.";
			spec[DESCINFO] = "Courte description qui s'affichera dans une infobulle comme celle-ci.";
			spec[IMAGEPATH] = "images/scene.svg";
			break;
		default:
			break;

	}
	return spec[specString];
}
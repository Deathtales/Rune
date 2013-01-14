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

#include "structure-menu.h"

StructureMenu::StructureMenu(Project* currentProject, StructureView* view)
{
	this->view = view;
	this->currentProject =currentProject;
	this->selected = currentProject;
	newBook = Gtk::manage(new Gtk::ImageMenuItem("Nouveau _Livre...",true));
	newBook->set_image(*Gtk::manage(new Gtk::Image(
	      Gdk::Pixbuf::create_from_file("images/new-book.svg", 20, 20, true))));
	newBook->signal_activate().connect( sigc::mem_fun(*this,
              &StructureMenu::createNewBook));
	append(*newBook);

	newPart = Gtk::manage(new Gtk::ImageMenuItem("Nouvelle _Partie...",true));
	newPart->set_image(*Gtk::manage(new Gtk::Image(
	      Gdk::Pixbuf::create_from_file("images/new-part.svg", 20, 20, true))));
	newPart->signal_activate().connect( sigc::mem_fun(*this,
              &StructureMenu::createNewPart));
	append(*newPart);

	newChapter = Gtk::manage(new Gtk::ImageMenuItem("Nouveau _Chapitre...",true));
	newChapter->set_image(*Gtk::manage(new Gtk::Image(
	   Gdk::Pixbuf::create_from_file("images/new-chapter.svg", 20, 20, true))));
	newChapter->signal_activate().connect( sigc::mem_fun(*this,
              &StructureMenu::createNewChapter));
	append(*newChapter);

	newScene = Gtk::manage(new Gtk::ImageMenuItem("Nouvelle _Scene",true));
	newScene->set_image(*Gtk::manage(new Gtk::Image(
	     Gdk::Pixbuf::create_from_file("images/new-scene.svg", 20, 20, true))));
	newScene->signal_activate().connect( sigc::mem_fun(*this,
              &StructureMenu::createNewScene));
	append(*newScene);
	
	open = Gtk::manage(new Gtk::ImageMenuItem(Gtk::Stock::OPEN));
	append(*open);
	open->signal_activate().connect( sigc::mem_fun(*this,
              &StructureMenu::openSection));
	edit = Gtk::manage(new Gtk::ImageMenuItem(Gtk::Stock::EDIT));
	append(*edit);
	edit->signal_activate().connect( sigc::mem_fun(*this,
              &StructureMenu::editResource));
	remove = Gtk::manage(new Gtk::ImageMenuItem(Gtk::Stock::DELETE));
	append(*remove);
	remove->signal_activate().connect( sigc::mem_fun(*this,
              &StructureMenu::removeResource));
}

StructureMenu* StructureMenu::rearrange(int type){
	newBook->hide();
	newPart->hide();
	newChapter->hide();
	newScene->hide();
	edit->hide();
	remove->hide();
	open->hide();
	switch (type){
		case PROJECT :
			newBook->show();
			break;

		case BOOK :
			newPart->show();
			newChapter->show();
			edit->show();
			remove->show();
			break;

		case PART :
			newChapter->show();
			edit->show();
			remove->show();
			break;

		case CHAPTER:
			newScene->show();
			edit->show();
			remove->show();

			break;

		case SCENE:
			edit->show();
			remove->show();
			open->show();
			break;
		default:
			break;
	};
	return this;
}

void StructureMenu::createNewBook(){
	createNewResource(BOOK);
}

void StructureMenu::createNewPart(){
	createNewResource(PART);
}

void StructureMenu::createNewChapter(){
	createNewResource(CHAPTER);
}

void StructureMenu::createNewScene(){
	createNewResource(SCENE);
}

void StructureMenu::createNewResource(int type){
	NewResourceDialog dial(type,NULL,currentProject->getAssociatedWindow());
	int response = dial.run();
	int index = 1;
	Glib::ustring name = "";
	std::ostringstream nameStream;
	if(response == Gtk::RESPONSE_OK){
		Section* sec;
		if (type == BOOK)
			selected = currentProject;
		if (dial.getName() == ""){
			name = "untitled";
		}
		else{
			name = dial.getName();
		}
		if (type == SCENE)
			sec = new Scene(name,dial.getDescription());
		else
			sec = new Section(type,name,dial.getDescription());
		selected->addSectionToToc(sec);
		view->m_signal_section_updated.emit(type, sec);
	}


}

void StructureMenu::editResource(){
	NewResourceDialog dial(selected->getType(),NULL,currentProject->getAssociatedWindow());
	dial.setName(selected->name);
	dial.setDescription(selected->description);
	int response = dial.run();
	Glib::ustring name;
	std::ostringstream nameStream;
	int index = 1;
	if(response == Gtk::RESPONSE_OK){
		if (dial.getName() == ""){
			name = "untitled";
		}
		else{
			name = dial.getName();
		}
		selected->name = dial.getName();
		selected->description = dial.getDescription();
		selected->rename(true);
		view->m_signal_section_updated.emit(selected->getType(), selected);
	}

}

void StructureMenu::removeResource(){
	Gtk::MessageDialog dial(*currentProject->getAssociatedWindow(), 
	               "Voulez-vous vraiment supprimer " + selected->name + "?\nCeci supprimera également tout son contenu.", 
	               true, Gtk::MESSAGE_WARNING, Gtk::BUTTONS_OK_CANCEL, true);
	int response = dial.run();
	if(response == Gtk::RESPONSE_OK){
		view->m_signal_section_updated.emit(NONE, selected);
		rearrange(PROJECT);
		selected = currentProject;
	}
	

}

void StructureMenu::openSection(){
	view->m_signal_section_open.emit(selected);
}
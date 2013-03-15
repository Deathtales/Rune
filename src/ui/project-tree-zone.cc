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

#include "ui/project-tree-zone.h"


ProjectTreeZone::ProjectTreeZone(Project *currentProject, UserConfiguration* uc){
	// initialize object properties:
	this->currentProject = currentProject;
	this->userConfiguration = uc;
	this->projectTreeView = Gtk::manage(new ProjectTreeView(currentProject));
	this->projectZoneMenu = NULL;

	//get the needed graphical widgets to display:
	Gtk::ScrolledWindow* projectZoneScroll = 
		Gtk::manage(new Gtk::ScrolledWindow);
	projectZoneScroll->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	Gtk::MenuToolButton* newSection = Gtk::manage(new Gtk::MenuToolButton);
	newSection->set_tooltip_text("Create a new Book");
	newSection->set_icon_widget(*Gtk::manage(new Gtk::Image(Gdk::Pixbuf::create_from_file("images/new-book.svg", 20, 20, false))));
	newSection->set_arrow_tooltip_text("Create a new Section");


	//TODO move this to ProjectTreeView
	projectTreeView->signal_section_updated().connect(sigc::mem_fun(projectTreeView,
	                                                                &ProjectTreeView::updateView));
	projectTreeView->signal_button_press_event()
		.connect(sigc::mem_fun(
		                       projectTreeView, &ProjectTreeView::on_button_press_event), false);
	//end of TODO
	
	//bind signals
	projectTreeView->signal_waiting_menu()
		.connect(sigc::mem_fun(*this,&ProjectTreeZone::on_menu_waiting));
	projectTreeView->signal_section_open()
		.connect(sigc::mem_fun(
		                       *this, &ProjectTreeZone::onSectionOpen));
	projectZoneMenu = getProjectZoneMenu(PROJECT);
	newSection->signal_clicked()
		.connect(sigc::bind<int>(sigc::mem_fun(*this,&ProjectTreeZone::createNewResource), BOOK));
	newSection->set_menu(*projectZoneMenu);

	//now add the toolbar
	Gtk::Toolbar* structureTools = Gtk::manage(new Gtk::Toolbar);
	structureTools->append(*newSection);

	//pack the elements to te box
	pack_start(*structureTools, Gtk::PACK_SHRINK);
	projectZoneScroll->add(*projectTreeView);
	pack_start(*projectZoneScroll,Gtk::PACK_EXPAND_WIDGET);
	show_all();
}

Gtk::Menu* ProjectTreeZone::getProjectZoneMenu(int type){

	//creates the menu if it does not exist
	if (projectZoneMenu == NULL){
		projectZoneMenu = Gtk::manage(new Gtk::Menu);
		newBook = Gtk::manage(new Gtk::ImageMenuItem("New _Book...",true));
		newBook->set_image(*Gtk::manage(new Gtk::Image(
		                                               Gdk::Pixbuf::create_from_file("images/new-book.svg", 20, 20, true))));
		newBook->signal_activate().connect( sigc::bind<int>(sigc::mem_fun(*this,
		                                                                  &ProjectTreeZone::createNewResource), BOOK));
		projectZoneMenu->append(*newBook);

		newPart = Gtk::manage(new Gtk::ImageMenuItem("New _Part",true));
		newPart->set_image(*Gtk::manage(new Gtk::Image(
		                                               Gdk::Pixbuf::create_from_file("images/new-part.svg", 20, 20, true))));
		newPart->signal_activate().connect( sigc::bind<int>(sigc::mem_fun(*this,
		                                                                  &ProjectTreeZone::createNewResource), PART));
		projectZoneMenu->append(*newPart);

		newChapter = Gtk::manage(new Gtk::ImageMenuItem("New _Chapter",true));
		newChapter->set_image(*Gtk::manage(new Gtk::Image(
		                                                  Gdk::Pixbuf::create_from_file("images/new-chapter.svg", 20, 20, true))));
		newChapter->signal_activate().connect( sigc::bind<int>(sigc::mem_fun(*this,
		                                                                     &ProjectTreeZone::createNewResource), CHAPTER));
		projectZoneMenu->append(*newChapter);

		newScene = Gtk::manage(new Gtk::ImageMenuItem("New _Scene",true));
		newScene->set_image(*Gtk::manage(new Gtk::Image(
		                                                Gdk::Pixbuf::create_from_file("images/new-scene.svg", 20, 20, true))));
		newScene->signal_activate().connect( sigc::bind<int>(sigc::mem_fun(*this,
		                                                                   &ProjectTreeZone::createNewResource), SCENE));
		projectZoneMenu->append(*newScene);

		open = Gtk::manage(new Gtk::ImageMenuItem(Gtk::Stock::OPEN));
		projectZoneMenu->append(*open);
		open->signal_activate().connect( sigc::mem_fun(*this,
		                                               &ProjectTreeZone::openSection));
		edit = Gtk::manage(new Gtk::ImageMenuItem(Gtk::Stock::EDIT));
		projectZoneMenu->append(*edit);
		edit->signal_activate().connect( sigc::mem_fun(*this,
		                                               &ProjectTreeZone::editResource));
		remove = Gtk::manage(new Gtk::ImageMenuItem(Gtk::Stock::DELETE));
		projectZoneMenu->append(*remove);
		remove->signal_activate().connect( sigc::mem_fun(*this,
		                                                 &ProjectTreeZone::removeResource));
		convert = Gtk::manage(new Gtk::ImageMenuItem(Gtk::Stock::CONVERT));
		projectZoneMenu->append(*convert);
		Gtk::Menu* bookConvertMenu = Gtk::manage(new Gtk::Menu);
		convertToMdwn = Gtk::manage(new Gtk::ImageMenuItem(Gtk::Stock::CONVERT));
		convertToMdwn->set_label("Convert to Markdown...");
		bookConvertMenu->append(*convertToMdwn);
		convert->set_submenu(*bookConvertMenu);
		bookConvertMenu->show_all();
		convertToMdwn->signal_activate().connect( sigc::mem_fun(*this,
		                                               &ProjectTreeZone::convertResourceToMarkdown));
		
	}

	//Hide everything and only show relevant items
	newBook->hide();
	newPart->hide();
	newChapter->hide();
	newScene->hide();
	edit->hide();
	remove->hide();
	open->hide();
	convert->hide();
	switch (type){
		case PROJECT :
			newBook->show();
			break;

		case BOOK :
			newPart->show();
			newChapter->show();
			edit->show();
			remove->show();
			convert->show();
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
	return projectZoneMenu;

}

void ProjectTreeZone::openView(){
	projectTreeView->openView(currentProject);
}

void ProjectTreeZone::createNewResource(int type){
	NewResourceDialog dial(type,currentProject->getAssociatedWindow());
	int response = dial.run();
	int index = 1;
	Glib::ustring name = "";
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
		sec->shortName = dial.getShName();
		selected->addSectionToToc(sec);
		projectTreeView->signal_section_updated().emit(type, sec);
	}
	currentProject->changesToProject = true;


}

void ProjectTreeZone::editResource(){
	NewResourceDialog dial(selected->getType(),currentProject->getAssociatedWindow());
	dial.setName(selected->name);
	dial.setShName(selected->shortName);
	dial.setDescription(selected->description);
	int response = dial.run();
	Glib::ustring name;
	int index = 1;
	if(response == Gtk::RESPONSE_OK){
		if (dial.getName() == ""){
			name = "untitled";
		}
		else{
			name = dial.getName();
		}
		selected->name = dial.getName();
		selected->shortName = dial.getShName();
		selected->description = dial.getDescription();
		projectTreeView->m_signal_section_updated.emit(selected->getType(), selected);
	}
	currentProject->changesToProject = true;
}

void ProjectTreeZone::removeResource(){
	Gtk::MessageDialog dial(*currentProject->getAssociatedWindow(), 
	                        "Do you really wish to delete " + selected->name + "?\nThis will remove all its content.", 
	                        true, Gtk::MESSAGE_WARNING, Gtk::BUTTONS_OK_CANCEL, true);
	int response = dial.run();
	if(response == Gtk::RESPONSE_OK){
		projectTreeView->m_signal_section_updated.emit(NONE, selected);
		getProjectZoneMenu (PROJECT);
		selected = currentProject;
	}
	currentProject->changesToProject = true;

}

void ProjectTreeZone::openSection(){
	signal_section_open().emit(selected);
}

void ProjectTreeZone::getConvertOptions(std::map<Glib::ustring,Glib::ustring> rt){
	Gtk::Dialog* dial = new Gtk::Dialog( "Convertion Options", *currentProject->getAssociatedWindow(), true);
	Gtk::Box* dialVBox = dial->get_vbox();
	Gtk::HBox* authorHBox = Gtk::manage(new Gtk::HBox);
	Gtk::Label* authorLabel = Gtk::manage(new Gtk::Label("Name of the author: "));
	Gtk::Entry* authorEntry = Gtk::manage(new Gtk::Entry);
	Gtk::CheckButton *useShNameButton = Gtk::manage(new Gtk::CheckButton("Display Short Name before Name in output."));
	authorHBox->pack_start(*authorLabel);
	authorHBox->pack_end(*authorEntry);	
	dialVBox->pack_start(*authorHBox);
	dialVBox->pack_end(*useShNameButton);
	dial->add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	dial->add_button(Gtk::Stock::CONVERT, Gtk::RESPONSE_OK);
	dial->show_all();
	int response = dial->run();
	if(response = Gtk::RESPONSE_OK){
		ConvertOptions* co = new ConvertOptions(authorEntry->get_text(),useShNameButton->get_active(),rt,currentProject->name);
		Glib::ustring uri = currentProject->getPath();
		MarkdownConverter::convertToFile(uri,selected,*co);
		delete dial;
		delete co;
	}
}

void ProjectTreeZone::convertResourceToMarkdown(){
	getConvertOptions(userConfiguration->getReplacementTable ());
}

void ProjectTreeZone::on_menu_waiting(Section* sec, GdkEventButton* event){
	getProjectZoneMenu(sec->getType());
	selected = sec;
	if( (event->type == GDK_BUTTON_PRESS) && (event->button == 3) )
	{
		projectZoneMenu->popup(event->button, event->time);

	}

}

void ProjectTreeZone::onSectionOpen(Section* sec){
	m_signal_section_open.emit(sec);
}


ProjectTreeZone::type_signal_section_open ProjectTreeZone::signal_section_open()
{
	return m_signal_section_open;
}

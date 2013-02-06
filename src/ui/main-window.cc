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
 * \file main-window.cc
 * \brief The main window function definitions.
 * \author Julien Sosthène
 *
 * Main window for Rune with every hook for managing a project.
 *
 */

#include "main-window.h"

MainWindow::MainWindow(){
	editionHPaned = NULL;
	currentProject = NULL;
	this->setDefaultProperties();

	mainVBox = Gtk::manage(new Gtk::VBox);
	mainVBox->show();
	this->add(*mainVBox);

	mainVBox->pack_start(*getMainMenuBar(), Gtk::PACK_SHRINK);
	this->setMainContent(getWelcomeBox());

}

void MainWindow::createNewProject(){
	NewResourceDialog dialog(PROJECT,NULL,this);
	Glib::ustring name;
	int response = dialog.run();
	if(response == Gtk::RESPONSE_OK){
		if (dialog.getName() == ""){
			name = "untitled";
		}
		else{
			name = dialog.getName();
		}
		currentProject = new Project(name,dialog.getDescription(),this);
		this->set_title("Rune: " + currentProject->name);
		this->setMainContent(getEditionPaned());
	}
	
}

void MainWindow::setDefaultProperties(){
	set_hide_titlebar_when_maximized();
	set_title("Rune - A novel Editor");
	set_icon_from_file("images/logo.svg");
	resize(900, 600);
}

void MainWindow::setMainContent(Gtk::Widget* widget){
	std::vector<Gtk::Widget*> childrenVect= mainVBox->get_children();
	if(childrenVect.size() > 1)
		mainVBox->remove((*childrenVect[1]));
	mainVBox->pack_start(*widget, Gtk::PACK_EXPAND_PADDING);
	mainVBox->show_all();
}

Gtk::MenuBar* MainWindow::getMainMenuBar(){
	Gtk::MenuBar* menuBar = Gtk::manage(new Gtk::MenuBar);

	// Adding menuItems
	Gtk::MenuItem* menuItemFile = 
		Gtk::manage(new Gtk::MenuItem("_Project", true));
	Gtk::MenuItem* menuItemDisplay = 
		Gtk::manage(new Gtk::MenuItem("_Display", true));
	Gtk::MenuItem* menuItemHelp = 
		Gtk::manage(new Gtk::MenuItem("_Help", true));
	menuBar->append(*menuItemFile);
	menuBar->append(*menuItemDisplay);
	menuBar->append(*menuItemHelp); 

	//Adding submenu File
	Gtk::Menu* fileMenu = Gtk::manage(new Gtk::Menu);
	menuItemFile->set_submenu(*fileMenu);
	Gtk::ImageMenuItem* newProjectItem = 
		Gtk::manage(new Gtk::ImageMenuItem(Gtk::Stock::NEW));
	newProjectItem->signal_activate().connect(sigc::mem_fun(*this, &MainWindow::createNewProject));
	fileMenu->append(*newProjectItem);
	Gtk::ImageMenuItem* openProjectItem = 
		Gtk::manage(new Gtk::ImageMenuItem(Gtk::Stock::OPEN));
	fileMenu->append(*openProjectItem);
	Gtk::ImageMenuItem* saveProjectItem = 
		Gtk::manage(new Gtk::ImageMenuItem(Gtk::Stock::SAVE));
	//saveProjectItem->signal_activate().connect(sigc::mem_fun(*this, &MainWindow::saveProject));
	fileMenu->append(*saveProjectItem);
	Gtk::ImageMenuItem* saveProjectAsItem = 
		Gtk::manage(new Gtk::ImageMenuItem(Gtk::Stock::SAVE_AS));
	//saveProjectAsItem->signal_activate().connect(sigc::mem_fun(*this, &MainWindow::saveProjectAs));
	fileMenu->append(*saveProjectAsItem);
	Gtk::SeparatorMenuItem* separator = Gtk::manage(new Gtk::SeparatorMenuItem);
	fileMenu->append(*separator);
	Gtk::ImageMenuItem* quitItem = 
		Gtk::manage(new Gtk::ImageMenuItem(Gtk::Stock::QUIT));
	quitItem->signal_activate().connect(sigc::ptr_fun(&Gtk::Main::quit));
	fileMenu->append(*quitItem);

	//Adding Display submenu
	Gtk::Menu* displayMenu = Gtk::manage(new Gtk::Menu);
	menuItemDisplay->set_submenu(*displayMenu);

	Gtk::ImageMenuItem* lightModeItem = 
		Gtk::manage(new Gtk::ImageMenuItem("_Day Mode",true));
	lightModeItem->set_image(*Gtk::manage(new Gtk::Image(Gdk::Pixbuf::create_from_file("images/light-mode.svg", 20,20))));
	lightModeItem->signal_activate().connect(sigc::mem_fun(*this, &MainWindow::switchToLightMode));
	displayMenu->append(*lightModeItem);

	Gtk::ImageMenuItem* darkModeItem = 
		Gtk::manage(new Gtk::ImageMenuItem("_Night Mode",true));
	darkModeItem->set_image(*Gtk::manage(new Gtk::Image(Gdk::Pixbuf::create_from_file("images/dark-mode.svg", 20,20))));
	darkModeItem->signal_activate().connect(sigc::mem_fun(*this,&MainWindow::switchToDarkMode));
	displayMenu->append(*darkModeItem);
	return menuBar;

}

Gtk::VBox* MainWindow::getWelcomeBox(){
	Gtk::VBox* welcomeBox = Gtk::manage(new Gtk::VBox);
	Gtk::Image* homeImage =
		Gtk::manage( new Gtk::Image("images/Title.svg"));
	welcomeBox->pack_start(*homeImage, Gtk::PACK_SHRINK);
	Gtk::Label* infoLabel = 
		Gtk::manage(
		            new Gtk::Label(
		                           "Welcome to Rune. Please create a project!"));
	welcomeBox->pack_start(*infoLabel, Gtk::PACK_SHRINK);
	return welcomeBox;
}

Gtk::HPaned* MainWindow::getEditionPaned(){
	if (editionHPaned == NULL){
		editionHPaned = Gtk::manage(new Gtk::HPaned);
		Gtk::HPaned* internalHPaned = Gtk::manage(new Gtk::HPaned);
		Gtk::VPaned* structureVPaned = Gtk::manage(new Gtk::VPaned);
		/*StructureZone* structureZone =
			Gtk::manage(new StructureZone(currentProject));
		structureZone->signal_section_open()
			.connect(sigc::mem_fun(*this,&EditWindow::openNewTab));
		structureVPaned->add1(*structureZone);*/
		structureVPaned->add2(*Gtk::manage(new Gtk::Label("HelloWorld")));
		structureVPaned->set_position(400);

		//editionHPaned->pack1(*welcome,true,false);
		editionHPaned->set_position(700);
		editionHPaned->pack2(*structureVPaned,false,false);
		show_all();

	}
	return editionHPaned;

}


void MainWindow::switchToLightMode(){
	//TODO : find another way for switching themes
	Glib::RefPtr<Gtk::CssProvider> css = Gtk::CssProvider::create();
	css->load_from_path("/usr/share/themes/Adwaita/gtk-3.0/gtk.css");
	Glib::RefPtr<Gdk::Screen> screen = Gdk::Screen::get_default();
	Glib::RefPtr<Gtk::StyleContext> ctx = get_style_context();
	ctx->add_provider_for_screen(screen, css, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}

void MainWindow::switchToDarkMode(){
	//TODO : find another way for switching themes
	Glib::RefPtr<Gtk::CssProvider> css = Gtk::CssProvider::get_named("Adwaita","dark");
	Glib::RefPtr<Gdk::Screen> screen = Gdk::Screen::get_default();
	Glib::RefPtr<Gtk::StyleContext> ctx = get_style_context();
	ctx->add_provider_for_screen(screen, css, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}

MainWindow::~MainWindow(){
	delete currentProject;
}

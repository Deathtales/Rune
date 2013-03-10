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
	this->editionHPaned = NULL;
	this->currentProject = NULL;
	this->tabOpened = false;
	this->setDefaultProperties();
	mainVBox = Gtk::manage(new Gtk::VBox);
	mainVBox->show();
	this->add(*mainVBox);

	mainVBox->pack_start(*getMainMenuBar(), Gtk::PACK_SHRINK);
	this->setMainContent(getWelcomeBox());

}

void MainWindow::reinitialize(){
	if(this->currentProject)
		delete this->currentProject;
	this->editionHPaned = NULL;
	this->currentProject = NULL;
	this->tabOpened = false;
}

void MainWindow::createNewProject(){
	if(!checkForChanges()){
		NewResourceDialog dialog(PROJECT,this);
		Glib::ustring name;
		int response = dialog.run();
		if(response == Gtk::RESPONSE_OK){
			this->reinitialize ();
			if (dialog.getName() == ""){
				name = "untitled";
			}
			else{
				name = dialog.getName();
			}
			currentProject = new Project(name,dialog.getDescription(),this);
			this->set_title(currentProject->name + " - Rune");
			this->setMainContent(getEditionPaned());
		}
	}
}

bool MainWindow::checkForChanges(){
		if(currentProject){
		for (std::map<Scene*,Gtk::TextView*>::iterator it=tabMap.begin(); it!=tabMap.end(); ++it)
			if(it->first->getBody() != it->second->get_buffer()->get_text()){
				currentProject->changesToProject = true;
				break;
			}
		if(currentProject->changesToProject){
			Gtk::MessageDialog dial(*currentProject->getAssociatedWindow(), 
			                        "Changes were made in " + currentProject->name + ".\nDo you want to save before quitting?", 
			                        true, Gtk::MESSAGE_WARNING, Gtk::BUTTONS_NONE, true);
			dial.add_button(Gtk::Stock::CLEAR, Gtk::RESPONSE_REJECT);
			dial.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
			dial.add_button(Gtk::Stock::SAVE, Gtk::RESPONSE_OK);
			int response = dial.run();
			if(response == Gtk::RESPONSE_REJECT){
				return false;
			}
			if(response == Gtk::RESPONSE_OK){
				saveProject();
				return false;
			}
			else{
				return true;
			}
		}
		else{
			return false;
		}
	}
	else{
		return false;
	}
}

bool MainWindow::on_delete_event(GdkEventAny* event){
	if (!checkForChanges()){
		this->reinitialize ();
		return Gtk::Widget::on_delete_event(event);
	}
	else 
		return true;
}

void MainWindow::saveProject(){
	if(currentProject != NULL){
		if(currentProject->getPath() !=""){
			for (std::map<Scene*,Gtk::TextView*>::iterator it=tabMap.begin(); it!=tabMap.end(); ++it)
				it->first->setBody(it->second->get_buffer()->get_text());
			currentProject->save();
		}
		else{
			this->saveProjectAs();
	}
}
}

void MainWindow::saveProjectAs(){
	if(currentProject != NULL){
		Gtk::FileChooserDialog dial(*currentProject->getAssociatedWindow(), 
		                            "In which folder do you want to save " + currentProject->name + "?", 
		                            Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
		dial.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
		dial.add_button(Gtk::Stock::SAVE, Gtk::RESPONSE_OK);
		//dial.set_uri(Glib::get_home_dir());
		int response = dial.run();
		if(response == Gtk::RESPONSE_OK){
			Glib::RefPtr<Gio::File> dir = dial.get_file()->get_child(currentProject->name);
			if(dir->query_exists()){
				Gtk::MessageDialog dial2(*currentProject->getAssociatedWindow (),
				                         dir->get_path() + " aready contains a folder named " + currentProject->name + 
				                         ".\nPlease choose another.", true,
				                         Gtk::MESSAGE_WARNING,
				                         Gtk::BUTTONS_OK, true);
				dial2.run();
				saveProjectAs();
			}
			else{
				dir->make_directory_with_parents ();
				currentProject->setPath(dir->get_uri());
				saveProject();
			}
		}
	}
}

void MainWindow::openProject(){
	if(!checkForChanges()){
		Gtk::FileChooserDialog dial(*this, 
		                            "Open a .rune project :", 
		                            Gtk::FILE_CHOOSER_ACTION_OPEN);
		dial.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
		dial.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);
		dial.set_select_multiple (false);
		Glib::RefPtr<Gtk::FileFilter> runeFilter = Gtk::FileFilter::create();
		runeFilter->add_pattern("*.rune");
		runeFilter->set_name("Rune project");
		dial.add_filter(runeFilter);
		int response = dial.run();
		if(response == Gtk::RESPONSE_OK){
			this->reinitialize ();
			Glib::RefPtr<Gio::File> runeFile = dial.get_file();
			currentProject = Project::createFromRuneFile(runeFile->get_parent()->get_uri(),runeFile->get_uri(), this);
			this->setMainContent(this->getEditionPaned());
			this->set_title(currentProject->name + " - Rune");
		}
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
	mainVBox->pack_start(*widget, Gtk::PACK_EXPAND_WIDGET);
	mainVBox->show_all();
}

Gtk::MenuBar* MainWindow::getMainMenuBar(){
	Gtk::MenuBar* menuBar = Gtk::manage(new Gtk::MenuBar);

	// Adding menuItems
	Gtk::MenuItem* menuItemFile = 
		Gtk::manage(new Gtk::MenuItem("_Project", true));
	Gtk::MenuItem* menuItemDisplay = 
		Gtk::manage(new Gtk::MenuItem("_Display", true));
	Gtk::MenuItem* menuItemTools = 
		Gtk::manage(new Gtk::MenuItem("_Tools", true));
	Gtk::MenuItem* menuItemHelp = 
		Gtk::manage(new Gtk::MenuItem("_Help", true));
	menuBar->append(*menuItemFile);
	menuBar->append(*menuItemDisplay);
	menuBar->append(*menuItemTools);
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
	openProjectItem->signal_activate().connect(sigc::mem_fun(*this, &MainWindow::openProject));
	Gtk::ImageMenuItem* saveProjectItem = 
		Gtk::manage(new Gtk::ImageMenuItem(Gtk::Stock::SAVE));
	saveProjectItem->signal_activate().connect(sigc::mem_fun(*this, &MainWindow::saveProject));
	fileMenu->append(*saveProjectItem);
	Gtk::ImageMenuItem* saveProjectAsItem = 
		Gtk::manage(new Gtk::ImageMenuItem(Gtk::Stock::SAVE_AS));
	saveProjectAsItem->signal_activate().connect(sigc::mem_fun(*this, &MainWindow::saveProjectAs));
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

	//Adding Tools submenu
	Gtk::Menu* toolsMenu = Gtk::manage(new Gtk::Menu);
	menuItemTools->set_submenu(*toolsMenu);

	Gtk::ImageMenuItem* replacementTableItem = 
		Gtk::manage(new Gtk::ImageMenuItem("_Replacement Table",true));
	replacementTableItem->set_image(*Gtk::manage(new Gtk::Image(Gdk::Pixbuf::create_from_file("images/ReplacementTable.svg", 20,20))));
	replacementTableItem->signal_activate().connect(sigc::mem_fun(*this, &MainWindow::openReplacementTable));
	toolsMenu->append(*replacementTableItem);


	//Return menu bar.
	return menuBar;

}

Gtk::VBox* MainWindow::getWelcomeBox(){
	Gtk::VBox* externalBox = Gtk::manage(new Gtk::VBox);
	Gtk::VBox* welcomeBox = Gtk::manage(new Gtk::VBox);
	Gtk::Image* homeImage =
		Gtk::manage( new Gtk::Image("images/Title.svg"));
	welcomeBox->pack_start(*homeImage, Gtk::PACK_SHRINK);
	Gtk::Label* infoLabel = 
		Gtk::manage(
		            new Gtk::Label(
		                           "Welcome to Rune. Please create a project!"));
	welcomeBox->pack_start(*infoLabel, Gtk::PACK_SHRINK);
	externalBox->pack_start(*welcomeBox, Gtk::PACK_EXPAND_PADDING);
	return externalBox;
}

Gtk::HPaned* MainWindow::getEditionPaned(){
	editionHPaned = Gtk::manage(new Gtk::HPaned);
	Gtk::VPaned* structureVPaned = Gtk::manage(new Gtk::VPaned);
	ProjectTreeZone* projectTreeZone =
		Gtk::manage(new ProjectTreeZone(currentProject));
	projectTreeZone->signal_section_open()
		.connect(sigc::mem_fun(*this,&MainWindow::openNewTab));
	projectTreeZone->openView();
	structureVPaned->add1(*projectTreeZone);
	structureVPaned->add2(*Gtk::manage
	                      (new Gtk::Label("")));
	structureVPaned->set_position(400);

	editionHPaned->pack1(*Gtk::manage(new Gtk::Label("Need some help from there? Go see the tutorial in the help menu.")),true,false);
	editionHPaned->set_position(700);
	editionHPaned->pack2(*structureVPaned,false,false);
	show_all();
	
	return editionHPaned;

}

void MainWindow::openNewTab(Section* sec){
	if (sec->getType() == SCENE){
		Scene *scene = static_cast<Scene*>(sec);
		if(!tabOpened){
			notebook = Gtk::manage(new Gtk::Notebook);
			editionHPaned->remove(*editionHPaned->get_child1());
			editionHPaned->pack1(*notebook,true,false);
			tabOpened = true;
		}
		if(!scene->is_opened){
			Gtk::HBox* tabLabelBox = Gtk::manage(new Gtk::HBox);
			Gtk::Label* tabLabel = Gtk::manage(new Gtk::Label(sec->name));
			Gtk::Button* tabButton = Gtk::manage(new Gtk::Button);
			Gtk::Image* fileImage = 
				Gtk::manage(new Gtk::Image(Gtk::Stock::FILE, 
				                           Gtk::ICON_SIZE_MENU));
			Gtk::Image* closeImage = 
				Gtk::manage(new Gtk::Image(Gtk::Stock::CLOSE, 
				                           Gtk::ICON_SIZE_MENU));

			tabButton->set_image(*closeImage);
			tabButton->set_can_focus (false);


			tabLabelBox->pack_start(*fileImage);
			tabLabelBox->pack_start(*tabLabel);
			tabLabelBox->pack_end(*tabButton);
			tabLabelBox->show_all();
			Gtk::ScrolledWindow* sceneViewScrolled = 
				Gtk::manage(new Gtk::ScrolledWindow);
			sceneViewScrolled->set_policy(Gtk::POLICY_AUTOMATIC, 
			                              Gtk::POLICY_AUTOMATIC);
			Gtk::TextView* sceneView = Gtk::manage(new Gtk::TextView);
			scene->openFromFile();
			sceneView->get_buffer()->set_text (scene->getBody());
			sceneView->set_editable();
			sceneView->set_wrap_mode(Gtk::WRAP_WORD);
			sceneView->set_justification(Gtk::JUSTIFY_FILL);
			sceneView->set_left_margin(10);
			sceneView->set_right_margin(10);
			sceneView->set_indent(30);
			sceneView->set_border_width(10);
			sceneViewScrolled->add(*sceneView);
			gtkspell_new_attach (sceneView->gobj(),
			                     setlocale(LC_CTYPE,
			                               NULL),
			                     NULL);
			gtkspell_init ();
			int number = notebook->append_page(*sceneViewScrolled,
			                                   *tabLabelBox, 
			                                   *Gtk::manage(new Gtk::Label(sec->name)));
			notebook->set_scrollable();
			notebook->popup_enable();
			notebook->set_tab_reorderable(*sceneViewScrolled);
			scene->is_opened = true;
			tabButton->signal_clicked().connect( 
			                                    sigc::bind<Gtk::ScrolledWindow*,
			                                		Gtk::Notebook*,
			                                		Gtk::TextView*,
			                                		Scene*>(
			                                                sigc::mem_fun(*this,&MainWindow::on_close_tab),
			                                                sceneViewScrolled,
			                                                notebook,
					                                        sceneView, 
					                                        scene));
			tabMap[scene] = sceneView;
			show_all();
		}
	}
}

void MainWindow::on_close_tab(Gtk::ScrolledWindow *sw, Gtk::Notebook* nb, Gtk::TextView* tv, Scene* scene){
	if(scene->getBody().compare(tv->get_buffer()->get_text()) != 0){
		Gtk::MessageDialog dial(*currentProject->getAssociatedWindow(), 
		                        "Changes were made in " + scene->name + ".\nWhat do you want to do?", 
		                        true, Gtk::MESSAGE_WARNING, Gtk::BUTTONS_NONE, true);
		dial.add_button(Gtk::Stock::CLEAR, Gtk::RESPONSE_REJECT);
		dial.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
		dial.add_button(Gtk::Stock::SAVE, Gtk::RESPONSE_OK);
		int response = dial.run();
		if(response == Gtk::RESPONSE_OK){
			scene->setBody(tv->get_buffer()->get_text());
			scene->saveToFile();
			nb->remove_page(nb->page_num(*sw));
			scene->is_opened = false;
			tabMap.erase(tabMap.find(scene));
		}
		if(response == Gtk::RESPONSE_REJECT){
			nb->remove_page(nb->page_num(*sw));
			scene->is_opened = false;
			tabMap.erase(tabMap.find(scene));
		}
	}
	else{
		nb->remove_page(nb->page_num(*sw));
		scene->is_opened = false;
		tabMap.erase(tabMap.find(scene));
	}
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

void MainWindow::openReplacementTable(){
	ReplacementTableDialog* rpd = new ReplacementTableDialog(this);
	rpd->run();
	delete rpd;
}

MainWindow::~MainWindow(){
	delete currentProject;
}

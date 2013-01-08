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

#include "edit-window.h"

EditWindow::EditWindow(){
	currentProject = NULL;
	tabOpened = false;
	set_hide_titlebar_when_maximized();
	set_title("Rune - L'éditeur de romans");
	set_icon_from_file("images/logo.svg");
	resize(900, 600);
	
	editVBox = Gtk::manage(new Gtk::VBox);
	editVBox->show();
	add(*editVBox);
	
	Gtk::MenuBar* editMenuBar = Gtk::manage(new Gtk::MenuBar);
	editVBox->pack_start(*editMenuBar, Gtk::PACK_SHRINK);
	editVBox->pack_start(*getWelcomeBox(), Gtk::PACK_EXPAND_PADDING);
	
	Gtk::MenuItem* menuItemFile = 
		Gtk::manage(new Gtk::MenuItem("_Projet", true));
	Gtk::MenuItem* menuItemDisplay = 
		Gtk::manage(new Gtk::MenuItem("_Affichage", true));
	Gtk::MenuItem* menuItemHelp = 
		Gtk::manage(new Gtk::MenuItem("_Aide", true));
	editMenuBar->append(*menuItemFile);
	editMenuBar->append(*menuItemDisplay);
	editMenuBar->append(*menuItemHelp); 

	Gtk::Menu* fileMenu = Gtk::manage(new Gtk::Menu);
    menuItemFile->set_submenu(*fileMenu);
    
    //Création d’un item de menu à partir d’un Stock Item et ajout au menu.
    Gtk::ImageMenuItem* newProjectItem = 
		Gtk::manage(new Gtk::ImageMenuItem(Gtk::Stock::NEW));
	newProjectItem->signal_activate().connect(sigc::mem_fun(*this, &EditWindow::createNewProject));
    fileMenu->append(*newProjectItem);
	Gtk::ImageMenuItem* openProjectItem = 
		Gtk::manage(new Gtk::ImageMenuItem(Gtk::Stock::OPEN));
    fileMenu->append(*openProjectItem);
	Gtk::ImageMenuItem* saveProjectItem = 
		Gtk::manage(new Gtk::ImageMenuItem(Gtk::Stock::SAVE));
	saveProjectItem->signal_activate().connect(sigc::mem_fun(*this, &EditWindow::saveProject));
    fileMenu->append(*saveProjectItem);
	Gtk::SeparatorMenuItem* separator = Gtk::manage(new Gtk::SeparatorMenuItem);
    fileMenu->append(*separator);
	Gtk::ImageMenuItem* quitItem = 
		Gtk::manage(new Gtk::ImageMenuItem(Gtk::Stock::QUIT));
	quitItem->signal_activate().connect(sigc::ptr_fun(&Gtk::Main::quit));
    fileMenu->append(*quitItem);

		Gtk::Menu* displayMenu = Gtk::manage(new Gtk::Menu);
    menuItemDisplay->set_submenu(*displayMenu);
	
	Gtk::ImageMenuItem* lightModeItem = 
		Gtk::manage(new Gtk::ImageMenuItem("Mode _Jour",true));
	lightModeItem->set_image(*Gtk::manage(new Gtk::Image(Gdk::Pixbuf::create_from_file("images/light-mode.svg", 20,20))));
	lightModeItem->signal_activate().connect(sigc::mem_fun(*this, &EditWindow::switchToLightMode));
    displayMenu->append(*lightModeItem);

	Gtk::ImageMenuItem* darkModeItem = 
		Gtk::manage(new Gtk::ImageMenuItem("Mode _Nuit",true));
	darkModeItem->set_image(*Gtk::manage(new Gtk::Image(Gdk::Pixbuf::create_from_file("images/dark-mode.svg", 20,20))));
	darkModeItem->signal_activate().connect(sigc::mem_fun(*this,&EditWindow::switchToDarkMode));
    displayMenu->append(*darkModeItem);


	
}

Gtk::VBox* EditWindow::getWelcomeBox(){
	Gtk::VBox* welcomeBox = Gtk::manage(new Gtk::VBox);
	Gtk::Image* homeImage =
		Gtk::manage( new Gtk::Image("images/Title.svg"));
	welcomeBox->pack_start(*homeImage, Gtk::PACK_SHRINK);
	Gtk::Label* infoLabel = 
		Gtk::manage(
		    new Gtk::Label(
				"Bienvenue dans Rune. Commencez par créer un projet!"));
	welcomeBox->pack_start(*infoLabel, Gtk::PACK_SHRINK);
	return welcomeBox;
}


void EditWindow::createNewProject(){
	NewResourceDialog dialog(PROJECT,NULL,this);
	int response = dialog.run();
	if(response == Gtk::RESPONSE_OK){
		currentProject = new Project(dialog.getName(),dialog.getDescription(),this);
		set_title("Rune: " + currentProject->name);
		std::vector<Gtk::Widget*> childrenVect= editVBox->get_children();
		editVBox->remove((*childrenVect[1]));
		editVBox->pack_start(*getDoublePaned(true),Gtk::PACK_EXPAND_WIDGET);
		editVBox->show_all();
		
	}
	
}

void EditWindow::saveProject(){
	if(currentProject != NULL){
		Gtk::FileChooserDialog dial(*currentProject->associatedWindow, 
			                        "Sauvegarder" + currentProject->name + "?", 
			                        Gtk::FILE_CHOOSER_ACTION_SAVE);
		dial.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
		dial.add_button(Gtk::Stock::SAVE, Gtk::RESPONSE_OK);
		int response = dial.run();
		if(response == Gtk::RESPONSE_OK){
			
		}
	}
}

void EditWindow::switchToLightMode(){
  Glib::RefPtr<Gtk::CssProvider> css = Gtk::CssProvider::create();
  css->load_from_path("/usr/share/themes/Adwaita/gtk-3.0/gtk.css");
  css->get_named("adwaita", "0");
  Glib::RefPtr<Gdk::Screen> screen = Gdk::Screen::get_default();
  Glib::RefPtr<Gtk::StyleContext> ctx = get_style_context();
  ctx->add_provider_for_screen(screen, css, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}

void EditWindow::switchToDarkMode(){
  Glib::RefPtr<Gtk::CssProvider> css = Gtk::CssProvider::create();
  css->load_from_path("/usr/share/themes/Adwaita/gtk-3.0/gtk-dark.css");
  Glib::RefPtr<Gdk::Screen> screen = Gdk::Screen::get_default();
  Glib::RefPtr<Gtk::StyleContext> ctx = get_style_context();
  ctx->add_provider_for_screen(screen, css, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}

EditWindow::~EditWindow(){
	if (currentProject != NULL)
		delete currentProject;
}

Gtk::HPaned* EditWindow::getDoublePaned(bool newProject){
	internalHPaned = Gtk::manage(new Gtk::HPaned);
	Gtk::HPaned* externalHPaned = Gtk::manage(new Gtk::HPaned);
	Gtk::VPaned* structureVPaned = Gtk::manage(new Gtk::VPaned);
	StructureZone* structureZone =
		Gtk::manage(new StructureZone(currentProject));
	structureZone->signal_section_open()
		.connect(sigc::mem_fun(*this,&EditWindow::openNewTab));
	structureVPaned->add1(*structureZone);
	structureVPaned->add2(*Gtk::manage(new Gtk::Label("HelloWorld")));
	structureVPaned->set_position(400);
	Glib::ustring welcomeString1;
	Glib::ustring welcomeString2;
	Glib::ustring welcomeString3;
	Glib::ustring welcomeString4;
	Glib::ustring welcomeString5;
	Glib::ustring welcomeString;
	if (newProject){
		welcomeString1 = "Créez un livre, des parties, des chapitres et des scènes. Seules les scènes contiennent le corps de votre texte.";
		welcomeString2 = "\n\nCliquez sur le petit livre rouge à droite pour ajouter un nouveau livre au projet, puis effectuez un clic droit ";
		welcomeString3 = "sur votre nouveau livre pour ajouter une partie ou un chapitre, puis une scène.\n";
		welcomeString4 = "Double-cliquez sur une scène pour commencer à l'éditer.\nVous pouvez les réorganiser à tout moment par glisser/déposer.\n\n";
		welcomeString5 = "NB: Nommer les différentes sections de votre projet est optionnel. Par défaut, ils seront numérotés.";
		welcomeString = welcomeString1 + welcomeString2 + welcomeString3 + welcomeString4 + welcomeString5;
	}
	else
		welcomeString = "";
	Gtk::Label* welcome = Gtk::manage(new Gtk::Label(welcomeString));
	welcome->set_line_wrap(true);
	welcome->set_line_wrap_mode (Pango::WRAP_WORD);
	welcome->set_justify (Gtk::JUSTIFY_CENTER);
	internalHPaned->pack1(*welcome,true,false);
	internalHPaned->set_position(700);
	internalHPaned->pack2(*structureVPaned,false,false);
	show_all();
	if (!newProject){

	}
	return internalHPaned;
}

void EditWindow::openNewTab(Section* sec){
	if (sec->getType() == SCENE){
		Scene *scene = static_cast<Scene*>(sec);
	if(!tabOpened){
		notebook = Gtk::manage(new Gtk::Notebook);
		internalHPaned->remove(*internalHPaned->get_child1());
		internalHPaned->pack1(*notebook,true,false);
		tabOpened = true;
	}
	if(!scene->is_opened){
		Gtk::HBox* tabLabelBox = Gtk::manage(new Gtk::HBox);
		Gtk::Label* tabLabel = Gtk::manage(new Gtk::Label(sec->name));
		Gtk::Button* tabButton = Gtk::manage(new Gtk::Button);
		Gtk::Image* fileImage = Gtk::manage(new Gtk::Image(Gtk::Stock::FILE, Gtk::ICON_SIZE_MENU));
		Gtk::Image* closeImage = Gtk::manage(new Gtk::Image(Gtk::Stock::CLOSE, Gtk::ICON_SIZE_MENU));
		
		tabButton->set_image(*closeImage);
		tabButton->set_can_focus (false);


		tabLabelBox->pack_start(*fileImage);
		tabLabelBox->pack_start(*tabLabel);
		tabLabelBox->pack_end(*tabButton);
		tabLabelBox->show_all();
		Gtk::ScrolledWindow* sceneViewScrolled = Gtk::manage(new Gtk::ScrolledWindow);
		sceneViewScrolled->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
		Gtk::TextView* sceneView = Gtk::manage(new Gtk::TextView);
		sceneView->get_buffer()->set_text (scene->body);
		sceneView->set_editable();
		sceneView->set_wrap_mode(Gtk::WRAP_WORD);
		sceneView->set_justification(Gtk::JUSTIFY_FILL);
		sceneView->set_left_margin(10);
		sceneView->set_right_margin(10);
		sceneView->set_indent(30);
		sceneView->set_border_width(10);
		sceneViewScrolled->add(*sceneView);
		gtkspell_new_attach (sceneView->gobj(),setlocale(LC_CTYPE, NULL),NULL);
		gtkspell_init ();
		int number = notebook->append_page(*sceneViewScrolled,*tabLabelBox, *Gtk::manage(new Gtk::Label(sec->name)));
		notebook->set_scrollable();
		notebook->popup_enable();
		notebook->set_tab_reorderable(*sceneViewScrolled);
		scene->is_opened = true;
		tabButton->signal_clicked().connect( 
		sigc::bind<Gtk::ScrolledWindow*,Gtk::Notebook*,Gtk::TextView*,Scene*>( 
                    sigc::mem_fun(*this,&EditWindow::on_close_tab),
                              sceneViewScrolled,
		                      notebook,sceneView, scene));
		show_all();
	}
	}
}

void EditWindow::on_close_tab(Gtk::ScrolledWindow *sw, Gtk::Notebook* nb, Gtk::TextView* tv, Scene* scene){
	if(scene->body.compare(tv->get_buffer()->get_text()) != 0){
		Gtk::MessageDialog dial(*currentProject->associatedWindow, 
			                        "Des modifications ont été effectuées sur " + scene->name + "\nQue faire?", 
			                        true, Gtk::MESSAGE_WARNING, Gtk::BUTTONS_NONE, true);
		dial.add_button(Gtk::Stock::CLEAR, Gtk::RESPONSE_REJECT);
		dial.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
		dial.add_button(Gtk::Stock::SAVE, Gtk::RESPONSE_OK);
		int response = dial.run();
		if(response == Gtk::RESPONSE_OK){
			/*TODO save*/
				nb->remove_page(nb->page_num(*sw));
				scene->is_opened = false;
			}
		if(response == Gtk::RESPONSE_REJECT){
				nb->remove_page(nb->page_num(*sw));
				scene->is_opened = false;
			}
		}
	else{
		nb->remove_page(nb->page_num(*sw));
		scene->is_opened = false;
	}
   }
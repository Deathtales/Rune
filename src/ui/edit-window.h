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

#ifndef _EDIT_WINDOW_H_
#define _EDIT_WINDOW_H_

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/menu.h>
#include <gtkmm/menubar.h>
#include <gtkmm/separatormenuitem.h>
#include <gtkmm/stock.h>
#include <gtkmm/imagemenuitem.h>
#include <gtkmm/button.h>
#include <gtkmm/main.h>
#include <gtkmm/label.h>
#include <gtkmm/paned.h>
#include <gtkmm/textview.h>
#include <gtkmm/textbuffer.h>
#include <gtkmm/notebook.h>
#include <gtkmm/filechooserdialog.h>
#include "entities/project.h"
#include "ui/new-resource-dialog.h"
#include "ui/structure-view.h"
#include <gtkmm/cssprovider.h>
#include <iostream>
#include "ui/structure-zone.h"
extern "C"{
#include <gtkspell/gtkspell.h>
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>
}

#define MY_ENCODING "UTF-8"

class EditWindow: public Gtk::Window 
{
public:
	EditWindow();
	~EditWindow();
	Project* currentProject;

protected:
	Gtk::VBox* editVBox;
private:
	bool tabOpened;
	Gtk::Notebook* notebook;
	Gtk::HPaned* internalHPaned;
	Gtk::VBox* getWelcomeBox();
	Gtk::HPaned* getDoublePaned(bool newProject);
	void createNewProject();
	void saveProject();
	void switchToLightMode();
	void switchToDarkMode();
	void openNewTab(Section* scene);
	void on_close_tab(Gtk::ScrolledWindow* sw, Gtk::Notebook* nb, Gtk::TextView* tv, Scene* sec);
};

#endif // _EDIT_WINDOW_H_


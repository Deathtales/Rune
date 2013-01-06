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

#ifndef _STRUCTURE_MENU_H_
#define _STRUCTURE_MENU_H_
#include <gtkmm/menu.h>
#include <gtkmm/imagemenuitem.h>
#include <gtkmm/image.h>
#include <gtkmm/stock.h>
#include <gtkmm/messagedialog.h>
#include "entities/section.h"
#include "entities/project.h"
#include "entities/scene.h"
#include "ui/new-resource-dialog.h"
#include "ui/structure-view.h"
#include "project-model.h"
#include <iostream>

class StructureMenu: public Gtk::Menu 
{
public:
	StructureMenu(Project *currentProject, StructureView* view);
	StructureMenu* rearrange(int type);
	StructureView* view;
	void createNewResource(int type);
	void editResource();
	void removeResource();
	void createNewBook();
	void createNewPart();
	void createNewChapter();
	void createNewScene();
	Section* selected;

protected:

private:
	Project* currentProject;
	void openSection();
	Gtk::ImageMenuItem* newBook;
	Gtk::ImageMenuItem* newPart;
	Gtk::ImageMenuItem* newChapter;
	Gtk::ImageMenuItem* newScene;
	Gtk::ImageMenuItem* remove;
	Gtk::ImageMenuItem* edit;
	Gtk::ImageMenuItem* open;

};

#endif // _STRUCTURE_MENU_H_


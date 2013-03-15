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

#ifndef _PROJECT_TREE_ZONE_H_
#define _PROJECT_TREE_ZONE_H_
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/toolbar.h>
#include <gtkmm/menutoolbutton.h>
#include <gtkmm/image.h>
#include <gtkmm/stock.h>
#include <gtkmm/menu.h>
#include <gtkmm/imagemenuitem.h>
#include <gtkmm/image.h>
#include <gtkmm/stock.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/checkbutton.h>

#include "converters/markdown-converter.h"
#include "ui/project-tree-view.h"
#include "entities/section.h"
#include "entities/project.h"
#include "entities/scene.h"
#include "ui/new-resource-dialog.h"
#include "project-store.h"
#include "converters/book-converter.h"
#include "utils/user-configuration.h"

/** \class ProjectTreeZone
 * \brief Vbox containing menu and ProjectTreeView
 * 
 * Simple Zone containing menu and TreeView.
 * 
 */

class ProjectTreeZone: public Gtk::VBox
{
public:

	/** \brief Constructor
	 * Initializes a new ProjectTreeZone.
	 *
	 * \param[in] currentProject Current opened project
	 */
	ProjectTreeZone(Project *currentProject, UserConfiguration* uc);
	
	/** \brief Throws a signal to the main window.
	 * 
	 * Prevents the main window that the section sec must be opened.
	 * 
	 * \param[in] sec Section to open;
	 */
	void onSectionOpen(Section* sec);
	void openView();

	typedef sigc::signal<void,Section*> type_signal_section_open;
	/**<New signal type to prevent the main window that a section must be opened*/
	type_signal_section_open signal_section_open();
	/**<Throws new signal signal_section_open*/
	type_signal_section_open m_signal_section_open;
	/**<New signal to prevent the main window that a section must be opened*/
protected:

private:
	ProjectTreeView* projectTreeView; /**<TreeView contained in this VBox*/
	Gtk::Menu* projectZoneMenu; /**<Popup menu for creating/editing resources*/
	Project* currentProject; /**<Current opened project*/
	UserConfiguration* userConfiguration; /**<User defined parameters*/
	Section* selected; /**<Selected section in the ProjectTreeView*/
	Gtk::ImageMenuItem* newBook; /**<MenuItem of the projectZoneMenu*/
	Gtk::ImageMenuItem* newPart; /**<MenuItem of the projectZoneMenu*/
	Gtk::ImageMenuItem* newChapter; /**<MenuItem of the projectZoneMenu*/
	Gtk::ImageMenuItem* newScene; /**<MenuItem of the projectZoneMenu*/
	Gtk::ImageMenuItem* remove; /**<MenuItem of the projectZoneMenu*/
	Gtk::ImageMenuItem* edit; /**<MenuItem of the projectZoneMenu*/
	Gtk::ImageMenuItem* open; /**<MenuItem of the projectZoneMenu*/
	Gtk::ImageMenuItem* convert; /**<MenuItem of the projectZoneMenu*/
	Gtk::ImageMenuItem* convertToMdwn; /**<MenuItem of the bookConvertMenu*/

	/** \brief Creates of rearranges the projectZoneMenu
	 * 
	 * Creates or rearranges the projectZoneMenu with only the relevant items.
	 * 
	 * \param[in] type type of the selected section;
	 */
	Gtk::Menu* getProjectZoneMenu(int type);

	/** \brief Sends signal for opening a section.
	 * 
	 * Sends signal for opening a section.
	 */
	void openSection();
	
	/** \brief Creates a new resource
	 * 
	 * Creates a new resource to put in the treeView via a NewResourceDialog.
	 * \param[in] type type of the section to create
	 */
	void createNewResource(int type);

	/** \brief Edits a resource
	 * 
	 * Allows to change resource properties on the go.
	 */
	void editResource();

	/** \brief Removes a resource
	 * 
	 * Removes a resource both from display and Section ToC
	 */
	void removeResource();

	/** \brief Exports a book
	 * 
	 * Exports a book to Markdown format after asking for convertOptions;
	 */
	void getConvertOptions(std::map<Glib::ustring,Glib::ustring> rt);
	
	/** \brief Exports a book
	 * 
	 * Exports a book to Markdown format;
	 */
	void convertResourceToMarkdown();

	/** \brief Prepares the projectZoneMenu
	 * 
	 * Rearranges the projectZoneMenu before poping it at the right place.
	 * \param[in] sec Selected section in the TreeView.
	 * \param[in] event The GdkEventButton with the click and location info.
	 */
	void on_menu_waiting(Section* sec, GdkEventButton* event);
};


#endif // _PROJECT_TREE_ZONE_H_



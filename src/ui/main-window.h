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
 * \file main-window.h
 * \brief The main window header.
 * \author Julien Sosthène
 *
 * Main window for Rune with every hook for managing a project.
 *
 */

#ifndef _EDIT_WINDOW_H_
#define _EDIT_WINDOW_H_

#include <gtkmm/main.h>
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/paned.h>
#include <gtkmm/menu.h>
#include <gtkmm/menubar.h>
#include <gtkmm/notebook.h>
#include <gtkmm/separatormenuitem.h>
#include <gtkmm/stock.h>
#include <gtkmm/imagemenuitem.h>
#include <gtkmm/button.h>
#include <gtkmm/cssprovider.h>
#include <gtkmm/filechooserdialog.h>

#include <gtkspell/gtkspell.h>

#include <map>

#include "entities/project.h"
#include "ui/new-resource-dialog.h"
#include "ui/project-tree-zone.h"
#include "ui/replacement-table-dialog.h"

/** \class MainWindow
 * \brief Main window 
 * 
 * Main window of the programm. Launches everything else.
 * 
 */

class MainWindow: public Gtk::Window 
{
	public:

		/** \brief Constructor
		 * Initializes a new EditWindow.
		 *
		 */
		MainWindow();

		/** \brief Destructor
		 * De-initializes an EditWindow.
		 *
		 */
		~MainWindow();

	protected:
		/** \brief Asks for saving before closing
		 * 
		 * If something was changed, asks if Rune should save before closing.
		 * \return A boolean to see if it worked well.
		 */
		virtual bool on_delete_event(GdkEventAny* event);
	private:
		Project* currentProject; /**< The currently edited project */
		Gtk::VBox* mainVBox; /**< The main container in the main window */
		Gtk::HPaned* editionHPaned; /**< The main container of the edit view*/
		Gtk::Notebook* notebook; /**< The main notebook for edition view*/
		bool tabOpened; /**< Indicator to create a notebook.*/
		std::map<Scene*,Gtk::TextView*> tabMap; /**< Map containing the list of open tabs indexed by their associated section*/
		
		void reinitialize ();

		bool checkForChanges();
		
		/** \brief convinience function
		 * 
		 * Sets the default properties of a Gtk::Window to defaults specific
		 * to Rune
		 */
		void createNewProject();

		/** \brief saves a project
		 * 
		 * Saves a project according to its path.
		 */
		void saveProject();

		/** \brief saves a project after asking for a path
		 * 
		 * Sets a new path to a project, then Saves it.
		 */
		void saveProjectAs();


		/** \brief opens a project
		 * 
		 * Opens a file selector to open a project then opens the selected file.
		 */
		void openProject();

		
		/** \brief convinience function
		 * 
		 * Sets the default properties of a Gtk::Window to defaults specific
		 * to Rune
		 */
		void setDefaultProperties();

		/** \brief Changes window content
		 * 
		 * \param[in] widget A pointer to the widget to fill the main part 
		 * of the window;
		 */
		void setMainContent(Gtk::Widget* widget);
		
		/** \brief convinience function
		 * 
		 * Constructs the menu bar for the main window
		 * \return a pointer to the menuBar.
		 */
		Gtk::MenuBar* getMainMenuBar();

		/** \brief convinience function
		 * 
		 * gets a pointer to a logo screen on startup
		 * \return a pointer to the constructed box.
		 */
		Gtk::VBox* getWelcomeBox();

		/** \brief convinience function
		 * 
		 * gets a pointer to the main edition paned.
		 * \return a pointer to the constructed Gtk::HPaned;
		 */
		Gtk::HPaned* getEditionPaned();

		/** \brief Opens a tab.
		 * 
		 * Opens a new tab corresponding to a Scene.
		 * \param[in] sec pointer to the section to open
		 */
		void openNewTab(Section* sec);

		/** \brief Closes a tab.
		 * 
		 * Asks for confirmation before closing tab.
		 * \param[in] sw the container
		 * \param[in] nb the notebook
		 * \param[in] tv specific textView
		 * \param[in] scene the specific scene.
		 */
		void on_close_tab(Gtk::ScrolledWindow *sw, Gtk::Notebook* nb, Gtk::TextView* tv, Scene* scene);
		/** \brief Changes to light theme
		 * 
		 * Changes current theme for light one.
		 */
		void switchToLightMode();

		/** \brief changes to dark theme
		 * 
		 * changes current theme for dark one.
		 */
		void switchToDarkMode();

		void openReplacementTable();
};

#endif // _EDIT_WINDOW_H_


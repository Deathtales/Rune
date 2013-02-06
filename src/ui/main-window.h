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
#include <gtkmm/separatormenuitem.h>
#include <gtkmm/stock.h>
#include <gtkmm/imagemenuitem.h>
#include <gtkmm/button.h>
#include <gtkmm/cssprovider.h>

#include "entities/project.h"
#include "ui/new-resource-dialog.h"

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

	private:
		Project* currentProject; /**< The currently edited project */
		Gtk::VBox* mainVBox; /**< The main container in the main window */
		Gtk::HPaned* editionHPaned; /**< The main container of the edit view*/

		
		/** \brief convinience function
		 * 
		 * Sets the default properties of a Gtk::Window to defaults specific
		 * to Rune
		 */
		void createNewProject();
		
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
};

#endif // _EDIT_WINDOW_H_


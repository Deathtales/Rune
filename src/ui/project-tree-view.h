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

#ifndef _EDITION_VIEW_H_
#define _EDITION_VIEW_H_

#include <gtkmm/treestore.h>
#include <gtkmm/treeview.h>
#include <gtkmm/progressbar.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/cellrenderer.h>
#include <gtkmm/cellrendererprogress.h>
#include <gtkmm/tooltip.h>

#include "entities/project.h"
#include "ui/project-model.h"

/** \class ProjectTreeView
 * \brief TreeView for showing ProjectStore
 * 
 * TreeView showing the Sections with description tooltips and progressBar
 * Possible to drag and drop. 
 * 
 */

class ProjectTreeView: public Gtk::TreeView
{
public:

	Project* currentProject; /**< current Opened Project */
	/** \brief Constructor
	 * Initializes a new ProjectTreeView.
	 *
	 * \param[in] cProject Current opened project
	 */
	ProjectTreeView(Project* cProject);
	
	/** \brief Updates the treeView
	 * 
	 * Updates the treeView when Sections are modified
	 * Initializes a new ProjectTreeView.
	 * \param[in] type Type of the new section;
	 * \param[in] newSec Section to be added to the treeView. 
	 */
	void updateView(int type, Section* newSec);

	typedef sigc::signal<void,int, Section*> type_signal_section_updated;
	type_signal_section_updated signal_section_updated();
	type_signal_section_updated m_signal_section_updated;
	typedef sigc::signal<void, Section*, GdkEventButton*> type_signal_waiting_menu;
	type_signal_waiting_menu signal_waiting_menu();
	type_signal_waiting_menu m_signal_waiting_menu;
	typedef sigc::signal<void, Section*> type_signal_section_open;
	type_signal_section_open signal_section_open();
	type_signal_section_open m_signal_section_open;
	
	/** \brief Catches button press event
	 * 
	 * Catches button_press_event and throw more precise signals.
	 * 
	 * \param[in] event The GdkEventButton for getting position of the mouse;
	 */
	bool on_button_press_event(GdkEventButton* event);
	
protected:

private:

    Gtk::TreeModel::iterator selectedRowIter; 
	/**<Iterator pointing on the currently selected row.*/
	Section* selected;
	/**<Convenience.Section corresponding to the selected row*/
	ProjectModelRecord projectStructure;
	/**<The projectModelRecord for accessing columns in a row*/
	Glib::RefPtr<Gtk::TreeStore> refStructure;
	/**<The ProjectStore associated with this Tree View*/
	Glib::RefPtr<Gdk::Pixbuf> bookbuf;
	/**<Pointer to a pixbuf for a book image.*/
	Glib::RefPtr<Gdk::Pixbuf> partbuf;
	/**<Pointer to a pixbuf for a part image.*/
	Glib::RefPtr<Gdk::Pixbuf> chapterbuf;
	/**<Pointer to a pixbuf for a chapter image.*/
	Glib::RefPtr<Gdk::Pixbuf> scenebuf;
	/**<Pointer to a pixbuf for a scene image.*/

	/** \brief Gets the appropriate pixbuf.
	 * 
	 * Gets the appropriate pixbuf according to the given type. 
	 * 
	 * \param[in] type the type of the section represented by the row.
	 * \return A pointer to the Pixbuf.
	 */
	Glib::RefPtr<Gdk::Pixbuf> getPixbuf(int type);
};

#endif // _EDITION_VIEW_H_



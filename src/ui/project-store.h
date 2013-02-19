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

#ifndef _PROJECT_MODEL_H_
#define _PROJECT_MODEL_H_

#include <gtkmm/treestore.h>
#include <glibmm/ustring.h>
#include <gtkmm/treemodelcolumn.h>
#include <gtkmm/image.h>
#include <glibmm/ustring.h>
#include <gtkmm/progressbar.h>
#include <gdkmm/pixbuf.h>
#include <entities/section.h>

#include "entities/project.h"

/** \class ProjectModelRecord
 * \brief Structure of the ProjectTreeview
 * 
 * Columns of the ProjectTreeView. Contains the type and name, both displayed
 * as one column, progress for the progressBar, the section and description
 * that won't be displayed. (for linking to the actual structure and tooltip)
 * 
 */
class ProjectModelRecord: public Gtk::TreeModelColumnRecord 
{
	public:

		/** \brief Constructor
		 * Initializes a new ProjectModelRecord.
		 *
		 * Puts the right columns into it.
		 */
		ProjectModelRecord(){
			add(type);
			add(name);
			add(progress);
			add(section);
			add(description);
		}

		Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf> > type; 
		/**< Pixbuf for the icon representing the sections' type */
		Gtk::TreeModelColumn<Glib::ustring> name;
		/**< Name of the section */
		Gtk::TreeModelColumn<float> progress;
		/**< Progress (percent) to be rendered in progress bar */
		Gtk::TreeModelColumn<Section*> section;
		/**< The actual section linked to this line. Not displayed. */
		Gtk::TreeModelColumn<Glib::ustring> description;
		/**< Description on the section for tooltipping */

	protected:

	private:

};

/** \class ProjectStore
 * \brief The actual store of the project.
 * 
 * Contains the info of the treeView and allows to control drag and drop.
 * 
 */
class ProjectStore: public Gtk::TreeStore 
{
	public:
		ProjectModelRecord projectStructure; 
		/**< The associated Project Tree Model. */
		static Glib::RefPtr<ProjectStore> create(Project* cProject);
		/**< Static function for a similar work as TreeStore::create() */

	protected:
		/** \brief Constructor
		 * Initializes a new ProjectStore.
		 *
		 * Initializes columns and signals for drag and drop treatment
		 */
		ProjectStore(Project* cProject);
		
		/** \brief Overrides row_drop_possible_vfunc
		 * 
		 * Makes Drag n Drop (DND) only possible if the sections are compatible.
		 * 
		 * \param[in] dest destination row.
		 * \param[in] selectionData Selected row for DnD.
		 */
		virtual bool row_drop_possible_vfunc(const Gtk::TreeModel::Path& dest, const Gtk::SelectionData& selection_data) const;

		/** \brief When a row is created.
		 * 
		 * Useful for managing drag n drop. Inserts the Section in its parent's
		 * ToC.
		 * 
		 * \param[in] path The Gtk::TreeModel::Path to this row. (yet empty for now)
		 * \param[in] iter iterator positionned at the right row.
		 */
		void insertSection(const Gtk::TreeModel::Path path, const Gtk::TreeModel::iterator iter);

		/** \brief When a row is deleted.
		 * 
		 * Useful for managing drag n drop. Reorders the Toc of the parent
		 * Section to make current Section unreachable.
		 * 
		 * \param[in] path The Gtk::TreeModel::Path to this row.
		 */
		void unrefSection(const Gtk::TreeModel::Path path);
		
	private:
		Project* currentProject; /**< Current opened project */
};

#endif

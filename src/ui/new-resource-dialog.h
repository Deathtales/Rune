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
 * \file new-resource-dialog.h
 * \brief Dialog for creating resources, header
 * \author Julien Sosthène
 *
 * Header of the dialog for creating resources like books or chapters.
 *
 */

#ifndef _NEW_RESOURCE_DIALOG_H_
#define _NEW_RESOURCE_DIALOG_H_
#include <glibmm/ustring.h>
#include <gtkmm/dialog.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/textview.h>
#include <gtkmm/stock.h>
#include <gtkmm/scrolledwindow.h>

#include "entities/section.h"

/**
 * \enum SpecificStrings
 * \brief String types
 *
 * Convenience enumeration for getting specific strings in an array.
 */
enum SpecificStrings{
	NEWRESOURCE,
	NAMEINFO,
	SHNAMEINFO,
	DESCINFO,
	IMAGEPATH,
	
	NUMBERITEMS
	
};


/** \class NewResourceDialog
 * \brief Dialog for creating resources
 * 
 * Dialog for creating new resources as books, chapters, or characters.
 * 
 */
class NewResourceDialog: public Gtk::Dialog
{
	public:
		/** \brief Constructor
		 * Initializes a new NewResourceDialog.
		 *
		 * \param[in] type The type of the entity to create.
		 * \param[in] parent Parent window to this dialog
		 */
		NewResourceDialog(int type, Gtk::Window* parent);

		/** \brief Gets the short name of new resource
		 * 
		 * \return The string contained in the second entry
		 */
		Glib::ustring getShName();

		/** \brief Gets the name of new resource
		 * 
		 * \return The string contained in the first entry
		 */
		Glib::ustring getName();
		
		/** \brief Gets the description of new resource
		 * 
		 * \return The string contained in the third entry
		 */
		Glib::ustring getDescription();

		/** \brief Sets the short name of resource
		 * 
		 * \param[in] name the name to replace the former one.
		 */
		void setShName(Glib::ustring name);

		/** \brief Sets the name of resource
		 * 
		 * \param[in] name the name to replace the former one.
		 */
		void setName(Glib::ustring name);
		
		/** \brief Sets the description of resource
		 * 
		 * \param[in] desc the description to replace the former one.
		 */
		void setDescription(Glib::ustring desc);
	protected:

	private:
		Gtk::Box* dialogVBox ; /**<Gtk::VBox for creating the dialog*/
		Gtk::Entry* nameEntry; /**<Gtk::Entry for typing the name of the resource*/
		Gtk::Entry* shNameEntry; /**<Gtk::Entry for typing the short name of the resource*/
		Gtk::TextView* descEntry; /**<Gtk::TextView for typing the description of the resource*/

		/** \brief Gets a string specific to a resource
		 * 
		 * \param[in] type the type of the resources
		 * \param[in] specString the SpecificStrings enum element
		 */
		Glib::ustring getSpecificString(int type, int specString);
};

#endif // _NEW_RESOURCE_DIALOG_H_

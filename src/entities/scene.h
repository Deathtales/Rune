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
 * \file scene.h
 * \brief Class Scene for real text in the book.
 * \author Julien Sosthene
 *
 * Class of the only section that actually contains body text.
 *
 */

#ifndef _SCENE_H_
#define _SCENE_H_

#include "entities/section.h"
#include "glibmm/ustring.h"

/** \class Scene
 * \brief Class representing a text entity.
 * 
 * A scene is the child of a chapter.  It inherits everything from class 
 * Section, but contains a body.
 * 
 */
class Scene: public Section 
{
	public:

		Glib::ustring body; /**< The body text of the scene*/
		bool is_opened; /**< Indicates if the scene is opened in a tab.*/

		/** \brief Constructor
		 * Initializes a new section of type SCENE.
		 *
		 * \param[in] name: Section's name.
		 * \param[in] desc: A brief description of the contents (for tooltips).
		 */
		Scene(Glib::ustring name,Glib::ustring desc);


	protected:

	private:

};

#endif // _SCENE_H_


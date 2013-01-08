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
 * \file section.h
 * \brief Class Section representing a text entity in a book.
 * \author Julien Sosthene
 *
 * Class Section representing a text entity in a book. Contains
 * the enumeration for the different section types.
 *
 */

#ifndef _ENTITY_H_
#define _ENTITY_H_
#include <glibmm/ustring.h>

/**
 * \enum SectionType
 * \brief Type of a section.
 * The different Section types, from the container to the contained.
 * This gives a type to a section, since Book, Part and Chapter don't have
 * specific children classes.
 */
enum SectionType{
	PROJECT, /**< Describes a Project. For casting to Project class. */
	BOOK, /**< Describes a Book. */
	PART, /**< Describes a Part in a book. */
	CHAPTER, /**< Describes a Chapter in a Book or a Part. */
	SCENE, /**< Describes a Scene in a Chapter. */
	AKNOLEGEMENTS, /**< Describes aknoledgements - spectial Chapter. */
	DEDICATION, /**< Describes dedications _ special Chapter. */
	NONE /**< Describes an empty section: Section is not valid. */
};


/** \class Section
 * \brief Class representing a text entity.
 *
 *  Class representing a text entity in a saga: project, book, part,
 *  chapter or scene. Sections of type Project, Book, Part, Chapters can have
 *  children listed in toc (table of contents), and any section works in a 
 *  chained list represented by prevSection and nextSection.
 */
class Section
{
	public:

		Glib::ustring name; /**< Name of the section */
		Glib::ustring description; /**< Brief description of the section */
		Section* prevSection; /**< pointer to the Previous entry in the chained List */
		Section* nextSection; /**< pointer to the next entry in the chained List */
		Section* toc; /**< pointer to the child of the section.  */
		float progress; /**< Progress for displaying in a Gtk::ProgressBar*/


		/** \brief Constructor
		 * Initializes a new section.
		 *
		 * \param[in] type: a section type (see SectionType enum)
		 * \param[in] name: Section's name.
		 * \param[in] desc: A brief description of the contents (for tooltips).
		 */
		Section(int type, Glib::ustring name, Glib::ustring desc);

		/** \brief Destructor
		 * Destroys a Section.
		 */
		~Section();

		/** \brief Gets the type of section.
		 * method meant to keep type private so that it won't change by mistake.
		 * \return int representing the type of the section according to SectionType
		 */
		int getType();

		/** \brief Adds a section to the end of the list.
		 * Method that adds a section to the end of the list containing this section.
		 * \param[in, out] sec : The section to add.
			 */
		void addSection(Section* sec);

		/** \brief Adds a section to the end of the toc.
		 * Method that adds a section to the end of table of contents (children).
		 * \param[in, out] sec : The section to add.
		 */
		void addSectionToToc(Section* sec);

	protected:

	private:
		int type; /**< An int representing fonction type, according to SectionType.*/

};

#endif // _ENTITY_H_


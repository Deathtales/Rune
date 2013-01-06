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

#ifndef _ENTITY_H_
#define _ENTITY_H_
#include <glibmm/ustring.h>

enum SectionType{
	PROJECT,
	BOOK,
	PART,
	CHAPTER,
	SCENE,
	AKNOLEGEMENTS,
	DEDICATION,
	NONE
};

class Section
{
public:
	Section(int type, Glib::ustring name, Glib::ustring desc);
	~Section();
	int getType();
	Glib::ustring name;
	Glib::ustring description;
	Section* prevSection;
	Section* nextSection;
	Section* toc;
	float progress;
	bool modified;
	void addSection(Section* sec);
	void addSectionToToc(Section* sec);

protected:

private:
	int type;

};

#endif // _ENTITY_H_


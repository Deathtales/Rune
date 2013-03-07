/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * Rune
 * Copyright (C) 2013 Julien SOSTHÈNE <juliensos10@gmail.com>
 * 
 * Rune is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Rune is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _BOOK_CONVERTER_H_
#define _BOOK_CONVERTER_H_
#include "entities/scene.h"
#include "converters/convert-options.h"
#include <giomm/file.h>
#include <sstream>

class BookConverter
{
public:
protected:
	static Glib::ustring replaceCharacters(Glib::ustring text,Glib::ustring src, Glib::ustring dest);
	static Glib::ustring processReplacementTable(Scene* scene,std::map<Glib::ustring,Glib::ustring> table);
	static Glib::ustring intToUString (int val);
private:

};

#endif // _BOOK_CONVERTER_H_


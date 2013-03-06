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

#include "book-converter.h"

Glib::ustring BookConverter::replaceCharacters(Glib::ustring text,Glib::ustring src, Glib::ustring dest){
	int pos = 0;
	int occurence = text.find(src,pos);
	Glib::ustring buffer = text;
	while(occurence != Glib::ustring::npos){
		buffer.replace(occurence, src.length(), dest);
		pos = occurence + dest.length();
		occurence = buffer.find(src,pos);
	}
	return buffer;
}

Glib::ustring BookConverter::processReplacementTable(Scene* scene,
                                                     std::map<Glib::ustring,
                                                     Glib::ustring> table){
	Glib::ustring buffer = scene->getBody();
	for (std::map<Glib::ustring,Glib::ustring>::iterator it=table.begin(); it!=table.end(); ++it)
		buffer = replaceCharacters(buffer,it->first,it->second);
	return buffer;
}

Glib::ustring BookConverter::intToUString(int iVal)
{
    std::ostringstream ssIn;
    ssIn << iVal;
    Glib::ustring strOut = ssIn.str();

    return strOut;
}
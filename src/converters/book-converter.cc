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
#include <iostream>

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


Glib::ustring BookConverter::replacePair(Glib::ustring text,Glib::ustring src, Glib::ustring dest1, Glib::ustring dest2){
	int pos = 0;
	int occurence1 = text.find(src,pos);
	int occurence2 = 0;
	Glib::ustring buffer = text;
	while(occurence1 != Glib::ustring::npos){
		buffer.replace(occurence1, src.length(), dest1);
		occurence2 = buffer.find(src,occurence1 + dest1.length());
		if(occurence2 != Glib::ustring::npos){
			buffer.replace(occurence2, src.length(), dest2);
		}
		pos = occurence2 + dest2.length();
		occurence1 = buffer.find(src,pos);
	}
	return buffer;
}

Glib::ustring BookConverter::processReplacementTable(Scene* scene,
                                                     std::map<Glib::ustring,
                                                     Glib::ustring> table){
	Glib::ustring buffer = scene->getBody();
	for (std::map<Glib::ustring,Glib::ustring>::iterator it=table.begin(); it!=table.end(); ++it)
		buffer = replaceCharacters(buffer,it->first,it->second);
	buffer = replacePair(buffer,"\"","\xc2\xab\xc2\xa0", "\xc2\xa0\xc2\xbb");
	return buffer;
}

Glib::ustring BookConverter::intToUString(int iVal)
{
    std::ostringstream ssIn;
    ssIn << iVal;
    Glib::ustring strOut = ssIn.str();

    return strOut;
}
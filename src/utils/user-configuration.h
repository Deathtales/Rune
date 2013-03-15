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

#ifndef _USER_CONFIGURATION_H_
#define _USER_CONFIGURATION_H_
#include <glibmm/ustring.h>
#include <glibmm/miscutils.h>
#include <libxml++/document.h>
#include <giomm/file.h>
#include "utils/xml-utils.h"
#include <libxml++/parsers/domparser.h>

class UserConfiguration
{
public:
	UserConfiguration();
	~UserConfiguration();
	void writeConfiguration();
	std::map<Glib::ustring,Glib::ustring> getReplacementTable();
	void addToReplacementTable(Glib::ustring src, Glib::ustring dest);
	void eraseFromReplacementTable(Glib::ustring src);
protected:
	std::map<Glib::ustring,Glib::ustring> replacementTable;
	Glib::ustring homePath;
	void readConfiguration(Glib::RefPtr<Gio::File> file);
	void parseReplacementTable(xmlpp::Node* node);
	void addReplacementTableToXml(xmlpp::Element* root);
	
private:

};

#endif // _USER_CONFIGURATION_H_


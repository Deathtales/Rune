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

#ifndef _XML_UTILS_H_
#define _XML_UTILS_H_
#include <libxml++/document.h>
#include <glibmm/ustring.h>

class XmlUtils
{
public:
	static xmlpp::Node* getFirstChildNode(xmlpp::Node* node, Glib::ustring name);
	static Glib::ustring getFirstChildNodeContent(xmlpp::Node* node, Glib::ustring name);
	static Glib::ustring getAttributeFrom(xmlpp::Node* node,Glib::ustring attrib);
protected:

private:

};

#endif // _XML_UTILS_H_


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

#include "xml-utils.h"


xmlpp::Node* XmlUtils::getFirstChildNode(xmlpp::Node* node,Glib::ustring nodeName){
	xmlpp::Node* tmp = node->get_first_child();

	while(tmp && tmp->get_name() != nodeName){
		tmp = tmp->get_next_sibling();
	}
		return tmp;
	
}

Glib::ustring XmlUtils::getFirstChildNodeContent(xmlpp::Node* node,Glib::ustring name){
	const xmlpp::TextNode* textNode = 
		dynamic_cast<const xmlpp::TextNode*> (getFirstChildNode(node,name)->get_first_child());
	if(textNode){
		return textNode->get_content();
	}
	else return "";
}

Glib::ustring XmlUtils::getAttributeFrom(xmlpp::Node* node,Glib::ustring attrib){
	const xmlpp::Element* elem = 
		dynamic_cast<const xmlpp::Element*> (node);
	if(elem){
		return elem->get_attribute_value(attrib);
	}
	else return "";
}


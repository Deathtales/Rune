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

#include "entities/section.h"
#include "entities/scene.h"

Section::Section( int type, Glib::ustring name, Glib::ustring desc){
	this->name = name;
	this->description = desc;
	this->type = type;
	this->nextSection = NULL;
	this->prevSection = NULL;
	this->toc = NULL;
	this->progress = 0;
}

int Section::getType()
{
	return type;
}

Glib::ustring Section::rename(){
	Glib::ustring newName;
	std::ostringstream nameStream;
	int index = 1;
	bool res = false;
	newName = *(new Glib::ustring(this->name));
	while(!nameIsAvailableBackwards(newName)){
		res = true;
		nameStream << this->name << "_" << index;
		newName = (Glib::ustring) (nameStream.str());
		nameStream.str("");
		index++;
	}
	return newName;
}

void Section::printTree(int indent){
	int i;
	for (i=0;i<indent;i++){
		std::cout << "\t";
	}
	std::cout << "|___" << this->name << std::endl;
	if(toc){
		toc->printTree(indent + 1);
	}
	if(nextSection){
		nextSection->printTree(indent);
	}
}

void Section::addSection(Section* sec){
	if (nextSection == NULL){
		nextSection = sec;
		sec->prevSection = this;
	}
	else{
		nextSection->addSection(sec);
	}
}

void Section::addSectionToToc(Section* sec){
	if (toc == NULL)
		toc = sec;
	else{	
	toc->addSection(sec);
	}
}

void Section::saveSectionXmlUnder(xmlpp::Element* root,Glib::ustring parentPath){
	xmlpp::Element* sec = root->add_child(getStringType(this->getType()));

	Glib::ustring currentPath = 
		Gio::File::create_for_uri(parentPath)->get_child(this->rename())->get_uri();
	sec->set_attribute("name", this->name);
	xmlpp::Element* desc = sec->add_child("description");
	desc->add_child_text(this->description);
	if(this->getType() == SCENE){
		xmlpp::Element* uri = sec->add_child("uri");
		uri->add_child_text(currentPath + ".txt");
	}
	Section* next = toc;
	while(next != NULL){
		next->saveSectionXmlUnder(sec, currentPath);
		next = next->nextSection;
	}
}

xmlpp::Node* Section::getNextSectionNode(xmlpp::Node* node){
	xmlpp::Node* tmp = node;
	while (tmp->get_next_sibling()){
		tmp = tmp->get_next_sibling();
		if (tmp->get_name() == "Book" || tmp->get_name() == "Part" || 
		    tmp->get_name() == "Chapter" || tmp->get_name() == "Scene"){
			return tmp;
		}
	}
	return NULL;
}

xmlpp::Node* Section::getFirstChildNode(xmlpp::Node* node,Glib::ustring nodeName){
	xmlpp::Node* tmp = node->get_first_child();

	while(tmp && tmp->get_name() != nodeName){
		tmp = tmp->get_next_sibling();
	}
		return tmp;
	
}

Glib::ustring Section::getFirstChildNodeContent(xmlpp::Node* node,Glib::ustring name){
	const xmlpp::TextNode* textNode = 
		dynamic_cast<const xmlpp::TextNode*> (getFirstChildNode(node,name)->get_first_child());
	if(textNode){
		return textNode->get_content();
	}
	else return "";
}

Glib::ustring Section::getAttributeFrom(xmlpp::Node* node,Glib::ustring attrib){
	const xmlpp::Element* elem = 
		dynamic_cast<const xmlpp::Element*> (node);
	if(elem){
		return elem->get_attribute_value(attrib);
	}
	else return "";
}

void Section::parseSectionFromXml(xmlpp::Node* node){
	xmlpp::Node* tmp;
	Section* tocItem;
	Section* nextItem;
	Glib::ustring secName = getAttributeFrom(node, "name");
	Glib::ustring secDesc = getFirstChildNodeContent(node, "description");
	this->name = secName;
	this->description = secDesc;
	this->type = getIntType(node->get_name());
	tmp = getNextSectionNode(node->get_first_child());
	if(tmp){
		if (tmp->get_name() == "Scene"){
			tocItem = new Scene("This will Change", "This too");
		}
		else{
			tocItem = new Section(BOOK,"This will change", "this too");
		}
		tocItem->parseSectionFromXml(tmp);
		this->addSectionToToc(tocItem);
	}
	tmp = getNextSectionNode(node);
	if(tmp){
		if (tmp->get_name() == "Scene"){
			nextItem = new Scene("This will Change", "This too");
		}
		else{
			nextItem = new Section(BOOK,"This will change", "this too");
		}
		nextItem->parseSectionFromXml(tmp);
		this->addSection(nextItem);
	}
}

Glib::ustring Section::getStringType(int type){
	switch(type){
		case PROJECT:
			return "Project";
			break;
		case BOOK:
			return "Book";
			break;
		case PART:
			return "Part";
			break;
		case CHAPTER:
			return "Chapter";
			break;
		case SCENE:
			return "Scene";
			break;
		default:
			return "Scene";
			break;
	}
}

int Section::getIntType(Glib::ustring type){
	switch(type[1]){
		case 'r':
			return PROJECT;
			break;
		case 'o':
			return BOOK;
			break;
		case 'a':
			return PART;
			break;
		case 'h':
			return CHAPTER;
			break;
		case 'c':
			return SCENE;
			break;
		default:
			return SCENE;
			break;
	}
}

bool Section::nameIsAvailableForward(Glib::ustring oName){
		if(nextSection == NULL)
			return true;
		else{
			if(nextSection->name == oName){
				return false;
			}
			else{
				return nextSection->nameIsAvailableForward(oName);
			}
	}
}
bool Section::nameIsAvailableBackwards(Glib::ustring oName){
		if(prevSection == NULL)
			return true;
		else{
			if(prevSection->name == oName){
				return false;
			}
			else{
				return prevSection->nameIsAvailableBackwards(oName);
			}
	}
}

bool Section::nameIsAvailable(Glib::ustring name){
	return (nameIsAvailableForward(name) && nameIsAvailableBackwards(name));
}


Section::~Section(){

}

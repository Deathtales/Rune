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

void Section::rename(bool exceptThis){
	Glib::ustring name;
	std::ostringstream nameStream;
	int index = 1;
	name = *(new Glib::ustring(this->name));
	while(!nameIsAvailable(name,exceptThis)){
		nameStream << this->name << "_" << index;
		name = (Glib::ustring) (nameStream.str());
		nameStream.str("");
		index++;
	}
	this->name = name;
}

void Section::addSection(Section* sec){

	Section* next = this->nextSection;
	Section* prev = NULL;

	while (next != NULL){
		prev = next;
		next = next->nextSection;
	}
	if(prev != NULL){
		prev->nextSection = sec;
	}
	sec->prevSection = prev;
	sec->rename();

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
	Gio::File::create_for_uri(parentPath)->get_child(this->name)->get_uri();
	sec->set_attribute("name", this->name);
	xmlpp::Element* desc = sec->add_child("description");
	desc->add_child_text(this->description);
	if(this->getType() == SCENE){
	xmlpp::Element* uri = sec->add_child("uri");
	uri->add_child_text(currentPath);
	}
	Section* next = toc;
	while(next != NULL){
		next->saveSectionXmlUnder(sec, currentPath);
		next = next->nextSection;
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

bool Section::nameIsAvailableForward(Glib::ustring name){
		if(nextSection == NULL)
			return true;
		else{
			if(nextSection->name == name){
				return false;
			}
			else{
				return nextSection->nameIsAvailableBackwards(name);
			}
	}
}
bool Section::nameIsAvailableBackwards(Glib::ustring name){
		if(prevSection == NULL)
			return true;
		else{
			if(prevSection->name == name){
				return false;
			}
			else{
				return prevSection->nameIsAvailableBackwards(name);
			}
	}
}

bool Section::nameIsAvailable(Glib::ustring name, bool exceptThis){
	if(!exceptThis)
	return (nameIsAvailableForward(name) && nameIsAvailableBackwards(name) && (this->name != name));
	else
	return (nameIsAvailableForward(name) && nameIsAvailableBackwards(name));
}


Section::~Section(){

}

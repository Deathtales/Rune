/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * rune
 * Copyright (C) 2012 Julien SOSTHÈNE <sosthene@Redtouch>
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



#include "entities/project.h"


Project::Project(Glib::ustring title, Glib::ustring desc, Gtk::Window* parent)
: Section::Section(PROJECT,title,desc){
	this->path = "";
	this->associatedWindow = parent;
	this->changesToProject = true;
}

Project* Project::createFromRuneFile(Glib::ustring parentPath, Glib::ustring path, Gtk::Window* assocWin) 
{
	Glib::ustring name;
	Glib::ustring desc;
	xmlpp::DomParser parser;
	Project* proj;
	const xmlpp::Element* runeRoot;
	try
	{
		parser.set_substitute_entities(false);
		parser.parse_file(path);

		if(parser)
		{
			//Walk the tree:
			runeRoot = parser.get_document()->get_root_node();
			proj = new Project("This will be changed","This too", assocWin);
			proj->parseSectionFromXml((xmlpp::Node*) runeRoot);
			proj->path = parentPath;
			proj->changesToProject = false;
		}
	}
	catch(const std::exception& ex)
	{
		return NULL;
	}
	
	return (proj);
}

Project::~Project(){

}

void Project::save(){
	xmlpp::Document* xmlDoc = new xmlpp::Document();
	xmlpp::Element* root = xmlDoc->create_root_node("Project");
	root->set_attribute("name", this->name);
	xmlpp::Element* desc = root->add_child("description");
	desc->add_child_text(this->description);
	Section* next = toc;
	while(next != NULL){
		next->saveSectionXmlUnder(root, this->getPath());
		next = next->nextSection;
	}
	Glib::RefPtr<Gio::File> runeFile = 
		Gio::File::create_for_uri(this->getPath())->get_child(this->name + ".rune");
	xmlDoc->write_to_file_formatted (runeFile->get_uri());
	Glib::RefPtr<Gtk::RecentManager> recent_manager = Gtk::RecentManager::get_default();
	recent_manager->add_item(runeFile->get_uri());
}

void Project::setPath(Glib::ustring uri){
	this->path = uri;
}
Glib::ustring Project::getPath(){
	return this->path;
}

Gtk::Window* Project::getAssociatedWindow(){
	return associatedWindow;
}
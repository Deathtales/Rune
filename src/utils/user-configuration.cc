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

#include "user-configuration.h"
#include <iostream>

UserConfiguration::UserConfiguration(){
	homePath = Glib::get_home_dir();
	if (homePath == ""){
		homePath = Glib::get_current_dir();
	}
	Glib::RefPtr<Gio::File> configFile = Gio::File::create_for_path(homePath)->get_child(".rune")->get_child("userconfig.xml");
	if(!configFile->query_exists()){
		replacementTable["--"] = "\xe2\x80\x94";
		replacementTable[";"] = "\xc2\xa0;";
		replacementTable[" ;"] = "\xc2\xa0;";
		replacementTable[" :"] = "\xc2\xa0:";
		replacementTable[":"] = "\xc2\xa0:";
		replacementTable[" ?"] = "\xc2\xa0?";
		replacementTable["?"] = "\xc2\xa0?";
		replacementTable[" !"] = "\xc2\xa0!";
		replacementTable["!"] = "\xc2\xa0!";
	}
	else{
		readConfiguration(configFile);
	}
	
}

UserConfiguration::~UserConfiguration(){

}

void UserConfiguration::readConfiguration(Glib::RefPtr<Gio::File> file){
	xmlpp::DomParser parser;
	const xmlpp::Element* configRoot;
	try
	{
		parser.set_substitute_entities(false);
		parser.parse_file(file->get_path());

		if(parser)
		{
			//Walk the tree:
			configRoot = parser.get_document()->get_root_node();
			parseReplacementTable(XmlUtils::getFirstChildNode((xmlpp::Node*) configRoot, "ReplacementTable"));
			
		}
	}
	catch(const std::exception& ex)
	{
	}
	
}

void UserConfiguration::parseReplacementTable(xmlpp::Node* rtNode){
	xmlpp::Node* entry = XmlUtils::getFirstChildNode(rtNode,"Entry");
	while(entry){
		Glib::ustring fromString = XmlUtils::getAttributeFrom(entry,"from");
		if(fromString != ""){
			replacementTable[fromString]=XmlUtils::getAttributeFrom(entry,"to");
		}
		entry = entry->get_next_sibling();
	}
}

void UserConfiguration::writeConfiguration(){
	xmlpp::Document* xmlDoc = new xmlpp::Document();
	xmlpp::Element* root = xmlDoc->create_root_node("UserConfiguration");
	this->addReplacementTableToXml(root);
	Glib::RefPtr<Gio::File> configDir = Gio::File::create_for_path(homePath)->get_child(".rune");
	Glib::RefPtr<Gio::File> configFile = configDir->get_child("userconfig.xml");
	if(!configDir->query_exists()){
		configDir->make_directory_with_parents ();
	}
	xmlDoc->write_to_file_formatted (configFile->get_uri());
}

void UserConfiguration::addReplacementTableToXml(xmlpp::Element* root){
	xmlpp::Element* rt = root->add_child("ReplacementTable");
	for (std::map<Glib::ustring,Glib::ustring>::iterator it=replacementTable.begin(); it!=replacementTable.end(); ++it){
		xmlpp::Element* entry = rt->add_child("Entry");
		entry->set_attribute("from",it->first);
		entry->set_attribute("to",it->second);
	}
}

std::map<Glib::ustring,Glib::ustring> UserConfiguration::getReplacementTable(){
	return this->replacementTable;
}

void UserConfiguration::addToReplacementTable(Glib::ustring src, Glib::ustring dest){
	this->replacementTable[src] = dest;
}

void UserConfiguration::eraseFromReplacementTable(Glib::ustring src){
	replacementTable.erase(replacementTable.find(src));
}

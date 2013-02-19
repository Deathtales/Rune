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

#include "scene.h"

Scene::Scene(Glib::ustring name,Glib::ustring desc) : Section(SCENE,name,desc){
	this->is_opened = false;
	this->body = "";
	this->uri = "";
}

void Scene::saveSectionXmlUnder(xmlpp::Element* root, Glib::ustring parentPath){
	Glib::RefPtr<Gio::File> dir = Gio::File::create_for_uri(parentPath);
	Glib::RefPtr<Gio::File> sceneFile = dir->get_child(this->rename() + ".txt");
	if(this->getUri() != "" && this->getUri() != sceneFile->get_uri()){
		Glib::RefPtr<Gio::File> lastFile = Gio::File::create_for_uri(this->getUri());
		if (this->getBody() == "" && lastFile->query_exists()){
			this->setBodyFromFile(lastFile);
		}
	}
	if(!dir->query_exists()){
		dir->make_directory_with_parents ();
	}
	Glib::RefPtr<Gio::FileOutputStream> sceneStream;
	if(sceneFile->query_exists() && this->getBody() != ""){
		sceneStream = sceneFile->replace();
		sceneStream->write(this->getBody());
	}
	else{
		if(!sceneFile->query_exists()){
			sceneStream = sceneFile->create_file();
			sceneStream->write(this->getBody());
		}
	}
	if(this->getUri() != "" && this->getUri() != sceneFile->get_uri()){
		Glib::RefPtr<Gio::File> lastFile = Gio::File::create_for_uri(this->getUri());
		try{
			lastFile->remove();
			lastFile->get_parent()->remove();
			lastFile->get_parent()->get_parent()->remove();
			lastFile->get_parent()->get_parent()->get_parent()->remove();
		} catch(Glib::Error error){
		}
	}

	this->setUri(sceneFile->get_uri());
	Section::saveSectionXmlUnder (root, parentPath);
	
}

void Scene::openFromFile(){
	Glib::RefPtr<Gio::File> sceneFile = Gio::File::create_for_uri(getUri());

	if(uri != "" && sceneFile->query_exists()){
		setBodyFromFile(sceneFile);
	}
}

void Scene::saveToFile(){
	Glib::RefPtr<Gio::File> sceneFile = Gio::File::create_for_uri(getUri());
	if(uri != "" && sceneFile->query_exists()){
		Glib::RefPtr<Gio::FileOutputStream> sceneStream;
		sceneStream = sceneFile->replace();
		sceneStream->write(this->getBody());
	}
}

void Scene::parseSectionFromXml(xmlpp::Node* node){
	Section::parseSectionFromXml(node);
	this->uri = getFirstChildNodeContent(node, "uri");
}

Glib::ustring Scene::getBody(){
	return body;
}

void Scene::setBody(Glib::ustring body){
	this->body = body;
}

void Scene::setBodyFromFile(Glib::RefPtr<Gio::File> file){
	char *raw;
	gsize read_bytes;
	std::string e_tag;

	file->load_contents(raw, read_bytes, e_tag);

	Glib::ustring buffer = raw;
	this->setBody(buffer);
} 

Glib::ustring Scene::getUri(){
	return uri;
}

void Scene::setUri(Glib::ustring path){
	this->uri = path;
}
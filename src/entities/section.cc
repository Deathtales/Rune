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
	this->modified = false;
}

int Section::getType()
{
	return type;
}

void Section::addSection(Section* sec){
	if (nextSection == NULL)
		nextSection = sec;
	else{
		Section* next = this->nextSection;
		Section* prev;
		while (next != NULL){
			prev = next;
			next = next->nextSection;
		}
		prev->nextSection = sec;
		sec->prevSection = prev;
	}
}

void Section::addSectionToToc(Section* sec){
	if (toc == NULL)
		toc = sec;
	else{
		Section* next = toc;
		Section* prev;
		while (next != NULL){
			prev = next;
			next = next->nextSection;
		}
		prev->nextSection = sec;
		sec->prevSection = prev;
	}
}

Section::~Section(){

}

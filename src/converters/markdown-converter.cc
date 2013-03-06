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

#include "markdown-converter.h"

Glib::ustring MarkdownConverter::convert(Section* sec,ConvertOptions co){
	Glib::ustring buffer = "";
	Section* nextBook;
	if (sec){

		switch(sec->getType()){
			case PROJECT:
				nextBook = sec->toc;
				while(nextBook){
					buffer = buffer + convert(sec->toc,co);
					nextBook = nextBook->nextSection;
				}
				break;
			case BOOK:
				buffer = buffer + "#" + sec->name + "\n\n";
				buffer = buffer + "#####" + co.author + "\n\n";
				if(sec->nextSection || sec->prevSection){
					Section* temp = sec;
					while(temp->prevSection){
						co.bookNumber++;
						temp = sec->prevSection;
					}
					buffer = buffer + "######" + co.seriesName + " - " + intToUString(co.bookNumber) + "\n\n";
				}
				buffer = buffer + convert(sec->toc,co);
				
				break;
			case PART:
				if(co.includeShortTitle){
					buffer = buffer + "##" + sec->shortName + "\n";
					buffer = buffer + "###" + sec->name + "\n\n";
				}
				else{
					buffer = buffer + "##" + sec->name + "\n\n";
				}
				buffer = buffer + convert(sec->toc,co);
				buffer = buffer + convert(sec->nextSection,co);
				break;
			case CHAPTER:
				if(co.includeShortTitle){
					buffer = buffer + "###" + sec->shortName + "\n";
					buffer = buffer + "####" + sec->name + "\n\n";
				}
				else{
					buffer = buffer + "###" + sec->name + "\n\n";
				}
				buffer = buffer + convert(sec->toc,co);
				buffer = buffer + convert(sec->nextSection,co);
				break;
			case SCENE:
				Scene *scene = static_cast<Scene*>(sec);
				if(scene && scene->getBody() == ""){
					scene->openFromFile();
				}
				buffer = buffer + processReplacementTable(scene,co.replacementTable);
				if(sec->nextSection){
					buffer = buffer + "\n\n***\n\n";
				}
				else{
					buffer = buffer + "\n\n";
				}

				buffer = buffer + convert(sec->nextSection,co);
				break;
				
		}
	}
	return buffer;
}
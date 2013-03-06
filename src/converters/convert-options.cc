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

#include "convert-options.h"

ConvertOptions::ConvertOptions(Glib::ustring auth,bool includeShT,std::map<Glib::ustring,Glib::ustring> rT,Glib::ustring seN,int bookNb){
	this->author = auth;
	this->includeShortTitle = includeShT;
	this->replacementTable = rT;
	this->seriesName = seN;
	this->bookNumber = bookNb;
}



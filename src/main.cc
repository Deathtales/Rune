/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.cc
 * Copyright (C) 2012 Julien SOSTHÈNE <juliensos10@gmail.com>
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
#include <gtkmm/main.h>
#include <iostream>
#include "ui/main-window.h"
#include <gtkmm/cssprovider.h>
#include <gtkmm/stylecontext.h>
#include <glibmm/refptr.h>

#ifdef ENABLE_NLS
#  include <libintl.h>
#endif

/** \brief main function. 
 * Initializes a new window and runs Rune
 *
 */
int
main (int argc, char *argv[])
{
	Gtk::Main app(argc, argv);
	MainWindow mainWin;
	mainWin.show_all();
	Gtk::Main::run(mainWin);


	return 0;
}



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

#include "ui/structure-zone.h"


StructureZone::StructureZone(Project *currentProject){
	this->currentProject = currentProject;
	Gtk::ScrolledWindow* structureScroll = 
	Gtk::manage(new Gtk::ScrolledWindow);
	structureScroll->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	Gtk::MenuToolButton* newSection = Gtk::manage(new Gtk::MenuToolButton);
	newSection->set_tooltip_text("Créer un nouveau livre");
	newSection->set_icon_widget(*Gtk::manage(new Gtk::Image(Gdk::Pixbuf::create_from_file("images/new-book.svg", 20, 20, false))));
	newSection->set_arrow_tooltip_text("Créer une nouvelle section");
	structureView = Gtk::manage(new StructureView(currentProject));
	structureView->signal_section_updated().connect(sigc::mem_fun(structureView,
              &StructureView::updateView));
    structureView->signal_button_press_event()
    .connect(sigc::mem_fun(
             structureView, &StructureView::on_button_press_event), false);
	structureView->signal_waiting_menu()
    .connect(sigc::mem_fun(*this,&StructureZone::on_menu_waiting));
	structureView->signal_section_open()
    .connect(sigc::mem_fun(
             *this, &StructureZone::on_section_open));
	structureMenu = Gtk::manage(new StructureMenu(currentProject,structureView));
	newSection->signal_clicked()
    .connect(sigc::mem_fun(structureMenu,&StructureMenu::createNewBook));
	newSection->set_menu(*structureMenu->rearrange(PROJECT));
	Gtk::Toolbar* structureTools = Gtk::manage(new Gtk::Toolbar);
	structureTools->append(*newSection);
	pack_start(*structureTools, Gtk::PACK_SHRINK);
	structureScroll->add(*structureView);
	pack_start(*structureScroll,Gtk::PACK_EXPAND_WIDGET);
	show_all();
}

void StructureZone::on_menu_waiting(Section* sec, GdkEventButton* event){

	structureMenu->selected = sec;
	structureMenu->rearrange(sec->getType());
  if( (event->type == GDK_BUTTON_PRESS) && (event->button == 3) )
  {
    structureMenu->popup(event->button, event->time);

  }

}

void StructureZone::on_section_open(Section* sec){
	m_signal_section_open.emit(sec);
}


StructureZone::type_signal_section_open StructureZone::signal_section_open()
{
  return m_signal_section_open;
}
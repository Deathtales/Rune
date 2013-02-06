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

#include "structure-view.h"


StructureView::StructureView(Project* cProject){
	bookbuf = Gdk::Pixbuf::create_from_file("images/book.svg", 20, 20, true);
	partbuf = Gdk::Pixbuf::create_from_file("images/part.svg", 20, 20, true);
	chapterbuf = Gdk::Pixbuf::create_from_file("images/chapter.svg", 20, 20, true);
	scenebuf = Gdk::Pixbuf::create_from_file("images/scene.svg", 20, 20, true);
	this->currentProject = cProject;
	selected = currentProject;
	
	refStructure = ProjectModel::create(currentProject);
	set_reorderable ();
	enable_model_drag_source();
	enable_model_drag_dest();
	set_has_tooltip ();

	Gtk::TreeView::Column* symbol = 
		Gtk::manage(new Gtk::TreeView::Column);
	symbol->pack_start(projectStructure.type,true);
	symbol->pack_end(projectStructure.name,true);
	append_column(*symbol);


	Gtk::CellRendererProgress* cell = Gtk::manage(new Gtk::CellRendererProgress);
	int cols_count = append_column("",*cell);
	Gtk::TreeViewColumn* pColumn = get_column(cols_count - 1);
	if(pColumn)
  {
    pColumn->add_attribute(cell->property_value(), projectStructure.progress);
  }

	set_model(refStructure);
	set_tooltip_column(4);
	
#ifndef GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED
  signal_button_press_event()
    .connect(sigc::mem_fun(structureView, &StructureView::on_button_press_event), false);
#endif

	show_all();
}

Glib::RefPtr<Gdk::Pixbuf> StructureView::getPixbuf(int type){
	Glib::ustring path = "";
	switch (type){
		case BOOK :
			return bookbuf;
		case PART :
			return partbuf;
		case CHAPTER :
			return chapterbuf;
		case SCENE :
			return scenebuf;
		default :
			return scenebuf;
	};
}

void StructureView::updateView(int type, Section* newSec){
	Gtk::TreeModel::iterator iter;
	Gtk::TreeModel::Row row0;
	Gtk::TreeModel::Row row1;
	row0 = *selectedRowIter;
	if (type == NONE){
		refStructure->erase(selectedRowIter);
		if (newSec->nextSection != NULL)
		newSec->nextSection->prevSection = newSec->prevSection;
		if (newSec->prevSection != NULL)	
		newSec->prevSection->nextSection = newSec->nextSection;
		selected = currentProject;
	}
	else{
	if (type == BOOK && newSec != selected){
		iter = refStructure->append();
		row1 = *iter;
	}
	else if (newSec == selected){
		row1 = row0;
		iter = selectedRowIter;
	}
	else{
		iter = refStructure->append(row0.children());
		row1 = *iter;
	}
	row1[projectStructure.name] = newSec->name;
	row1[projectStructure.type] = getPixbuf(newSec->getType());
	row1[projectStructure.progress] = newSec->progress;
	row1[projectStructure.section] = newSec;
	row1[projectStructure.description] = newSec->description;
	Gtk::TreePath rowPath = refStructure->get_path(iter);
	expand_to_path (rowPath);
	}
	
}


bool StructureView::on_button_press_event(GdkEventButton* event){
	bool return_value = false;

  //Call base class, to allow normal handling,
  //such as allowing the row to be selected by the right-click:
  return_value = TreeView::on_button_press_event(event);


	if( ((event->type == GDK_BUTTON_PRESS) || (event->type == GDK_2BUTTON_PRESS)) && 
	   ((event->button == 3) || (event->button == 1)))
	{
		Glib::RefPtr<Gtk::TreeView::Selection> refSelection = get_selection();
		if(refSelection)
		{
			Gtk::TreeModel::iterator iter = refSelection->get_selected();
			if(iter)
			{
				selectedRowIter = iter;
				selected = (*iter)[projectStructure.section];
				if (event->type == GDK_BUTTON_PRESS)
					m_signal_waiting_menu.emit(selected, event);
				if (event->type == GDK_2BUTTON_PRESS)
					m_signal_section_open.emit(selected);
			}
		}

	}

  return return_value;
}

StructureView::type_signal_section_updated StructureView::signal_section_updated()
{
  return m_signal_section_updated;
}

StructureView::type_signal_waiting_menu StructureView::signal_waiting_menu ()
{
  return m_signal_waiting_menu;
}

StructureView::type_signal_section_open StructureView::signal_section_open()
{
  return m_signal_section_open;
}


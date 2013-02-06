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

#include "project-model.h"

ProjectModel::ProjectModel(Project* cProject)
{
	set_column_types(projectStructure);
	signal_row_changed().connect(sigc::mem_fun(*this,
              &ProjectModel::catchRowInserted));
	signal_row_deleted().connect(sigc::mem_fun(*this,
              &ProjectModel::catchRowDeleted));
	currentProject = cProject;
	enterTheCondition = true;
}

Glib::RefPtr<ProjectModel> ProjectModel::create(Project* cProject) 
{
	return Glib::RefPtr<ProjectModel> (new ProjectModel(cProject));
}



bool ProjectModel::row_drop_possible_vfunc(const Gtk::TreeModel::Path& dest, const Gtk::SelectionData& selection_data) const 
{
	//Make the value of the "receives drags" column determine whether a row can be
	//dragged into it:
	//Glib::RefPtr<const Gtk::TreeModel> refThis = Glib::RefPtr<const Gtk::TreeModel>(this);
	
	Glib::RefPtr<Gtk::TreeModel> refThis =
	Glib::RefPtr<Gtk::TreeModel>(const_cast<ProjectModel*>(this));
	refThis->reference();
	Gtk::TreeModel::Path path_dragged_row;
	Gtk::TreeModel::Path::get_from_selection_data(selection_data, refThis,
	path_dragged_row);
	Gtk::TreeModel::iterator dragged_iter = refThis->get_iter(path_dragged_row);
	Gtk::TreeModel::Row dragged_row = *dragged_iter;
	Section* dragged_section = dragged_row[projectStructure.section];
	int dragged_type = dragged_section->getType();
	//dest is the path that the row would have after it has been dropped:
	//But in this case we are more interested in the parent row:
	Gtk::TreeModel::Path dest_parent = dest;
	bool dest_is_not_top_level = dest_parent.up();
	if(!dest_is_not_top_level || dest_parent.empty())
	{
		return (dragged_type == BOOK);
	}
	else
	{
		ProjectModel* unconstThis = const_cast<ProjectModel*>(this);
		const_iterator iter_dest_parent = unconstThis->get_iter(dest_parent);
		if(iter_dest_parent)
		{
			Row dest_row = *iter_dest_parent;
			Section* dest_section = dest_row[projectStructure.section];
			int dest_type = dest_section->getType();
			bool receives_drag;
			switch (dest_type){
				case BOOK :
					receives_drag = (dragged_type == PART) || (dragged_type == CHAPTER);
					break;
				case PART :
					receives_drag = (dragged_type == CHAPTER);
					break;
				case CHAPTER :
					receives_drag = (dragged_type == SCENE);
					break;
				case SCENE :
					receives_drag = false;
					break;
				default:
					receives_drag = false;
			}
			return receives_drag;
		}
	}

	return Gtk::TreeStore::row_drop_possible_vfunc(dest, selection_data);
}

void ProjectModel::catchRowInserted(const Gtk::TreeModel::Path& path,const Gtk::TreeModel::iterator& iter){
	on_row_inserted(path, iter);
	insertSection(path,iter);
}

void ProjectModel::catchRowDeleted(const Gtk::TreeModel::Path& path){
	on_row_deleted(path);
	unrefSection(path);
}

void ProjectModel::insertSection(Gtk::TreeModel::Path path, Gtk::TreeModel::iterator iter){
	Gtk::TreeModel::Row row = (*iter);
	Section* sec = row[projectStructure.section];
	Gtk::TreeModel::Path originalPath = path;
	Section* parentSec;
	Glib::ustring name;
	std::ostringstream nameStream;
	int index = 1;
	if (sec != NULL){
		if (path.prev()){
			Section* prevSec = (*get_iter(path))[projectStructure.section];
			sec->prevSection = prevSec;
			prevSec->nextSection = sec;
			
		}
		else{
			sec->prevSection = NULL;
			path = originalPath;
			path.up();
			if(!path.empty()){
				parentSec = (*get_iter(path))[projectStructure.section];
				parentSec->toc = sec;
			}
			else{
				currentProject->toc = sec;
			}
		}
		path = originalPath;
		path.next();
		if (get_iter(path)){
			Section* nextSec = (*get_iter(path))[projectStructure.section];
			sec->nextSection = nextSec;
			nextSec->prevSection = sec;
		}
		else
			sec->nextSection = NULL;
		sec->rename(true);
	}
}


void ProjectModel::unrefSection(Gtk::TreeModel::Path path){
	Gtk::TreeModel::Path originalPath = path;
	if (get_iter(path)){
		Section* sec = (*get_iter(path))[projectStructure.section];
		if (path.prev()){
			Section* prevSec = (*get_iter(path))[projectStructure.section];
			prevSec->nextSection = sec;
			sec->prevSection = prevSec;
		}
		else{
			path.up();
			if(!path.empty()){
				Section* parentSec = (*get_iter(path))[projectStructure.section];
				parentSec->toc = sec;
			}
			else{
				currentProject->toc = sec;
			}
		}
	}
	else{
		if (path.prev()){
			Section* prevSec = (*get_iter(path))[projectStructure.section];
			prevSec->nextSection = NULL;
		}
		else{
			path.up();
			if(!path.empty()){
				Section* parentSec = (*get_iter(path))[projectStructure.section];
				parentSec->toc = NULL;
			}
			else{
				currentProject->toc = NULL;
			}
		}
	}

}


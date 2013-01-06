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

#ifndef _PROJECT_MODEL_H_
#define _PROJECT_MODEL_H_

#include <gtkmm/treestore.h>
#include <glibmm/ustring.h>
#include "ui/project-structure.h"
#include <iostream>
#include "entities/project.h"

class ProjectModel: public Gtk::TreeStore 
{
public:
	ProjectStructure projectStructure;
	static Glib::RefPtr<ProjectModel> create(Project* cProject);

protected:
	ProjectModel(Project* cProject);
	virtual bool row_drop_possible_vfunc(const Gtk::TreeModel::Path& dest, const Gtk::SelectionData& selection_data) const;
	void catchRowInserted(const Gtk::TreeModel::Path& path,const Gtk::TreeModel::iterator& iter);
	void catchRowDeleted(const Gtk::TreeModel::Path& path);
	void insertSection(Gtk::TreeModel::Path path, Gtk::TreeModel::iterator iter);
	void unrefSection(Gtk::TreeModel::Path path);
private:
	Project* currentProject;
};

#endif // _PROJECT_MODEL_H_


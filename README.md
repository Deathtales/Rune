![Title](https://raw.github.com/tiesselune/Rune/development/images/Title.png)



A novel planner and editor for creative writers.

# WARNING

Rune is still under heavy development. So far, it is in its 0.0.2 version (see Roadmap). It means you **cannot export your project yet**, although you can save and open saved versions. Version 0.0.3 will  be available soon with text (markdown) and html export.

Though feel free to submit a bug, or a patch anytime you wish.

# About

### Description
Rune is a GTK+ **tool for creative writers** meant to help them **plan** and **edit** their novels. 
It lets you check your planning and advancement, your plot and characters while typing in a format-abstracted manner. Rune will export your manuscript in text, HTML or Epub format.

### Licence
Rune is licensed under the GPLv3 license. Thus it is free to use, copy, distribute or modify.

### Dependencies

Rune depends on: 
* GTK+3
* libxml2
* gtkspell3
* Adwaita Theme (Theme switch won't work if not installed)

Please make sure you have all that installed before compiling Rune.

# Install

* Please make sure you have all the necessary dependencies installed on your system.
* Download and exctract Rune tarball (or clone it; branch Master is the most likely to work properly)
* Execute `./configure; make; make install` (The last has to be executed as root)
* Now you can run `rune`.

# Roadmap

## Version 0.0.x Series

### Version 0.0.1
- [x] Text view for editing
- [x] TreeView with book structure
    
### Version 0.0.2
- [x] Xml export of the text (saving the project)
- [x] Loading project
- [x] Documentation of code
- [x] English translation

### Version 0.0.3
- [ ] Text export
- [ ] HTML export

### Version 0.0.4
- [ ] Checklist for scene in list-view
- [ ] Advancement indicator

## Version 0.1 Series

### Version 0.1.0
- [ ] Make the code clearer, documentation.
- [ ] Bug Correction
- [ ] HTML View in interface

### Version 0.1.1
- [ ] Character management

### Version 0.1.2
- [ ] Epub export

### Version 0.1.3
- [ ] Chronologic view 

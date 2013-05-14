/*

Copyright (C) 2013 John W. Eaton
Copyright (C) 2011-2012 Jacob Dawid

This file is part of Octave.

Octave is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 3 of the License, or (at your
option) any later version.

Octave is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with Octave; see the file COPYING.  If not, see
<http://www.gnu.org/licenses/>.

*/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <QInputDialog>
#include <QApplication>
#include <QClipboard>
#include <QMessageBox>
#include <QLineEdit>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMenu>

#include "workspace-view.h"
#include "resource-manager.h"

workspace_view::workspace_view (QWidget *p)
  : octave_dock_widget (p), view (new QTableView (this))
{
  setObjectName ("WorkspaceView");
  setWindowIcon (QIcon (":/actions/icons/logo.png"));
  setWindowTitle (tr ("Workspace"));
  setStatusTip (tr ("View the variables in the active workspace."));

  view->setWordWrap (false);
  view->setContextMenuPolicy (Qt::CustomContextMenu);

  // Set an empty widget, so we can assign a layout to it.
  setWidget (new QWidget (this));

  // Create a new layout and add widgets to it.
  QVBoxLayout *vbox_layout = new QVBoxLayout ();
  vbox_layout->addWidget (view);
  vbox_layout->setMargin (2);

  // Set the empty widget to have our layout.
  widget ()->setLayout (vbox_layout);

  // Initialize collapse/expand state of the workspace subcategories.

  QSettings *settings = resource_manager::get_settings ();

  // Initialize column order and width of the workspace
  
  view->horizontalHeader ()->restoreState (settings->value ("workspaceview/column_state").toByteArray ());

  // Connect signals and slots.

  connect (view, SIGNAL (customContextMenuRequested (const QPoint&)),
           this, SLOT(contextmenu_requested (const QPoint&)));

  connect (this, SIGNAL (command_requested (const QString&)),
           p, SLOT (handle_command_double_clicked (const QString&)));
}

workspace_view::~workspace_view (void)
{
  QSettings *settings = resource_manager::get_settings ();

  settings->setValue("workspaceview/column_state",
                     view->horizontalHeader ()->saveState ());

  settings->sync ();
}

void
workspace_view::closeEvent (QCloseEvent *e)
{
  emit active_changed (false);
  QDockWidget::closeEvent (e);
}

void
workspace_view::contextmenu_requested (const QPoint& pos)
{
  QMenu menu (this);

  QModelIndex index = view->indexAt (pos);
  QAbstractItemModel *m = view->model ();

  // if it isnt Local, Glocal etc, allow the ctx menu
  if (index.isValid() && index.column () == 0)
    {
      index = index.sibling (index.row(), 0);

      QMap<int, QVariant> item_data = m->itemData (index);
  
      QString var_name = item_data[0].toString ();

      menu.addAction (tr ("Copy"), this,
                      SLOT (handle_contextmenu_copy ()));

      QAction *rename = menu.addAction (tr ("Rename"), this,
                                        SLOT (handle_contextmenu_rename ()));

      const workspace_model *wm = static_cast<const workspace_model *> (m);

      if (! wm->is_top_level ())
        {
          rename->setDisabled (true);
          rename->setToolTip (tr ("Only top-level symbols may be renamed."));
        }

      menu.addSeparator ();

      menu.addAction ("disp(" + var_name + ")", this,
                      SLOT (handle_contextmenu_disp ()));

      menu.addAction ("plot(" + var_name + ")", this,
                      SLOT (handle_contextmenu_plot ()));

      menu.addAction ("stem(" + var_name + ")", this,
                      SLOT (handle_contextmenu_stem ()));

      menu.exec (view->mapToGlobal (pos));
    }
}

void
workspace_view::handle_contextmenu_copy (void)
{
  QModelIndex index = view->currentIndex ();

  if (index.isValid ())
    {
      index = index.sibling(index.row(), 0);

      QAbstractItemModel *m = view->model ();

      QMap<int, QVariant> item_data = m->itemData (index);
  
      QString var_name = item_data[0].toString ();

      QClipboard *clipboard = QApplication::clipboard ();

      clipboard->setText (var_name);
    }
}

void
workspace_view::handle_contextmenu_rename (void)
{
  QModelIndex index = view->currentIndex ();

  if (index.isValid ())
    {
      index = index.sibling(index.row(), 0);

      QAbstractItemModel *m = view->model ();

      QMap<int, QVariant> item_data = m->itemData (index);
  
      QString var_name = item_data[0].toString ();

      QInputDialog* inputDialog = new QInputDialog ();

      inputDialog->setOptions (QInputDialog::NoButtons);

      bool ok = false;

      QString new_name
        =  inputDialog->getText (0, "Rename Variable", "New name:",
                                 QLineEdit::Normal, var_name, &ok);

      if (ok && ! new_name.isEmpty ())
        m->setData (index, new_name, Qt::EditRole);
    }
}

void
workspace_view::handle_contextmenu_disp (void)
{
  relay_contextmenu_command ("disp"); 
}

void
workspace_view::handle_contextmenu_plot (void)
{
  relay_contextmenu_command ("figure;\nplot"); 
}

void
workspace_view::handle_contextmenu_stem (void)
{
  relay_contextmenu_command ("figure;\nstem"); 
}

void
workspace_view::relay_contextmenu_command (const QString& cmdname)
{
  QModelIndex index = view->currentIndex ();

  if (index.isValid ())
    {
      index = index.sibling(index.row(), 0);

      QAbstractItemModel *m = view->model ();

      QMap<int, QVariant> item_data = m->itemData (index);
  
      QString var_name = item_data[0].toString ();

      emit command_requested (cmdname + "(" + var_name + ")\n");
    }
}

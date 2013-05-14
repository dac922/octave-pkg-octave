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

#ifndef TERMINALDOCKWIDGET_H
#define TERMINALDOCKWIDGET_H

#include <QString>

#include "QTerminal.h"
#include "octave-dock-widget.h"

class terminal_dock_widget : public octave_dock_widget
{
  Q_OBJECT

public:

  terminal_dock_widget (QWidget *parent = 0);

signals:

public slots:

  void notice_settings (const QSettings *settings);

  void relay_command (const QString& command);

  void copyClipboard (void);

  void pasteClipboard (void);

  void focus (void);

signals:

  void notice_settings_signal (const QSettings *settings); 

  void relay_command_signal (const QString& command);

  void copyClipboard_signal (void);

  void pasteClipboard_signal (void);

private:

  QTerminal *terminal;
};

#endif // TERMINALDOCKWIDGET_H

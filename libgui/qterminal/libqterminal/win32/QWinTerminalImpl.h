/*

Copyright (C) 2011 Michael Goffioul.

This file is part of QConsole.

Foobar is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

QConsole is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef __QConsole_h__
#define __QConsole_h__ 1

#include <QWidget>
#include "QTerminalInterface.h"
class QFocusEvent;
class QKeyEvent;
class QPaintEvent;
class QResizeEvent;
class QWheelEvent;

class QConsolePrivate;
class QConsoleThread;
class QConsoleView;

//////////////////////////////////////////////////////////////////////////////

class QWinTerminalImpl : public QTerminalInterface
{
  Q_OBJECT
  friend class QConsolePrivate;
  friend class QConsoleThread;
  friend class QConsoleView;

public:
  QWinTerminalImpl (QWidget* parent = 0);
  QWinTerminalImpl (const QString& cmd, QWidget* parent = 0);
  ~QWinTerminalImpl (void);

  void setTerminalFont (const QFont& font);
  void setSize (int columns, int lines);
  void sendText (const QString& s);

public slots:
  void copyClipboard (void);
  void pasteClipboard (void);

signals:
  void terminated (void);
  void titleChanged (const QString&);

protected:
  void viewPaintEvent (QConsoleView*, QPaintEvent*);
  void viewResizeEvent (QConsoleView*, QResizeEvent*);
  void wheelEvent (QWheelEvent*);
  void focusInEvent (QFocusEvent*);
  bool winEvent (MSG*, long*);
  virtual void start (void);

private slots:
  void scrollValueChanged (int value);
  void monitorConsole (void);

private:
  QConsolePrivate* d;
};

//////////////////////////////////////////////////////////////////////////////

#endif // __QConsole_h__

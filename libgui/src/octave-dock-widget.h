/*

Copyright (C) 2012-2013 Richard Crozier

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

#if !defined (octave_dock_widget_h)
#define octave_dock_widget_h 1

#include <QDockWidget>
#include <QSettings>

class octave_dock_widget : public QDockWidget
{
  Q_OBJECT

public:

  octave_dock_widget (QWidget *p)
    : QDockWidget (p)
  {
    connect (this, SIGNAL (visibilityChanged (bool)),
             this, SLOT (handle_visibility_changed (bool)));

    connect (this, SIGNAL (topLevelChanged (bool)),
             this, SLOT (top_level_changed (bool)));

    connect (p, SIGNAL (settings_changed (const QSettings*)),
             this, SLOT (notice_settings (const QSettings*)));
  }

  virtual ~octave_dock_widget () { }

  virtual void connect_visibility_changed (void)
  {
    connect (this, SIGNAL (visibilityChanged (bool)),
             this, SLOT (handle_visibility (bool)));
  }


signals:

  /** Custom signal that tells whether a user has clicked away
   *  that dock widget, i.e the active dock widget has
   *  changed. */
  void active_changed (bool active);

protected:

  virtual void closeEvent (QCloseEvent *e)
  {
    emit active_changed (false);
    QDockWidget::closeEvent (e);
  }

public slots:

  virtual void focus (void)
  {
    if (! isVisible ())
      setVisible (true);

    setFocus ();
    activateWindow ();
    raise ();
  }

  virtual void handle_visibility (bool visible)
  {
    if (visible && ! isFloating ())
      focus ();
  }

  virtual void notice_settings (const QSettings*)
  {
  }

protected slots:

  /** Slot to steer changing visibility from outside. */
  virtual void handle_visibility_changed (bool visible)
  {
    if (visible)
      emit active_changed (true);
  }

  /** Slot when floating property changes */
  virtual void top_level_changed (bool floating)
  {
    if (floating)
      {
        // Make a window from the widget when floating and make it
        // visible again since setWindowFlags hides it.
        setWindowFlags (Qt::Window);
        show();
      }
  }
};

#endif

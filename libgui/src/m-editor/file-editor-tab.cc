/*

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

#ifdef HAVE_QSCINTILLA

#include <Qsci/qsciapis.h>
// Not available in the Debian repos yet!
// #include <Qsci/qscilexeroctave.h>
#include "lexer-octave-gui.h"
#include <Qsci/qscilexercpp.h>
#include <Qsci/qscilexerbash.h>
#include <Qsci/qscilexerperl.h>
#include <Qsci/qscilexerbatch.h>
#include <Qsci/qscilexerdiff.h>
#include "resource-manager.h"
#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QVBoxLayout>

#include "file-editor-tab.h"
#include "file-editor.h"
#include "octave-link.h"

#include "debug.h"
#include "oct-env.h"

// Make parent null for the file editor tab so that warning
// WindowModal messages don't affect grandparents.
file_editor_tab::file_editor_tab (QString directory)
{
  // Make sure there is a slash at the end of the directory name
  // for identification when saved later.
  if (directory.count () && directory.at (directory.count () - 1) != '/')
    directory.append ("/");
  _file_name = directory;
  _edit_area = new QsciScintilla (this);

  // Leave the find dialog box out of memory until requested.
  _find_dialog = 0;
  _find_dialog_is_visible = false;

  // symbols
  _edit_area->setMarginType (1, QsciScintilla::SymbolMargin);
  _edit_area->setMarginSensitivity (1, true);
  _edit_area->markerDefine (QsciScintilla::RightTriangle, bookmark);
  _edit_area->markerDefine (QPixmap (":/actions/icons/redled.png"),
                            breakpoint);
  _edit_area->markerDefine (QPixmap (":/actions/icons/arrow_right.png"),
                            debugger_position);

  connect (_edit_area, SIGNAL (marginClicked (int, int,
                                              Qt::KeyboardModifiers)),
           this, SLOT (handle_margin_clicked (int, int,
                                              Qt::KeyboardModifiers)));

  // line numbers
  _edit_area->setMarginsForegroundColor(QColor(96,96,96));
  _edit_area->setMarginsBackgroundColor(QColor(232,232,220));
  _edit_area->setMarginType (2, QsciScintilla::TextMargin);

  // code folding
  _edit_area->setMarginType (3, QsciScintilla::SymbolMargin);
  _edit_area->setFolding (QsciScintilla::BoxedTreeFoldStyle , 3);

  //highlight current line color
  _edit_area->setCaretLineBackgroundColor(QColor(245,245,245));

  // other features
  _edit_area->setBraceMatching (QsciScintilla::StrictBraceMatch);
  _edit_area->setAutoIndent (true);
  _edit_area->setIndentationWidth (2);
  _edit_area->setIndentationsUseTabs (false);

  _edit_area->setUtf8 (true);

  // auto completion
  _edit_area->autoCompleteFromAll ();
  _edit_area->setAutoCompletionSource(QsciScintilla::AcsAll);

  QVBoxLayout *edit_area_layout = new QVBoxLayout ();
  edit_area_layout->addWidget (_edit_area);
  edit_area_layout->setMargin (0);
  setLayout (edit_area_layout);

  // connect modified signal
  connect (_edit_area, SIGNAL (modificationChanged (bool)),
           this, SLOT (update_window_title (bool)));
  connect (_edit_area, SIGNAL (copyAvailable (bool)),
           this, SLOT (handle_copy_available (bool)));
  connect (&_file_system_watcher, SIGNAL (fileChanged (QString)),
           this, SLOT (file_has_changed (QString)));

  notice_settings ();
}

file_editor_tab::~file_editor_tab ()
{
  // Destroy items attached to _edit_area.
  QsciLexer *lexer = _edit_area->lexer ();
  if (lexer)
    {
      delete lexer;
      _edit_area->setLexer(0);
    }
  if (_find_dialog)
    {
      delete _find_dialog;
      _find_dialog = 0;
    }

  // Destroy _edit_area.
  delete _edit_area;
}

void
file_editor_tab::closeEvent (QCloseEvent *e)
{
  // ignore close event if file is not saved and user cancels
  // closing this window
  if (check_file_modified () == QMessageBox::Cancel)
    {
      e->ignore ();
    }
  else
    {
      e->accept();
    }
}

void
file_editor_tab::set_file_name (const QString& fileName)
{
  // update tracked file if we really have a file on disk
  QStringList trackedFiles = _file_system_watcher.files ();
  if (!trackedFiles.isEmpty ())
    _file_system_watcher.removePath (_file_name);
  if (!fileName.isEmpty ())
    _file_system_watcher.addPath (fileName);
  _file_name = fileName;

  // update lexer after _file_name change
  update_lexer ();

  // update the file editor with current editing directory
  emit editor_state_changed (_copy_available, QDir::cleanPath (_file_name));
  // add the new file to the mru list
  emit mru_add_file (QDir::cleanPath (_file_name));
}

void
file_editor_tab::handle_margin_clicked(int margin, int line,
                                       Qt::KeyboardModifiers state)
{
  if (margin == 1)
    {
      unsigned int markers_mask = _edit_area->markersAtLine (line);

      if (state & Qt::ControlModifier)
        {
          if (markers_mask && (1 << bookmark))
            _edit_area->markerDelete(line,bookmark);
          else
            _edit_area->markerAdd(line,bookmark);
        }
      else
        {
          if (markers_mask && (1 << breakpoint))
            {
              request_remove_breakpoint (line);
            }
          else
            {
              request_add_breakpoint (line);
            }
        }
    }
}

void
file_editor_tab::update_lexer ()
{
  QsciLexer *lexer = _edit_area->lexer ();
  delete lexer;

  if (_file_name.endsWith (".m") || _file_name.endsWith (".M"))
    {
      lexer = new lexer_octave_gui ();
    }
  else if (_file_name.endsWith (".c")
           || _file_name.endsWith (".cc")
           || _file_name.endsWith (".cpp")
           || _file_name.endsWith (".cxx")
           || _file_name.endsWith (".c++")
           || _file_name.endsWith (".h")
           || _file_name.endsWith (".hh")
           || _file_name.endsWith (".hpp")
           || _file_name.endsWith (".h++"))
    {
      lexer = new QsciLexerCPP ();
    }
  else if (_file_name.endsWith (".pl"))
    {
      lexer = new QsciLexerPerl ();
    }
  else if (_file_name.endsWith (".bat"))
    {
      lexer = new QsciLexerBatch ();
    }
  else if (_file_name.endsWith (".diff"))
    {
      lexer = new QsciLexerDiff ();
    }
  else // Default to bash lexer.
    {
      lexer = new QsciLexerBash ();
    }

  QSettings *settings = resource_manager::get_settings ();

  // Editor font (default or from settings)
  if (settings)
    lexer->setDefaultFont (QFont (
                                  settings->value ("editor/fontName",
                                                   "Courier").toString (),
                                  settings->value ("editor/fontSize",
                                                   10).toInt ()));

  // TODO: Autoindent not working as it should
  lexer->setAutoIndentStyle (QsciScintilla::AiMaintain ||
                             QsciScintilla::AiOpening  ||
                             QsciScintilla::AiClosing);

  _edit_area->setLexer (lexer);
}

// slot for fetab_set_focus: sets the focus to the current edit area
void
file_editor_tab::set_focus (const QWidget* ID)
{
  if (ID != this)
    return;
  _edit_area->setFocus ();
}

void
file_editor_tab::undo (const QWidget* ID)
{
  if (ID != this)
    return;

  _edit_area->undo ();
}

void
file_editor_tab::redo (const QWidget* ID)
{
  if (ID != this)
    return;

  _edit_area->redo ();
}

void
file_editor_tab::copy (const QWidget* ID)
{
  if (ID != this)
    return;

  _edit_area->copy ();
}

void
file_editor_tab::cut (const QWidget* ID)
{
  if (ID != this)
    return;

  _edit_area->cut ();
}

void
file_editor_tab::paste (const QWidget* ID)
{
  if (ID != this)
    return;

  _edit_area->paste ();
}

void
file_editor_tab::save_file (const QWidget* ID)
{
  if (ID != this)
    return;

  save_file (_file_name);
}
void

file_editor_tab::save_file (const QWidget* ID, const QString& fileName, bool remove_on_success)
{
  if (ID != this)
    return;

  save_file (fileName, remove_on_success);
}

void
file_editor_tab::save_file_as (const QWidget* ID)
{
  if (ID != this)
    return;

  save_file_as ();
}

void
file_editor_tab::run_file_callback (void)
{
  // Maybe someday we will do something here?
}

void
file_editor_tab::run_file (const QWidget* ID)
{
  if (ID != this)
    return;

  if (_edit_area->isModified ())
    save_file (_file_name);

  QFileInfo file_info (_file_name);
  QString path = file_info.absolutePath ();
  QString current_path
    = QString::fromStdString (octave_link::last_working_directory ());
  QString function_name = file_info.fileName ();

  // We have to cut off the suffix, because octave appends it.
  function_name.chop (file_info.suffix ().length () + 1);
  emit process_octave_code (QString ("cd \'%1\'\n%2\n")
                    .arg(path).arg (function_name));
 
  // TODO: Sending a run event crashes for long scripts. Find out why.
  // octave_link::post_event
  //   (this, &file_editor_tab::run_file_callback, _file_name.toStdString ()));
}

void
file_editor_tab::toggle_bookmark (const QWidget* ID)
{
  if (ID != this)
    return;

  int line, cur;
  _edit_area->getCursorPosition (&line,&cur);
  if ( _edit_area->markersAtLine (line) && (1 << bookmark) )
    _edit_area->markerDelete (line, bookmark);
  else
    _edit_area->markerAdd (line, bookmark);
}

void
file_editor_tab::next_bookmark (const QWidget* ID)
{
  if (ID != this)
    return;

  int line, cur, nextline;
  _edit_area->getCursorPosition (&line, &cur);
  if ( _edit_area->markersAtLine (line) && (1 << bookmark) )
    line++; // we have a breakpoint here, so start search from next line
  nextline = _edit_area->markerFindNext (line, (1 << bookmark));
  _edit_area->setCursorPosition (nextline, 0);
}

void
file_editor_tab::previous_bookmark (const QWidget* ID)
{
  if (ID != this)
    return;

  int line, cur, prevline;
  _edit_area->getCursorPosition (&line, &cur);
  if ( _edit_area->markersAtLine (line) && (1 << bookmark) )
    line--; // we have a breakpoint here, so start search from prev line
  prevline = _edit_area->markerFindPrevious (line, (1 << bookmark));
  _edit_area->setCursorPosition (prevline, 0);
}

void
file_editor_tab::remove_bookmark (const QWidget* ID)
{
  if (ID != this)
    return;

  _edit_area->markerDeleteAll (bookmark);
}

void
file_editor_tab::add_breakpoint_callback (const bp_info& info)
{
  bp_table::intmap intmap;
  intmap[0] = info.line + 1;

  std::string previous_directory = octave_env::get_current_directory ();
  octave_env::chdir (info.path);
  intmap = bp_table::add_breakpoint (info.function_name, intmap);
  octave_env::chdir (previous_directory);

  if (intmap.size () > 0)
    {
    // FIXME -- Check file.
      _edit_area->markerAdd (info.line, breakpoint);
    }
}

void
file_editor_tab::remove_breakpoint_callback (const bp_info& info)
{
  bp_table::intmap intmap;
  intmap[0] = info.line;

  std::string previous_directory = octave_env::get_current_directory ();
  octave_env::chdir (info.path);
  bp_table::remove_breakpoint (info.function_name, intmap);
  octave_env::chdir (previous_directory);

  // FIXME -- check result
  bool success = true;

  if (success)
    {
      // FIXME -- check file.
      _edit_area->markerDelete (info.line, breakpoint);
    }
}

void
file_editor_tab::remove_all_breakpoints_callback (const bp_info& info)
{
  bp_table::intmap intmap;
  std::string previous_directory = octave_env::get_current_directory ();
  octave_env::chdir (info.path);
  intmap = bp_table::remove_all_breakpoints_in_file (info.function_name, true);
  octave_env::chdir (previous_directory);

  if (intmap.size() > 0)
    _edit_area->markerDeleteAll (breakpoint);
}

void
file_editor_tab::request_add_breakpoint (int line)
{
  QFileInfo file_info (_file_name);
  QString path = file_info.absolutePath ();
  QString function_name = file_info.fileName ();

  // We have to cut off the suffix, because octave appends it.
  function_name.chop (file_info.suffix ().length () + 1);

  bp_info info (path, function_name, line);

  octave_link::post_event
    (this, &file_editor_tab::add_breakpoint_callback, info);
}

void
file_editor_tab::request_remove_breakpoint (int line)
{
  QFileInfo file_info (_file_name);
  QString path = file_info.absolutePath ();
  QString function_name = file_info.fileName ();

  // We have to cut off the suffix, because octave appends it.
  function_name.chop (file_info.suffix ().length () + 1);

  bp_info info (path, function_name, line);

  octave_link::post_event
    (this, &file_editor_tab::remove_breakpoint_callback, info);
}

void
file_editor_tab::toggle_breakpoint (const QWidget* ID)
{
  if (ID != this)
    return;

  int line, cur;
  _edit_area->getCursorPosition (&line, &cur);
  if ( _edit_area->markersAtLine (line) && (1 << breakpoint) )
    request_remove_breakpoint (line);
  else
    request_add_breakpoint (line);
}

void
file_editor_tab::next_breakpoint (const QWidget* ID)
{
  if (ID != this)
    return;

  int line, cur, nextline;
  _edit_area->getCursorPosition (&line, &cur);
  if ( _edit_area->markersAtLine (line) && (1 << breakpoint) )
    line++; // we have a breakpoint here, so start search from next line
  nextline = _edit_area->markerFindNext (line, (1 << breakpoint));
  _edit_area->setCursorPosition (nextline, 0);
}

void
file_editor_tab::previous_breakpoint (const QWidget* ID)
{
  if (ID != this)
    return;

  int line, cur, prevline;
  _edit_area->getCursorPosition (&line, &cur);
  if ( _edit_area->markersAtLine (line) && (1 << breakpoint) )
    line--; // we have a breakpoint here, so start search from prev line
  prevline = _edit_area->markerFindPrevious (line, (1 << breakpoint));
  _edit_area->setCursorPosition (prevline, 0);
}

void
file_editor_tab::remove_all_breakpoints (const QWidget* ID)
{
  if (ID != this)
    return;

  QFileInfo file_info (_file_name);
  QString path = file_info.absolutePath ();
  QString function_name = file_info.fileName ();

  // We have to cut off the suffix, because octave appends it.
  function_name.chop (file_info.suffix ().length () + 1);

  bp_info info (path, function_name, 0);

  octave_link::post_event
    (this, &file_editor_tab::remove_all_breakpoints_callback, info);
}

void
file_editor_tab::comment_selected_text (const QWidget* ID)
{
  if (ID != this)
    return;

  do_comment_selected_text (true);
}

void
file_editor_tab::uncomment_selected_text (const QWidget* ID)
{
  if (ID != this)
    return;

  do_comment_selected_text (false);
}

void
file_editor_tab::handle_find_dialog_finished (int)
{
  // Find dialog is going to hide.  Save location of window for
  // when it is reshown.
  _find_dialog_geometry = _find_dialog->geometry ();
  _find_dialog_is_visible = false;
}

void
file_editor_tab::find (const QWidget* ID)
{
  if (ID != this)
    return;

  // The find_dialog feature doesn't need a slot for return info.
  // Rather than Qt::DeleteOnClose, let the find feature hang about
  // in case it contains useful information like previous searches
  // and so on.  Perhaps one find dialog for the whole editor is
  // better, but individual find dialogs has the nice feature of
  // retaining position per file editor tabs, which can be undocked.

  if (!_find_dialog)
    {
       _find_dialog = new find_dialog (_edit_area);
      connect (_find_dialog, SIGNAL (finished (int)),
               this, SLOT (handle_find_dialog_finished (int)));
      _find_dialog->setWindowModality (Qt::NonModal);
      _find_dialog_geometry = _find_dialog->geometry ();
    }

  if (!_find_dialog->isVisible ())
    {
      _find_dialog->setGeometry (_find_dialog_geometry);
      _find_dialog->show ();
      _find_dialog_is_visible = true;
    }

  _find_dialog->activateWindow ();
  _find_dialog->init_search_text ();

}

void
file_editor_tab::do_comment_selected_text (bool comment)
{
  if ( _edit_area->hasSelectedText() )
    {
      int lineFrom, lineTo, colFrom, colTo, i;
      _edit_area->getSelection (&lineFrom,&colFrom,&lineTo,&colTo);
      if ( colTo == 0 )  // the beginning of last line is not selected
        lineTo--;        // stop at line above
      _edit_area->beginUndoAction ();
      for ( i=lineFrom; i<=lineTo; i++ )
        {
          if ( comment )
            _edit_area->insertAt("%",i,0);
          else
            {
              QString line(_edit_area->text(i));
              if ( line.startsWith("%") )
                {
                  _edit_area->setSelection(i,0,i,1);
                  _edit_area->removeSelectedText();
                }
            }
        }
      _edit_area->endUndoAction ();
    }
}

void
file_editor_tab::update_window_title (bool modified)
{
  QString title ("");
  QString tooltip ("");
  if (_file_name.isEmpty () || _file_name.at (_file_name.count () - 1) == '/')
    title = tr("<unnamed>");
  else
    {
      if ( _long_title )
        title = _file_name;
      else
        {
          QFileInfo file(_file_name);
          title = file.fileName();
          tooltip = _file_name;
        }
    }

  if ( modified )
    {
      emit file_name_changed (title.prepend("* "), tooltip);
    }
  else
    emit file_name_changed (title, tooltip);
}

void
file_editor_tab::handle_copy_available(bool enableCopy)
{
  _copy_available = enableCopy;
  emit editor_state_changed (_copy_available, QDir::cleanPath (_file_name));
}

int
file_editor_tab::check_file_modified ()
{
  int decision = QMessageBox::Yes;
  if (_edit_area->isModified ())
    {
      // File is modified but not saved, ask user what to do.  The file
      // editor tab can't be made parent because it may be deleted depending
      // upon the response.  Instead, change the _edit_area to read only.
      QMessageBox* msgBox = new QMessageBox (
          QMessageBox::Warning, tr ("Octave Editor"),
          tr ("The file\n"
              "%1\n"
              "is about to be closed but has been modified.\n"
              "Do you want to cancel closing, save or discard the changes?").
          arg (_file_name),
          QMessageBox::Save | QMessageBox::Cancel | QMessageBox::Discard, 0);
      msgBox->setDefaultButton (QMessageBox::Save);
      _edit_area->setReadOnly (true);
      connect (msgBox, SIGNAL (finished (int)),
               this, SLOT (handle_file_modified_answer (int)));
      msgBox->setWindowModality (Qt::NonModal);
      msgBox->setAttribute (Qt::WA_DeleteOnClose);
      msgBox->show ();
      return (QMessageBox::Cancel);
    }
  else
    {
      // Nothing was modified, just remove from editor.
      emit tab_remove_request ();
    }
 
  return (decision);
}

void
file_editor_tab::handle_file_modified_answer (int decision)
{
  if (decision == QMessageBox::Save)
    {
      // Save file, then remove from editor.
      save_file (_file_name, true);
    }
  else if (decision == QMessageBox::Discard)
    {
      // User doesn't want to save, just remove from editor.
      emit tab_remove_request ();
    }
  else
    {
      // User canceled, allow editing again.
      _edit_area->setReadOnly (false);
    }
}

void
file_editor_tab::set_modified (bool modified)
{
  _edit_area->setModified (modified);
}

QString
file_editor_tab::load_file(const QString& fileName)
{
  QFile file (fileName);
  if (!file.open (QFile::ReadOnly))
    {
      return file.errorString ();
    }

  QTextStream in (&file);
  QApplication::setOverrideCursor (Qt::WaitCursor);
  _edit_area->setText (in.readAll ());
  QApplication::restoreOverrideCursor ();

  set_file_name (fileName);
  update_window_title (false); // window title (no modification)
  _edit_area->setModified (false); // loaded file is not modified yet

  return QString ();
}

void
file_editor_tab::new_file ()
{
  update_window_title (false); // window title (no modification)
  _edit_area->setText ("");
  _edit_area->setModified (false); // new file is not modified yet
}

void
file_editor_tab::save_file (const QString& saveFileName, bool remove_on_success)
{
  // If it is a new file with no name, signal that saveFileAs
  // should be performed.
  if (saveFileName.isEmpty () || saveFileName.at (saveFileName.count () - 1) == '/')
     {
      save_file_as (remove_on_success);
      return;
    }

  // stop watching file
  QStringList trackedFiles = _file_system_watcher.files ();
  if (!trackedFiles.isEmpty ())
    _file_system_watcher.removePath (saveFileName);

  // open the file for writing
  QFile file (saveFileName);
  if (!file.open (QIODevice::WriteOnly))
    {
      // Unsuccessful, begin watching file again if it was being
      // watched previously.
      if (trackedFiles.contains (saveFileName))
        _file_system_watcher.addPath (saveFileName);

      // Create a NonModal message about error.
      QMessageBox* msgBox = new QMessageBox (
              QMessageBox::Critical, tr ("Octave Editor"),
              tr ("Could not open file %1 for write:\n%2.").
              arg (saveFileName).arg (file.errorString ()),
              QMessageBox::Ok, 0);
      msgBox->setWindowModality (Qt::NonModal);
      msgBox->setAttribute (Qt::WA_DeleteOnClose);
      msgBox->show ();
      return;
    }

  // save the contents into the file
  QTextStream out (&file);
  QApplication::setOverrideCursor (Qt::WaitCursor);
  out << _edit_area->text ();
  QApplication::restoreOverrideCursor ();
  file.close();

  // save file name after closing file as set_file_name starts watching again
  set_file_name (saveFileName);
  // set the window title to actual file name (not modified)
  update_window_title (false);
  // files is save -> not modified
  _edit_area->setModified (false);

  if (remove_on_success)
    {
      emit tab_remove_request ();
      return;  // Don't touch member variables after removal
    }
}

void
file_editor_tab::save_file_as (bool remove_on_success)
{
  // Simply put up the file chooser dialog box with a slot connection
  // then return control to the system waiting for a file selection.

  // If the tab is removed in response to a QFileDialog signal, the tab
  // can't be a parent.
  QFileDialog* fileDialog;
  if (remove_on_success)
    {
      // If tab is closed, "this" cannot be parent in which case modality
      // has no effect.  Disable editing instead.
      _edit_area->setReadOnly (true);
      fileDialog = new QFileDialog ();
    }
  else
    fileDialog = new QFileDialog (this);

  if (!_file_name.isEmpty () && _file_name.at (_file_name.count () - 1) != '/')
    {
      fileDialog->selectFile (_file_name);
    }
  else
    {
      fileDialog->selectFile ("");
      if (_file_name.isEmpty ())
        {
          fileDialog->setDirectory (QDir::currentPath ());
        }
      else
        {
          // The file name is actually the directory name from the
          // constructor argument.
          fileDialog->setDirectory (_file_name);
        }
    }
  fileDialog->setNameFilter (tr("Octave Files (*.m);;All Files (*.*)"));
  fileDialog->setDefaultSuffix ("m");
  fileDialog->setAcceptMode (QFileDialog::AcceptSave);
  fileDialog->setViewMode (QFileDialog::Detail);
  if (remove_on_success)
    {
      connect (fileDialog, SIGNAL (fileSelected (const QString&)),
               this, SLOT (handle_save_file_as_answer_close (const QString&)));
      connect (fileDialog, SIGNAL (rejected ()),
               this, SLOT (handle_save_file_as_answer_cancel ()));
    }
  else
    {
      connect (fileDialog, SIGNAL (fileSelected (const QString&)),
               this, SLOT (handle_save_file_as_answer (const QString&)));
    }
  fileDialog->setWindowModality (Qt::WindowModal);
  fileDialog->setAttribute (Qt::WA_DeleteOnClose);
  fileDialog->show ();
}

void
file_editor_tab::message_duplicate_file_name (const QString& saveFileName)
{
  // Could overwrite the file here (and tell user the file was
  // overwritten), but the user could have unintentionally
  // selected the same name not intending to overwrite.

  // Create a NonModal message about error.
  QMessageBox* msgBox = new QMessageBox (
          QMessageBox::Critical, tr ("Octave Editor"),
          tr ("File not saved! The selected file name\n%1\n"
              "is the same as the current file name").
          arg (saveFileName),
          QMessageBox::Ok, 0);
  msgBox->setWindowModality (Qt::NonModal);
  msgBox->setAttribute (Qt::WA_DeleteOnClose);
  msgBox->show ();
}

void
file_editor_tab::handle_save_file_as_answer (const QString& saveFileName)
{
  if (saveFileName == _file_name)
    {
      message_duplicate_file_name (saveFileName);
      // Nothing done, allow editing again.
      _edit_area->setReadOnly (false);
    }
  else
    {
      // Have editor check for conflict, do not delete tab after save.
      emit editor_check_conflict_save (saveFileName, false);
    }
}

void
file_editor_tab::handle_save_file_as_answer_close (const QString& saveFileName)
{
  if (saveFileName == _file_name)
    {
      message_duplicate_file_name (saveFileName);
      // Nothing done, allow editing again.
      _edit_area->setReadOnly (false);
    }
  else
    {
      // Have editor check for conflict, delete tab after save.
      emit editor_check_conflict_save (saveFileName, true);
    }
}

void
file_editor_tab::handle_save_file_as_answer_cancel ()
{
  // User canceled, allow editing again.
  _edit_area->setReadOnly (false);
}

void
file_editor_tab::file_has_changed (const QString&)
{
  // Prevent popping up multiple message boxes when the file has
  // been changed multiple times by temporarily removing from the
  // file watcher.
  QStringList trackedFiles = _file_system_watcher.files ();
  if (!trackedFiles.isEmpty ())
    _file_system_watcher.removePath (_file_name);

  if (QFile::exists (_file_name))
    {
      // Create a WindowModal message that blocks the edit area
      // by making _edit_area parent.
      QMessageBox* msgBox = new QMessageBox (
              QMessageBox::Warning, tr ("Octave Editor"),
              tr ("It seems that \'%1\' has been modified by another application. Do you want to reload it?").
              arg (_file_name), QMessageBox::Yes | QMessageBox::No, this);
      connect (msgBox, SIGNAL (finished (int)),
               this, SLOT (handle_file_reload_answer (int)));
      msgBox->setWindowModality (Qt::WindowModal);
      msgBox->setAttribute (Qt::WA_DeleteOnClose);
      msgBox->show ();
    }
  else
    {
      QString modified = "";
      if (_edit_area->isModified ())
        modified = tr ("\n\nWarning: The contents in the editor is modified!");
      // Create a WindowModal message. The file editor tab can't be made
      // parent because it may be deleted depending upon the response.
      // Instead, change the _edit_area to read only.
      QMessageBox* msgBox = new QMessageBox (
              QMessageBox::Warning, tr ("Octave Editor"),
              tr ("It seems that the file\n"
                  "%1\n"
                  "has been deleted or renamed. Do you want to save it now?%2").
              arg (_file_name).arg (modified),
              QMessageBox::Save | QMessageBox::Close, 0);
      _edit_area->setReadOnly (true);
      connect (msgBox, SIGNAL (finished (int)),
               this, SLOT (handle_file_resave_answer (int)));
      msgBox->setWindowModality (Qt::WindowModal);
      msgBox->setAttribute (Qt::WA_DeleteOnClose);
      msgBox->show ();
    }
}

void
file_editor_tab::notice_settings ()
{
  QSettings *settings = resource_manager::get_settings ();

  if (settings==NULL)
    return; // this shouldn't happen!

  _edit_area->setCaretLineVisible(settings->value ("editor/highlightCurrentLine",true).toBool ());

  if (settings->value ("editor/codeCompletion",true).toBool ())
    _edit_area->setAutoCompletionThreshold (1);
  else
    _edit_area->setAutoCompletionThreshold (-1);

  QFont xfont (settings->value ("editor/fontName","Courier").toString (),
               settings->value ("editor/fontSize",10).toInt ());

  if (settings->value ("editor/showLineNumbers",true).toBool ())
    {
      _edit_area->setMarginLineNumbers (2, true);
      _edit_area->setMarginsFont (xfont);
      QFontMetrics metrics (xfont);
      _edit_area->setMarginWidth(2, metrics.width("9999"));
    }
  else
    {
      _edit_area->setMarginLineNumbers (2, false);
      _edit_area->setMarginWidth(2, 0);
    }

  update_lexer ();

  _long_title = settings->value ("editor/longWindowTitle",false).toBool ();

  update_window_title (false);
}

void
file_editor_tab::conditional_close (const QWidget* ID)
{
  if (ID != this)
    return;

  close ();
}

void
file_editor_tab::change_editor_state (const QWidget* ID)
{
  if (ID != this)
    {
      // Widget may be going out of focus.  If so, record location.
      if (_find_dialog)
        {
          if (_find_dialog->isVisible ())
            {
              _find_dialog_geometry = _find_dialog->geometry ();
              _find_dialog->hide ();
            }
        }
      return;
    }

  if (_find_dialog && _find_dialog_is_visible)
    {
      _find_dialog->setGeometry (_find_dialog_geometry);
      _find_dialog->show ();
    }
  emit editor_state_changed (_copy_available, QDir::cleanPath (_file_name));
}

void
file_editor_tab::file_name_query (const QWidget* ID)
{
  // A zero (null pointer) means that all file editor tabs
  // should respond, otherwise just the desired file editor tab.
  if (ID != this && ID != 0)
    return;

  // Unnamed files shouldn't be transmitted.
  if (!_file_name.isEmpty ())
    emit add_filename_to_list (_file_name);
}

void
file_editor_tab::handle_file_reload_answer (int decision)
{
  if (decision == QMessageBox::Yes)
    { // reload: file is readded to the file watcher in set_file_name ()
      load_file (_file_name);
    }
  else
    { // do not reload: readd to the file watche
      _file_system_watcher.addPath (_file_name);
    }
}

void
file_editor_tab::handle_file_resave_answer (int decision)
{
  // check decision of user in dialog
  if (decision == QMessageBox::Save)
    {
      save_file (_file_name);  // readds file to watcher in set_file_name ()
      _edit_area->setReadOnly (false);  // delete read only flag
    }
  else
    {
      // Definitely close the file.
      // Set modified to false to prevent the dialog box when the close event
      // is posted. If the user cancels the close in this dialog the tab is
      // left open with a non-existing file.
      _edit_area->setModified (false);
      close ();
    }
}

void
file_editor_tab::set_debugger_position (int line)
{
  _edit_area->markerDeleteAll (debugger_position);
  if (line > 0)
    {
      _edit_area->markerAdd (line, debugger_position);
    }
}

#endif

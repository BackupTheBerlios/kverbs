/*
 * kverbs.h
 *
 * Copyright (c) 2004 Nicolas Bellm <nbellm@gmx.de>
 */
#ifndef KVERBS_H
#define KVERBS_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <kapp.h>
#include <qwidgetstack.h>
#include <qlayout.h>
#include <qlineedit.h>
#include <qcombobox.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qvaluelist.h>
#include <qsplitter.h>

#include <ktextbrowser.h>
#include <kmainwindow.h>
#include <kpopupmenu.h>

#include "verb.h"

struct VerbInfo
{
  QString name;
  QString libraryName;
  int stackId;
};

class KVerbLayout;

class KVerbs: public KMainWindow
{
  Q_OBJECT
  
  public:
    KVerbs( QWidget *parent = 0 );
    ~KVerbs();
    KTextBrowser *conjwidget;
    void mousePressEvent( QMouseEvent *e );
  
  private:
    KPopupMenu *m_menu;
    QWidgetStack *formwidget;
    QComboBox *languageBox;
    KVerbLayout *formgrid;
    Verb *verb;
    QValueList<VerbInfo> verbList;
    
    QStringList findModules();
    void initializeModule();

  public slots:
    void loadModule( int index );
};

class KVerbLayout: public QWidget
{
  Q_OBJECT
  
  public:
    KVerbLayout( QWidget *parent, Verb *verb, KVerbs *topLevel );
    ~KVerbLayout();
  
  private:
    Verb *m_verb;
    QGridLayout *layout;
    KVerbs *m_topLevel;
    QValueList<QLabel*> formlabel;
    QValueList<QLineEdit*> formedit;
    QLabel *conjlabel;
    QComboBox *conjedit;
    QLabel *tenselabel;
    QComboBox *tenseedit;
    QLabel *voicelabel;
    QComboBox *voiceedit;
    QPushButton *button;
  
  public slots:
    void conjugate();
};
  
#endif

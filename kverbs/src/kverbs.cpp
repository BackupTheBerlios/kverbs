/*
 * kverbs.cpp
 *
 * Copyright (c) 2004 Nicolas Bellm <nbellm@gmx.de>
 */
#include "kverbs.h"
#include "verb.h"

#include <qcombobox.h>
#include <qdir.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qlineedit.h>
#include <qmenubar.h>
#include <qpushbutton.h>
#include <qstringlist.h>
#include <qvbox.h>

#include <kaboutdata.h>
#include <kdesktopfile.h>
#include <khelpmenu.h>
#include <kiconloader.h>
#include <klocale.h>
#include <klibloader.h>
#include <kmessagebox.h>
#include <kpopupmenu.h>
#include <kstandarddirs.h>

KVerbs::KVerbs( QWidget *parent ) : KMainWindow( parent )
{
  // setup help menu
  m_menu = helpMenu( 0, false );
  m_menu->insertTitle( kapp->miniIcon(), KGlobal::instance()->aboutData()->programName(), -1, 0 );
  m_menu->insertSeparator();
  m_menu->insertItem( SmallIconSet( "exit" ), i18n( "&Quit" ), kapp, SLOT( quit() ) );
  
  QVBox *central = new QVBox( this );
  central->setMargin( 5 );
  central->setSpacing( 5 );
  setCentralWidget( central );
  
  languageBox = new QComboBox( central );
  findModules();
  
  QSplitter *splitter = new QSplitter( QSplitter::Horizontal, central );
  formwidget = new QWidgetStack( splitter );
  conjwidget = new KTextBrowser( splitter );

  connect( languageBox, SIGNAL( activated(int) ), this, SLOT( loadModule(int) ) );
  
  formgrid = 0;

  loadModule( 0 );
}

KVerbs::~KVerbs()
{
}

/*
 * Show the context menu
 */
void KVerbs::mousePressEvent( QMouseEvent *e )
{
  if ( e->button() == RightButton )
    m_menu->popup( mapToGlobal( e->pos() ) );
}

void KVerbLayout::conjugate(){
  QStringList wordlist;
  QString text;

  for ( QValueList<QLineEdit*>::iterator it = formedit.begin(); it != formedit.end(); ++it ) {
    wordlist.append( (*it)->text() );
  }

  m_verb->setWord( wordlist, conjedit != 0 ? conjedit->currentItem() : 0 );

  text = "<table>";
  for ( int i = 0; i <= 5; i++ )
    text += "<tr><td>" + m_verb->conjugate( i, tenseedit->currentItem(), voiceedit->currentItem() ) + "</td></tr>";
  text += "</table>";
  m_topLevel->conjwidget->setText( text );
}

QStringList KVerbs::findModules()
{
  QStringList dirList = KGlobal::dirs()->findDirs( "data", "kverbs" );
  QStringList::ConstIterator it;
  QStringList modules;

  for ( it = dirList.begin(); it != dirList.end(); it++ )
  {
    QDir dir( *it );
    if ( dir.exists() )
      for ( QFileInfoListIterator it( *dir.entryInfoList() ); it.current(); ++it)
      {
        QString filename( it.current()->absFilePath() );
        if (KDesktopFile::isDesktopFile( filename ) )
        {
          KDesktopFile desktopFile( filename );
          QString libName = desktopFile.readEntry( "X-KDE-Library" );

          if ( !libName.isEmpty() && libName.startsWith( "kverbs_" ) )
          {
            VerbInfo vi;
            vi.name = desktopFile.readName();
            vi.libraryName = libName;
            vi.stackId = -1;
            verbList.append( vi );
            languageBox->insertItem( desktopFile.readName() );
          }
        }
      }
  }
  return modules;
}

void KVerbs::loadModule( int index )
{
  QValueList<VerbInfo>::Iterator it = verbList.at( index );
  
  if ( (*it).stackId == -1 )
  {
    QString module = ( (*it).libraryName );
    (KLibFactory *)verb = KLibLoader::self()->factory( module.latin1() );
    if (!verb) exit( 1 );
    
    (*it).stackId = formwidget->addWidget( new KVerbLayout( formwidget, verb, this ) );
  }
  formwidget->raiseWidget( (*it).stackId );
}

KVerbLayout::KVerbLayout( QWidget *parent, Verb *verb, KVerbs *topLevel ) : QWidget( parent ), m_verb( verb ), m_topLevel( topLevel )
{
  QStringList formstring = m_verb->getForms();
  layout = new QGridLayout( this, 0, 0, 8 );

  int i=0;
  for (QStringList::iterator it = formstring.begin(); it != formstring.end(); ++it) {
    layout->addWidget(*formlabel.append( new QLabel( *it, this) ), i, 0);
    layout->addWidget(*formedit.append( new QLineEdit( this ) ), i++, 1);
  }
  
  if ( !verb->getConjugations().isEmpty() )
  {
    conjlabel = new QLabel( i18n( "Conjugation:"), this );
    layout->addWidget( conjlabel, i, 0 );
  
    conjedit = new QComboBox( this );
    conjedit ->insertStringList( verb->getConjugations() );
    layout->addWidget( conjedit, i++, 1 );
  }
  else
    conjedit = 0;

  if ( !verb->getTenses().isEmpty() )
  {
    tenselabel = new QLabel( i18n( "Tense:" ), this );
    layout->addWidget( tenselabel, i, 0 );
  
    tenseedit = new QComboBox( this );
    tenseedit->insertStringList( verb->getTenses() );
    layout->addWidget( tenseedit, i++, 1 );
  }

  if ( !verb->getVoices().isEmpty() )
  {
    voicelabel = new QLabel( i18n( "Voice:" ), this );
    layout->addWidget( voicelabel, i, 0 );
  
    voiceedit = new QComboBox( this );
    voiceedit->insertStringList( verb->getVoices() );
    layout->addWidget( voiceedit, i++, 1 );
  }

  button = new QPushButton( i18n( "&Conjugate" ), this);
  layout->addMultiCellWidget(button, i, i, 0, 1);
  
  connect( button, SIGNAL( clicked() ), this, SLOT( conjugate() ) );
}

KVerbLayout::~KVerbLayout() 
{
}

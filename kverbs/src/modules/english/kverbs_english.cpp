#include "kverbs_english.h"
#include <iostream>
#include <qregexp.h>

QString EnglishVerb::persons[6] = { "I", "you", "he/she/it", "we", "you", "they" };
QString EnglishVerb::be[6] = { "am", "are", "is", "are", "are", "are" };
QString EnglishVerb::was[6] = { "was", "were", "was", "were", "were", "were" };

extern "C"
{
    void* init_kverbs_english()
    {
    return new EnglishVerb;
    }
};

QStringList EnglishVerb::getLanguages() const
{
  QStringList ret;
  ret << "English";
  return ret;
}

void EnglishVerb::setWord( QStringList wordlist, int ) {
  m_word = *wordlist.begin();
  if ( m_word.left( 3 ) == "to " ) m_word = m_word.right( m_word.length() - 3 );
  
  m_past = *wordlist.at( 1 );
  m_participle = *wordlist.at( 2 );
}

QString EnglishVerb::conjugate( int person, int tense, int voice ) const {
  QString form = persons[person] + "</td><td>";
  
  switch ( tense )
  {
    case PRES:
      if ( voice == ACT ) return form + ( person == 2 ? thirdPerson() : m_word );
      else return form + be[person] + " " + pastParticiple();
    case PRESPR:
      if ( voice == ACT ) return form + be[person] + " " + presentParticiple();
      else return form + be[person] + " being " + pastParticiple();
    case PAST:
      if ( voice == ACT ) return form + pastParticiple( false );
      else return form + was[person] + " " + pastParticiple();
    case PASTPR:
      if ( voice == ACT ) return form + was[person] + " " + presentParticiple();
      else return form + was[person] + " being " + pastParticiple();
    case PRESPERF:
      if ( voice == ACT ) return form + ( person == 2 ? "has " : "have " ) + pastParticiple();
      else return form + ( person == 2 ? "has" : "have" ) + " been " + pastParticiple();
    case PRESPERFPR:
      if ( voice == ACT ) return form + ( person == 2 ? " has" : " have" ) + " been " + presentParticiple();
      else return "-";
    case PASTPERF:
      if ( voice == ACT ) return form + "had " + pastParticiple();
      else return form + "had been " + pastParticiple();
    case FUTURE:
      if ( voice == ACT ) return form + "will " + m_word;
      else return form + "will be " + pastParticiple();
    case FUTUREPERF:
      if ( voice == ACT ) return form + "will have " + pastParticiple();
      else return form + "will have been " + pastParticiple();
      break;
  }
  return 0;
}

QString EnglishVerb::thirdPerson() const
{
  if ( m_word.contains( QRegExp( "[^aeiou]y$" ) ) ) return m_word.left( m_word.length() - 1 ) + "ies";
  else if ( m_word.contains( QRegExp( "([sxz]|ch|sh|do|go)$" ) ) ) return m_word + "es";
  else return m_word + "s";
}

QString EnglishVerb::presentParticiple() const
{
  if ( m_word.contains( QRegExp( "ie$" ) ) ) return m_word.left( m_word.length() - 2 ) + "ying";
  else if ( m_word.contains( QRegExp( "e$" ) ) ) return m_word.left( m_word.length() - 1 ) + "ing";
  else return m_word + "ing";
}

QString EnglishVerb::pastParticiple( bool participle ) const
{
  QString form = participle ? m_participle : m_past;
  if ( form.isEmpty() )
  {
    if ( m_word.contains( QRegExp( "e$" ) ) ) return m_word + "d";
    else if ( m_word.contains( QRegExp( "[^aeiou]y$" ) ) ) return m_word.left( m_word.length() - 1 ) + "ied";
    else return m_word + "ed";
  }
  return form;
}

QStringList EnglishVerb::getConjugations() const {
  QStringList ret;
  return ret;
}

QStringList EnglishVerb::getForms() const {
  QStringList ret;
  ret << "Infinitive:"
      << "Simple past:"
      << "Past Participle:";
  return ret;
}

QStringList EnglishVerb::getTenses() const {
  QStringList ret;
  ret << "Simple Present"
      << "Present Progressive"
      << "Simple Past"
      << "Past Progressive"
      << "Present Perfect"
      << "Present Perfect Progressive"
      << "Past Perfect"
      << "Future"
      << "Future Perfect";
  return ret;
}

QStringList EnglishVerb::getVoices() const {
  QStringList ret;
  ret << "Active"
      << "Passive";
  return ret;
}

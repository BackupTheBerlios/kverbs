#include "kverbs_latin.h"
#include <klocale.h>
#include <qstring.h>

QString LatinVerb::m_endings[9][7] = { { "m", "s", "t", "mus", "tis", "nt", "o" },
                                      { "r", "ris", "tur", "mur", "mini", "ntur", "or" },
                                      { "i", "isti", "it", "imus", "istis", "erunt", "" },
                                      { "sum", "es", "est", "sumus", "estis", "sunt", "" },
                                      { "erim", "eris", "erit", "erimus", "eritis", "erint", "ero" },
                                      { "sim", "sis", "sit", "sumus", "sitis", "sint", "" },
                                      { "eram", "eras", "erat", "eramus", "eratis", "erant", "" },
                                      { "issem", "isses", "isset", "issemus", "issetis", "issent", "" },
                                      { "essem", "esses", "esset", "essemus", "essetis", "essent", "" } };

extern "C"
{
    void* init_kverbs_latin()
    {
    return new LatinVerb;
    }
};

QStringList LatinVerb::getLanguages() const
{
  QStringList ret;
  ret << "Latin";
  return ret;
}

void LatinVerb::setWord( QStringList wordlist, int conj )
{
  m_word = *wordlist.begin();

  m_perfstem = *wordlist.at( 1 );
  m_perfstem = m_perfstem.left( m_perfstem.length() - 1 );

  m_participle = *wordlist.at( 2 );
  m_participle = m_participle.left( m_participle.length() - 2 );

  m_conj = (Conj)conj;

  if ( m_word.right(1) == "e" )
  {
    m_deponent = false;
    switch ( m_conj )
    {
      case TRDI:
        m_stem = m_word.left( m_word.length() - 3 ) + "i";
        break;
      case TRD:
        m_stem = m_word.left( m_word.length() - 3 );
        break;
      default:
        m_stem = m_word.left( m_word.length() - 2 );
    }
    switch ( m_conj )
    {
      case FST:
        if ( m_perfstem.isEmpty() ) m_perfstem = m_stem + "v";
        if ( m_participle.isEmpty() ) m_participle = m_stem + "t";
        break;
      case SND:
        if ( m_perfstem.isEmpty() ) m_perfstem = m_stem.left( m_stem.length() - 1 ) + "u";
        if ( m_participle.isEmpty() ) m_participle = m_stem.left( m_stem.length() - 1 ) + "it";
        break;
      default:
        break;
    }
  }
  else
  {
    m_deponent = true;
    switch ( m_conj )
    {
    case TRD:
      m_stem = m_word.left( m_word.length() - 1 );
      break;
    case TRDI:
      m_stem = m_word;
      break;
    default:
      m_stem = m_word.left( m_word.length() - 2 );
    }
  }
}

QString LatinVerb::conjugate( int person, int tense, int voice ) const
{
  if ( voice == ACT && m_deponent ) return "-";

  switch ( tense )
  {
    case PRES:
      return conjIndPres( person, (Voice)voice );
    case PRESSJ:
      return conjKonjPres( person, (Voice)voice );
    case IMPF:
      return conjIndImpf( person, (Voice)voice );
    case IMPFSJ:
      return conjKonjImpf( person, (Voice)voice );
    case F:
      return conjFuturI( person, (Voice)voice );
    default:
      if ( voice == ACT )
        return conjPerfAct( person, (Tense)tense );
      else
        return conjPerfPas( person, (Tense)tense );
  }
}

QString LatinVerb::conjIndPres( int person, Voice voice ) const {
  QString form = m_stem;

  switch( m_conj )
  {
    case FST:
      if ( person == 0 ) form = form.left( form.length() - 1 );
      break;
    case TRDI:
      if ( person == 1 && voice == PAS ) form = form.left( form.length() - 1 ) + "e";
    case FTH:
      if ( person == 5 ) form += "u";
      break;
    case TRD:
      if ( person == 1 && voice == PAS ) form += "e";
      else if ( person == 5 ) form += "u";
      else if ( person != 0 ) form += "i";
  }
  form += m_endings[voice][person == 0 ? 6 : person];

  return form;
}

QString LatinVerb::conjKonjPres( int person, Voice voice ) const
{
  QString form;

  switch( m_conj )
  {
    case FST:
      form = m_stem.left( m_stem.length() - 1 ) + "e";
      break;
    default:
      form = m_stem + "a";
  }
  form += m_endings[voice][person];

  return form;
}

QString LatinVerb::conjIndImpf( int person, Voice voice ) const
{
  QString form = m_stem;

  if ( m_conj == FTH || m_conj == TRDI || m_conj == TRD) form += "e";

  form += "ba" + m_endings[voice][person];

  return form;
}

QString LatinVerb::conjKonjImpf( int person, Voice voice ) const
{
  QString form = m_stem;

  if ( m_conj == TRDI) form = form.left( form.length() - 1 );
  if ( m_conj == TRDI || m_conj == TRD) form += "e";

  form += "re" + m_endings[voice][person];

  return form;
}

QString LatinVerb::conjFuturI( int person, Voice voice ) const
{
  QString form;

  if ( m_conj == FST || m_conj == SND ) {
    form = m_stem + "b";
    if ( person == 0 ) person = 6;
    else if ( person == 1 && voice == PAS ) form += "e";
    else if ( person == 5 ) form += "u";
    else form += "i";
  }
  else
    form = m_stem + ( person == 0 ? "a" : "e" );
  
  form += m_endings[voice][person];

  return form;
}

QString LatinVerb::conjPerfAct( int person, Tense tense ) const
{
  switch (tense)
  {
    case PERF:
      return m_perfstem + m_endings[2][person];
    case PERFSJ:
      return m_perfstem + m_endings[4][person];
    case PLPERF:
      return m_perfstem + m_endings[6][person];
    case PLPERFSJ:
      return m_perfstem + m_endings[7][person];
    case FP:
      return m_perfstem + m_endings[4][person == 0 ? 6 : person];
    default:
      return 0;
  }
}

QString LatinVerb::conjPerfPas( int person, Tense tense ) const
{
  QString participle = m_participle + ( (person < 3) ? "us" : "i" ) + " ";
  switch (tense)
  {
    case PERF:
      return participle + m_endings[3][person];
    case PERFSJ:
      return participle + m_endings[5][person];
    case PLPERF:
      return participle + m_endings[6][person];
    case PLPERFSJ:
      return participle + m_endings[8][person];
    case FP:
      return participle + m_endings[5][person == 0 ? 6 : person];
    default:
      return 0;
  }
}

QStringList LatinVerb::getConjugations() const
{
  QStringList ret;
  ret << i18n( "1st Conjugation" )
      << i18n( "2nd Conjugation" )
      << i18n( "3rd Conjugation non i-stem" )
      << i18n( "3rd Conjugation i-stem" )
      << i18n( "4th Conjugation" );
  return ret;
}

QStringList LatinVerb::getForms() const
{
  QStringList ret;
  ret << i18n( "Infinitive:" )
      << i18n( "Perfect:" )
      << i18n( "PPP:" );
  return ret;
}

QStringList LatinVerb::getTenses() const
{
  QStringList ret;
  ret << i18n( "Present" )
      << i18n( "Present Subjunctive" )
      << i18n( "Imperfect" )
      << i18n( "Imperfect Subjunctive" )
      << i18n( "Future" )
      << i18n( "Perfect" )
      << i18n( "Perfect Subjunctive" )
      << i18n( "Pluperfect" )
      << i18n( "Pluperfect Subjunctive" )
      << i18n( "Future Perfect" );
  return ret;
}

QStringList LatinVerb::getVoices() const
{
  QStringList ret;
  ret << i18n( "Active" )
      << i18n( "Passive" );
  return ret;
}

#include "../../verb.h"
#include <klibloader.h>
#include <qstring.h>

enum Conj { FST, SND, TRD, TRDI, FTH };
enum Number { SG, PL };
enum Tense { PRES, PRESSJ, IMPF, IMPFSJ, F, PERF, PERFSJ, PLPERF, PLPERFSJ, FP };
enum Voice { ACT, PAS };

class LatinVerb: public Verb
{
  public:
    LatinVerb() {}
    virtual QStringList getLanguages() const;
    virtual void setWord( QStringList _wordlist, int _conj );
    QString conjugate( int person, int tense, int voice ) const;
    QString conjIndPres( int person, Voice voice ) const;
    QString conjKonjPres( int person, Voice voice ) const;
    QString conjIndImpf( int person, Voice voice ) const;
    QString conjKonjImpf( int person, Voice voice ) const;
    QString conjFuturI( int person, Voice voice ) const;
    QString conjPerfAct(int person, Tense tense) const;
    QString conjPerfPas(int person, Tense tense) const;
    virtual QStringList getConjugations() const;
    virtual QStringList getForms() const;
    virtual QStringList getTenses() const;
    virtual QStringList getVoices() const;

  private:
    QString m_word;
    int m_conj;
    static QString m_endings[9][7];
    QString m_stem, m_perfstem, m_participle;
    bool m_deponent;
};

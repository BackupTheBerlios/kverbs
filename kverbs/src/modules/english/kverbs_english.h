#include "../../verb.h"
#include <klibloader.h>
#include <qstringlist.h>

enum Conj { A, E, I, GEM, KONS, IRR };
enum Number { SG, PL };
enum Tense { PRES, PRESPR, PAST, PASTPR, PRESPERF, PRESPERFPR, PASTPERF, FUTURE, FUTUREPERF };
enum Voice { ACT, PAS };

class EnglishVerb: public Verb
{
  public:
    EnglishVerb() {}
    virtual QStringList getLanguages() const;
    virtual void setWord(QStringList wordlist, int conj = 0);
    QString conjugate(int person, int tense, int voice) const;
    virtual QStringList getConjugations() const;
    virtual QStringList getForms() const;
    virtual QStringList getTenses() const;
    virtual QStringList getVoices() const;

  private:
    QString thirdPerson() const;
    QString presentParticiple() const;
    QString pastParticiple( bool participle = true ) const;
    QString m_word, m_past, m_participle;
    static QString persons[6], be[6], was[6];
};

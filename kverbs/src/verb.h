#ifndef VERB_H
#define VERB_H

#include <klibloader.h>
#include <qstringlist.h>

class Verb: public KLibFactory
{
  public:
    Verb() {}
    // reimplemented from KLibFactory
    virtual QObject * createObject( QObject * = 0, const char * = 0, const char * = "QObject", const QStringList & = QStringList()) { return 0; }
    virtual QStringList getLanguages() const = 0;
    virtual void setWord( QStringList wordlist, int conj = 0 ) = 0;
    virtual QString conjugate( int person, int tense, int voice ) const = 0;
    virtual QStringList getConjugations() const = 0;
    virtual QStringList getForms() const = 0;
    virtual QStringList getTenses() const = 0;
    virtual QStringList getVoices() const = 0;
};

#endif

#include "kverbs.h"
#include <kapplication.h>
#include <dcopclient.h>
#include <kaboutdata.h>
#include <kcmdlineargs.h>
#include <klocale.h>

static const char description[] =
  I18N_NOOP("A KDE Application");

static const char version[] = "v0.1";

int main(int argc, char **argv)
{
  KAboutData about("kverbs", I18N_NOOP("KVerbs"), version, description, KAboutData::License_GPL, "(C) 2003 Nicolas Bellm", 0, 0, "nbellm@gmx.de");
  about.addAuthor( "Nicolas Bellm", 0, "nbellm@gmx.de" );
  KCmdLineArgs::init(argc, argv, &about);
  KApplication app;

  // register ourselves as a dcop client
  app.dcopClient()->registerAs(app.name(), false);

  KVerbs *widget = new KVerbs;
  widget->show();

  return app.exec();
}

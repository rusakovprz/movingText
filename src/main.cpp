/****************************************************************************
**  File: main.cpp
** 
****************************************************************************/

#ifdef __linux__
#include <signal.h>
#endif
#include <QApplication>
#include <qdebug.h>
#include "mainwindow.h"


static MainWindow *objWindow = NULL;


#ifdef __linux__
static void _Signal(int sig)
{
  fprintf(stderr, "signal: %i\n", sig);
  objWindow->reSet();
}
#endif


static const char * cursor_xpm[] = {
"2 2 1 1",
"  	c None",
"  ",
"  ",};


int main(int argc, char **argv)
{
  QString confName;

  if (argc < 2)
    confName = "config.xml";
  else
    confName = argv[1];

#ifdef __linux__
  signal(SIGUSR1, _Signal);
  signal(SIGHUP, _Signal);
#endif
 
  QApplication app(argc, argv);
  app.setApplicationName("Media player");
  app.setOverrideCursor(QCursor(QPixmap(cursor_xpm)));
  MainWindow mainWin( 0, 0, confName );
  mainWin.showFullScreen();

  objWindow = &mainWin;

  return app.exec();
}


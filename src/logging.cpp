/****************************************************************************
**  File: logging.cpp
**
**
****************************************************************************/

#include <QDebug>
#include <QDateTime>
#include "logging.h"


QString logging::getCurrentTime()
{
  return QDateTime().currentDateTime().toString("hh:mm:ss_dd-MM-yyyy");
}


void logging::setLogFile(QString fileName)
{
  closeLogFile();

  logFile.setFileName(fileName);

  if (!logFile.open(QFile::WriteOnly | QFile::Text | QIODevice::Append))
    qCritical() << QObject::tr("Cannot open file %1").arg(fileName); 
}


void logging::messageOutput(QtMsgType type, const char *msg)
{

  if(!logFile.isOpen())
    return;
  
  QTextStream logStream(&logFile);

  switch (type)
  {
    case QtDebugMsg:
      logStream << msg << "\n" << flush;
      break;
    case QtWarningMsg:
      fprintf(stderr, "Warning: %s\n", msg);
      break;
    case QtCriticalMsg:
      fprintf(stderr, "Critical: %s\n", msg);
      break;
    case QtFatalMsg:
      fprintf(stderr, "Fatal: %s\n", msg);
  }
}


void logging::closeLogFile()
{
  if(logFile.isOpen())
    logFile.close();
}


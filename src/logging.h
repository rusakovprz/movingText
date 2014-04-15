/****************************************************************************
**  File: logging.h
** 
**  Функции ведения журнал событий (время начала работы ролика, время начала
**  и окончания проигрывания видеоролика или показа бегущей строки, 
**  время обновления конфигурации).
**
****************************************************************************/

#include <QFile>


namespace logging
{
  static QFile logFile;
  
  void setLogFile(QString fileName);
  
  void messageOutput(QtMsgType type, const char *msg); 
  
  void closeLogFile();
  
  QString getCurrentTime();

};


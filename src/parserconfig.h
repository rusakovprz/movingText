/****************************************************************************
**  File: parserconfig.h
** 
****************************************************************************/

#ifndef PARSERCONFIG_H
#define PARSERCONFIG_H

#include<QColor>
#include<QFile>
#include<QString> 
#include<QDebug>

class ParserConfig : public QObject
{
    Q_OBJECT

public:

   ParserConfig(QString fileName, QObject *parent);

   void parser();

  QString getLogFileName(){ return logFileName; };
  QStringList getPlayList(){ return playList; };
  QStringList getTextList(){ return textList; };
  QColor getTextColor(){ return textColor; };
  QColor getBackgroundColor(){ return backgroundColor; };
  int getTextTimeout(){ return textTimeout; };
  int getTextSize(){ return textSize; };
  int getTextPos(){ return textPos; };

private:
  QString m_fileName;
  QString logFileName;
  QStringList playList;
  QStringList textList;
  QColor textColor;
  QColor backgroundColor;
  int textTimeout;
  int textSize;
  int textPos;

};

#endif



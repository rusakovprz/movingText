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

  QString getLogFileName(){ return m_logFileName; };
  QStringList getPlayList(){ return m_playList; };
  QStringList getTextList(){ return m_textList; };
  QColor getTextColor(){ return m_textColor; };
  QColor getBackgroundColor(){ return m_backgroundColor; };
  int getTextTimeout(){ return m_textTimeout; };
  int getTextSize(){ return m_textSize; };
  int getTextPos(){ return m_textPos; };

private:

  QString m_fileName;
  QString m_logFileName;
  QStringList m_playList;
  QStringList m_textList;
  QColor m_textColor;
  QColor m_backgroundColor;
  int m_textTimeout;
  int m_textSize;
  int m_textPos;

};

#endif


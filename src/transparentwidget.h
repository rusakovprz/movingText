/****************************************************************************
**    File: transparentwidget.h
**    
**
****************************************************************************/

#ifndef TRANSPARENTWIDGET_H
#define TRANSPARENTWIDGET_H

#include <QLabel>
#include <QTimer>
#include <QPainter>
#include <QStringList>
#include "parserconfig.h"


class TransparentWidget : public QLabel
{
      Q_OBJECT

public:

  TransparentWidget(QWidget *parent = 0);

  void setTextPos(int pos);
  void setTextSize(int size);
  void setTextColor(QColor text, QColor  background);
  void setTextList(QStringList list);
  void setTextTimeout(int timeout);
  void setConfig(ParserConfig *conf);
  void start();
  void reStart();

public slots:
  void nextPos();
  void firstString();
  void nextString();
  void putToLogNextText();
  
private:

  void updateConfData();
  
  void paintEvent( QPaintEvent * event );
  QWidget *m_parent;
  
  QStringList m_textList;
  QColor m_textColor;
  QColor m_backgroundColor;
  int m_textSize;

  QString m_currentString;
  int m_currentIndexString;
  int m_pos_x;
  int m_lenImageString;
  int m_textTimeout;
  ParserConfig *m_config;

};

#endif


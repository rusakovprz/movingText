/****************************************************************************
**    File: transparentwidget.cpp
** 
**
****************************************************************************/

#include <QColor>
#include <QSize>
#include <QFont>
#include <QDebug>
#include "transparentwidget.h"
#include "logging.h"

QString getCurrentTime(); // in file:  mainwindow.cpp

TransparentWidget::TransparentWidget(QWidget *parent)
    : QLabel(parent),
    currentString(),
    lenImageString(0)
{
  qDebug() << "constructor TransparentWidget";
  m_parent = parent;

  this->setTextPos(10);
  this->hide();
}


void TransparentWidget::paintEvent( QPaintEvent * event )
{ 
  QRect rectangle(0, 0, this->size().width()-1, this->size().height()-1);
	QPainter* painter =  new QPainter(this);
	painter->setBrush(this->backgroundColor);
	painter->setPen(this->backgroundColor);
	painter->drawRect(rectangle);
  painter->setPen(this->textColor);
  painter->setFont(QFont("Helvetica [Cronyx]", textSize));
	painter->drawText(pos_x, this->size().height()-15, currentString );
  painter->end();
  delete painter;
  
  // С целью избежать предупреждения во время компиляции:
  // параметр «event» не используется [-Wunused-parameter]
  if (event){};
  
}


void TransparentWidget::setTextPos(int pos)
{
  this-> move(0,pos);
}


void TransparentWidget::setTextSize(int size)
{

  textSize = size;
  QSize s = this->size();
  this->resize(s.width(), size+20);
  
}


void TransparentWidget::setTextColor(QColor text, QColor  background)
{
  this->textColor = text;
  this->backgroundColor = background;
  
}


void TransparentWidget::setTextList(QStringList list)
{
  this->textList = list;
}


void TransparentWidget::setTextTimeout(int timeout)
{
  this->textTimeout = timeout;
}


void TransparentWidget::setConfig(ParserConfig *conf)
{
  this->config = conf;
}


void TransparentWidget::updateConfData()
{
  this->setTextPos(config->getTextPos());
  this->setTextColor(config->getTextColor(), config->getBackgroundColor());
  this->setTextSize(config->getTextSize());
  this->setTextList(config->getTextList());
  this->setTextTimeout(config->getTextTimeout());
}

void TransparentWidget::start()
{
  this->updateConfData();

  if (textList.size() == 0)
    return;

  this->firstString();
}

void TransparentWidget::reStart()
{
  if (textList.size() == 0)
    return;
  
  currentIndexString = -1;
}


void TransparentWidget::firstString()
{
  currentIndexString = 0;
 
  pos_x = m_parent->size().width()+1;
  currentString = textList.at(currentIndexString);
  int s = currentString.size();
  lenImageString = s*textSize*0.53;

  putToLogNextText();
  nextPos();
}   


void TransparentWidget::nextString()
{
  this->hide();
  currentIndexString++;
  
  if (this->textList.size() <= currentIndexString)
  {  
     // достигли конца списка текстов
    // обновить данные из конфига
    this->updateConfData();
      
    currentIndexString = 0;
  }


  pos_x = m_parent->size().width()+1;
  currentString = textList.at(currentIndexString);
  int s = currentString.size();
  lenImageString = s*textSize*0.53;
  
  QTimer::singleShot(this->textTimeout, this, SLOT(nextPos()));
  QTimer::singleShot(this->textTimeout, this, SLOT(putToLogNextText()));

}   


void TransparentWidget::nextPos()
{
  pos_x--;

  if (pos_x < 0-lenImageString)
  {
    qDebug() << logging::getCurrentTime() << "End drawing text";
    this->nextString();
    return;
  }

  this->show();
  this->repaint();
  QTimer::singleShot(30, this, SLOT(nextPos()));
}


void TransparentWidget::putToLogNextText()
{
  qDebug() << logging::getCurrentTime() << "Begin drawing text = " << currentString;
}


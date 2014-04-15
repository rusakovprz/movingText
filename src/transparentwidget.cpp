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


TransparentWidget::TransparentWidget(QWidget *parent):
                                        QLabel(parent),
                                        m_currentString(),
                                        m_lenImageString(0)
{
  m_parent = parent;

  this->setTextPos(10);
  this->hide();
}


void TransparentWidget::paintEvent( QPaintEvent * event )
{ 
  QRect rectangle(0, 0, this->size().width()-1, this->size().height()-1);
	QPainter* painter =  new QPainter(this);
	painter->setBrush(m_backgroundColor);
	painter->setPen(m_backgroundColor);
	painter->drawRect(rectangle);
  painter->setPen(m_textColor);
  painter->setFont(QFont("Helvetica [Cronyx]", m_textSize));
	painter->drawText(m_pos_x, this->size().height()-15, m_currentString );
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
  m_textSize = size;
  QSize s = this->size();
  this->resize(s.width(), size+20);
}


void TransparentWidget::setTextColor(QColor text, QColor  background)
{
  m_textColor = text;
  m_backgroundColor = background;
}


void TransparentWidget::setTextList(QStringList list)
{
  this->m_textList = list;
}


void TransparentWidget::setTextTimeout(int timeout)
{
  m_textTimeout = timeout;
}


void TransparentWidget::setConfig(ParserConfig *conf)
{
  m_config = conf;
}


void TransparentWidget::updateConfData()
{
  this->setTextPos(m_config->getTextPos());
  this->setTextColor(m_config->getTextColor(), m_config->getBackgroundColor());
  this->setTextSize(m_config->getTextSize());
  this->setTextList(m_config->getTextList());
  this->setTextTimeout(m_config->getTextTimeout());
}

void TransparentWidget::start()
{
  this->updateConfData();

  if (m_textList.size() == 0)
    return;

  this->firstString();
}

void TransparentWidget::reStart()
{
  if (m_textList.size() == 0)
    return;
  
  m_currentIndexString = -1;
}


void TransparentWidget::firstString()
{
  m_currentIndexString = 0;
 
  m_pos_x = m_parent->size().width()+1;
  m_currentString = m_textList.at(m_currentIndexString);
  int s = m_currentString.size();
  m_lenImageString = s*m_textSize*0.53;

  putToLogNextText();
  nextPos();
}   


void TransparentWidget::nextString()
{
  this->hide();
  m_currentIndexString++;
  
  if (this->m_textList.size() <= m_currentIndexString)
  {  
     // достигли конца списка текстов
    // обновить данные из конфига
    this->updateConfData();
      
    m_currentIndexString = 0;
  }


  m_pos_x = m_parent->size().width()+1;
  m_currentString = m_textList.at(m_currentIndexString);
  int s = m_currentString.size();
  m_lenImageString = s*m_textSize*0.53;
  
  QTimer::singleShot(m_textTimeout, this, SLOT(nextPos()));
  QTimer::singleShot(m_textTimeout, this, SLOT(putToLogNextText()));
}   


void TransparentWidget::nextPos()
{
  m_pos_x--;

  if (m_pos_x < 0-m_lenImageString)
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
  qDebug() << logging::getCurrentTime() << "Begin drawing text = " << m_currentString;
}


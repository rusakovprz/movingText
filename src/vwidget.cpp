/****************************************************************************
**    File: vwidget.cpp
** 
**
****************************************************************************/

#include <QColor>
#include "vwidget.h"

VWidget::VWidget(QWidget *parent)
    : Phonon::VideoWidget(parent)
{
  tv =  new TransparentWidget(this);
}


void VWidget::resizeEvent( QResizeEvent * event )
{
  QSize size = event->size();
  int height = tv->height();
  tv->resize(size.width(), height);
}



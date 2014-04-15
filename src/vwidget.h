/****************************************************************************
**  File: vwidget.h
** 
**
****************************************************************************/

#ifndef VWIDGET_H
#define VWIDGET_H

#include <QResizeEvent>
#include <Phonon/VideoWidget>
#include "transparentwidget.h"


class VWidget : public Phonon::VideoWidget
{
      Q_OBJECT

public:

  VWidget(QWidget *parent = 0);
  TransparentWidget *tv;
  
private:
  
  void resizeEvent( QResizeEvent * event );

};

#endif


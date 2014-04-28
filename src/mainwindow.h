/****************************************************************************
**  File: mainwindow.h
** 
**
****************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Phonon/MediaSource>
#include <Phonon/MediaObject>
#include <Phonon/VideoWidget>
#include <Phonon/AudioOutput>
#include "vwidget.h"
#include "parserconfig.h"


class MainWindow : public QMainWindow
{
      Q_OBJECT

public:
  MainWindow(QWidget *parent = 0,
             Qt::WindowFlags flags = 0, 
             QString configName = QString("config_default.xml"));
  
  ~MainWindow();

public slots:

  void start();
  void reSet();
  void stop();
  void printState( Phonon::State newstate, Phonon::State oldstate );
  
private:

  Phonon::MediaObject *media;
  Phonon::AudioOutput *audioOutput;
  Phonon::MediaSource src;
  VWidget *vwidget;
  
  ParserConfig *m_config;
  QString m_currentFileName;
  QStringList m_mediaFileList;
  
  void runVideo();
  void runText();
  bool isMediaFile(QString filename);
    
};

#endif


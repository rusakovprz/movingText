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

  Phonon::MediaObject *m_mediaObject;
  Phonon::AudioOutput *m_audioOutput;
  Phonon::MediaSource m_mediaSource;
  
  VWidget *vwidget;
  
  ParserConfig *m_config;
  QStringList m_mediaFileList;
  QString m_currentFileName;
  
  void runVideo();
  void runText();
  bool isMediaFile(QString filename);
    
};

#endif


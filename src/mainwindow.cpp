/****************************************************************************
**  File: mainwindow.cpp
** 
**
****************************************************************************/

#include <stdio.h>
#include <QColor>
#include "mainwindow.h"
#include "logging.h"


MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags, QString configName):
                                                      QMainWindow(parent, flags)
{
  setWindowTitle("Media player");
  
  m_config = new ParserConfig(configName, this);
  
  media = new Phonon::MediaObject(this);
  vwidget = new VWidget(this);
  this->setCentralWidget(vwidget); 
  Phonon::createPath(media, (Phonon::MediaNode*)vwidget);
 
  connect(media, SIGNAL(finished ()), this, SLOT(stop()));
  
  connect(media, SIGNAL(stateChanged ( Phonon::State, Phonon::State) ),
       this, SLOT(printState( Phonon::State, Phonon::State) ));
  
  audioOutput = new Phonon::AudioOutput(Phonon::VideoCategory, this);
  Phonon::createPath(media, audioOutput);

  m_mediaFileList << ".avi" << ".AVI" << ".mp4" << ".MP4" << ".mpg" << ".MPG" << ".mpeg" << ".MPEG" 
                << ".3gp" << ".3GP" << ".mkv" << ".MKV" << ".flv" << ".FLV" << ".mov" << ".MOV" 
                << ".swf" << ".SWF" << ".vob" << ".VOB" << ".wmv" << ".WMV";   

  QTimer::singleShot(10, this, SLOT(start()));

}

MainWindow::~MainWindow()
{
  logging::closeLogFile();
}


void MainWindow::start()
{
  m_config->parser();
  logging::setLogFile( m_config->getLogFileName() );
  qInstallMsgHandler(logging::messageOutput);
  
  qDebug() << logging::getCurrentTime() << "Start applications";
  this->runVideo();
  this->runText();
}

                
void MainWindow::reSet()
{
  m_config->parser();
  logging::setLogFile( m_config->getLogFileName() );
  vwidget->tv->setConfig(m_config);
}


void MainWindow::runVideo()
{
  media->clear();
  
  QStringList playList = m_config->getPlayList();

  for(int i=0; i<playList.size(); i++ )
  {

    if (!isMediaFile(playList.at(i)))
    {
      qDebug() << logging::getCurrentTime() << playList.at(i) << " no media file.";
      continue;
    }   
  
    QFile file(playList.at(i));
    if (!file.open(QIODevice::ReadOnly))
    {
      qDebug() << logging::getCurrentTime() << "No such file or directory: " << playList.at(i);
      continue;
    };
    
    src = Phonon::MediaSource(playList.at(i));
    media->enqueue(src);
  };
  
  media->play();
}


void MainWindow::runText()
{
  vwidget->tv->setConfig(m_config);
  vwidget->tv->start();
}


void MainWindow::stop()
{
  this->runVideo();
}


void MainWindow::printState( Phonon::State newstate, Phonon::State oldstate )
{
  if (oldstate){};
  Phonon::MediaSource src = media->currentSource();

  if(newstate == 2)
  {
    m_currentFileName = src.fileName();
    qDebug() << logging::getCurrentTime() << " Begin playing file: " << m_currentFileName;
  };  
    
  if(newstate == 0 || newstate == 4)
    qDebug() << logging::getCurrentTime() << " Stop playing file: " << m_currentFileName;
  
}


bool MainWindow::isMediaFile(QString filename)
{
  for (int i= 0; i< m_mediaFileList.size(); i++)
  {
    if (filename.right(m_mediaFileList.at(i).length()) == m_mediaFileList.at(i))
      return true;
  }

  return false;
}


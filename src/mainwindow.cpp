/****************************************************************************
**  File: mainwindow.cpp
** 
**
****************************************************************************/

#include <stdio.h>
#include <QColor>
#include <QDateTime>
#include "mainwindow.h"

static QString logFileName;
QString getCurrentTime();
void messageOutput(QtMsgType type, const char *msg);


MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags, QString configName)
    : QMainWindow(parent, flags)
{
  setWindowTitle("Media player");
  
  configFileName = configName;
  config = new ParserConfig(configFileName);
  
  media = new Phonon::MediaObject(this);
  vwidget = new VWidget(this);
  this->setCentralWidget(vwidget); 
  Phonon::createPath(media, (Phonon::MediaNode*)vwidget);
 
  connect(media, SIGNAL(finished ()), this, SLOT(stop()));
  
  connect(media, SIGNAL(stateChanged ( Phonon::State, Phonon::State) ),
       this, SLOT(printState( Phonon::State, Phonon::State) ));
  
  audioOutput = new Phonon::AudioOutput(Phonon::VideoCategory, this);
  Phonon::createPath(media, audioOutput);

  mediaFileList << ".avi" << ".AVI" << ".mp4" << ".MP4" << ".mpg" << ".MPG" << ".mpeg" << ".MPEG" 
                << ".3gp" << ".3GP" << ".mkv" << ".MKV" << ".flv" << ".FLV" << ".mov" << ".MOV" 
                << ".swf" << ".SWF" << ".vob" << ".VOB" << ".wmv" << ".WMV";   

  QTimer::singleShot(10, this, SLOT(start()));

}


MainWindow::~MainWindow()
{
  delete config;
  delete media;
  delete vwidget;
  delete audioOutput;
}


void MainWindow::start()
{
  config->parser();

  logFileName = config->getLogFileName();
    
  qInstallMsgHandler(messageOutput);
  
  qDebug() << getCurrentTime() << "Start applications";
  this->runVideo();
  this->runText();
}

                
void MainWindow::reSet()
{
  config->parser();
  logFileName = config->getLogFileName();
  vwidget->tv->setConfig(config);
}


void MainWindow::runVideo()
{
  media->clear();
  
  QStringList playList = config->getPlayList();

  for(int i=0; i<playList.size(); i++ )
  {

    if (!isMediaFile(playList.at(i)))
    {
      qDebug() << getCurrentTime() << playList.at(i) << " no media file.";
      continue;
    }   
  
    QFile file(playList.at(i));
    if (!file.open(QIODevice::ReadOnly))
    {
      qDebug() << getCurrentTime() << "No such file or directory: " << playList.at(i);
      continue;
    };
    
    src = Phonon::MediaSource(playList.at(i));
    media->enqueue(src);
  };
  
  media->play();
}


void MainWindow::runText()
{
  vwidget->tv->setConfig(config);
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
    currentFileName = src.fileName();
    qDebug() << getCurrentTime() << " Begin playing file: " << currentFileName;
  };  
    
  if(newstate == 0 || newstate == 4)
    qDebug() << getCurrentTime() << " Stop playing file: " << currentFileName;
  
}


bool MainWindow::isMediaFile(QString filename)
{
  for (int i= 0; i< mediaFileList.size(); i++)
  {
    if (filename.right(mediaFileList.at(i).length()) == mediaFileList.at(i))
      return true;
  }

  return false;
}


QString getCurrentTime()
{
  return QDateTime().currentDateTime().toString("hh:mm:ss_dd-MM-yyyy");
}


void messageOutput(QtMsgType type, const char *msg)
{
  QFile logFile(logFileName);

  if (!logFile.open(QFile::WriteOnly | QFile::Text | QIODevice::Append))
  {
    qCritical() << QObject::tr("Cannot open file %1").arg(logFileName); 
  };
  
  QTextStream logStream(&logFile);

  switch (type) {
  case QtDebugMsg:
   //fprintf(stderr, "%s\n", msg);
   logStream << msg << "\n" << flush;
   break;
  case QtWarningMsg:
    //fprintf(stderr, "Warning: %s\n", msg);
    //logStream << "Warning: " << msg << "\n";
    break;
  case QtCriticalMsg:
    fprintf(stderr, "Critical: %s\n", msg);
    //logStream << "Critical: " << msg << "\n";
    break;
  case QtFatalMsg:
    fprintf(stderr, "Fatal: %s\n", msg);
    //logStream << "Fatal: " << msg << "\n";
    //abort();
  }
}



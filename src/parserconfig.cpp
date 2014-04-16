/****************************************************************************
**  File: parserconfig.cpp
** 
****************************************************************************/

#include <QDomDocument>
#include <QStringList>
#include "parserconfig.h"


ParserConfig::ParserConfig(QString fileName, QObject *parent = 0):
                QObject(parent),                
                m_fileName(fileName),
                m_logFileName("mpmt_log.txt"),
                m_playList(),
                m_textList(),
                m_textColor(0,0,0),
                m_backgroundColor(255,255,255),
                m_textTimeout(100),
                m_textSize(10),
                m_textPos(20)
{ }


void ParserConfig::parser()
{
  m_playList.clear();
  m_textList.clear();

  if (m_fileName.isEmpty())
    return;

  QFile file(m_fileName);
  if (!file.open(QFile::ReadOnly | QFile::Text))
  {
    qCritical() << tr("Cannot read file %1: %2.")
                                   .arg(m_fileName)
                                   .arg(file.errorString());
     return;
  }

	QDomDocument doc("config");

	QString errorMsg;
	int errorLine(0), errorColumn(0);

 	if (!doc.setContent(&file, &errorMsg, &errorLine, &errorColumn ))
 	{
     file.close();
     qCritical() << trUtf8("Error: [%1], row [%2], column [%3]")
                                                  .arg(errorMsg)
				                                          .arg(errorLine)
     			                                        .arg(errorColumn);
     return;
 	}
 	
 	file.close();

	QDomElement root = doc.documentElement();
	qDebug() <<  "root.tagName() = " << root.tagName() ;

	if (root.tagName() == "config")
		qDebug() << trUtf8("File contain config data.");
  else 
  {     
    qWarning() << trUtf8("Error. File no contain config data.");
    return;
  };
        
	QDomNodeList nodelist = doc.elementsByTagName( "file" );
	qDebug() << trUtf8("Match media files = %1 ").arg(nodelist.length());

	QDomNode node;
	QDomElement	 element;

	for (unsigned int i=0; i<nodelist.length(); i++)
	{
		node = nodelist.item(i);
		if ( node.isElement() )
		{
			element = node.toElement();
      m_playList.append(element.attribute("name"));
		};
	};

  qDebug() << "playList " << m_playList;
 
	nodelist = doc.elementsByTagName( "string" );
	qDebug() << trUtf8(" Match nodes <string> = %1 ").arg(nodelist.length ());

	for (unsigned int i=0; i<nodelist.length(); i++)
	{
		node = nodelist.item(i);
		if ( node.isElement() )
		{
			element = node.toElement();
      m_textList.append(element.text());
		};
	};

  qDebug() << "textList " << m_textList;

  int r, g, b;

  nodelist = doc.elementsByTagName( "textcolor" );
  if (nodelist.length() > 0) {
    node = nodelist.item(0);
    element = node.toElement();
    r = QString(element.attribute("r")).toInt();
    g = QString(element.attribute("g")).toInt();
    b = QString(element.attribute("b")).toInt();
    m_textColor = QColor( r, g, b );
  };

  qDebug() << "textColor = " << m_textColor;

  nodelist = doc.elementsByTagName( "backgroundcolor" );
  if (nodelist.length() > 0) {
    node = nodelist.item(0);
    element = node.toElement();
    r = QString(element.attribute("r")).toInt();
    g = QString(element.attribute("g")).toInt();
    b = QString(element.attribute("b")).toInt();
    m_backgroundColor = QColor( r, g, b );
  };

  qDebug() << "backgroundcolor = " << m_backgroundColor;

  nodelist = doc.elementsByTagName( "logfile" );
  if (nodelist.length() > 0) {
    node = nodelist.item(0);
    element = node.toElement();
    m_logFileName = element.attribute("pathname");
  };

  qDebug() << "logFileName = " << m_logFileName;    
 
  nodelist = doc.elementsByTagName( "textlist" );
  if (nodelist.length() > 0) {
    node = nodelist.item(0);
    element = node.toElement();
    m_textTimeout = QString( element.attribute("timeout") ).toInt()*1000;
    m_textSize      = QString( element.attribute("size") ).toInt();
    m_textPos      = QString( element.attribute("pos") ).toInt();
  };

  qDebug() << "textTimeout = " << m_textTimeout; 
  qDebug() << "textSize = " << m_textSize;
  qDebug() << "textPos = " << m_textPos;

}


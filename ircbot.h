#include <QCoreApplication>
#include <QTcpSocket>
#include <QFile>

#ifndef IRCBOT_H
#define IRCBOT_H

class Bot : public QObject
{
    Q_OBJECT;
    int port;
    QString server;
    QString nick;
    QString channel;
    QTcpSocket *socket;

public :
     Bot (const QString _server,
          const int _port,
          const  QString _nick,
          const QString _channel )
     {
         port = _port;
         server = _server;
         nick = _nick;
         channel = _channel;
         socket = new QTcpSocket(NULL);
         QObject::connect(socket, SIGNAL(connected()), this, SLOT(config_load()));
         QObject::connect(socket, SIGNAL(connected()), this, SLOT(connected ()));
         QObject::connect(socket, SIGNAL(connected()), this, SLOT(loop ()));
         QObject::connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected ()));
         QObject::connect (socket, SIGNAL (connected()), this, SLOT (foo()));
         QObject::connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
      };

     ~Bot ()
     {
         delete socket;
     }

    QString read_blocked();
    bool connect();
    void send(QString );
    void config_save();
    QString rename(QString , QString);
    void registr();
    void codepage();
    void join();
public slots :
     void connected ();
     void disconnected();
     void config_load();
     void loop();
     void foo() {qDebug()<<"foo()\n";  if(socket->QAbstractSocket::bytesAvailable()) qDebug()<<"get line\n";}
     void bytesWritten(qint64);
//  signals:
};

#endif


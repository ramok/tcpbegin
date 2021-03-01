#include <iostream>
#include <QSettings>
#include "ircbot.h"
using namespace std;

QSettings * settings = new QSettings( "settings.conf", QSettings::IniFormat );

QString Bot::read_blocked()
{
    while (!(socket->bytesAvailable()))
    {
        socket->waitForReadyRead(10000);
    }
    QString q = socket->readAll().constData();
    qDebug()<<q;
    return q;
}

bool Bot::connect()
{
    socket->connectToHost(server.toLatin1().constData(), port);
    //    soc->connectToHost("127.0.0.1", 4567);                                 // lochost
    if (!socket->waitForConnected(1000))
    {
        qDebug() << "Not Connected";
        return 0;
    }
    qDebug() << "Connected";
    return  1;
}

void Bot::send(QString q)
{
    //    cout<<"i send (cout) - "<<ch<<endl;
    qDebug()<<"i send (qDebug() ) - "<<q<<endl;
    socket->write(q.toLatin1().constData());
}

void Bot::registr()
{
    read_blocked();
    send( "NICK "+ nick +"\n");
 //   send("PING\n");
  //  read_blocked();
    send("USER qwert_zaq 8 x : qwert_zaq\n");
}

void Bot::codepage()
{
    read_blocked();
    send("CODEPAGE UTF-8\n");
}

void Bot::join()
{
    read_blocked();
    send("JOIN " + channel + "\n");
    read_blocked();
    send("PRIVMSG " + channel + " :hi from netcat\n");
}

void Bot::config_save()
{
    settings->beginGroup("login");
    settings->setValue("settings/server", server);
    settings->setValue("settings/port", port);
    settings->setValue("settings/nick", nick);
    settings->setValue("settings/channel", channel);
    settings->endGroup();
    settings->sync();
}


void Bot::disconnected()
{
    config_save();
    socket->close();
}

BotConfig Bot::config_load()
{
     BotConfig log;
     settings->beginGroup("login");
     log.ser = settings->value("settings/server", conf.ser).toString();
     log.por = settings->value("settings/port", conf.por).toInt();
     log.ni = settings->value("settings/nick", conf.ni).toString();
     log.chan = settings->value("settings/channel", conf.chan).toString();
     settings->endGroup();
     return log;
}


QString Bot::rename( QString oldn, QString q)
{
    QStringList list2 = q.split(QLatin1Char(':'), QString::SkipEmptyParts);
    QString head = list2[0];
    QString msg = list2[1];
    if ((head.indexOf("PRIVMSG "+ channel , 0) != -1) && (msg.startsWith("!nick")))
    {
        msg = msg.remove(0, 5);
        msg= msg.simplified();
        if (msg.contains(QRegExp("[^a-zA-Z_-/d]")))
        {
            qDebug()<<"error nick\n";
        }
        else
        {
            QString h = "NICK "+msg+'\n';
            send(h);
            QString s = read_blocked();
             if (s.indexOf("Nickname is already in use" , 0) != -1)
            {
                return oldn;
            }
            nick = msg;
            config_save();
            return msg;
        }
    }
}

void Bot::loop()
{
while (1)
{
    QString c = read_blocked();
    qDebug() << c;
    if (c.indexOf("!quit", 0)!= -1)
        disconnected();
    if ((c.indexOf("PRIVMSG "+ channel, 0) != -1) && (c.indexOf(nick , 0) != -1))
    {
        send("PRIVMSG " + channel + " : i hear you\n");
        socket->waitForBytesWritten();
    }
    if (c.indexOf("PING", 0)!= -1)
    {
        send("PONG " + server + "\n");
    }
    if ((c.indexOf("PRIVMSG "+ channel, 0) != -1) && (c.indexOf("!nick" , 0) != -1))
    {
        nick = rename(nick, c);
    }
}
}

 void Bot::connected ()
 {
      registr();
      codepage();
      join();
 }

 void Bot::bytesWritten(qint64 bytes)
 {
     qDebug() << bytes << " bytes written...";
 }

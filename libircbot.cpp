#include <iostream>
#include "ircbot.h"
using namespace std;

const char * reg_data = "bot_data.txt";
QFile init_file(reg_data);

#include <ircbot.h>

QString Bot :: read_blocked(Bot *pi)
{
    while (!(pi->socket->bytesAvailable()))
    {
        pi->socket->waitForReadyRead(10000);
    }
    QString q = pi->socket->readAll().constData();
    qDebug()<<q;
    return q;
}

bool Bot :: connect(Bot  *pi)
{
    pi->socket->connectToHost(pi->def_server.toLatin1().constData(), pi->prt);
    //    soc->connectToHost("127.0.0.1", 4567);                                 // lochost
    if (!pi->socket->waitForConnected(1000))
    {
        qDebug() << "Not Connected";
        return 0;
    }
    qDebug() << "Connected";
    return  1;
}

void Bot :: send(Bot  *pi, QString q)
{
    //    cout<<"i send (cout) - "<<ch<<endl;
    qDebug()<<"i send (qDebug() ) - "<<q<<endl;
    pi->socket->write(q.toLatin1().constData());
}

void Bot :: registr(Bot *pi)
{
    read_blocked(pi);
    send(pi, "NICK "+ pi->def_nick +"\n");
    send(pi,"PING\n");
    read_blocked(pi);
    send(pi,"USER qwert_zaq 8 x : qwert_zaq\n");
}

void Bot :: codepage(Bot *pi)
{
    read_blocked(pi);
    send(pi,"CODEPAGE UTF-8\n");
}

void Bot :: join(Bot *pi)
{
    read_blocked(pi);
    send(pi, "JOIN " + pi->def_channel + "\n");
    read_blocked(pi);
    send(pi, "PRIVMSG " + pi->def_channel + " :hi from netcat\n");
}

void Bot :: config_save(Bot *pi)
{
    if(init_file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        init_file.write(pi->def_nick.toLatin1());
        init_file.close();
    }
    else
        cout<<"cant open file bot_data for save\n";
}

void Bot :: disconnect(Bot *pi)
{
    config_save(pi);
    pi->socket->close();
}

void Bot :: config_load(Bot *pi)
{
    if (!init_file.open(QIODevice::ReadOnly))
    {
        qWarning("Cannot open file for reading");
        qDebug()<<"name is "<<pi->def_nick<<endl;
        config_save(pi);
    }
    else
    {
        QTextStream in(&init_file);
        QString line = in.readLine();
        qDebug()<<"line is "<<line<<endl;
        pi->def_nick = line;
        init_file.close();
    }
}

QString Bot :: rename(Bot *pi, QString oldn, QString q)
{
    QStringList list2 = q.split(QLatin1Char(':'), QString::SkipEmptyParts);
    QString head = list2[0];
    QString msg = list2[1];
    if ((head.indexOf("PRIVMSG "+ pi->def_channel , 0) != -1) && (msg.startsWith("!nick")))
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
            send(pi, h);
            QString s = read_blocked(pi);
             if (s.indexOf("Nickname is already in use" , 0) != -1)
            {
                return oldn;
            }
            pi->def_nick = msg;
            config_save(pi);
            return msg;
        }
    }
}

void Bot :: loop(Bot *pi)
{
while (1)
{
    QString c = read_blocked(pi);
    qDebug() << c;
    if (c.indexOf("!quit", 0)!= -1)
        disconnect(pi);
    if ((c.indexOf("PRIVMSG "+ pi->def_channel, 0) != -1) && (c.indexOf(pi->def_nick , 0) != -1))
    {
        send(pi, "PRIVMSG " + pi->def_channel + " : i hear you\n");
        pi->socket->waitForBytesWritten();
    }
    if (c.indexOf("PING", 0)!= -1)
    {
        send(pi, "PONG " + pi->def_server + "\n");
    }
    if ((c.indexOf("PRIVMSG "+ pi->def_channel, 0) != -1) && (c.indexOf("!nick" , 0) != -1))
    {
        pi->def_nick = rename(pi, pi->def_nick, c);
    }
}
}

/*
const char * reg_data = "bot_data.txt";
QFile init_file(reg_data);

#include <ircbot.h>

QString ircbot_read_blocked(ircbot *pi)
{
    while (!(pi->socket->bytesAvailable()))
    {
        pi->socket->waitForReadyRead(10000);
    }
    QString q = pi->socket->readAll().constData();
    qDebug()<<q;
    return q;
}

bool ircbot_connect(ircbot *pi)
{
    pi->socket->connectToHost(pi->def_server.toLatin1().constData(), pi->prt);
    //    soc->connectToHost("127.0.0.1", 4567);                                 // lochost
    if (!pi->socket->waitForConnected(1000))
    {
        qDebug() << "Not Connected";
        return 0;
    }
    qDebug() << "Connected";
    return  1;
}

void ircbot_send(QTcpSocket *soc, QString q)
{
    //    cout<<"i send (cout) - "<<ch<<endl;
    qDebug()<<"i send (qDebug() ) - "<<q<<endl;
    soc->write(q.toLatin1().constData());
}

void ircbot_register(ircbot *pi)
{
    ircbot_read_blocked(pi);
    ircbot_send(pi->socket, "NICK "+ pi->def_nick +"\n");
    ircbot_send(pi->socket,"PING\n");
    ircbot_read_blocked(pi);
    ircbot_send(pi->socket,"USER qwert_zaq 8 x : qwert_zaq\n");
}

void ircbot_codepage(ircbot *pi)
{
    ircbot_read_blocked(pi);
    ircbot_send(pi->socket,"CODEPAGE UTF-8\n");
}

void ircbot_join(ircbot *pi)
{
    ircbot_read_blocked(pi);
    ircbot_send(pi->socket, "JOIN " + pi->def_channel + "\n");
    ircbot_read_blocked(pi);
    ircbot_send(pi->socket, "PRIVMSG " + pi->def_channel + " :hi from netcat\n");
}

void ircbot_config_save(ircbot *pi)
{
    if(init_file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        init_file.write(pi->def_nick.toLatin1());
        init_file.close();
    }
    else
        cout<<"cant open file bot_data for save\n";
}

void ircbot_disconnect(ircbot *pi)
{
    ircbot_config_save(pi);
    pi->socket->close();
}

void ircbot_config_load(ircbot *pi)
{
    if (!init_file.open(QIODevice::ReadOnly))
    {
        qWarning("Cannot open file for reading");
        qDebug()<<"name is "<<pi->def_nick<<endl;
        ircbot_config_save(pi);
    }
    else
    {
        QTextStream in(&init_file);
        QString line = in.readLine();
        qDebug()<<"line is "<<line<<endl;
        pi->def_nick = line;
        init_file.close();
    }
}

QString ircbot_rename(ircbot *pi, QString oldn, QString q)
{
    QStringList list2 = q.split(QLatin1Char(':'), QString::SkipEmptyParts);
    QString head = list2[0];
    QString msg = list2[1];
    if ((head.indexOf("PRIVMSG "+ pi->def_channel , 0) != -1) && (msg.startsWith("!nick")))
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
            ircbot_send(pi->socket, h);
            QString s = ircbot_read_blocked(pi);
             if (s.indexOf("Nickname is already in use" , 0) != -1)
            {
                return oldn;
            }
            pi->def_nick = msg;
            ircbot_config_save(pi);
            return msg;
        }
    }
}

void ircbot_loop(ircbot *pi)
{
while (1)
{
    QString c = ircbot_read_blocked(pi);
    qDebug() << c;
    if (c.indexOf("!quit", 0)!= -1)
        ircbot_disconnect(pi);
    if ((c.indexOf("PRIVMSG "+ pi->def_channel, 0) != -1) && (c.indexOf(pi->def_nick , 0) != -1))
    {
        ircbot_send(pi->socket, "PRIVMSG " + pi->def_channel + " : i hear you\n");
        pi->socket->waitForBytesWritten();
    }
    if (c.indexOf("PING", 0)!= -1)
    {
        ircbot_send(pi->socket, "PONG " + pi->def_server + "\n");
    }
    if ((c.indexOf("PRIVMSG "+ pi->def_channel, 0) != -1) && (c.indexOf("!nick" , 0) != -1))
    {
        pi->def_nick = ircbot_rename(pi, pi->def_nick, c);
    }
}
}
*/

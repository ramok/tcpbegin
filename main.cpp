#include <QCoreApplication>
#include <iostream>
#include <QTcpSocket>
#include <QThread>
#include  <QAbstractSocket>
using namespace std;

//    qDebug()<<socket->readAll();
//qDebug()<<"Reading"<<socket->bytesAvailable(); // кол во байт
//while(socket->bytesAvailable() == 0) { socket->waitForReadyRead(100); }  // ожидание ОТ сокета
//  socket->waitForBytesWritten(100);   // проталкивание В сокет

/***************************************************************************/ //  бот
int main()
{
    QTcpSocket *socket;

    socket = new QTcpSocket(NULL);
    socket->connectToHost("5.196.134.158", 6667);
    if (!socket->waitForConnected(1000))
    {
        qDebug() << "Not Connected";
        return 1;
    }
        qDebug() << "Connected";
        while (1)
            {
            while ( !(socket->bytesAvailable()))
            {
            socket->waitForReadyRead(10000);
            }

            qDebug() << socket->readAll();
            socket->write( "NICK test_bot\n ");
            socket->write( "PING\n");

            while (!( socket->bytesAvailable()))
            {
            socket->waitForBytesWritten(10000);
            }
            qDebug() << socket->readAll();
            socket->write( "USER qwert_zaq 8 x : qwert_zaq\n");

            while (!( socket->bytesAvailable()))
            {
            socket->waitForBytesWritten(10000);
            }
            qDebug() << socket->readAll();
            socket->write("JOIN #RusChat\n");

            while (!( socket->bytesAvailable()))
            {
            socket->waitForBytesWritten(10000);
            }
            qDebug() << socket->readAll();
            socket->write("PRIVMSG #RusChat : hi from netcat\n");

            while (!( socket->bytesAvailable()))
            {
            socket->waitForBytesWritten(10000);
            }
           qDebug() << socket->readAll();
           socket->write("PONG irc.lucky.net\n ");

           while(socket->bytesAvailable() == 0) {
           socket->waitForReadyRead(100);
           }
           socket->close();
       }


      return 0;
}
/***************************************************************************/ //  бот


/*************************************************************************** // локал бот
int main()
{
    QTcpSocket *socket;

    socket = new QTcpSocket(NULL);
 //   socket->connectToHost("62.149.7.206", 6660);
    socket->connectToHost("127.0.0.1", 4567);
    if (!socket->waitForConnected(1000))
    {
        qDebug() << "Not Connected";
        return 1;
    }
        qDebug() << "Connected";
        while (1)
            {
            while ( !(socket->bytesAvailable()))
            {
            socket->waitForReadyRead(10000);
            }

            qDebug() << socket->readAll();
            socket->write( "NICK test_bot\n ");
            socket->write( "PING\n");

            while ( !(socket->bytesAvailable())) // удалить в ирц
            {                                    //
            socket->waitForReadyRead(10000);     //
            }                                    //

        //    while (!( socket->bytesAvailable()))
        //    {
        //    socket->waitForBytesWritten(10000);
        //    }
            qDebug() << socket->readAll();
            socket->write( "USER qwert_zaq 8 x : qwert_zaq\n");

            while ( !(socket->bytesAvailable())) // удалить в ирц
            {                                    //
            socket->waitForReadyRead(10000);     //
            }                                    //

         //   while (!(socket->bytesAvailable()))
         //   {
         //   socket->waitForBytesWritten(10000);
          //  }
            qDebug() << socket->readAll();
            socket->write("JOIN #Kashchenko\n");

            while ( !(socket->bytesAvailable())) // удалить в ирц
            {                                    //
            socket->waitForReadyRead(10000);     //
            }                                    //

         //   while (!(socket->bytesAvailable()))
         //   {
         //   socket->waitForBytesWritten(10000);
          //  }
            qDebug() << socket->readAll();
            socket->write("PRIVMSG #Kashchenko : hi from netcat\n");

            while ( !(socket->bytesAvailable())) // удалить в ирц
            {                                    //
            socket->waitForReadyRead(10000);     //
            }                                    //

         //   while (!(socket->bytesAvailable()))
         //   {
         //   socket->waitForBytesWritten(10000);
          //  }
           qDebug() << socket->readAll();
           socket->write("PONG irc.lucky.net\n ");

           while ( !(socket->bytesAvailable())) // удалить в ирц
           {                                    //
           socket->waitForReadyRead(10000);     //
           }                                    //

           while(socket->bytesAvailable() == 0) {
           socket->waitForReadyRead(100);
           }
           socket->close();
       }


      return 0;
}
***************************************************************************/ // локал бот

/*
int main()
{
    QTcpSocket *socket;

    socket = new QTcpSocket(NULL);
    socket->connectToHost("127.0.0.1", 4567);

    if (!socket->waitForConnected(1000))
    {
        qDebug() << "Not Connected";
        return 1;
    }

    qDebug() << "Connected";
    while (1) {
        socket->write("input> ");

        while(socket->bytesAvailable() == 0) {
            socket->waitForReadyRead(100);
        }

        qDebug() << "Reading" << socket->bytesAvailable();

        QString c = socket->readLine();
        qDebug() << c;

        if (c.simplified().compare("exit") == 0)
            break;

        QString d = "you type: " + c;
        socket->write(d.toLocal8Bit().constData());
    }

    socket->close();

    return 0;
}
*/

/*
int main()
 {
    QTcpSocket * socket;
    socket = new QTcpSocket(NULL);
    socket->connectToHost("127.0.0.1", 4567);
    if (socket->waitForConnected (1000))
    {
        qDebug() << "Connected";
        while (1){
        socket->write("input> ");
         socket->waitForBytesWritten(1000);
        while(socket->bytesAvailable() == 0) { socket->waitForReadyRead(100); }
         qDebug()<<"Reading"<<socket->bytesAvailable();
         QString c = socket->readLine(10);
         qDebug()<<c;
         QString d="you type: "+c;
         char const* ch = d.toLocal8Bit().constData();
         socket->write(ch);
         if (strcmp(ch,"exit")==0) socket->close();
        }

    }
    else  {  qDebug()<<"Not Connected";
  }
}
*/
/*
int main()
 {
    QTcpSocket * socket;
    socket = new QTcpSocket(NULL);
    socket->connectToHost("127.0.0.1", 4567);
    if (socket->waitForConnected (1000))
    {
        qDebug() << "Connected";
         socket->write("hello\n");
         socket->waitForBytesWritten(1000);
        while(socket->bytesAvailable() == 0) { socket->waitForReadyRead(100); }
         qDebug()<<"Reading"<<socket->bytesAvailable();
         //qDebug()<<socket->readLine(10);
         qDebug()<<socket->readAll();
         socket->close();
    }
    else  {  qDebug()<<"Not Connected";
  }
}
*/
/*
int main()
 {
    QTcpSocket * socket;
    socket = new QTcpSocket(NULL);
    socket->connectToHost("127.0.0.1", 4567);
    if (socket->waitForConnected (1000))
    {
        qDebug() << "Connected";
       for (int i=5; i>=0; --i)
       {
         QString c = QString::number(i);
         QString d="hello "+c;
         char const* ch = d.toLocal8Bit().constData();
         socket->write(ch);
         socket->write("\n");
         socket->waitForBytesWritten();
         QThread::sleep (1);
       }
       socket->write("BOOM!!!\n");
       socket->waitForBytesWritten();
       socket->close();
    }
    else  {  qDebug()<<"Not Connected";    }
  }
*/
/*
int main()
 {
    QTcpSocket * socket;
    socket = new QTcpSocket(NULL);
    socket->connectToHost("127.0.0.1", 4567);
    if (socket->waitForConnected (1000))
    {
        qDebug() << "Connected";
     }
         socket->write("Hello\n");
         socket->write("World\n");
       socket->waitForBytesWritten();
       socket->close();
    }
*/

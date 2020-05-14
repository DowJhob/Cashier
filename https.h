#ifndef HTTPS_H
#define HTTPS_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QElapsedTimer>

#include <QAuthenticator>

class https : public QObject
{
    Q_OBJECT
public:
    QByteArray a{};
    QString addr;
    QString port;
    QString SUID;
    QString idContractor;
    QString lang = "ru-RU";
    https()
    {
        manager = new QNetworkAccessManager(this);
        connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
        connect(manager, SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)), SLOT(provideAuthenication(QNetworkReply*,QAuthenticator*)));
        QSslConfiguration conf = QSslConfiguration::defaultConfiguration();
        conf.setPeerVerifyMode(QSslSocket::VerifyNone);
        conf.setProtocol(QSsl::AnyProtocol);

        request.setSslConfiguration(conf);
     ////   request.setUrl(QUrl("https://10.1.7.11:27001/ExternalGate.svc/webssl/GetSectorSchemaDataWithPriceCategory?SUID=101&idEvent=501B6BB6-F5A1-4AB9-A0EE-5735A82EAC3D&idSector=90AFA12F-A86F-4FBA-B382-25BC4CE17FF5&lang=ru-RU"));
        ////GetSectorSchemaDataWithPriceCategory?SUID=45&idEvent=248e246b-9912-4570-bc97-061e4f3c1f07&idSector=16887554-65c7-4df6-9dbf-67cc9907a8ae&lang=ru-RU
    }
    void setAddress(QString addr)
    {
        this->addr = addr;
    }
    void setPort(QString port)
    {
        this->port = port;
    }
    void setSUID(QString SUID)
    {
        this->SUID = SUID;
    }
    void setLang(QString lang)
    {
        this->lang = lang;
    }

public slots:
    void GetEventsListByContractorData()
    {
        t.start();
        request.setUrl(QUrl("https://" + addr + ":" + port + "/ExternalGate.svc/webssl/"
                                                             "GetEventsListByContractorData?SUID=" + SUID + "&"
                                                                              "idContractor=" + idContractor + "&"
                                                                              "lang=" + lang));
        manager->get(request);
    }
    void GetSectorsListByEventData(QString idEvent)
    {
        t.start();
        request.setUrl(QUrl("https://" + addr + ":" + port + "/ExternalGate.svc/webssl/"
                                                             "GetSectorsListByEventData?"
                                                             "SUID=" + SUID + "&"
                                                                              "idEvent=" + idEvent + "&"
                                                                              "lang=" + lang));
        manager->get(request);
    }
    void GetSectorSchemaDataWithPriceCategory(QString idEvent, QString idSector)
    {
        t.start();
        request.setUrl(QUrl("https://" + addr + ":" + port + "/ExternalGate.svc/webssl/"
                                                             "GetSectorSchemaDataWithPriceCategory?"
                                                             "SUID=" + SUID + "&"
                                                                              "idEvent=" + idEvent + "&"
                                                                              "idSector=" + idSector + "&"
                                                                              "lang=" + lang));
        manager->get(request);
    }

private:
    QNetworkAccessManager *manager;
    QNetworkRequest request;
    QElapsedTimer t;
private slots:
    void provideAuthenication(QNetworkReply *reply, QAuthenticator *ator){
        qDebug() << "INSIDE AUTH";
        qDebug() << reply->readAll(); // this is just to see what we received
        ator->setUser(QString("spark"));
        ator->setPassword(QString("spark"));
    }
    void replyFinished(QNetworkReply *reply){
        if(reply->error())
        {
            qDebug() << "ERROR!";
            qDebug() << reply->errorString();
        }
        else {
            a = reply->readAll() ;
            qDebug() << a.size();
            //i print out some stuff pertaining to the message+
            emit read(a);
        }

        reply->deleteLater();
        long long tt = t.nsecsElapsed();
            emit log("ответ сервера http: " + QString::number( tt / 1000000 ) + "." + QString::number( tt % 1000000 ) +" ms" );

    }
signals:
    void read(QByteArray);
    void log(QString);
};

#endif // HTTPS_H

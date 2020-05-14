#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QElapsedTimer>
#include "https.h"
#include <common_types.h>
#include "settings.h"

class controller : public QObject
{
    Q_OBJECT
public:
    QVector<Seat*> vectorSeatList{};
    controller()
    {
        init();
        connect(&h, SIGNAL(read(QByteArray)), SLOT(parse(QByteArray)));

    }
    void setAddress(QString addr)
    {
        h.addr = addr;
    }
    void setPort(QString port)
    {
        h.port = port;
    }
    void setSUID(QString SUID)
    {
        h.SUID = SUID;
    }
    void setIdContractor(QString idContractor)
    {
        h.idContractor = idContractor;
    }
    void setLang(QString lang)
    {
        h.lang = lang;
    }

public slots:
    void getEvent()
    {
        h.GetEventsListByContractorData();
    }
    void _sectorSelected(QString sectorUID)
    {
        h.GetSectorSchemaDataWithPriceCategory(currentEventID, sectorUID);
    }
    void eventSelected(QString currentEventID)
    {
        this->currentEventID = currentEventID;
        h.GetSectorsListByEventData(currentEventID);
    }
    void setCurrentEvent(QString currentEventID)
    {
        this->currentEventID = currentEventID;
    }

private:
    QElapsedTimer t;

    settings sett;
    QString currentEventID;
    QByteArray currentSectorList;
    QByteArray currentSector;

    https h;

    void init()
    {
        if ( sett.settings_reader() )
        {
            h.setAddress( sett.server_addr );
            h.setPort( sett.port );
            h.setSUID( sett.SUID );
            h.idContractor = sett.idContractor;
            connect(&h, &https::log,  [=](const QString newValue){emit log(newValue);});
        }
    }
private slots:
    void parse(QByteArray a)
    {
        long long tt = 0;
        t.start();
        QJsonDocument document = QJsonDocument::fromJson(a);
        // Забираем из документа корневой объект
        QJsonObject root = document.object();
        QString str = root.keys().at(0);
        //
        if ( str == "GetEventsListByContractorDataResult" )
        {
            QJsonValue EventList = root.value(str).toObject().value("result").toObject().value("EventList");
            QList<QStringList> qEventList{};
            if ( EventList.isArray() )
            {

                QJsonArray a = EventList.toArray();
                for ( int i = 0; i < a.count(); i++ )
                {
                    QStringList event{};
                    QJsonObject o = a.at(i).toObject();
                    event.append( o.value("Caption").toString() );
                    event.append( o.value("EventDateTime").toString() );
                    event.append( o.value("IdEvent").toString() );
                    qEventList.append(event);
                    //   o.value("Caption");
                    //   o.value("Caption");
                    //   o.value("Caption");
                }
            }
            emit GetEventsListByContractorDataResult(qEventList);
            //qDebug() << qEventList;
            //    qDebug() << result.toString();
        }
        if ( str == "GetSectorsListByEventDataResult" )
        {

            QJsonValue SectorList = root.value(str).toObject().value("result").toObject().value("SectorList");
            QList<QStringList> qSectortList{};
            if ( SectorList.isArray() )
            {

                QJsonArray a = SectorList.toArray();

                for ( int i = 0; i < a.count(); i++ )
                {
                    QStringList sector{};
                    QJsonObject o = a.at(i).toObject();
                    sector.append( o.value("Caption").toString() );

                    sector.append( o.value("IdSector").toString() );
                    qSectortList.append(sector);

                    //              sector.append( o.value("PricingZonesWithCategories").toString() );

                }
            }
            tt = t.nsecsElapsed();
            emit GetSectorsListByEventDataResult(qSectortList);
        }
        if ( str == "GetSectorSchemaDataWithPriceCategoryResult" )
        {
            QJsonDocument document = QJsonDocument::fromJson(a);
            QJsonObject root = document.object();
            //============================ Места =====================================
            QJsonValue Seats = root.value(str).toObject().value("result").toObject().value("SectorSchema").toObject().value("Seats");
            foreach (Seat *s, vectorSeatList )
                delete s;
vectorSeatList.clear();
            if( Seats.isArray() )
            {
                QJsonArray SeatsArray = Seats.toArray();
                for(int i = 0; i < SeatsArray.count(); i++)
                {
                    QJsonObject _Seat = SeatsArray.at(i).toObject();
                    //=========================================

                    Seat *ssss = new Seat();
                    ssss->Row = _Seat.value("Row").toInt();
                    ssss->Number=_Seat.value("Number").toInt();
                    ssss->IsSeat =_Seat.value("IsSeat").toInt();
                    ssss->Available =_Seat.value("Available").toInt();
                    ssss->NumberCaption =_Seat.value("NumberCaption").toString();
                    ssss->RowCaption =_Seat.value("RowCaption").toString();
                    ssss->IdSeat =_Seat.value("IdSeat").toString();
                    ssss->PriceColor =_Seat.value("PriceColor").toString();

vectorSeatList.append( ssss );

                }
            }
            //============================ Категории =====================================
            QJsonValue Zones = root.value(str).toObject().value("result").toObject().value("SectorSchema").toObject().value("PricingZonesWithCategories");
            QList<QStringList> qZonesList{};
            if( Zones.isArray() )
            {
                QJsonArray CatArray = Zones.toArray();
                for(int i = 0; i < CatArray.count(); i++)
                {
                    QJsonObject _Cat = CatArray.at(i).toObject();
                    QStringList cat{};
                }
            }
tt = t.nsecsElapsed();
            //emit GetSectorSchemaDataWithPriceCategoryResult(qSeatsList);
            emit vectorGetSectorSchemaDataWithPriceCategoryResult(&vectorSeatList);

        }
//      tt = t.nsecsElapsed();
        emit log("обработка ответа сервера (преобразование JSON): " + QString::number( tt / 1000000 ) + "." + QString::number( tt % 1000000 ) +" ms" );

    }

signals:
    void GetEventsListByContractorDataResult(QList<QStringList>);
    void GetSectorsListByEventDataResult(QList<QStringList>);
    void GetSectorSchemaDataWithPriceCategoryResult(QList<QStringList>);
    void vectorGetSectorSchemaDataWithPriceCategoryResult(QVector<Seat*>*);  //передаем указатель на массив указателей на структуру места
    void log(QString);
};

#endif // CONTROLLER_H

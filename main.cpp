#include <QApplication>

#include <QObject>

#include <mainwindow.h>
#include <controller.h>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    controller ctrl;



    MainWindow w;




    QObject::connect(&w, SIGNAL(getEvent()), &ctrl, SLOT(getEvent()));
    QObject::connect(&w, SIGNAL(eventSelected(QString)), &ctrl, SLOT(eventSelected(QString)));
    QObject::connect(&w, SIGNAL(_sectorSelected(QString)), &ctrl, SLOT(_sectorSelected(QString)));

    QObject::connect(&ctrl, SIGNAL(GetEventsListByContractorDataResult(QList<QStringList>)), &w, SLOT(GetEventsListByContractorDataResult(QList<QStringList>)));
    QObject::connect(&ctrl, SIGNAL(GetSectorsListByEventDataResult(QList<QStringList>)), &w, SLOT(GetSectorsListByEventDataResult(QList<QStringList>)));
    //QObject::connect(&ctrl, SIGNAL(GetSectorSchemaDataWithPriceCategoryResult(QList<QStringList>)), &w, SLOT(GetSectorSchemaDataWithPriceCategoryResult(QList<QStringList>)));
    QObject::connect(&ctrl, SIGNAL(vectorGetSectorSchemaDataWithPriceCategoryResult(QVector<Seat*>*)), &w, SLOT(vectorGetSectorSchemaDataWithPriceCategoryResult(QVector<Seat*>*)));





    QObject::connect(&ctrl, SIGNAL(log(QString)), &w, SLOT(logger(QString)));
//QObject::connect(&w, SIGNAL(_getSector(QString)), &ctrl, SLOT(_getSector(QString)));
w.init();
    w.show();;

    return app.exec();
}

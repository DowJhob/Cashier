#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QStringListModel>
#include <common_types.h>
#include "https.h"
#include  <viewwidget.h>

#include "eventselector.h"
#include <QTableModel>

#include <LimeReport>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void init()
    {


     emit getEvent();
    }
public slots:
    void GetEventsListByContractorDataResult(QList<QStringList> currentEventList)
    {
        this->EventList = currentEventList;
    }
    void GetSectorsListByEventDataResult(QList<QStringList> sectorList)
    {
        this->SectorList = sectorList;
        view.createSectors( sectorList);
    }
    void vectorGetSectorSchemaDataWithPriceCategoryResult(QVector<Seat*>* seats)
    {
        view.vector_seatsCreate( seats );
    }
void logger(QString s);
private slots:
    void eventSelectTrigger();
    void saleTrigger();
    void reportTrigger();
    void settingsTrigger();
    void EventSelected(QString s)
    {
        emit eventSelected(s);
    }

void sectorSelected(QString sectorUID)
{
    emit _sectorSelected(sectorUID);
}
void on_action_triggered()
{

    QStringListModel *model = new QStringListModel();
    QStringList list;
        list << "a" << "b" << "c";
        model->setStringList(list);

    mReport.dataManager()->addModel("rep", model, false);
    mReport.designReport();
}

void on_action_001_triggered()
{

}

private:
    Ui::MainWindow *ui;
    eventSelector *evSEL;
//    QString currentidContractor = "E79F6F21-306C-4B0C-973C-BE54EF4A6BD6";
    QLabel statusLabel;
    viewWidget view;
    QList<QStringList> EventList;
    QList<QStringList> SectorList;
    QByteArray currentSector;
    LimeReport::ReportEngine mReport;

signals:
    void getEvent();
    void eventSelected(QString);
    void _sectorSelected(QString sectorUID);
};

#endif // MAINWINDOW_H

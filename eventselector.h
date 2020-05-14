#ifndef EVENTSELECTOR_H
#define EVENTSELECTOR_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QTableWidget>
#include <QGridLayout>
#include <QHeaderView>


class eventSelector : public QDialog
{
    Q_OBJECT
public:
    eventSelector(QWidget* parent = nullptr, QList<QStringList> EventList = {} ) : QDialog( parent,   Qt::WindowTitleHint | Qt::WindowSystemMenuHint ) //: QWidget( parent )
    {
        //setParent(parent);
        setLayout(&lay);
        eventTable.setRowCount( EventList.count() );
        eventTable.setColumnCount(3);
        eventTable.setEditTriggers(nullptr);
        eventTable.setSelectionBehavior(QAbstractItemView::SelectRows);

        for( int row = 0;  row < EventList.count(); row++ )
        {
            QStringList strlst = EventList.at(row);
            //      eventTable.setItem(row, 0, new QTableWidgetItem(strlst.at(0)));
            //      eventTable.setItem(row, 1, new QTableWidgetItem(strlst.at(1)));
            //      eventTable.setItem(row, 2, new QTableWidgetItem(strlst.at(2)));
            for( int col = 0;  col <= 2; col++ )
            {
                QTableWidgetItem *it = new QTableWidgetItem(strlst.at(col));
                eventTable.setItem(row, col, it);

            }
        }
        connect(&eventTable ,SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(eventSelected(QTableWidgetItem*)));
        eventTable.verticalHeader()->sectionResizeMode(QHeaderView::ResizeToContents);
        eventTable.horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
        eventTable.horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
        eventTable.horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
        eventTable.resizeRowsToContents();
        eventTable.resizeColumnsToContents();
        resize( eventTable.size() );

        //  setGeometry( eventTable.geometry());
        //this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

        lay.addWidget(&eventTable);

    }
private:

    QTableWidget eventTable;
    QGridLayout lay;
private slots:
    void eventSelected( QTableWidgetItem* it )
    {
        emit eventID( eventTable.item(it->row(), 2 )->text() );
        accept();
        //emit accepted();
        //deleteLater();
    }
signals:
    void eventID(QString);
};

#endif // EVENTSELECTOR_H

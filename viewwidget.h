#ifndef VIEWWIDGET_H
#define VIEWWIDGET_H

#include <QObject>
#include <QWidget>
#include <QMouseEvent>
#include <QRubberBand>
#include <QTabWidget>
#include <QLabel>
#include <QDialog>
#include <QLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QDebug>
#include <QSpacerItem>
#include <QElapsedTimer>
#include <common_types.h>
//#include <QOpenGLWidget>



class viewWidget : public QWidget
{
    Q_OBJECT
public:

    viewWidget()
    {
        createLayouts();
        rubberBand = new QRubberBand(QRubberBand::Rectangle, this);




        //create();
    }
    void init()
    {

        //     this->setLayout(&seatLayot);

        for ( int col = 0; col < 45; col++)
            for ( int row = 0; row < 20; row++)

            {

            }

    }
public slots:
    void vector_seatsCreate(QVector<Seat*>* seats)
    {
        t.start();

        delete_child(&seatLayot);

        rowCount = 0;
        seatList.clear();
        foreach( Seat *seat, *seats )
        {
            seatCreate(seat->Row,
                       seat->Number ,
                       seat->IsSeat ,
                       seat->Available ,
                       seat->NumberCaption ,
                       seat->RowCaption ,
                       seat->IdSeat ,
                       seat->PriceColor );
        }
        int _col = seatLayot.columnCount();
        for ( int row = 0; row < seatLayot.rowCount(); row++ )
            if ( seatLayot.itemAtPosition(row, 0) != nullptr )
            {
          //      static_cast<QLabel*>( seatLayot.itemAtPosition(row, 0)->widget() )->text()
                QLabel *l = createSeatMarker( static_cast<QLabel*>( seatLayot.itemAtPosition(row, 0)->widget() )->text() );
                l->setStyleSheet(//"margin-left: 10px;
                                 "border-radius: 3px; background: #ffffff; border: 2px solid black; color: black;" );
                seatLayot.addWidget( l, row, _col + 1 );
                       QSpacerItem *vS = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
                seatLayot.addItem( vS, row, _col );
        }
        long long tt = t.nsecsElapsed();
emit log( "seats label total create time: " + QString::number( tt / 1000000 ) + "." + QString::number( tt % 1000000 ) +" ms" );
        qDebug() << "seats label total create time: " <<  t.nsecsElapsed();
    }
    void CatchSeatWithPrice()
    {

    }
    void ReleaseSeat()
    {

    }
    void createSectors(QList<QStringList> sectorList)
    {
        delete_child(&seatLayot);
        delete_child(&sectorListLayout);
        sectorButtonList.clear();
        //    ui->SaleBox->setVisible(true);
        foreach ( QStringList sector,  sectorList)
        {
            QPushButton *b = new QPushButton(this);

            b->setText( sector.at(0) );

            b->setProperty("UID", sector.at(1));

            sectorListLayout.addWidget( b );
            sectorButtonList.append(b);
            connect(b, SIGNAL(clicked()), SLOT(buttonHandler()));
        }
    }
void create_Legends()
{
    legendBox.layout()->addWidget( &tabWidget );
}
private slots:
    void buttonHandler()
    {
        QPushButton *b = reinterpret_cast<QPushButton*>(sender());
        foreach ( QPushButton *b,  sectorButtonList)
        {
            b->setStyleSheet(" background: ;color: black;" );
        }

        b->setStyleSheet(" background: #808080;color: red;" );
        emit sectorSelected(b->property("UID").toString());
        qDebug() << b->property("UID").toString() ;
    }
private:
    void delete_child(QLayout* lay)
    {
        QLayoutItem* child;
        while ( lay->count() != 0 ) {
            child = lay->takeAt ( 0 );
            if ( child->layout() != nullptr )
            {
                lay->removeItem( child->layout() );
            } else
                if ( child->widget() != nullptr )
                {
                    child->widget()->deleteLater();
                }

            delete child;
        }

    }
    void createLayouts()
    {
        setLayout(&main_gridLayout);
        //       SaleBox.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        SaleBox.setTitle( "Продажа" );
        //==================================================
legendBox.setLayout(&legendBoxLayout);
        legendBox.setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        legendBox.setMaximumSize(200, 6000);
        legendBox.setTitle( "Легенда" );
        //==================================================
        sectorListBox.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sectorListBox.setMinimumSize(0, 50);
        sectorListBox.setTitle("Список секторов");
        sectorListBox.setLayout(&sectorListLayout);

        main_gridLayout.addWidget( &sectorListBox, 0 , 0 , 1 ,2 );
        main_gridLayout.addWidget( &legendBox, 1 , 0 );
        main_gridLayout.addLayout( &seatLayot , 1, 1//, 1 , 2
                                   );
        seatLayot.setSpacing(5);

    }
    void mousePressEvent(QMouseEvent* event)
    {
        if ( event ->buttons() & Qt::LeftButton )
        {

            origin = event->pos();

            if (!rubberBand)
                rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
            rubberBand->setGeometry( QRect( origin, QSize() ) );
            rubberBand->show();
        }

    }
    void mouseMoveEvent(QMouseEvent *event)
    {
        rubberBand->setGeometry(QRect(origin, event->pos()).normalized());
    }
    void mouseReleaseEvent(QMouseEvent *event)
    {

        foreach (QLabel *seatLabel, seatList)
        {
            if ( rubberBand->geometry().intersects( seatLabel->geometry() ) )
            {
                if ( seatLabel->property( "Available" ).toBool() )
                {
                    if ( seatLabel->property( "toggle" ) == 'a' )
                    {   // тут выбор-захват места
                        seatLabel->setStyleSheet("background: #" + seatLabel->property( "PriceColor" ).toString() + "; "
                                                                                                                    "border: 5px solid black;"
                                                                                                                    "border-radius: 3px;"
                                                                                                                    "color: black;"
                                                 );
                        seatLabel->setProperty("toggle", 't');
                        if ( !catchList.contains(seatLabel) )
                            catchList.append(seatLabel);
                 //       emit catchSeat(seatLabel->property("IdSeat").toString());

                    }
                    else
                    {
                        seatLabel->setStyleSheet("background:#" + seatLabel->property( "PriceColor" ).toString() + "; border: 2px solid black;"
                                                                                                                   "border-radius: 3px;"
                                                                                                                   "color: black;"
                                                 );
                        seatLabel->setProperty("toggle", 'a');
                        if ( catchList.contains(seatLabel) )
                            catchList.removeAll(seatLabel);
                    }
                }


            }
        }

        CatchSeatWithPrice();
        // determine selection, for example using QRect::intersects()
        // and QRect::contains().
        rubberBand->hide();
    }
    QLabel* createSeatMarker( QString Number )
    {
        QLabel *l = new QLabel(this);
        l->setText( Number);
        l->setFrameStyle(3);
        l->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        l->setMaximumSize( 100, 100);
        return l;
    }
    void seatCreate(int row, int col, bool visible, bool Available, QString Number, QString Row, QString UID, QString price_color)
    {

        if ( visible )
        {
            if ( seatLayot.itemAtPosition(row, 0) == nullptr )
            {
                QLabel *l = createSeatMarker( Row );
                l->setStyleSheet(//"margin-left: 10px;
                                 "border-radius: 3px; background: #ffffff; border: 2px solid black; color: black;" );
                seatLayot.addWidget( l, row, 0 );
                QSpacerItem *vS = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
                seatLayot.addItem( vS, row, col + 1 );
            }

            if ( price_color.isEmpty() )
                price_color = "000000";
            QLabel *l = createSeatMarker(Number);
            l->setProperty("toggle", 'a');
            l->setProperty("Available", Available);
//            l->setProperty("Number", Number);
//            l->setProperty("Row", Row);
            l->setProperty("UID", UID);
            l->setProperty("PriceColor", price_color);
            if( Available )
                l->setStyleSheet(//"margin-left: 10px;
                                 "border-radius: 3px; background: #" + price_color +"; border: 2px solid black;"
                                 //"color: black;"
                                 );
            else
                l->setStyleSheet(//"margin-left: 10px;
                                 "border-radius: 3px; background: #888888; "
                                 "border: 2px solid #" + price_color +";"
                                                                      "color: #dddddd;"
                                 );
            seatLayot.addWidget( l, row, col + 2 );
            seatList.append( l );
        }
        else{ //l->setVisible( false );

            QSpacerItem *vS = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
            seatLayot.addItem( vS, row, col + 2 );
        }

    }

    QElapsedTimer t;
    QPoint origin;
    QRubberBand *rubberBand;
    QGridLayout seatLayot;
    int rowCount = 0;
    QList<QPushButton*> sectorButtonList{};
    QList<QLabel*> seatList{};          //общий список мест
    QList<QLabel*> catchList{};            //список захваченных мест

    QGridLayout main_gridLayout;
    QGroupBox SaleBox;
    QGroupBox legendBox;
    QGridLayout legendBoxLayout;
QTabWidget tabWidget;
    QHBoxLayout sectorListLayout;
    QGroupBox sectorListBox;
signals:
    void sectorSelected(QString sectorUID);
    void catchSeat(QString seatUID);
    void log(QString);
};

#endif // VIEWWIDGET_H

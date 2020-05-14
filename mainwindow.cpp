#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLibrary>
#include <QMessageBox>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QAction *eventSelectAction = new QAction (tr("Выбор мероприятия"), this);
    QAction *saleAction = new QAction (tr("Продажа"), this);
    QAction *reportAction = new QAction (tr("Отчеты"), this);
    QAction *settingsAction = new QAction (tr("Настройка"), this);

    ui->menuBar->addAction(eventSelectAction);
    ui->menuBar->addAction(saleAction);
    ui->menuBar->addAction(reportAction);
    ui->menuBar->addAction(settingsAction);
    connect(eventSelectAction, SIGNAL(triggered()), SLOT(eventSelectTrigger()));
    connect(saleAction, SIGNAL(triggered()), SLOT(saleTrigger()));
    connect(reportAction, SIGNAL(triggered()), SLOT(reportTrigger()));
    connect(settingsAction, SIGNAL(triggered()), SLOT(settingsTrigger()));

    statusLabel.setText("         тут будет статус соединения и поллинга                      ");
    ui->statusBar->addWidget( &statusLabel );
//    ui->SaleBox->setVisible(false);
  //  ui->SaleBox->layout() ->addWidget( &view, 1, 1 );

//reinterpret_cast<QGridLayout*>( centralWidget()->layout() )->addWidget(&view , 1 , 1 );









   // ui->gridLayout_2->addWidget(proxy., 0,1  );
    ui->gridLayout_2->addWidget(&view, 0,1  );


    connect(&view, SIGNAL(sectorSelected(QString )), SLOT(sectorSelected(QString)));
connect(&view, SIGNAL(log(QString )), SLOT(logger(QString)));

    qDebug() << QSslSocket::sslLibraryBuildVersionString();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::logger(QString s)
{
    ui->textBrowser->append(s);
}
void MainWindow::eventSelectTrigger()
{


    evSEL = new eventSelector(this, EventList);
connect(evSEL, SIGNAL(eventID(QString)), SLOT(EventSelected(QString)));
            if (evSEL->exec() == QDialog::Accepted) {
//                QMessageBox::information(0,
//                                         "Information",
//                                         "First Name: "
//                                         + pInputDialog->firstName()
//                                         + "\nLast Name: "
//                                         + pInputDialog->lastName()
//                                        );
            }
            delete evSEL;




//evSEL->show();
   //emit EventSelected();
}
void MainWindow::saleTrigger()
{

    //ui->SaleBox->setVisible(true);
}

void MainWindow::reportTrigger()
{
    //ui->SaleBox->setVisible(true);
}
void MainWindow::settingsTrigger()
{
    //ui->SaleBox->setVisible(true);
}





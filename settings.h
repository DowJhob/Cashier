#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QApplication>
#include <QSettings>
#include <QFile>

class settings : public QObject
{
    Q_OBJECT
public:
    QString server_addr;
    QString port;
    QString  SUID;
    QString idContractor;
    settings()
    {

    }
    bool settings_reader()
    {
        QString path = QCoreApplication::applicationDirPath() + "/settings.ini";
        if( !QFile::exists(path) )
        {
            //       logger("Файл конфигурации не найден, будут использованы значения по умолчанию" );
            return false;
        }
        QSettings settings( path, QSettings::IniFormat );
        //settings.


        settings.beginGroup( "connection" );
        if ( settings.contains("server_addr") && settings.contains("port") && settings.contains("idContractor") && settings.contains("SUID") )
        {
            server_addr = settings.value( "server_addr" ).toString();
            port = settings.value( "port" ).toString();
            SUID = settings.value( "SUID" ).toString();
            idContractor  = settings.value( "idContractor" ).toString();
            settings.endGroup();

            return true;
        }
        return false;
    }
};

#endif // SETTINGS_H

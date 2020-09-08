#ifndef CONNECTION_H
#define CONNECTION_H
#pragma once
#include <QtNetwork/QtNetwork>
#include <util.hpp>
#if __cplusplus >= 201703L
    #define throw(...)
    #include <cppconn/exception.h>
    #undef throw /* reset */
#endif
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
namespace ouroboros{
    class Connection : public Util{
        Q_OBJECT
            QNetworkAccessManager* manager = nullptr ;
            QString key;
            QByteArray response;
    signals:
            void connectionEstablishedSignal();
    public:
        explicit Connection(QWidget *parent = nullptr) : Util(parent){}
        ~Connection() override{ delete manager; }
        bool checkKey(){ return response.toInt(); }
        void setKey(QString key){  this->key = key; }
        void connectServer(){
            manager = new QNetworkAccessManager(this);
            manager->get(QNetworkRequest(QUrl(url+key)));
            connect(manager,SIGNAL(finished(QNetworkReply*)),SLOT(result(QNetworkReply*)));
        }
        void wait() override{
            QEventLoop loop;
            connect(this,SIGNAL(connectionEstablishedSignal()),&loop,SLOT(quit()));
            loop.exec();
        }
        QString getResponse(){ return response;  }
        private slots:
            void closeErrorDialog() override{ error_dialog->close();     }
            void result(QNetworkReply* reply){
                response = QByteArray(reply->readAll());
                reply->deleteLater();
                emit connectionEstablishedSignal();
            }
    };

    class MysqlConnect : private IMysqlConnect{
        sql::Driver *driver;
        std::string error;
        sql::Connection *conn;
    public:
        sql::Connection* connection() {return this->conn;}
        bool connect() override {
            try {
                  driver = get_driver_instance();
                  this->conn = driver->connect(hostname, username, password);
                  this->conn->setSchema(db_name);
                  return true;
            }catch (sql::SQLException &e) { qDebug() << e.what(); return false;}
         }
        void closeConnection() override {
            delete conn;
        }
    };
}
#endif // CONNECTION_H

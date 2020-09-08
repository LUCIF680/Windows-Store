#pragma once
#ifndef UPDATEAPP_H
#define UPDATEAPP_H
#include "./ui_gui.h"
#include <QMainWindow>
#include <util.h> // also include mysql header
#include <QtCore>
#include <QtNetwork/QtNetwork>
#include <string>
#include <cstdio>
namespace Ui {
class UpdateApp;
}
    class UpdateApp : public QMainWindow{
        Q_OBJECT
        Ui::UpdateApp* ui;
        QNetworkAccessManager manager;
        QQueue<QUrl> downloadQueue;
        QNetworkReply *currentDownload = nullptr;
        QFile output;
        QTime downloadTime;
        int downloadedCount = 0;
        int totalCount = 0;
        qint64 total_size_remaining,download_size;
        std::string host_name, database_name,user_name,password;
        QList<qint64>integer;
        QList<std::string> qstring;
    signals:
            void finished();
    public:
        UpdateApp(QWidget* parent = nullptr) : QMainWindow(parent),ui(new Ui::UpdateApp) {
                ui->setupUi(this);
                this->setWindowFlags(Qt::CustomizeWindowHint);
                this->setFixedSize(QSize(895, 130));
                this->setStyleSheet("background-color:white");
        }
        void appendUrl(QList<std::string> &urls)    {
                for (std::string &urlAsString : urls){
                    urlAsString = "https://lucif680.github.io/morningstar/"+ urlAsString;
                    appendUrl(QUrl::fromEncoded(QString::fromStdString(urlAsString).toLocal8Bit()));
                }
                if (downloadQueue.isEmpty())
                    QTimer::singleShot(0, this, SIGNAL(finished()));
            }
        void appendUrl(const QUrl &url)    {
                if (downloadQueue.isEmpty())
                    QTimer::singleShot(0, this, SLOT(startNextDownload()));
                downloadQueue.enqueue(url);
                ++totalCount;
            }
        QString saveFileName(const QUrl &url) {
                QString path = url.path();
                QString basename = QFileInfo(path).fileName();
                if (basename.isEmpty())
                    basename = "download";
                return basename;
        }
        void setDownloadSize(qint64 total_download_size){
            total_size_remaining = total_download_size;
            download_size = total_download_size;
        }
        void setDatabase(std::string host_name,std::string database_name,std::string user_name,std::string password){
            this->host_name = host_name;
            this->database_name = database_name;
            this->user_name = user_name;
            this->password = password;
        }
        QList<std::string> fetchString(std::string query){
                    try {
                        sql::ResultSet* res;
                        sql::Statement* stmt;
                        sql::Driver* driver;
                        sql::Connection* con;
                        driver = get_driver_instance();
                        con = driver->connect(host_name, user_name, password);
                        con->setSchema(database_name);
                        stmt = con->createStatement();
                        res = stmt->executeQuery(query);
                        for (size_t i= 0;res->next();i++)
                           qstring.push_back(res->getString(1));
                        delete res;
                        delete stmt;
                        delete con;
                        return qstring;
                    }
                    catch (sql::SQLException& e) {
                        std::cout << "# ERR: SQLException in " << __FILE__;
                        std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
                        std::cout << "# ERR: " << e.what();
                        std::cout << " (MySQL error code: " << e.getErrorCode();
                        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
                        return {};
                    }
        }
        QList<qint64> fetchInt(std::string query){
                    try {
                        sql::ResultSet* res;
                        sql::Statement* stmt;
                        sql::Driver* driver;
                        sql::Connection* con;
                        driver = get_driver_instance();
                        con = driver->connect(host_name, user_name, password);
                        con->setSchema(database_name);
                        stmt = con->createStatement();
                        res = stmt->executeQuery(query);
                        for (size_t i= 0;res->next();i++)
                           integer.push_back(res->getInt64(1));
                        delete res;
                        delete stmt;
                        delete con;
                        return integer;
                    }
                    catch (sql::SQLException& e) {
                        std::cout << "# ERR: SQLException in " << __FILE__;
                        std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
                        std::cout << "# ERR: " << e.what();
                        std::cout << " (MySQL error code: " << e.getErrorCode();
                        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
                        return {};
                    }

                }
        ~UpdateApp(){
            delete ui;
            delete currentDownload;
        }
    public slots:
        void setGuiRemainingSize(qint64 size,qint64 useless_var){
            total_size_remaining -= size;
            ui->update_size->setText("Remaining Size : " +easycpp::Model::sizeConvertorWithString(total_size_remaining));
        }
    private slots:
        void setGuiPercentage(qint64 useless_var,qint64 percentage){
            percentage = easycpp::Model::sizeConvertor(((download_size - total_size_remaining) * 100) / download_size);
            ui->progressBar->setValue(percentage);
        }
        void startNextDownload(){
            if (downloadQueue.isEmpty()) {
                printf("%d/%d files downloaded successfully\n", downloadedCount, totalCount);
                emit finished();
                return;
            }
            QUrl url = downloadQueue.dequeue();
            QString filename = saveFileName(url);
            output.setFileName(filename);
            if (!output.open(QIODevice::WriteOnly)) {
                fprintf(stderr, "Problem opening save file '%s' for download '%s': %s\n",
                        qPrintable(filename), url.toEncoded().constData(),
                        qPrintable(output.errorString()));
                startNextDownload();
                return;                 // skip this download
            }
            QNetworkRequest request(url);
            currentDownload = manager.get(request);
            connect(currentDownload, SIGNAL(downloadProgress(qint64,qint64)),SLOT(setGuiRemainingSize(qint64,qint64)));
            connect(currentDownload, SIGNAL(downloadProgress(qint64,qint64)),SLOT(setGuiPercentage(qint64,qint64)));
            connect(currentDownload, SIGNAL(finished()),SLOT(downloadFinished()));
            connect(currentDownload, SIGNAL(readyRead()),SLOT(downloadReadyRead()));
            // prepare the output
            printf("Downloading %s...\n", url.toEncoded().constData());
            downloadTime.start();
        }
        void downloadReadyRead(){
            output.write(currentDownload->readAll());
        }
        void downloadFinished(){
            //progressBar.clear();
            output.close();

            if (currentDownload->error()) {
                // download failed
                fprintf(stderr, "Failed: %s\n", qPrintable(currentDownload->errorString()));
                output.remove();
            } else {
                // let's check if it was actually a redirect

                    printf("Succeeded.\n");
                    ++downloadedCount;
            }

            currentDownload->deleteLater();
            startNextDownload();
        }
    };

#endif // UpdateApp_H

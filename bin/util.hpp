#ifndef UTIL_H
#define UTIL_H
#pragma once
#include <QMainWindow>
#include "./ui_dialog.h"
namespace ouroboros {
    class IMysqlConnect{
    protected:
        std::string hostname = "db4free.net";
        std::string db_name = "ouroboros";
        std::string username = "lucifer680";
        std::string password = "lucifer123" ;
        virtual ~IMysqlConnect(){}
        virtual bool connect() = 0;
        virtual void closeConnection() = 0;
    };
    class Util : public QMainWindow{
    protected:
        QString url;
        QWidget *error_dialog;
        Ui::Dialog* ui_error_dialog;
        QRect screenSize;
    public:
        Util(QWidget *parent = nullptr) : QMainWindow(parent),ui_error_dialog(new Ui::Dialog){}
        virtual void wait() = 0;
        virtual void setScreenSize(QRect availableGeometry) { this->screenSize = availableGeometry; }
        virtual void setUrl(QString url){this->url = url;}
        virtual void setDialog(int error_code){
            QString error_text;
            switch(error_code){
                case 100:
                    error_text = "Please enter both fields.";
                    break;
                case 101:
                    error_text = "Password length must be greater than 8 charecters.";
                    break;
                case 102:
                    error_text = "Mobile number must be 10 digits.";
                    break;
                case 103:
                    error_text = "Wrong credentials! Try Again";
                    break;
                case 104:
                    error_text = "Opps! Looks like their is a error. Your amount will be refunded in 3-5 days.";
                    break;
                default:
                     error_text = "Unknown Error Occured.";
            }
            this->setDialog(error_text);
        }
        virtual void setDialog(QString error_text){
            error_dialog = new QWidget;
            ui_error_dialog->setupUi(error_dialog);
            error_dialog->resize(screenSize.width()/2,screenSize.height()/6);
            ui_error_dialog->error_text->setText(error_text);
            error_dialog->show();
            connect(ui_error_dialog->close_btn,SIGNAL(clicked()),SLOT(closeErrorDialog()));
        }
        virtual ~Util(){
            delete  error_dialog;
            delete ui_error_dialog;
        }
    public slots:
        virtual void closeErrorDialog() = 0;
    };
}

#endif // UTIL_H

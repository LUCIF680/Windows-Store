#ifndef APPLICATION_H
#define APPLICATION_H
#pragma once
#include <./ui_login.h>
#include <./ui_home_page.h>
#include <connection.hpp>
#include <util.hpp>
#include <QIntValidator>
#include <cppconn/prepared_statement.h>
#include <session.hpp>
#include <bcrypt/BCrypt.hpp>
/*Sracper are considerd to the page/fragment/widget*/
namespace Ui { class Application;}
namespace ouroboros {
    class Application : public Util {
        Q_OBJECT
        struct Login{
            Ui::Login *ui;
            QWidget* Sracper;
        }LoginSracper;
        struct MainMenu{
            QWidget* Sracper;
            Ui::MainMenu *ui;
            QGridLayout* grid;
            QVector<QLabel*> cards;
        }MainSracper;
        size_t user_id;
        int total_cards = 0;
    signals:
        void loggedIn();
    public:
        void wait() override{
            QEventLoop loop;
            connect(this,SIGNAL(loggedIn()),&loop,SLOT(quit()));
            loop.exec();
        }
        void closeMainSracper(){   QMainWindow::showFullScreen(); MainSracper.Sracper->close();   }
        void showLoginSracper(){   QMainWindow::showFullScreen(); LoginSracper.Sracper->show();   }
        void showMainSracper(){   QMainWindow::showFullScreen(); MainSracper.Sracper->show();   }
        void closeLoginSracper(){   QMainWindow::showFullScreen(); LoginSracper.Sracper->close();   }
        void setMainSracper(){
            MainSracper.Sracper = new QWidget;
            this->setCentralWidget(MainSracper.Sracper);
            MainSracper.ui->setupUi(MainSracper.Sracper);
            MainSracper.grid = new QGridLayout(MainSracper.Sracper);
            while (total_cards < 5){
                MainSracper.cards.append(new QLabel);
                MainSracper.cards.at(total_cards)->setText(QString::number(total_cards));
                total_cards++;
                MainSracper.grid->addWidget(MainSracper.cards.back());
            }
        }
        void setLoginSracper(){
            LoginSracper.Sracper = new QWidget;
            this->setCentralWidget(LoginSracper.Sracper);
            LoginSracper.ui->setupUi(LoginSracper.Sracper);
            LoginSracper.ui->mob_number->setValidator(new QIntValidator(0,1000000000,this));
        }
        void verifyLoginInfo(MysqlConnect conn){
            connect(LoginSracper.ui->login_btn,&QPushButton::clicked,this,[this,conn]{verifyLoginInfoPrivate(conn);});
        }
        explicit Application(QWidget *parent = nullptr) : Util(parent){
             MainSracper.ui = new Ui::MainMenu ;
             LoginSracper.ui = new Ui::Login;
             this->setWindowFlags(Qt::CustomizeWindowHint);
         }
         ~Application() override{
             delete MainSracper.ui;
             delete MainSracper.grid;
             delete MainSracper.Sracper;
             delete LoginSracper.Sracper;
             delete LoginSracper.ui;
         }
    private slots:
        void verifyLoginInfoPrivate(MysqlConnect conn){
            QString password = LoginSracper.ui->password->text();
            QString mob_number = LoginSracper.ui->mob_number->text();
            if (password.isEmpty()|| mob_number.isEmpty())
                Util::setDialog(100);
            else if (password.length() < 9)
                Util::setDialog(101);
            else if (mob_number.length() != 10)
                Util::setDialog(102);
            else{
                sql::PreparedStatement* statement;
                try{
                    statement = conn.connection()->prepareStatement("SELECT * FROM user WHERE mob_number = ?");
                    statement->setInt64(1,mob_number.toLong());
                    Session::user = statement->executeQuery();
                    delete statement;
                    if (Session::user->rowsCount() == 0)
                        Util::setDialog(103);
                    else{
                        Session::user->next();
                        std::string pws_salt = password.toStdString() + Session::user->getString("salt");
                        if (BCrypt::validatePassword(pws_salt,Session::user->getString("password"))){
                            Application::setMainSracper();
                            Application::closeLoginSracper();
                            Application::showMainSracper();
                            emit loggedIn();
                        }else
                            Util::setDialog(103);
                    }
                }catch(sql::SQLException &error){ qDebug() << error.what();}
            }
        }
        void closeErrorDialog() override{ error_dialog->close();     }
    };
}
#endif // OUROBOROS_H

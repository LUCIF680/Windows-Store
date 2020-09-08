#include <QApplication>
#include <application.hpp>
#include <videoplayer.hpp>
#include <aes.hpp>

using namespace ouroboros;
using namespace easycpp;
sql::ResultSet* Session::user;
int main(int argc, char *argv[]){

    //system("./updater");
    QApplication app(argc, argv);
    std::unique_ptr<Connection>conn (new Connection);
    std::unique_ptr<Application> application(new Application);

    // Get screen resolution
    const QRect availableGeometry = QApplication::desktop()->availableGeometry(application.get());
    application->setScreenSize(availableGeometry);

    // Change mysql details in util.h
    MysqlConnect mysql; // Allocating mysql to heap might cause error
    mysql.connect();
    application->setLoginSracper();
    application->showLoginSracper();
    application->verifyLoginInfo(mysql);
    application->wait(); // wait for user to log in
    /*
    AES256 *crypto = new AES256(AES256::uRandom(32),AES256::uRandom(16));
    QString  encryption = QString::fromStdString(crypto->encrypt("hi there"));
    delete crypto;
    conn->setUrl("http://127.0.0.1:5000/encryption/"); // set url for checking user key
    conn->setKey(encryption);
    conn->connectServer();
    conn->wait(); // Waiting for connection to be established
    if (conn->checkKey()){
        VideoPlayer player;
        player.setUrl("http://lsasocalhost/a.mp4");
        player.playVideo();
        player.wait();
        //application->setCard();

        return app.exec();
    }*/
    return 0;
}

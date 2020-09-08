#include <QtWidgets/QApplication>
#include <updateapp.h>
int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    UpdateApp manager;
    manager.setDatabase("db4free.net","ouroboros","lucifer680","lucifer123");
    QList<std::string> qstring_response = manager.fetchString("select files from push_update");
    QList<qint64> int_response= manager.fetchInt("select size from push_update");
    if (int_response.at(0)){
        manager.setGuiRemainingSize(int_response.at(1),0);
        manager.setDownloadSize(int_response.at(1));
        qstring_response.pop_front();
        qstring_response.pop_front();
        manager.appendUrl(qstring_response);
        manager.show();
        return a.exec();
    }
    return 0;
}

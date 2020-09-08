#ifndef UTIL_H
#define UTIL_H
#include<QString>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
namespace easycpp {
    class Model{
    public:
       static qint64 sizeConvertor(qint64 size){
            if(size < 1024)
                return size;
            else if (size < 1048576)
                return size/1024;
            else if (size < 1073741824)
                return size/1048576;
            else
                return size/1073741824;
        }
       static QString sizeConvertorWithString(qint64 size){
            if(size < 1024)
                return QString::number(size)+" Bytes";
            else if (size < 1048576){
                size = size / 1024;
                return QString::number(size)+" KB";
            }
            else if (size < 1073741824){
                size = size / 1048576;
                return QString::number(size)+" MB";
            }
            else{
                size = size / 1073741824;
                return QString::number(size)+" GB";
            }
        }
    };
}
#endif // MODEL_H

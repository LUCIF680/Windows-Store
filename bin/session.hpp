#ifndef SESSION_H
#define SESSION_H
#pragma once
#include<cppconn/resultset.h>
class Session  {
public:
    static sql::ResultSet* user;
    ~Session(){
        delete user;
    }
};

#endif // SESSION_H

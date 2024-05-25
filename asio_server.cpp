#include "Networker.h"
#include "DataBaseWorker.h"
#include <cstdio>
#include <boost/asio/io_context.hpp>
#include <iostream>
//#include <process.h>
int main() 
{
    //TODO: Добавить отправку текстового сообщения с ошибкой или сообщения ок 
    boost::asio::io_context context; 
    Networker net(context,1337,"127.0.0.1");
    DataBaseWorker dbw;
    net.sig.connect(dbw);
    net.start_server();
    dbw.start_db();
    context.run();
}

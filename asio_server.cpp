#include "Networker.h"
#include "DataBaseWorker.h"
#include <cstdio>
#include <boost/asio/io_context.hpp>
//#include <process.h>
int main() 
{
    boost::asio::io_context context; 
    Networker net(context,1337,"127.0.0.1");
    DataBaseWorker dbw;
    net.sig.connect(dbw);
    net.start_server();
    dbw.start_db();
    context.run();
    //  net.sig("INSERT A 1 l");
    //  net.sig("INSERT B 2 sweet");
    // net.sig("INSERT B 1 lean");
    // net.sig("INSERTB 3 SWTT");
    
}

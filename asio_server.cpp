#include "Networker.h"
#include "DataBaseWorker.h"
#include <process.h>
int main() 
{
    Networker net(1500);
    DataBaseWorker dbw;
    net.sig.connect(dbw);
    dbw.start_db();
    net.sig("A 0 lean");
    net.sig("A 1 sweet");
    net.sig("B 0 lean");
    net.sig("B 1 SWTT");
    system("pause");
}

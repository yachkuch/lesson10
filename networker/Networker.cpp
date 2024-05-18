#include "Networker.h"

Networker::Networker(unsigned int port)
{
}

void Networker::sendData(std::string data)
{
    sig(data);
}

Networker::~Networker()
{
}
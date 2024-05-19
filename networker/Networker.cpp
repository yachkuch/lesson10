#include "Networker.h"
#include <boost/asio/buffer.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/address_v4.hpp>
#include <boost/system/detail/error_code.hpp>
#include <iostream>
Networker::Networker(unsigned int port, std::string ip_adress)
{
    this->port_ = port;
    this->ip_ = ip_adress;   
}

void Networker::start_server()
{
    namespace asio = boost::asio;
    asio::io_context context;
    asio::ip::tcp::endpoint endpoint(asio::ip::address::from_string(ip_),port_);
    asio::ip::tcp::acceptor acceptor{
      context,
      endpoint};
    std::shared_ptr<asio::ip::tcp::socket> pSocket(new asio::ip::tcp::socket(context));  
    acceptor.async_accept(*pSocket,std::bind(&Networker::handleAccept,this,pSocket));   
}

void Networker::sendData(std::string data)
{
    sig(data);
}

void Networker::handleAccept(std::shared_ptr<boost::asio::ip::tcp::socket> socket)
{
    std::cout<<"New connection"<<std::endl;
}

Networker::~Networker()
{
}
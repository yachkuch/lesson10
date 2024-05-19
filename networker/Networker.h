#ifndef __NETWORKER_H_6RM5NKCO09GG__
#define __NETWORKER_H_6RM5NKCO09GG__
#include <functional>
#include <string>
#include <boost/signals2.hpp>
#include <memory>
#include <boost/asio/ip/tcp.hpp>
///////////////////////////////////////////////////////////
/// @brief Networker класс сервера
///
class Networker final
{
public:
    explicit Networker(unsigned int port, std::string ip_adress = "");
    virtual ~Networker(); 
    Networker(const Networker &other) = delete;
    Networker(Networker &&other) = delete;
    Networker &operator=(const Networker &other) = delete;
    Networker &operator=(Networker &&other) = delete;

    void start_server();

    boost::signals2::signal<void(std::string string)> sig;
private:

    void sendData(std::string data);
    void handleAccept(std::shared_ptr<boost::asio::ip::tcp::socket> socket);
    unsigned int port_ = 0;
    std::string ip_ = "127.0.0.1";    
};

#endif  // __NETWORKER_H_6RM5NKCO09GG__

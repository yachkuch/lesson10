#ifndef __NETWORKER_H_6RM5NKCO09GG__
#define __NETWORKER_H_6RM5NKCO09GG__
#include <functional>
#include <string>
#include <boost/signals2.hpp>
///////////////////////////////////////////////////////////
/// @brief Networker
///
class Networker final
{
public:
    Networker(unsigned int port);
    virtual ~Networker(); 
    Networker(const Networker &other) = delete;
    Networker(Networker &&other) = delete;
    Networker &operator=(const Networker &other) = delete;
    Networker &operator=(Networker &&other) = delete;

    boost::signals2::signal<void(std::string string)> sig;
private:

    void sendData(std::string data);    
};

#endif  // __NETWORKER_H_6RM5NKCO09GG__

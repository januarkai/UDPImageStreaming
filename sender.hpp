#ifndef SENDER_HPP
#define SENDER_HPP

#include "udp.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>

namespace FIXIO {
    class DataPublisher : public UDPSocket {
    public:
        DataPublisher(std::string serv_address, unsigned short serv_port);
        bool publishStringData();
    };
}

#endif
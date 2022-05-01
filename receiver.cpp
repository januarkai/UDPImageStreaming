#include "udp.hpp"
#include <iostream>
#include <cstdlib>

#include <opencv2/opencv.hpp>
#include "config.hpp"

#define BUF_LEN 65540;

int main() {
    unsigned short serv_port = 8080;
    cv::namedWindow("Received", cv::WINDOW_AUTOSIZE);
    try
    {
        UDPSocket sock(serv_port);
        int is_received;
        std::string source_address;
        unsigned short source_port;
        char buffer[65540];

        while(1) {
            do{
                is_received = sock.recvFrom(buffer, 65540, source_address, source_port);
            }while(is_received > sizeof(int));
            int total_pack = ((int*)buffer)[0];

            char* longbuf = new char[PACK_SIZE*total_pack];
            for(int i = 0; i < total_pack; i++) {
                is_received = sock.recvFrom(buffer, 65540, source_address, source_port);
                if(is_received != PACK_SIZE) {
                    std::cout << "Packets are not complete: " << is_received << std::endl;
                    continue;
                }
                memcpy(&longbuf[i*PACK_SIZE], buffer, PACK_SIZE);
            }

            cv::Mat image_raw = cv::Mat(1, PACK_SIZE*total_pack, CV_8UC1, longbuf);
            cv::Mat image = cv::imdecode(image_raw, cv::IMREAD_COLOR);
            if(image.empty()) {
                std::cout << "Decode failure!" << std::endl;
                continue;
            }
            cv::imshow("Received", image);
            free(longbuf);
            if(cv::waitKey(FRAME_INTERVAL) == 27) {
                break;
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        exit(1);
    }
    return 0;
    
}
#include "udp.hpp"
#include "config.hpp"
#include <iostream>
#include <cstdlib>

#include <opencv2/opencv.hpp>

int main() {
    std::string serv_address = "192.168.10.255";
    unsigned short serv_port = Socket::resolveService("8080", "udp");

    try
    {
        UDPSocket sock;
        int jpeg_quality = ENCODE_QUALITY;

        cv::Mat image, image_sent;
        std::vector<unsigned char> encoded;

        cv::VideoCapture cam(0);
        cam.set(cv::CAP_PROP_FRAME_WIDTH, 640);
        cam.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
        cv::namedWindow("ImageSent", cv::WINDOW_AUTOSIZE);
        while(1) {
            cam >> image;
            if(image.empty())
                continue;
            std::vector<int> compression_params;
            compression_params.push_back(cv::IMWRITE_JPEG_QUALITY);
            compression_params.push_back(jpeg_quality);

            cv::imencode(".jpg", image, encoded, compression_params);
            cv::imshow("ImageSent", image);
            int total_pack = 1 + (encoded.size() - 1) / PACK_SIZE;

            int ibuf[1];
            ibuf[0] = total_pack;
            sock.sendTo(ibuf, sizeof(int), serv_address, serv_port);
            for(int i = 0; i < total_pack; i++)
                sock.sendTo(&encoded[i*PACK_SIZE], PACK_SIZE, serv_address, serv_port);
            if(cv::waitKey(FRAME_INTERVAL) == 27)
                break;
        }

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        exit(1);
    }
    return 0;
    
}

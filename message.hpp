#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <array>
#include <vector>

enum MESSAGETYPE {
    INT=0,
    STRING=1,
    IMAGE=2,
    POINTCLOUD=3
};

class ImageData {
public:
    ImageData();
    std::array<char, 4> header;
    std::vector<unsigned char> data;
    void inputData(std::array<char, 4> header, std::vector<unsigned char> data);
};


#endif
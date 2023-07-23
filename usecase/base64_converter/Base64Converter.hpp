#pragma once

#include "opencv2/opencv.hpp"
#include "base64.h"
#include <iostream>
#include <string>
#include <vector>
#include "IBase64Converter.hpp"

class Base64Converter : public IBase64Converter
{
private:
    std::vector<u_char> buf_;

public:
    Base64Converter();
    ~Base64Converter(){};

    std::string Encode(const cv::Mat &image) override;
    cv::Mat Decode(const std::string &data) override;
};
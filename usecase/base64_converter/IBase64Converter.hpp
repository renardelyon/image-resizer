#pragma once

#include "opencv2/opencv.hpp"

class IBase64Converter
{
public:
    virtual std::string Encode(const cv::Mat &image) = 0;
    virtual cv::Mat Decode(const std::string &data) = 0;
};
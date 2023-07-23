#pragma once

#include "opencv2/opencv.hpp"
#include "../base64_converter/IBase64Converter.hpp"
#include "ResizeImage.hpp"

class ResizeImage
{
private:
    std::shared_ptr<IBase64Converter> base64Converter_;
    std::string base64String_;
    cv::Mat resizedImage_;

public:
    ResizeImage(
        std::string &base64String,
        std::shared_ptr<IBase64Converter> base64Converter)
        : base64Converter_(std::move(base64Converter)),
          base64String_(base64String){};
    ~ResizeImage(){};

    ResizeImage& operator()(double width, double height);
    cv::Mat GetResizedImage();
    std::string GetEncodedImage();
};

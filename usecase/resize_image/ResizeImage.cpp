#include "ResizeImage.hpp"

ResizeImage& ResizeImage::operator()(double width, double height)
{
    auto decodedImage = base64Converter_->Decode(base64String_);
    cv::resize(decodedImage, resizedImage_, cv::Size(width, height), cv::INTER_LINEAR);
    return *this;
}

cv::Mat ResizeImage::GetResizedImage()
{
    return resizedImage_;
}

std::string ResizeImage::GetEncodedImage()
{
    return std::move(base64Converter_->Encode(resizedImage_));
}
#include "Base64Converter.hpp"

Base64Converter::Base64Converter()
{
}

std::string Base64Converter::Encode(const cv::Mat &image)
{
    cv::imencode(".jpg", image, buf_);
    auto *enc_msg = reinterpret_cast<unsigned char *>(buf_.data());
    std::string encoded = base64_encode(enc_msg, buf_.size());

    return encoded;
}

cv::Mat Base64Converter::Decode(const std::string &encoded)
{
    std::string dec_jpg = base64_decode(encoded);
    std::vector<uchar> data(dec_jpg.begin(), dec_jpg.end());
    cv::Mat img = cv::imdecode(cv::Mat(data), 1);

    return img;
}
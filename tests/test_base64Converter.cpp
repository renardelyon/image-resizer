#include <gtest/gtest.h>
#include "../usecase/base64_converter/Base64Converter.hpp"

TEST(TestBase64Converter, Base64ConverterEncodeImage)
{
    // Load the image from file
    cv::Mat image = cv::imread("example.jpg", cv::IMREAD_COLOR);

    // Check if the image was loaded successfully
    if (image.empty())
    {
        std::cout << "Error: Could not open or read the image.\n";
        ASSERT_FALSE(true);
    }

    Base64Converter base64Converter;

    auto encodedImage = base64Converter.Encode(image);
    ASSERT_GT(encodedImage.length(), 0);
}

TEST(TestBase64Converter, Base64ConverterDecodeImage)
{
    // Load the image from file
    cv::Mat image = cv::imread("example.jpg", cv::IMREAD_COLOR);

    // Check if the image was loaded successfully
    if (image.empty())
    {
        std::cout << "Error: Could not open or read the image.\n";
        ASSERT_FALSE(true);
    }

    Base64Converter base64Converter;

    auto encodedImage = base64Converter.Encode(image);
    auto decodedImage = base64Converter.Decode(encodedImage);
    ASSERT_FALSE(decodedImage.empty());
}
#include <gtest/gtest.h>
#include "../usecase/resize_image/ResizeImage.hpp"
#include "../usecase/base64_converter/Base64Converter.hpp"

TEST(TestResizeImage, TestResizeImageObject)
{
    // Load the image from file
    cv::Mat image = cv::imread("example.jpg", cv::IMREAD_COLOR);

    // Check if the image was loaded successfully
    if (image.empty())
    {
        std::cout << "Error: Could not open or read the image.\n";
        ASSERT_FALSE(true);
    }

    Base64Converter Testbase64Converter;
    std::shared_ptr<IBase64Converter> base64Converter(new Base64Converter);

    auto encodedImage = Testbase64Converter.Encode(image);

    ResizeImage resizeImage(encodedImage, base64Converter);
    resizeImage(200, 200);

    cv::Size resizedImageSize = resizeImage.GetResizedImage().size();
    ASSERT_EQ(resizedImageSize.height, 200);
    ASSERT_EQ(resizedImageSize.width, 200);
}
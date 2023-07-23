#include "libasyik/service.hpp"
#include "libasyik/http.hpp"
#include "json.hpp"
#include "ResizeImage.hpp"
#include "Base64Converter.hpp"
#include "IBase64Converter.hpp"

using json = nlohmann::json;

int main()
{
  auto as = asyik::make_service();
  auto server = asyik::make_http_server(as, "127.0.0.1", 8080);

  // serve http request
  server->on_http_request(
      "/resize_image", "POST", [](auto req, auto args)
      {
    try
    {
      json j;
      json jsonData = json::parse(req->body);
      auto width = (double)jsonData ["desired_width"];
      auto height = (double)jsonData["desired_height"];
      auto inputJpeg = std::string(jsonData["input_jpeg"]);

      std::shared_ptr<IBase64Converter> base64Converter(new Base64Converter);
      ResizeImage resizeImage(inputJpeg, base64Converter);
      resizeImage(width, height);
      auto resizedJpeg = resizeImage.GetEncodedImage();

      j["code"] = 200;
      j["message"] = "success";
      j["output_jpeg"] = resizedJpeg;

      req->response.body = j.dump();
      req->response.result(200);
    } 
    catch (const std::exception& ex) 
    {
      std::string errorMessage = ex.what();

      json j;
      j["code"] = 400;
      j["message"] = errorMessage;

      req->response.body = j.dump();
      req->response.result(400);
    } });

  as->run();
}
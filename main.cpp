#include <vector>
#include <iterator>
#include <string>


#define STB_IMAGE_IMPLEMENTATION
#include "middleware/stb_image/include/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "middleware/stb_image/include/stb_image_write.h"


struct texture 
{
  static unsigned int id;
  std::string path;
  unsigned char* data;
  int width;
  int height;
  int channels; //per Pixel
  std::vector<unsigned char> pixelData;

  texture( int num, std::string type){
    this->path = "textures/" + std::to_string(num) + "/" + type;
    data = stbi_load(this->path.c_str(), &width, &height, &channels, 0);
    pixelData.assign(data, data + ((int64_t)width * (int64_t)height * channels));
    stbi_image_free(data);
  }

  void write_png() {
    path = "output/" + path;
    stbi_write_png(path.c_str(),
      width,
      height,
      channels, //RGB = 3, RGBA = 4
      &pixelData[0], //the pixel data
      //distance in bytes from the first byte of a row of pixels to 
      //the first byte of the next row of pixels
      width * channels);
  }

  ~texture() {

  }
};

int main(int argc, char** argv) {
  std::vector<int> textureCount = { 1,2,3,4,5,6 };
  std::vector<std::string> textureFiles = { "d.png","h.png","m.png","n.png","r.png" };

  std::vector<texture> textureList;

  for (auto&& num : textureCount) {
    for (auto&& item : textureFiles) {
      textureList.push_back(texture(num, item.c_str()));
    }
  }

  for (auto&& item : textureList) {
    item.write_png();
  }
  return 0;
}
# ppm-image
Save and load 24-bit color ppm images.

*Example code below creates an 800x600 solid-green image and saves it. Then it reloads the image and confirms the image hasn't changed.*

```cpp
#include <fstream>
#include "ppm.hpp"

constexpr std::size_t height = 1080, width = 1920; // The image size.
ppm::image<height, width> img; // The image.

int main(){
	// Populate the image with a black-to-white letf-to-right gradient.
	for(std::size_t row = 0; row < height; row++){
		for(std::size_t column = 0; column < width; column++){
			auto v = (ppm::value_type)column / width;
			img[row][column] = {v, v, v};
		}
	}
	
	// Save the image as "linear.ppm"
	std::ofstream output("linear.ppm");
	output << img;
	output.close();
	
	// Convert the color space to sRGB.
	ppm::convert_color_space(img, {ppm::linear_to_srgb});
	
	// Save the image as "srgb.ppm"
	output.open("srgb.ppm");
	output << img;
	output.close();
	
	// Reload the image from "srgb.ppm"
	std::ifstream input("srgb.ppm");
	input >> img;
	input.close();
	
	// Convert the color space back to a linear color space.
	ppm::convert_color_space(img, {ppm::srgb_to_linear});
	
	// Save the image as "linear2.ppm"
	output.open("linear2.ppm");
	output << img;
	output.close();
}
```

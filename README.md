# ppm-image
Save and load 24-bit color ppm images.

*The example code below creates an 800 by 600 image containing a black-to-white gradient. The image is first saved without changing the color space to a file named "linear.ppm", then the color space is converted to sRGB and another copy of the image is saved to "srgb.ppm". The "srgb.ppm" image is then reloaded and reconverted back into linear color space and resaved as "linear2.ppm". Note that "linear2.ppm" is not a perfect copy of "linear.ppm" due to the color space conversion.*

```cpp
#include <fstream>
#include "ppm.hpp"

constexpr std::size_t height = 600, width = 800; // The image size.
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

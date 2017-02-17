# ppm-image
Save and load 24-bit color ppm images.

*Example code below creates an 800x600 solid-green image and saves it. Then it reloads the image and confirms the image hasn't changed.*

```cpp
#include <fstream>
#include "ppm.hpp"

constexpr std::size_t rows = 600, columns = 800; // The image dimensions.
ppm::image<rows, columns> img; // The image.

int main(){
	// Fill the image with a pleasant green color.
	for(std::size_t row = 0; row < rows; row++){
		for(std::size_t column = 0; column < columns; column++){
			img[row][column] = {63, 181, 95};
		}
	}

	// Save the image as "out.ppm"
	std::ofstream output("out.ppm");
	output << img;
	output.close();

	// Reload "out.ppm" and prove it's still the same.
	decltype(img) loaded_img;
	std::ifstream input("out.ppm");
	input >> loaded_img;
	input.close();
	if(loaded_img == img) std::cout << "It's the same." << std::endl;
}
```

#include<iostream>

#include"lodepng.h"
#include"pg_utility.h"

void saveToImage(std::string fileName, const std::vector<unsigned char> &image, int width, int height) {
	
	//Encode the image
	unsigned error = lodepng::encode(fileName, image, width, height);
	//if there's an error, display it
	if (error) std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
}

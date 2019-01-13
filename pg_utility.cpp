#include<iostream>

#include"lodepng.h"
#include"pg_utility.h"
//void encodeOneStep(const char* filename, const unsigned char* image, unsigned width, unsigned height) {
//	/*Encode the image*/
//	unsigned error = lodepng_encode32_file(filename, image, width, height);
//
//	/*if there's an error, display it*/
//	if (error) printf("error %u: %s\n", error, lodepng_error_text(error));
//}
//
//void saveToImage(std::string fileName, const std::vector<unsigned char> &image, int width, int height) {
//	
//	/*generate some image*/
//	unsigned width = 512, height = 512;
//	unsigned char* data = new unsigned char[width * height * 4];
//	unsigned x, y;
//	for (y = 0; y < height; y++)
//		for (x = 0; x < width; x++) {
//
//			data[4 * width * y + 4 * x + 0] = 255 * !(x & y);
//			data[4 * width * y + 4 * x + 1] = x ^ y;
//			data[4 * width * y + 4 * x + 2] = x | y;
//			data[4 * width * y + 4 * x + 3] = 255;
//		}
//
//	/*run an example*/
//	encodeOneStep(fileName.c_str(), data, width, height);
//
//	free(data);
//}

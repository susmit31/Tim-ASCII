#define STB_IMAGE_IMPLEMENTATION
#include "../libs/stb_image.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "../libs/stb_image_resize.h"
#include <cstdio>
#include <cmath>
#include "Img.h"

Image::Image(const char* filename){
	data = stbi_load(filename, &width, &height, &channels, 0);
	if (data != NULL){
		printf("Read %s\n", filename);
		printf("%d X %d X %d\n", width, height, channels);
	} else
		printf("Failed to read %s\n", filename);
}

Image::~Image(){
	stbi_image_free(data);
}

void Image::resize(float scale){
	int new_width = floor(scale*width);
	int new_height = floor(scale*height);
	unsigned char* new_data = (unsigned char*) malloc(new_width*new_height*channels*sizeof(unsigned char));
	printf("Working\n");
	stbir_resize_uint8(data, width, height, 0,
				 new_data, new_width, new_height, 0, channels);
	if (new_data != NULL){
		printf("Resized to %d X %d X %d\n", new_width, new_height, channels);
	} else {
		printf("Error.\n");
	}
	free(new_data);
}

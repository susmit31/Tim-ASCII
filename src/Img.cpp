#define STB_IMAGE_IMPLEMENTATION
#include "../libs/stb_image.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "../libs/stb_image_resize.h"
#include <cstdio>
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
	uint8_t* new_data;
	stbir_resize_uint8(data, width, height, 0,\
				 new_data, scale*width, scale*height, 0, channels);
	if (new_data != NULL){
		data = new_data;
	}
	
}

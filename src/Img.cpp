#define STB_IMAGE_IMPLEMENTATION
#include "../libs/stb_image.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "../libs/stb_image_resize.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../libs/stb_image_write.h"
#include <cstdio>
#include <cmath>
#include <cstring>
#include "Img.h"


Image::Image(const char* filename){
	data = stbi_load(filename, &width, &height, &channels, 0);
	if (data != NULL){
		printf("Read %s\n", filename);
		printf("%d X %d X %d\n", width, height, channels);
	} else
		printf("Failed to read %s\n", filename);
	this->size = width*height*channels;
}

Image::Image(int width, int height, int channels, unsigned char* data){
	this->data = data;
	this->width = width;
	this->height = height;
	this->channels = channels;
	this->size = width*height*channels; 
}

Image::Image(int width, int height, int channels){
	this->width = width;
	this->height = height;
	this->channels = channels;
	this->size = width*height*channels;
	this->data = (unsigned char*) malloc(this->size*sizeof(unsigned char));
}

int Image::get_width(){
	return this->width;
}

int Image::get_height(){
	return this->height;
}

int Image::get_channels(){
	return this->channels;
}

uint8_t* Image::get_data(){
	return this->data;
}

Image::~Image(){
	stbi_image_free(data);
}


bool Image::resize(float scale, Image& output){
	bool success;
	int new_width = floor(scale*width);
	int new_height = floor(scale*height);
	int new_imsize = new_width*new_height*channels;
	unsigned char* new_data;
	new_data = (unsigned char*) malloc(new_imsize*sizeof(unsigned char));
	
	printf("Working\n");
	stbir_resize_uint8(data, width, height, 0,
				 new_data, new_width, new_height, 0, channels);


	success = new_data != NULL;
	if (success){
		printf("Resized to %d X %d X %d\n", new_width, new_height, channels);
		output.data = new_data;
	} else {
		printf("Error.\n");
	}
	//free(new_data);

	return success;
}


bool Image::save(const char* filename){
	bool success;
	const char* extension = strrchr(filename, '.');

	if (extension != NULL){
		if (strcmp(extension, ".png")==0){
			int result = stbi_write_png(filename, width, height, channels, data, 0);
			success = result != 0;
		} else if (strcmp(extension, ".jpg")==0){
			int result = stbi_write_jpg(filename, width, height, channels, data, 0);
			success = result != 0;
		} else {
			success = false;
		}
	}

	return success;	
}

int Image::get_size(){
	return (int) size;
}

void Image::to_array(int* arr[]){	
	if (channels != 4) {
		for (int i=0; i<height*width; i++)
			arr[3][i] = 255;
	}

	for (int i=0; i<(int) size; i++){
		arr[i%3][i/3] = (int) data[i];
	}

}

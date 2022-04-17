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

void Image::to_array_rgba(int* rgba_arr[]){	
	if (channels != 4) {
		for (int i=0; i<height*width; i++)
			rgba_arr[3][i] = 255;
	}

	for (int i=0; i<(int) size; i++){
		rgba_arr[i%channels][i/channels] = (int) data[i];
	}

}

void Image::to_array_gray(float* gray){
	int* red = (int*) malloc(width*height*sizeof(int));
	int* green = (int*) malloc(width*height*sizeof(int));
	int* blue = (int*) malloc(width*height*sizeof(int));
	int* opacity = (int*) malloc(width*height*sizeof(int));
	int* rgba_arr[4] = {red, green, blue, opacity};
	
	to_array_rgba(rgba_arr);
	
	for (int i=0; i<width*height; i++){
		gray[i] = (red[i]*.299 + green[i]*.587 + blue[i]*.114)/255;
	}
}

void Image::normalize_gray(float* gray){
	float maxpixel = arrmax(gray, width*height);
	printf("%f\n", maxpixel);
	for (int i = 0; i < width*height; i++){
		gray[i] /= maxpixel;
	}
}

void Image::to_array_ascii(char* ascii){
	float* gray = (float*) malloc(width*height*sizeof(float));
	to_array_gray(gray);
	normalize_gray(gray);

	for (int i=0; i < width*height; i++){
		if (gray[i] > .9){
			ascii[2*i] = '#';
			ascii[2*i+1] = '#';
		}
		else if (gray[i] > .8){
			ascii[2*i] = '&';
			ascii[2*i+1] = '#';
		}
		else if (gray[i] > .7){
			ascii[2*i] = '&';
			ascii[2*i+1] = '&';
		}
		else if (gray[i] > .6){
			ascii[2*i] = '$';
			ascii[2*i+1] = '-';
		}
		else if (gray[i] > .5){
			ascii[2*i] = '%';
			ascii[2*i+1] = '-';
		}
		else if (gray[i] > .4){
			ascii[2*i] = '*';
			ascii[2*i+1] = '*';
		}
		else if (gray[i] > .3){
			ascii[2*i] = '*';
			ascii[2*i+1] = ' ';
		}
		else if (gray[i] > .2){
			ascii[2*i] = '-';
			ascii[2*i+1] = ' ';
		}
		else{
			ascii[2*i] = ' ';
			ascii[2*i+1] = ' ';
		}
	}
}

float arrmax(float* arr, int len_arr){
	float maxel = arr[0];
	for (int i = 0;  i< len_arr; i++){
		if (arr[i] > maxel)
			maxel = arr[i];
	}
	return maxel;
}

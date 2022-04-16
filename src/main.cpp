#include "Img.h"
#include <cmath>
#include <cstdio>

void display_ascii(char* ascii, int width, int height);

int main(int argc, char* argv[]){
	const char* img_name = argv[1];
	Image img(img_name);
	int w = img.get_width(), h = img.get_height(), c = img.get_channels();
	float scale =  .1;
	Image output(floor(w*scale), floor(h*scale), c);
	img.resize(scale, output);
	printf("%d X %d X %d\n", output.get_width(), output.get_height(), output.get_channels());
	output.save("./resizedu.png");

	int target_width;
	sscanf(argv[2], "%d", &target_width);
	scale = (float) target_width/img.get_width();
	int re_w = floor(w*scale), re_h = floor(h*scale);
	Image output2(re_w, re_h, c);
	img.resize(scale, output2);
	
	int* red = (int*) malloc(sizeof(int)*re_w*re_h);
	int* green = (int*) malloc(sizeof(int)*re_w*re_h);
	int* blue = (int*) malloc(sizeof(int)*re_w*re_h);
	int* opacity = (int*) malloc(sizeof(int)*re_w*re_h);

	int* arr[4] = { red, green, blue, opacity };
	output2.to_array_rgba(arr);
	printf("%d, %d, %d, %d\n", red[0], green[0], blue[0], opacity[0]);
	free(red);
	free(green);
	free(blue);
	free(opacity);

	float* gray = (float*) malloc(sizeof(float)*re_w*re_h);
	output2.to_array_gray(gray);
	printf("%f, %f, %f, %f\n", gray[0], gray[1], gray[2], gray[3]);
	free(gray);

	char* ascii = (char*) malloc(2*re_w*re_h*sizeof(char));
	output2.to_array_ascii(ascii);
	display_ascii(ascii, output2.get_width(), output2.get_height());
	return 0;
}

void display_ascii(char* ascii, int width, int height){
	for (int i = 0; i < 2*width*height; i++){
		printf("%c", ascii[i]);
		if (i % (2*width) == 0 && i != 0) {
			printf("\n");
		}
	}
	printf("\n");
}

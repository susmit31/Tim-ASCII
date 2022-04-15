#include "Img.h"
#include <cmath>
#include <cstdio>

int main(int argc, char* argv[]){
	const char* img_name = argv[1];
	Image img(img_name);
	int w = img.get_width(), h = img.get_height(), c = img.get_channels();
	float scale =  .1;
	Image output(floor(w*scale), floor(h*scale), c);
	img.resize(scale, output);
	printf("%d X %d X %d\n", output.get_width(), output.get_height(), output.get_channels());
	output.save("./resizedu.png");
	
	scale = .01;
	int re_w = floor(w*scale), re_h = floor(h*scale);
	Image output2(re_w, re_h, c);
	img.resize(scale, output2);
	
	int* red = (int*) malloc(sizeof(int)*re_w*re_h);
	int* green = (int*) malloc(sizeof(int)*re_w*re_h);
	int* blue = (int*) malloc(sizeof(int)*re_w*re_h);
	int* opacity = (int*) malloc(sizeof(int)*re_w*re_h);

	int* arr[4] = { red, green, blue, opacity } ;
	printf("Hehehe\n");
	output2.to_array_rgba(arr);
	printf("%d, %d, %d, %d\n", red[0], green[0], blue[0], opacity[0]);

	float* gray = (float*) malloc(sizeof(float)*re_w*re_h);
	output2.to_array_gray(arr, gray);
	printf("%f, %f, %f, %f\n", gray[0], gray[1], gray[2], gray[3]);
	return 0;
}

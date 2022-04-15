#include "Img.h"
#include <cmath>
#include <cstdio>

int main(int argc, char* argv[]){
	const char* img_name = argv[1];
	Image img(img_name);
	float scale = .2;
	Image output(floor(img.get_width()*scale), floor(img.get_height()*scale), floor(img.get_channels()));
	img.resize(scale, output);
	printf("%d X %d X %d\n", output.get_width(), output.get_height(), output.get_channels());
	output.save("resizedu.png");
	return 0;
}

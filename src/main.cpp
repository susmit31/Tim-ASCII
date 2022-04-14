#include "Img.h"

int main(int argc, char* argv[]){
	const char* img_name = argv[1];
	Image img(img_name);
	img.resize(.2);
	return 0;
}

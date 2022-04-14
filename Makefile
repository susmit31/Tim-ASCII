img++: src/* libs/stb_image.h libs/stb_image_write.h libs/stb_image_resize.h
	g++ -o img++ src/* libs/*
libs/stb_image.h:
	wget https://raw.githubusercontent.com/nothings/stb/master/stb_image.h -O libs/stb_image.h
libs/stb_image_write.h:
	wget https://raw.githubusercontent.com/nothings/stb/master/stb_image_write.h -O libs/stb_image_write.h
libs/stb_image_resize.h:
	wget https://raw.githubusercontent.com/nothings/stb/master/stb_image_resize.h -O libs/stb_image_resize.h
		

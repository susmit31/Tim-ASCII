#include <cstdint>

class Image {
	private:
		int width, height, channels;
		uint8_t* data;
		std::size_t size = 0;
	public:
		Image(const char* filename);
		~Image();
};

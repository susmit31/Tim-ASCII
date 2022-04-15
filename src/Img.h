#include <cstdint>

class Image {
	private:
		int width, height, channels;
		uint8_t* data;
		std::size_t size = 0;
	public:
		Image(const char* filename);
		Image(int width, int height, int channels, unsigned char* data);
		Image(int width, int height, int channels);
		int get_size();
		int get_width();
		int get_height();
		int get_channels();
		bool resize(float scale, Image& output);
		uint8_t* get_data();
		bool save(const char* filename);
		~Image();
};


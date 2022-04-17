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
		void to_array_rgba(int* rgba_arr[]);
		void to_array_gray(float* gray);
		void normalize_gray(float* gray);
		void to_array_ascii(char* ascii);
		bool resize(float scale, Image& output);
		uint8_t* get_data();
		bool save(const char* filename);
		~Image();
};

float arrmax(float* arr, int size);

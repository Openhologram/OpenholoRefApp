#include <iostream>

#include "ophPointCloud.h"

using namespace std;

int main(void)
{
	ophPointCloud* Hologram = new ophPointCloud();

	Hologram->loadComplex("teapot_real_1920,1080.txt", "teapot_imag_1920,1080.txt", 1920, 1080);

	Hologram->encoding(ophGen::ENCODE_TWOPHASE);
	//Hologram->encoding(Hologram->ENCODE_SSB, Hologram->SSB_LEFT);

	Hologram->normalizeEncoded();

	ivec2 encode_size = Hologram->getEncodeSize();

	Hologram->save("result/Encoding_TWOPHASE.bmp",8,nullptr,encode_size[_X], encode_size[_Y]);
	
	return 0;

}
#include <iostream>

#include "ophPointCloud.h"

using namespace std;

int main(void)
{
	ophPointCloud* Hologram = new ophPointCloud();

	// Load
	Hologram->loadAsOhc("source/complex_field.ohc");		// Load the complex field file

	// Encode
	Hologram->encoding(ophGen::ENCODE_AMPLITUDE);		// Encode the hologram
		/// Put the encoding type

	// Save
	Hologram->normalizeEncoded();		// Normalize the encoded hologram to generate image file
	ivec2 encode_size = Hologram->getEncodeSize();		// Encoded hologram size
	Hologram->save("result/Encoding.bmp",8,nullptr,encode_size[_X], encode_size[_Y]);		// Save the encoded hologram image
	
	return 0;

}
#include "ophLightField.h"

using namespace std;


int main(void)
{
	ophLF* Hologram = new ophLF();

	// Load
	Hologram->readLFConfig("config/TestSpecLF.xml");     // Read the LF hologram configuration file
	Hologram->loadLF("source/sample_orthographic_images_5x5","bmp");		// Load the Light field source image files
		/// Put the directory which has the source files and Put the image file type
	
	// Generate
	Hologram->generateHologram();		// Generate the hologram

	// Save as Complex field data
	Hologram->saveAsOhc("result/LF_complexField.ohc");		// Save the hologram complex field data

	// Encode
	Hologram->encoding(Hologram->ENCODE_SIMPLENI);		// Encode the hologram

	// Save as Encoded Image
	Hologram->normalizeEncoded();		// Normalize the encoded hologram to generate image file
	ivec2 encode_size = Hologram->getEncodeSize();		// Encoded hologram size
	Hologram->save("result/Light_Field_NI_carrier.bmp", 8, nullptr, encode_size[_X], encode_size[_Y]);		// Save the encoded hologram image
	

	cin.get();
	return 0;
}
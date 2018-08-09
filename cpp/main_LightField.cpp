#include "ophLightField.h"

using namespace std;


int main(void)
{
	ophLF* Hologram = new ophLF();

	Hologram->readLFConfig("config/TestSpecLF.xml");

	Hologram->loadLF("source/sample_orthographic_images","bmp");

	Hologram->generateHologram();

	Hologram->encoding(Hologram->ENCODE_AMPLITUDE);

	Hologram->normalizeEncoded();

	ivec2 encode_size = Hologram->getEncodeSize();

	Hologram->save("result/Light_Field.bmp", 8, nullptr, encode_size[_X], encode_size[_Y]);

	cin.get();
	return 0;
}
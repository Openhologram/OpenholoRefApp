#include "ophLightField.h"

using namespace std;


int main(void)
{
	ophLF* Hologram = new ophLF();

	Hologram->setNumImage(20, 20);
	Hologram->setResolImage(200, 200);

	Hologram->setPixelNumber(4000, 4000);
	Hologram->setPixelPitch(8e-6, 8e-6);
	Hologram->setWaveLength(532e-9);

	Hologram->readLFConfig("LF_config.xml");

	Hologram->loadLF("sample_orthographic_images","bmp");

	Hologram->generateHologram();

	Hologram->encoding(Hologram->ENCODE_AMPLITUDE);

	Hologram->normalizeEncoded();

	ivec2 encode_size = Hologram->getEncodeSize();

	Hologram->save("result/Light_Field.bmp", 8, nullptr, encode_size[_X], encode_size[_Y]);

	cin.get();
	return 0;
}
#include "ophTriMesh.h"

using namespace std;


int main(void)
{
	ophTri* Hologram = new ophTri();
	
	Hologram->loadMeshData("mesh_teapot.txt");

	Hologram->setPixelNumber(10, 10);
	Hologram->setPixelPitch(8e-6, 8e-6);
	Hologram->setWaveLength(532e-9);
	Hologram->setIllumination(0, 0, 1);
	
	Real scale = 10*8e-6*0.8;
	Real shift[3] = { 0, 0, 0.02 };

	Hologram->setObjSize(scale);
	Hologram->setObjShift(shift);

	Hologram->objScaleShift();

	Hologram->setShadingType(Hologram->SHADING_FLAT);

	Hologram->generateMeshHologram();

	Hologram->setEncodeMethod(Hologram->ENCODE_AMPLITUDE);

	Hologram->encoding();

	Real* en = Hologram->getEncodedBuffer();

	Hologram->normalizeEncoded();

	ivec2 encode_size = Hologram->getEncodeSize();
	Hologram->save("result/Mesh.bmp", 8, nullptr, encode_size[_X], encode_size[_Y]);

	cin.get();
}
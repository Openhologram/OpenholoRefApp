#include "ophTriMesh.h"

#include <fstream>

using namespace std;


int main(void)
{
	ophTri* Hologram = new ophTri();
	
	Hologram->readMeshConfig("testMeshXML.xml");

	Hologram->loadMeshData("mesh_teapot.txt");

	Hologram->objScaleShift();

	Hologram->generateMeshHologram(Hologram->SHADING_FLAT);

	Hologram->encoding(Hologram->ENCODE_AMPLITUDE);

	Hologram->normalizeEncoded();

	ivec2 encode_size = Hologram->getEncodeSize();

	Hologram->save("result/Mesh.bmp", 8, nullptr, encode_size[_X], encode_size[_Y]);

	cin.get();
}
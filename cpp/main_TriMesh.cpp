#include "ophTriMesh.h"

using namespace std;

int main(void)
{
	ophTri* Hologram = new ophTri();

	Hologram->readMeshConfig("config/TestSpecMesh.xml");

	Hologram->loadMeshData("source/mesh_teapot.ply","ply");
	
	Hologram->objScaleShift();

	Hologram->generateMeshHologram(Hologram->SHADING_FLAT);
	Hologram->encoding(Hologram->ENCODE_AMPLITUDE);
	Hologram->normalizeEncoded();
	ivec2 encode_size = Hologram->getEncodeSize();

	Hologram->save("result/Mesh.bmp", 8, nullptr, encode_size[_X], encode_size[_Y]);
	cin.get();
}
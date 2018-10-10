#include "ophTriMesh.h"

using namespace std;

int main(void)
{
	ophTri* Hologram = new ophTri();

	// Load
	Hologram->readMeshConfig("config/TestSpecMesh.xml");		// Read the Mesh hologram configuration file
	Hologram->loadMeshData("source/mesh_teapot.ply","ply");		// Read the Meshed object data
	Hologram->objScaleShift();					// Object scaling and shifting

	// Generate
	Hologram->generateMeshHologram(Hologram->SHADING_FLAT);		// Generate the hologram
		/// Put the shading effect type

	// Save as Complex Field Data
	Hologram->saveAsOhc("result/Mesh_complexField.ohc");		// Save the hologram complex field data
	
	// Encode
	Hologram->encoding(Hologram->ENCODE_SIMPLENI);		// Encode the hologram

	// Save as Encoded Image
	Hologram->normalizeEncoded();		// Normalize the encoded hologram to generate image file
	ivec2 encode_size = Hologram->getEncodeSize();		// Encoded hologram size
	Hologram->save("result/Mesh_0.1m_ni_-0.3deg.bmp", 8, nullptr, encode_size[_X], encode_size[_Y]);		// Save the encoded hologram image
	

	cin.get();
	return 0;
}
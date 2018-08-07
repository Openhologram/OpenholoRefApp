#include <iostream>
using namespace std;

#include "ophWRP.h"

int main(int argc, char **argv)
{
	cout << "OpenHolo Library : Generation Hologram - Wavefront Recording Plane(WRP) Example" << endl;

	ophWRP* Hologram = new ophWRP();

	Hologram->readConfig("config/TestSpecWRP.xml");
	Hologram->loadPointCloud("source/TestPointCloud_WRP.ply");

	Hologram->calculateMWRP();
	Hologram->generateHologram();
	Hologram->encodeHologram();
	Hologram->normalize();
	Hologram->save("result/Result_WRP.bmp");

	Hologram->release();

	return 0;
}
#include <iostream>
using namespace std;

#include "ophDepthMap.h"

int main(int argc, char **argv)
{
	cout << "OpenHolo Library : Generation Hologram - Depth Map Example" << endl;

	ophDepthMap* Hologram = new ophDepthMap();

	Hologram->setMode(MODE_CPU); //Select CPU or GPU Processing
	Hologram->readConfig("config/TestSpecDepthMap.xml");
	Hologram->readImageDepth("source", "RGB_D", "D_D");

	Hologram->generateHologram();
	Hologram->encodeHologram();
	Hologram->normalize();
	Hologram->save("result/Result_DepthmapSample.bmp");

	Hologram->release();

	return 0;
}
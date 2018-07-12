#include <iostream>
using namespace std;

#include "ophDepthMap.h"

int main(int argc, char **argv)
{
	cout << "OpenHolo Library : Generation Hologram - Depth Map Example" << endl;

	ophDepthMap* Hologram = new ophDepthMap();

	Hologram->setMode(MODE_CPU); //Select CPU or GPU Processing
	Hologram->readConfig("TestSpecDepthMap.xml");

	Hologram->generateHologram();
	Hologram->encodeHologram();
	Hologram->normalize();

	Hologram->save();
	Hologram->release();
}
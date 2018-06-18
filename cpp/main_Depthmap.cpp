#include <iostream>
using namespace std;

#include "ophDepthMap.h"

int main(int argc, char **argv)
{
	cout << "OpenHolo Library : Generation Hologram - Depth Map Example" << endl;

	ophDepthMap* Hologram = new ophDepthMap();

	Hologram->setMode(MODE_GPU); //Select CPU or GPU Processing
	Hologram->readConfig("config_openholo.txt");

	Hologram->generateHologram();
	Hologram->encodeHologram();
	Hologram->normalize();

	Hologram->save();
	Hologram->release();

	return 0;
}
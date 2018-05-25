#include <iostream>
using namespace std;

#include "ophDepthMap.h"

int main(int argc, char **argv)
{
	cout << "OpenHolo Library : Generation Hologram - Depth Map Example" << endl;

	ophDepthMap* Hologram = new ophDepthMap();
			
	Hologram->setMode(MODE_GPU); //Select CPU or GPU Processing

	if (!Hologram->readConfig("config_openholo.txt"))
	{
		cerr << "Warning Error: Wrong Format\n" << endl;
		return -1;
	}

	double time = Hologram->generateHologram();
	Hologram->encodeHologram();
	Hologram->normalize();

	cout << "Implement Time : " << time << " sec" << endl;

	Hologram->save();
	
	Hologram->release();

	return 0;
}
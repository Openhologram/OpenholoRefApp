#include <iostream>
using namespace std;

#include "ophDepthMap.h"

#define OUTPUT_BMP "result/2250ppi_3840_UD_flat0"

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

	Hologram->save(OUTPUT_BMP, 24);

	delete Hologram;

	return 0;
}
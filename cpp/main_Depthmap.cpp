/* OpenHolo Beta v1.0 - Generation Module - DepthMap
Example for Depth Map based Fringe Pattern Generation
*/

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

	Hologram->initialize();
	Hologram->generateHologram();

	return 0;
}

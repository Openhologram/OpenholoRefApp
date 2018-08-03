#include <iostream>
using namespace std;

#include "ophPointCloud.h"

int main(int argc, char **argv)
{
	cout << "OpenHolo Library : Generation Hologram - Point Cloud Example" << endl;

	ophPointCloud* Hologram = new ophPointCloud();

	Hologram->setMode(MODE_CPU); //Select CPU or GPU Processing
	Hologram->readConfig("config/TestSpecPointCloud.xml");
	Hologram->loadPointCloud("source/TestPointCloud.ply");

	Hologram->generateHologram(PC_DIFF_RS_NOT_ENCODED);
	Hologram->encode();
	Hologram->normalize();
	Hologram->save("result/Result_FringePattern");

	Hologram->release();

	return 0;
}
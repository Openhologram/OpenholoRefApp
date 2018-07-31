#include <iostream>
using namespace std;

#include "ophPointCloud.h"

// Define I/O Data File Path
#define INPUT_3D_MODEL	"source/TestPointCloud.ply" // 3D Point Cloud Data Base
#define INPUT_CONFIG	"config/TestSpecPointCloud.xml" // Parameters Config Specification
#define OUTPUT_BMP		"result/Result_FringePattern" // Fringe Pattern Image Output Bitmap File Name

int main(int argc, char **argv)
{
	cout << "OpenHolo Library : Generation Hologram - Point Cloud Example" << endl;

	ophPointCloud* Hologram = new ophPointCloud();

	Hologram->setMode(MODE_CPU); //Select CPU or GPU Processing
	Hologram->loadPointCloud(INPUT_3D_MODEL);
	Hologram->readConfig(INPUT_CONFIG);

	Hologram->generateHologram(PC_DIFF_RS_NOT_ENCODED);

	Hologram->encode();

	Hologram->normalize();

	Hologram->save(OUTPUT_BMP);

	Hologram->release();

	return 0;
}
#include <iostream>
using namespace std;

#include "ophPointCloud.h"

int main(int argc, char **argv)
{
	cout << "OpenHolo Library : Generation Hologram - Point Cloud Example" << endl;

	ophPointCloud* Hologram = new ophPointCloud();

	Hologram->setMode(MODE_GPU); //Select CPU or GPU Processing
	Hologram->readConfig("config/TestSpecPointCloud.xml");
	Hologram->loadPointCloud("source/TestPointCloud_Saturn.ply");

	Hologram->generateHologram(PC_DIFF_RS_NOT_ENCODED);
	Hologram->encodeHologram();
	Hologram->normalize();
	Hologram->save("result/Result_PointCloudSample_Saturn");
	Hologram->saveAsOhc("result/Result_PointCloudSample_Saturn");

	//Hologram->loadAsOhc("result/Result_PointCloudSample_Saturn");
	//Hologram->setMode(MODE_GPU);
	//Hologram->setOffsetDepth(0.3);
	//Hologram->setScale(0.01, 0.01, 0.01);

	//Hologram->encodeHologram();
	//Hologram->normalize();

	//Hologram->save("result/Result_PointCloudSample_SaturnByOHC");

	Hologram->release();

	return 0;
}
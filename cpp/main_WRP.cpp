
#include <iostream>
using namespace std;

#include "ophwrp.h"
#include "ophpointcloud.h"

// Define I/O Data File Path
#define INPUT_3D_MODEL	"TestPointCloud.dat" // 3D Point Cloud Data Base
#define INPUT_CONFIG	"TestSpec.config" // Parameters Config Specification
#define OUTPUT_BMP		"result/Result_FringePattern" // Fringe Pattern Image Output Bitmap File Name

int main(int argc, char **argv)
{
	cout << "OpenHolo Library : Generation Hologram - Wavefront Recording Plane(WRP) Example" << endl;

	ophWRP ow;

	bool colorinfo = true;

	if (ow.loadwPointCloud(INPUT_3D_MODEL,colorinfo) == -1)
	{ 
		cerr << "Failed to load Point Cloud Data File(*.dat)" << endl;
		return -1;
	}
	
	if (!ow.readConfig(INPUT_CONFIG))
	{
		cerr << "Failed to load Config Specification Data File(*.config)" << endl;
		return -1;
	}

	int n = 3;
	double time = ow.calculateWRP(0.005);

	return 0;

}





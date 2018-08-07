#include "ophSig.h"

int main() {

	std::cout << "OpenHolo Library : Hologram core processing - Off-axis hologram transform Example" << std::endl;

	ophSig *holo = new ophSig();

	if (!holo->readConfig("config/holoParam.xml")) {
		// no file 
		return false;
	}

	if (!holo->load("source/3_point_re.bmp", "source/3_point_im.bmp", 8)) {
		// no file 
		return false;
	}

	holo->sigConvertOffaxis();
	
	holo->save("result/Off_axis_re_C.bmp", "result/Off_axis_im_C.bmp",8);

	return 0;
}
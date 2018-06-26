#include "ophSigConvert.h"

int main() {

	std::cout << "OpenHolo Library : Hologram core processing - Off-axis hologram transform Example" << std::endl;

	ophSigConvert *holo = new ophSigConvert();

	if (!holo->loadParam("holoParam.ini")) {
		// no file 
		return false;
	}

	if (!holo->loadHolo("source/3_point_re.bmp", "source/3_point_im.bmp", "bmp", 0)) {
		// no file 
		return false;
	}

	holo->sigConvertOffaxis();

	holo->saveHolo("result/Off_axis_re.bmp", "result/Off_axis_im.bmp", "bmp", 0);

	return 0;
}
#include "ophSigConvert.h"

int main() {

	std::cout << "OpenHolo Library : Hologram core processing - HPO transform Example" << std::endl;

	ophSigConvert *holo = new ophSigConvert();

	if (!holo->loadParam("config/holoParam.ini")) {
		// no file 
		return false;
	}

	if (!holo->loadHolo("source/3_point_re.bmp", "source/3_point_im.bmp", "bmp", 0)) {
		// no file 
		return false;
	}
	holo->sigConvertHPO();

	holo->saveHolo("result/HPO_H_re.bmp", "result/HPO_H_im.bmp", "bmp", 0);

	return 0;
}
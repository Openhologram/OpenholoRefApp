#include "ophSigConvert.h"

int main() {

	std::cout << "OpenHolo Library : Hologram core processing - CAC transform Example" << std::endl;

	ophSigConvert *holo = new ophSigConvert();

	if (!holo->loadParam("config/holoParam.ini")) {
		// no file 
		return false;
	}

	if (!holo->loadHolo("source/ColorPoint_re.bmp", "source/ColorPoint_im.bmp", "bmp", 1)) {
		// no file 
		return false;
	}

	holo->sigConvertCAC();	

	holo->saveHolo("result/CAC_re.bmp", "result/CAC_im.bmp", "bmp", 1);

	return 0;
}
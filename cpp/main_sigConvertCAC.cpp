#include "ophSig.h"

int main() {

	std::cout << "OpenHolo Library : Hologram core processing - CAC transform Example" << std::endl;

	ophSig *holo = new ophSig();

	if (!holo->readConfig("config/holoParam.xml")) {
		// no file 
		return false;
	}

	if (!holo->load("source/ColorPoint_re.bmp", "source/ColorPoint_im.bmp",24)) {
		// no file 
		return false;
	}

	holo->sigConvertCAC(0.000000633,0.000000532,0.000000473);	

	holo->save("result/CAC_re_C.bin", "result/CAC_im_C.bin",24);

	return 0;
}
#include "ophSigCH.h"

int main() {

	std::cout << "OpenHolo Library : Hologram core processing - Compressed Holography Example" << std::endl;

	ophSigCH *holo = new ophSigCH;

	if (!holo->readConfig("config/TestSpecCH.xml")) {
		return false;
	}

	if (!holo->loadCHtemp("source/sample_CH/sampleComplexH_re.bmp", "source/sample_CH/sampleComplexH_im.bmp", 8)) {
		return false;
	}


	// Do compressed Hologram algorithm
	holo->runCH(0);

	// Save results
	holo->saveNumRec("result/CH_Test.bmp");

	return 0;
}
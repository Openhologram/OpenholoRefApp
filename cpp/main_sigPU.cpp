#include "ophSigPU.h"

int main() {

	std::cout << "OpenHolo Library : Hologram core processing - Phase Unwrapping Example" << std::endl;

	ophSigPU *holo = new ophSigPU;

	if (!holo->loadPhaseOriginal("source/sample_Phase_Unwrapping/phase_unwrapping_example.bmp",  8)) {
		return false;
	}
	int maxBoxRadius = 4;
	holo->setPUparam(maxBoxRadius);

	// Do compressed Hologram algorithm
	holo->runPU();

	// Save results
	holo->savePhaseUnwrapped("result/PU_Test.bmp");

	return 0;
}
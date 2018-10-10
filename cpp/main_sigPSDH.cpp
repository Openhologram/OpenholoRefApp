#include "ophSig.h"

int main() {

	std::cout << "OpenHolo Library : Hologram core processing - Complex Field from Phase Shift Digital Hologram Example" << std::endl;

	ophSig *holo = new ophSig();

	const char *f0 = "source/samplePhaseShiftedHolograms/0930_005_gray.bmp";
	const char *f90 = "source/samplePhaseShiftedHolograms/0930_006_gray.bmp";
	const char *f180 = "source/samplePhaseShiftedHolograms/0930_007_gray.bmp";
	const char *f270 = "source/samplePhaseShiftedHolograms/0930_008_gray.bmp";

	holo->getComplexHFromPSDH(f0, f90, f180,f270);

	holo->save("result/PSDH_re_C.bmp", "result/PSDH_im_C.bmp", 8);

	return 0;
}
#include"ophSigGetParam.h"

int main(void)
{
	std::cout << "OpenHolo Library : Hologram core processing - get parameter using axis transformation Example" << std::endl;

	ophSigGetParam* holo = new ophSigGetParam();

	float depth = 0;
	float lambda = 0.000000532;

	if (!holo->loadParam("config/holoParam.ini")) {
		// no file 
		return false;
	}

	if (!holo->loadHolo("source/0.1point_re.bmp", "source/0.1point_im.bmp", "bmp", 0)) {
		// no file 
		return false;
	}

	depth = holo->sigGetParamAT(lambda);

	// backpropagation
	holo->propagationHolo(-depth, lambda);

	holo->saveHolo("result/AT_re.bmp", "result/AT_im.bmp", "bmp", 0);

	return 0;
}
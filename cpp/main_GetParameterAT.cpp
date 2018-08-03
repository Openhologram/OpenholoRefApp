#include"ophSig.h"

int main(void)
{
	std::cout << "OpenHolo Library : Hologram core processing - get parameter using axis transformation Example" << std::endl;

	ophSig* holo = new ophSig();

	float depth = 0;

	if (!holo->readConfig("config/holoParam.xml")) {
		// no file 
		return false;
	}

	if (!holo->load("source/0.1point_re.bmp", "source/0.1point_im.bmp", 8)) {
		// no file 
		return false;
	}

	depth = holo->sigGetParamAT();
	std::cout << depth << endl;
	// backpropagation
	holo->propagationHolo(-depth);
	
	holo->save("result/AT_re.bmp", "result/AT_im.bmp", 8);


	return 0;
}
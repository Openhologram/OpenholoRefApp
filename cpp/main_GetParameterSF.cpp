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

	if (!holo->load("source/3_point_re.bmp", "source/3_point_im.bmp", 8)) {
		// no file 
		return false;
	}

	depth = holo->sigGetParamSF(10, -10, 100, 0.3);
	std::cout << depth << endl;
	// backpropagation
	holo->propagationHolo(depth);
	
	holo->save("result/SF_re.bmp", "result/SF_im.bmp", 8);

	return 0;
}



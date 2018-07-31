#include"ophSigGetParam.h"

int main(void)
{
	std::cout << "OpenHolo Library : Hologram core processing - get parameter using sharfness function maximization Example" << std::endl;

	ophSigGetParam* holo = new ophSigGetParam();

	float depth = 0;

	if (!holo->loadParam("config/holoParam.ini")) {
		// no file 
		return false;
	}

	if (!holo->loadHolo("source/3_point_re.bmp", "source/3_point_im.bmp", "bmp", 0)) {
		// no file 
		return false;
	}
	depth = holo->sigGetParamSF(10, -10, 100);

	// backpropagation
	holo->propagationHolo(-depth);

	holo->saveHolo("result/SF_re.bmp", "result/SF_im.bmp", "bmp", 0);
		
	return 0;
}
//#include"ophSigGetParam.h"
//int main(void)
//{
//	std::cout << "OpenHolo Library : Hologram core processing - propagation Example" << std::endl;
//	ophSigGetParam *siggetparam = new ophSigGetParam();
//	siggetparam->loadParam("holoParam.ini");
//	siggetparam->loadHolo("3_point_re.bmp", "3_point_im.bmp", "bmp", 0);
//	siggetparam->propagationHolo(-0.8);
//	siggetparam->saveHolo("propa_re.bmp", "propa_im.bmp", "bmp", 0);
//
//
//
//	/*float result = 0;
//	ophSigGetParam* siggetparam = new ophSigGetParam();
//	cv::Mat test;
//	siggetparam->loadParam("holoParam.ini");
//	siggetparam->loadHolo("3_point_re.bmp", "3_point_im.bmp", "bmp", 0);
//	result = siggetparam->sigGetParamSF(10, -10, 100);
//	std::cout << result;*/
//
//	return 0;
//}
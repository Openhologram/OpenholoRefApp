#include <iostream>
using namespace std;

#include "ophCascadedPropagation.h"

int main()
{
	ophCascadedPropagation* pCp = new ophCascadedPropagation(L"config/TestSpecCascadedPropagation.xml");
	if (pCp->propagate())
		pCp->saveIntensityAsImg(L"result/intensityRGB.bmp", pCp->getNumColors() * 8);

	pCp->release();

	return 0;
}
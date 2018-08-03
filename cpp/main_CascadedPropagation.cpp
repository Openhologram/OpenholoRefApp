#include <iostream>
using namespace std;

#include "ophCascadedPropagation.h"

int main()
{
	OphCascadedPropagation* pCp = new OphCascadedPropagation(L"TestSpecCascadedPropagation.xml");
	if (pCp->propagate())
		pCp->saveIntensityAsImg(L"result/intensityRGB.bmp", pCp->GetNumColors() * 8);

	pCp->release();

	return 0;
}
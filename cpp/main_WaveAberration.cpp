
#include <iostream>
using namespace std;

#include "ophWaveAberration.h"


int main()
{

	ophWaveAberration* wa = new ophWaveAberration;

	wa->readConfig("TestSpecAberration.xml");  // reads parameters from a configuration file
	wa->accumulateZernikePolynomial();         // generates 2D complex data array of wave aberration according to parameters   
	wa->complex_W;                            // double pointer variable of 2D complex data array of wave aberration
	wa->resolutionX;                           // resolution in x axis of 2D complex data array of wave aberration
	wa->resolutionY;                           // resolution in y axis of 2D complex data array of wave aberration
	wa->saveAberration("aberration.bin");      // saves 2D complex data array of complex wave aberration into a file

	wa->readAberration("aberration.bin");      // reads 2D complex data array of complex wave aberration from a file
	wa->complex_W;                            // double pointer variable of 2D complex data array of wave aberration
	wa->resolutionX;                           // resolution in x axis of 2D complex data array of wave aberration
	wa->resolutionY;                           // resolution in y axis of 2D complex data array of wave aberration


	wa->release();

	return 0;
}

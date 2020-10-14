#include <ophPointCloud.h>
#include <ophDepthMap.h>
#include <ophLightField.h>
#include <ophTriMesh.h>
#include <ophWRP.h>

#include <ophWaveAberration.h>
#include <ophCascadedPropagation.h>

#include <ophSig.h>
#include <ophSigPU.h>
#include <ophSigCH.h>


#define POINT_CLOUD	    true			// Point Cloud
#define DEPTH_MAP		false			// Depth Map
#define LIGHT_FIELD		false			// Light Field
#define TRI_MESH		false			// Triangle Mesh
#define WRP				true			// WRP

#define ENCODE			false			// Encode

#define WAVE_ABERR		false			// Wave Aberration
#define CAS_PROPA		false			// Cascaded Propagation

#define OFF_AXIS		false			// Convert Off-axis
#define CONV_CAC		false			// Convert CAC
#define CONV_HPO		false			// Convert HPO
#define GET_AT			false			// Get Parameter AT
#define GET_SF			false			// Get Parameter SF
#define SIG_PSDH		false			// Signal Phase Shift
#define SIG_PU			false			// Signal Phase Unwrapping
#define SIG_CH			false			// Signal Compressive Holography


#define USE_RGB			true			// on/off

char g_szResult[MAX_PATH] = { 0, };


using namespace std;
void reset(Complex<Real>*in, int nx, int ny)
{
	for (int i = 0; i < nx; i++)
	{
		for (int j = 0; j < ny; j++)
		{
			in[i*ny + j] = i * ny + j;
		}
	}
}


int main()
{
#if POINT_CLOUD &true
	cout << "OpenHolo Library : Generation Hologram - Point Cloud Example" << endl;

	ophPointCloud* Hologram = new ophPointCloud();
	Hologram->setMode(MODE_GPU);												// Select CPU or GPU Processing

#if USE_RGB & true
	Hologram->readConfig("config/PointCloud_3ch.xml");							// Read Config Parameters for Point Cloud CGH
	Hologram->loadPointCloud("source/PointCloud/PointCloud_Dice_RGB.ply");		// Load Point Cloud Data(*.PLY)
#else
	Hologram->readConfig("config/PointCloud_1ch.xml");
	Hologram->loadPointCloud("source/PointCloud/PointCloud_Dice_Grayscale.ply");			
#endif

	int nChannel = Hologram->getContext().waveNum;
	int pnX = Hologram->getContext().pixel_number[_X];
	int pnY = Hologram->getContext().pixel_number[_Y];
	//Complex<Real> *dst = new Complex<Real>[pnX * pnY];
	//memset(dst, 0, pnX*pnY);

#if 0
	Hologram->readImage("source/DepthMap/DepthMap_Dice_RGB.bmp", true);
	int w = Hologram->m_width;
	int h = Hologram->m_height;
	uchar *color = new uchar[w * h];
	memset(color, 0, w * h);
	for (int i = 0; i < nChannel; i++) {
		Real wave = Hologram->getContext().wave_length[i];
		Hologram->separateColor(i, w, h, Hologram->imgRGB, color);

		Hologram->RS_Propagation(color, Hologram->getComplexField()[i], wave, 2.0);
	}
	Hologram->Shift(0.0, -0.25);
	//Hologram->RS_Propagation(vec3(0.0005, 0.0003, 0.0), dst, wave, 1.0, 0.5);
#else
	Hologram->generateHologram(ophPointCloud::PC_DIFF_RS);						// CGH by R-S Diffract
#endif
																				//Hologram->saveAsOhc("result/PointCloud/Result_PointCloud_Dice.ohc");		// Save to ohc
	Hologram->encoding(ophGen::ENCODE_PHASE);									// Encode Complex Field to Real Field
	Hologram->normalize();														// Normalize Real Field to unsigned char(0~255) for save to image(*.BMP)

	sprintf(g_szResult, "result/PointCloud/Result_PointCloud_Dice_%dch.bmp", nChannel);
	Hologram->save(g_szResult, nChannel * 8);									// Save to bmp/png/jpg...

	Hologram->release();														// Release memory used to Generate Point Cloud

#endif
#if DEPTH_MAP & true

	cout << "OpenHolo Library : Generation Hologram - Depth Map Example" << endl;

	ophDepthMap* Hologram = new ophDepthMap();

	Hologram->setMode(MODE_CPU);												// Select CPU or GPU Processing
#if USE_RGB & true
	Hologram->readConfig("config/DepthMap_3ch.xml");							// Read Config Parameters for Depth Map CGH
#else
	Hologram->readConfig("config/DepthMap_1ch.xml");
#endif

	Hologram->readImageDepth("source/DepthMap", 
		"DepthMap_Dice_RGB", "DepthMap_Dice_Depth");							// Read depth image & rgb image

	int nChannel = Hologram->getContext().waveNum;

	Hologram->generateHologram();												// CGH by depth map
	Hologram->saveAsOhc("result/DepthMap/DepthMap_Dice.ohc");				// Save the hologram complex field data

	Hologram->encoding(ophDepthMap::ENCODE_PHASE);								// Encode Complex Field to Real Field
	Hologram->normalize();														// Normalize Real Field to unsigned char(0~255) for save to image(*.BMP)

	sprintf(g_szResult, "result/DepthMap/Result_DepthMap_Dice_%dch.bmp", nChannel);
	Hologram->save(g_szResult, nChannel * 8);									// Save to bmp/png/jpg...

	Hologram->release();														// Release memory used to Generate Point Cloud
		
#endif
#if LIGHT_FIELD & true
	cout << "OpenHolo Library : Generation Hologram - Light Field Example" << endl;

	ophLF* Hologram = new ophLF();

	Hologram->setMode(MODE_GPU);												// Select CPU or GPU Processing

#if USE_RGB & true
	Hologram->readConfig("config/LightField_3ch.xml");							// Read the LF hologram configuration file
#else
	Hologram->readConfig("config/LightField_1ch.xml");
#endif
	
	Hologram->loadLF("source/LightField", "bmp");								// Load the Light field source image files

	int nChannel = Hologram->getContext().waveNum;

	Hologram->generateHologram();												// Generate the hologram

	Hologram->saveAsOhc("result/LightField/LightField_Dice.ohc");				// Save the hologram complex field data

	
	Hologram->encoding(ophLF::ENCODE_PHASE);									// Encode the hologram
	Hologram->normalize();														// Normalize the encoded hologram to generate image file

	sprintf(g_szResult, "result/LightField/Result_LightField_Dice_%dch.bmp", nChannel);
	Hologram->save(g_szResult, nChannel * 8);									// Save to bmp/png/jpg...						// Save the encoded hologram image
	
	Hologram->release();														// Release memory used to Generate Light Field

#endif
#if TRI_MESH & true
	cout << "OpenHolo Library : Generation Hologram - Mesh Example" << endl;

	ophTri* Hologram = new ophTri();

	Hologram->setMode(MODE_GPU);												// Select CPU or GPU Processing

#if USE_RGB & true
	Hologram->readConfig("config/TriMesh_3ch.xml");								// Read the LF hologram configuration file
	Hologram->loadMeshData("source/TriMesh/TriMesh_Dice_RGB.ply", "ply");		// Read the Meshed object data
#else
	Hologram->readConfig("config/TriMesh_1ch.xml");
	Hologram->loadMeshData("source/TriMesh/TriMesh_Dice_Grayscale.ply", "ply");	
#endif
	int nChannel = Hologram->getContext().waveNum;

	Hologram->generateHologram(Hologram->SHADING_FLAT);							// Generate the hologram
	
	Hologram->saveAsOhc("result/TriMesh/TriMesh_Dice.ohc");						// Save the hologram complex field data


	Hologram->encoding(Hologram->ENCODE_PHASE);									// Encode the hologram

	Hologram->normalize();														// Normalize the encoded hologram to generate image file
	ivec2 encode_size = Hologram->getEncodeSize();								// Get encoded hologram size

	sprintf(g_szResult, "result/TriMesh/Result_TriMesh_Dice_%dch.bmp", nChannel);
	Hologram->save(g_szResult, nChannel * 8);									// Save the encoded hologram image
		
	Hologram->release();														// Release memory used to Generate Triangle Mesh

#endif
#if WRP & true
	cout << "OpenHolo Library : Generation Hologram - Wavefront Recording Plane(WRP) Example" << endl;
	
	ophWRP* Hologram = new ophWRP();										    // ophWRP instance
	Hologram->setMode(MODE_GPU);												// Select CPU or GPU Processing

#if USE_RGB & true
	Hologram->readConfig("config/WRP_3ch.xml");									// Read Config Parameters for Point Cloud CGH based WRP algorithm
	Hologram->loadPointCloud("source/WRP/WRP_Dice_RGB.ply");
#else
	Hologram->readConfig("config/WRP_1ch.xml");
	Hologram->loadPointCloud("source/WRP/WRP_Dice_Grayscale.ply");
#endif
	int nChannel = Hologram->getContext().waveNum;
	
	Hologram->generateHologram();												// CGH from WRP
	Hologram->encoding(ophGen::ENCODE_PHASE);									// Encode Complex Field to Real Field
	Hologram->normalize();														// Normalize Real Field to unsigned char(0~255) for save to image(*.BMP)
	sprintf(g_szResult, "result/WRP/Result_WRP_Dice_%dch.bmp", nChannel);
	Hologram->save(g_szResult, nChannel * 8);									// Save to bmp

	Hologram->release();														// Release memory used to Generate Point Cloud 

#endif
#if ENCODE & true
{
	ophPointCloud* Hologram = new ophPointCloud();

	Hologram->loadAsOhc("result/PointCloud/Result_PointCloud_Dice.ohc");

	Hologram->encoding(ophGen::ENCODE_AMPLITUDE);

	Hologram->normalize();

	Hologram->setMergeImage(true); // R, G, B merge one image
	int nChannel = Hologram->getContext().waveNum;

	Hologram->save("result/Encoding/Encoding.bmp", nChannel * 8);

	Hologram->release();
}
#endif
#if WAVE_ABERR & true
{
	ophWaveAberration* wa = new ophWaveAberration;

	wa->readConfig("config/TestSpecAberration.xml");  // reads parameters from a configuration file
	wa->accumulateZernikePolynomial();         // generates 2D complex data array of wave aberration according to parameters   
	wa->complex_W;							// double pointer variable of 2D complex data array of wave aberration
	wa->resolutionX;                           // resolution in x axis of 2D complex data array of wave aberration
	wa->resolutionY;                           // resolution in y axis of 2D complex data array of wave aberration
	wa->saveAsOhc("result/WaveAberration/aberration.ohc");      // saves 2D complex data array of complex wave aberration into a file

	wa->loadAsOhc("result/WaveAberration/aberration.ohc");      // reads 2D complex data array of complex wave aberration from a file
	wa->complex_W;                            // double pointer variable of 2D complex data array of wave aberration
	wa->resolutionX;                           // resolution in x axis of 2D complex data array of wave aberration
	wa->resolutionY;                           // resolution in y axis of 2D complex data array of wave aberration


	wa->release();
}
#endif
#if CAS_PROPA & true
{
	ophCascadedPropagation* pCp = new ophCascadedPropagation(L"config/TestSpecCascadedPropagation(img).xml");	// ophCascadedPropagation instance generation and parameter setup
	if (pCp->isReadyToPropagate()																			// check if all the input are ready
		&& pCp->propagateSlmToPupil()																		// 1st propagation: from SLM to pupil
		&& pCp->propagatePupilToRetina())																	// 2nd propagation: from pupil to retina
	{
		pCp->save(L"result/CascadedPropagation/intensityRGB.bmp", pCp->getNumColors() * 8);					// save numerical reconstruction result in BMP format
		pCp->saveAsOhc("result/CascadedPropagation/intensityRGB_OHC.ohc");
	}

	pCp->release();
}
#endif
#if OFF_AXIS & true
{		
	std::cout << "OpenHolo Library : Hologram core processing - Off-axis hologram transform Example" << std::endl;

	//declaration ophSig class
	ophSig *holo = new ophSig();

	//read parameter
	if (!holo->readConfig("config/TestSpecHoloParam.xml")) {
		// no file 
		return false;
	}

	//hologram data load
	if (holo->loadAsOhc("source/OffAxis/3_point.ohc") < 0) {
		// no file 
		return false;
	}

	//run Convert Offaxis function
	holo->sigConvertOffaxis();

	//save hologram data for ohc file 
	holo->saveAsOhc("result/OffAxis/Off_axis.ohc");

	//release
	holo->release();
}
#endif
#if CONV_CAC & true
{
	std::cout << "OpenHolo Library : Hologram core processing - CAC transform Example" << std::endl;

	//declaration ophSig class
	ophSig *holo = new ophSig();

	double red = 0.000000633;
	double green = 0.000000532;
	double blue = 0.000000473;


	//read parameter
	if (!holo->readConfig("config/TestSpecHoloParam.xml")) {
		// no file 
		return false;
	}

	//hologram data load
	if (holo->loadAsOhc("source/CAC/ColorPoint.ohc") < 1) {
	//if (!holo->load("source/ColorPoint_re.bmp", "source/ColorPoint_im.bmp")) {
		// no file 
		return false;
	}

	//run convert chromatic aberration compensation
	holo->sigConvertCAC(red, green, blue);

	//save hologram data for ohc file
	holo->saveAsOhc("result/CAC/CAC.ohc");

	//release
	holo->release();

}
#endif
#if CONV_HPO & true
{
	std::cout << "OpenHolo Library : Hologram core processing - HPO transform Example" << std::endl;

	//declaration ophSig class
	ophSig *holo = new ophSig();

	//read parameter
	if (!holo->readConfig("config/TestSpecHoloParam.xml")) {
		// no file 
		return false;
	}

	//hologram data load
	if (holo->loadAsOhc("source/HPO/3_point.ohc") < 1) {
		// no file 
		return false;
	}

	//run convert horizontal parallax only hologram
	holo->sigConvertHPO();

	//save hologram data for ohc file
	holo->saveAsOhc("result/HPO/HPO.ohc");

	//release
	holo->release();

}
#endif
#if GET_AT & true
{
	std::cout << "OpenHolo Library : Hologram core processing - get parameter using axis transformation Example" << std::endl;

	ophSig* holo = new ophSig();

	float depth = 0;

	if (!holo->readConfig("config/TestSpecHoloParam.xml")) {
		// no file 
		return false;
	}

	//hologram data load
	if (holo->loadAsOhc("source/AT/point_150mm.ohc") < 1) {
		// no file 
		return false;
	}

	//get parameter using axis transformation
	depth = holo->sigGetParamAT();

	std::cout << depth << endl;

	// backpropagation
	holo->propagationHolo(-depth);

	//save hologram data for ohc file	
	holo->saveAsOhc("result/AT/AT.ohc");

	//release
	holo->release();
}
#endif
#if GET_SF & true
{
	std::cout << "OpenHolo Library : Hologram core processing - get parameter using axis transformation Example" << std::endl;

	////declaration ophSig class
	ophSig* holo = new ophSig();

	float depth = 0;

	//read parameter
	if (!holo->readConfig("config/TestSpecHoloParam.xml")) {
		// no file 
		return false;
	}

	//hologram data load
	if (holo->loadAsOhc("source/SF/3_point.ohc") < 1) {	
		// no file 
		return false;
	}

	//get parameter using sharpness function
	depth = holo->sigGetParamSF(10, -10, 100, 0.3);
	std::cout << depth << endl;

	// backpropagation
	holo->propagationHolo(-depth);

	//save hologram data for ohc file
	holo->saveAsOhc("result/SF/SF.ohc");

	//release
	holo->release();

}
#endif
#if SIG_PSDH & true
{
	std::cout << "OpenHolo Library : Hologram core processing - Complex Field from Phase Shift Digital Hologram Example" << std::endl;

	ophSig *holo = new ophSig();

	const char *f0 = "source/PhaseShiftedHolograms/0930_005_gray.bmp";		// File names of interference patterns with 90 degree reference wave phase shifts
	const char *f90 = "source/PhaseShiftedHolograms/0930_006_gray.bmp";
	const char *f180 = "source/PhaseShiftedHolograms/0930_007_gray.bmp";
	const char *f270 = "source/PhaseShiftedHolograms/0930_008_gray.bmp";

	holo->getComplexHFromPSDH(f0, f90, f180, f270);							// Extract complex field from 4 interference patterns

	holo->save("result/PhaseShift/PSDH_re_C.bmp", "result/PhaseShift/PSDH_im_C.bmp"); // Save complex field to image files (real and imaginary parts)
	holo->release();
}
#endif
#if SIG_PU & true
{
	std::cout << "OpenHolo Library : Hologram core processing - Phase Unwrapping Example" << std::endl;

	ophSigPU *holo = new ophSigPU;

	// Load original wrapped phase data
	if (!holo->loadPhaseOriginal("source/PhaseUnwrapping/phase_unwrapping_example.bmp", 8)) {
		return false;
	}
	int maxBoxRadius = 4;
	holo->setPUparam(maxBoxRadius);		// Set phase unwrapping algorithm parameter (maximum box radius for Goldstein phase unwrapping)

	// Do phase unwrapping algorithm
	holo->runPU();

	// Save results
	holo->savePhaseUnwrapped("result/PhaseUnwrapping/PU_Test.bmp");
	holo->release();
}
#endif
#if SIG_CH & true
{
	std::cout << "OpenHolo Library : Hologram core processing - Compressed Holography Example" << std::endl;

	ophSigCH *holo = new ophSigCH;

	// Load configure file (xml)
	if (!holo->readConfig("config/TestSpecCH.xml")) {
		return false;
	}

	if (!holo->loadCHtemp("source/CompressiveHolo/sampleComplexH_re.bmp", "source/CompressiveHolo/sampleComplexH_im.bmp", 8)) {
		return false;
	}

	// Do compressed Hologram algorithm
	holo->runCH(0);

	// Save results (numerical reconstructions) to image files
	holo->saveNumRec("result/CompressiveHolo/CH_Test.bmp");
	holo->release();
}
#endif

return 0;
}
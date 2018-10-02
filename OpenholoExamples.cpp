#include "ophPointCloud.h"
#include "ophDepthMap.h"
#include "ophLightField.h"
#include "ophTriMesh.h"
#include "ophWRP.h"

#include "ophWaveAberration.h"
#include "ophCascadedPropagation.h"

#include "ophSig.h"
#include "ophSigPU.h"
#include "ophSigCH.h"

#define POINT_CLOUD		false			// Point Cloud
#define DEPTH_MAP		false			// Depth Map
#define LIGHT_FIELD		true			// Light Field
#define TRI_MESH		false			// Triangle Mesh
#define WRP				false			// WRP

#define WAVE_ABERR		false			// Wave Aberration
#define CAS_PROPA		false			// Cascaded Propagation

#define OFF_AXIS		false			// Convert Off-axis
#define CONV_CAC		false			// Convert CAC
#define CONV_HPO		false			// Convert HPO
#define GET_AT			false			// Get Parameter AT
#define GET_SF			false			// Get Parameter SF
#define SIG_PSDH		false			// Signal Phase Shift-
#define SIG_PU			false			// Signal Phase Unwrapping
#define SIG_CH			false			// Signal Compressive Holography

int main()
{
#if POINT_CLOUD & true
	{
		cout << "OpenHolo Library : Generation Hologram - Point Cloud Example" << endl;

		ophPointCloud* Hologram = new ophPointCloud();

		Hologram->setMode(MODE_GPU); //Select CPU or GPU Processing
		Hologram->readConfig("config/TestSpecPointCloud.xml");
		Hologram->loadPointCloud("source/TestPointCloud_Plane.ply");

		Hologram->generateHologram(PC_DIFF_RS_NOT_ENCODED);
		Hologram->encodeHologram();
		Hologram->normalize();
		Hologram->save("result/PointCloud/Result_PointCloudSample_Plane");
		//Hologram->saveAsOhc("result/PointCloud/Result_PointCloudSample_Saturn");

		//Hologram->loadAsOhc("result/PointCloud/Result_PointCloudSample_Saturn");
		//Hologram->setMode(MODE_GPU);
		//Hologram->setOffsetDepth(0.3);
		//Hologram->setScale(0.01, 0.01, 0.01);

		//Hologram->encodeHologram();
		//Hologram->normalize();

		//Hologram->save("result/PointCloud/Result_PointCloudSample_SaturnByOHC");

		Hologram->release();
	}
#elif DEPTH_MAP & true
	{
		cout << "OpenHolo Library : Generation Hologram - Depth Map Example" << endl;

		ophDepthMap* Hologram = new ophDepthMap();

		Hologram->setMode(MODE_GPU); //Select CPU or GPU Processing
		Hologram->readConfig("config/TestSpecDepthMap.xml");
		Hologram->readImageDepth("source", "RGB_D", "D_D");

		Hologram->generateHologram();
		Hologram->encodeHologram();
		Hologram->normalize();
		Hologram->save("result/DepthMap/Result_DepthmapSample.bmp");

		Hologram->release();
	}
#elif LIGHT_FIELD & true
	{
		ophLF* Hologram = new ophLF();

		Hologram->readLFConfig("config/TestSpecLF.xml");

		Hologram->loadLF("source/sample_orthographic_images", "bmp");

		Hologram->generateHologram();

		Hologram->encoding(Hologram->ENCODE_AMPLITUDE);

		Hologram->normalizeEncoded();

		ivec2 encode_size = Hologram->getEncodeSize();

		Hologram->save("result/LightField/Light_Field.bmp", 8, nullptr, encode_size[_X], encode_size[_Y]);
	}
#elif TRI_MESH & true
	{
		ophTri* Hologram = new ophTri();

		Hologram->readMeshConfig("config/TestSpecMesh.xml");

		Hologram->loadMeshData("source/mesh_teapot.ply", "ply");

		Hologram->objScaleShift();

		Hologram->generateMeshHologram(Hologram->SHADING_FLAT);
		Hologram->encoding(Hologram->ENCODE_AMPLITUDE);
		Hologram->normalizeEncoded();
		ivec2 encode_size = Hologram->getEncodeSize();

		Hologram->save("result/TriMesh/Mesh.bmp", 8, nullptr, encode_size[_X], encode_size[_Y]);
	}
#elif WRP & true
	{
		cout << "OpenHolo Library : Generation Hologram - Wavefront Recording Plane(WRP) Example" << endl;

		ophWRP* Hologram = new ophWRP();

		Hologram->readConfig("config/TestSpecWRP.xml");
		Hologram->loadPointCloud("source/TestPointCloud_WRP.ply");

		Hologram->calculateMWRP();
		Hologram->generateHologram();
		Hologram->encodeHologram();
		Hologram->normalize();
		Hologram->save("result/WRP/Result_WRP.bmp");

		Hologram->release();
	}
#elif WAVE_ABERR & true
	{
		ophWaveAberration* wa = new ophWaveAberration;

		wa->readConfig("config/TestSpecAberration.xml");  // reads parameters from a configuration file
		wa->accumulateZernikePolynomial();         // generates 2D complex data array of wave aberration according to parameters   
		wa->complex_W;                            // double pointer variable of 2D complex data array of wave aberration
		wa->resolutionX;                           // resolution in x axis of 2D complex data array of wave aberration
		wa->resolutionY;                           // resolution in y axis of 2D complex data array of wave aberration
		wa->saveAberration("result/WaveAberration/aberration.bin");      // saves 2D complex data array of complex wave aberration into a file

		wa->readAberration("result/WaveAberration/aberration.bin");      // reads 2D complex data array of complex wave aberration from a file
		wa->complex_W;                            // double pointer variable of 2D complex data array of wave aberration
		wa->resolutionX;                           // resolution in x axis of 2D complex data array of wave aberration
		wa->resolutionY;                           // resolution in y axis of 2D complex data array of wave aberration


		wa->release();
	}
#elif CAS_PROPA & true
	{
		ophCascadedPropagation* pCp = new ophCascadedPropagation(L"config/TestSpecCascadedPropagation.xml");
		if (pCp->propagate())
			pCp->saveIntensityAsImg(L"result/CascadedPropagationintensityRGB.bmp", pCp->getNumColors() * 8);

		pCp->release();
	}
#elif OFF_AXIS & true
	{
		std::cout << "OpenHolo Library : Hologram core processing - Off-axis hologram transform Example" << std::endl;

		ophSig *holo = new ophSig();

		if (!holo->readConfig("config/holoParam.xml")) {
			// no file 
			return false;
		}

		if (!holo->load("source/3_point_re.bmp", "source/3_point_im.bmp", 8)) {
			// no file 
			return false;
		}

		holo->sigConvertOffaxis();

		holo->save("result/OffAxis/Off_axis.bmp", 8);
	}
#elif CONV_CAC & true
	{
		std::cout << "OpenHolo Library : Hologram core processing - CAC transform Example" << std::endl;

		ophSig *holo = new ophSig();

		if (!holo->readConfig("config/holoParam.xml")) {
			// no file 
			return false;
		}

		if (!holo->load("source/ColorPoint_re.bmp", "source/ColorPoint_im.bmp", 24)) {
			// no file 
			return false;
		}

		holo->sigConvertCAC(0.000000633, 0.000000532, 0.000000473);

		holo->save("result/CAC/CAC_re_C.bin", "result/CAC/CAC_im_C.bin", 24);
	}
#elif CONV_HPO & true
	{
		std::cout << "OpenHolo Library : Hologram core processing - HPO transform Example" << std::endl;

		ophSig *holo = new ophSig();

		if (!holo->readConfig("config/holoParam.xml")) {
			// no file 
			return false;
		}

		if (!holo->load("source/3_point_re.bmp", "source/3_point_im.bmp", 8)) {
			// no file 
			return false;
		}

		holo->sigConvertHPO();

		holo->save("result/HPO/HPO_re_C.bmp", "result/HPO/HPO_im_C.bmp", 8);
	}
#elif GET_AT & true
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

		holo->save("result/AT/AT_re.bmp", "result/AT/AT_im.bmp", 8);
	}
#elif GET_SF & true
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

		holo->save("result/SF/SF_re.bmp", "result/SF/SF_im.bmp", 8);
		holo->release();
	}
#elif SIG_PSDH & true
	{
		std::cout << "OpenHolo Library : Hologram core processing - Complex Field from Phase Shift Digital Hologram Example" << std::endl;

		ophSig *holo = new ophSig();

		const char *f0 = "source/samplePhaseShiftedHolograms/0930_005_gray.bmp";
		const char *f90 = "source/samplePhaseShiftedHolograms/0930_006_gray.bmp";
		const char *f180 = "source/samplePhaseShiftedHolograms/0930_007_gray.bmp";
		const char *f270 = "source/samplePhaseShiftedHolograms/0930_008_gray.bmp";

		holo->getComplexHFromPSDH(f0, f90, f180, f270);

		holo->save("result/PhaseShift/PSDH_re_C.bmp", "result/PhaseShift/PSDH_im_C.bmp", 8);
		holo->release();
	}
#elif SIG_PU & true
	{
		std::cout << "OpenHolo Library : Hologram core processing - Phase Unwrapping Example" << std::endl;

		ophSigPU *holo = new ophSigPU;

		if (!holo->loadPhaseOriginal("source/sample_Phase_Unwrapping/phase_unwrapping_example.bmp", 8)) {
			return false;
		}
		int maxBoxRadius = 4;
		holo->setPUparam(maxBoxRadius);

		// Do compressed Hologram algorithm
		holo->runPU();

		// Save results
		holo->savePhaseUnwrapped("result/PhaseUnwrapping/PU_Test.bmp");
		holo->release();
	}
#elif SIG_CH & true
	{
		std::cout << "OpenHolo Library : Hologram core processing - Compressed Holography Example" << std::endl;

		ophSigCH *holo = new ophSigCH;

		if (!holo->readConfig("config/TestSpecCH.xml")) {
			return false;
		}

		if (!holo->loadCHtemp("source/sample_CH/sampleComplexH_re.bmp", "source/sample_CH/sampleComplexH_im.bmp", 8)) {
			return false;
		}

		// Do compressed Hologram algorithm
		holo->runCH(0);

		// Save results
		holo->saveNumRec("result/CompressiveHolo/CH_Test.bmp");
		holo->release();
	}
#endif
	return 0;
}
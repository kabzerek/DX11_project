#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


#include "D3DClass.h"
#include "CameraClass.h"
#include "ModelClass.h"
//#include "LightShaderClass.h"
#include "LightClass.h"
//#include "MultiTextureShaderClass.h"
//#include "AlphaMapShaderClass.h"
//#include "BumpMapShaderClass.h"
#include "SpecMapShaderClass.h"

#include <vector>

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame(int, int);

private:
	bool Render(float);

	D3DClass* m_D3D;
	CameraClass* m_Camera;
	//ModelClass* m_Model;
	std::vector<ModelClass*> m_Models;
	//LightShaderClass* m_LightShader;
	LightClass* m_Light;
	//MultiTextureShaderClass* m_MultiTextureShader;
	//AlphaMapShaderClass* m_AlphaMapShader;
	//BumpMapShaderClass* m_BumpMapShader;	
	SpecMapShaderClass* m_SpecMapShader;

	//std::vector<ModelClass::ModelInit> m_ModelsToLoad;
};

#endif
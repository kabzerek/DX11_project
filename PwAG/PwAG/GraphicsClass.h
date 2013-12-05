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
#include "RenderTextureClass.h"
#include "ShadowShaderClass.h"
#include "DepthShaderClass.h"
#include "DebugWindowClass.h"
//#include "TextureShaderClass.h"

#include <vector>

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 100.0f;
const float SCREEN_NEAR = 1.00f;
const int SHADOWMAP_WIDTH = 1024;
const int SHADOWMAP_HEIGHT = 1024;

class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	//bool Frame(int, int);
	bool Frame(float posX, float posY, float posZ, float rotX, float rotY, float rotZ);
private:
	bool RenderSceneToTexture();
	bool Render();

	D3DClass* m_D3D;
	CameraClass* m_Camera;
	//ModelClass* m_Model;
	std::vector<ModelClass*> m_Models;
//	LightShaderClass* m_LightShader;
	LightClass* m_Light;
	//TextureShaderClass* m_TextureShader;
	//MultiTextureShaderClass* m_MultiTextureShader;
	//AlphaMapShaderClass* m_AlphaMapShader;
	//BumpMapShaderClass* m_BumpMapShader;	
	SpecMapShaderClass* m_SpecMapShader;
	ShadowShaderClass* m_ShadowShader;
	RenderTextureClass* m_RenderTexture;
	DepthShaderClass* m_DepthShader;
	//DebugWindowClass* m_DebugWindow;
};

#endif
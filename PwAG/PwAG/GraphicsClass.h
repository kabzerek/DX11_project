#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_

#include "D3DClass.h"
#include "CameraClass.h"
#include "ModelClass.h"
#include "LightClass.h"
#include "RenderTextureClass.h"
#include "DebugWindowClass.h"
#include "OrthoWindowClass.h"
#include "TextClass.h"

#include "EngineObjectClass.h"
#include "PhysicsDebugObjectClass.h"

#include "ShaderManagerClass.h"

#include <btBulletDynamicsCommon.h>

#include <vector>

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 100.0f;
const float SCREEN_NEAR = 1.00f;
const int SHADOWMAP_WIDTH = 1024;
const int SHADOWMAP_HEIGHT = 1024;

class GraphicsClass : btIDebugDraw
{
private:
	struct DebugVertexType
		{
			D3DXVECTOR3 position;
			D3DXVECTOR3 color;
		};
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	//bool Frame(int, int);
	bool Frame(float, float, float, float, float, float, bool);
	bool SetWireframe();
	void ToggleDebugMode();

	void SetSentence(int, std::string);

	btDiscreteDynamicsWorld* GetDynamicsWorld() { return m_dynamicsWorld; }

	void GetPos(float&, float&, float&, float&, float&, float&, float&, float&, float&);

private:
	bool RenderSceneToTexture();
	bool Render();

	bool RenderBlackAndWhiteShadows();
	bool DownSampleTexture();
	bool RenderHorizontalBlurToTexture();
	bool RenderVerticalBlurToTexture();
	bool UpSampleTexture();
	bool Render2DTextureScene();

	bool InitializePhysics();
	void ShutdownPhysics();

	/////////////////
	// dtDebugDraw //
	/////////////////
	void drawLine(const btVector3 &from, const btVector3 &to, const btVector3 &color);
	void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) { return; }
	void reportErrorWarning(const char* warningString) { return; }
	void draw3dText(const btVector3& location, const char* textString) { return; }
	void setDebugMode(int debugMode) { m_debugMode = debugMode; }
	int  getDebugMode() const { return m_debugMode; }

protected:
	btDiscreteDynamicsWorld* m_dynamicsWorld;

private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	std::vector<EngineObjectClass*> m_EngineObjects;
	EngineObjectClass* m_Ragdoll;
	LightClass* m_Light;
	TextClass* m_Text;

	ShaderManagerClass* m_ShaderManager;

	RenderTextureClass *m_RenderTexture, *m_BlackWhiteRenderTexture, *m_DownSampleTexture;
	RenderTextureClass *m_HorizontalBlurTexture, *m_VerticalBlurTexture, *m_UpSampleTexture;

	//DebugWindowClass* m_DebugWindow;
	OrthoWindowClass *m_SmallWindow, *m_FullScreenWindow;

	/////////////////
	// dtDebugDraw //
	/////////////////
	int m_debugMode;
	bool m_isDebug;

	std::vector<PhysicsDebugObjectClass*> m_DebugObjects;
};

#endif
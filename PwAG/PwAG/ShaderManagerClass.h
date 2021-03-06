#ifndef _SHADERMANAGERCLASS_H_
#define _SHADERMANAGERCLASS_H_

#include "d3dclass.h"

//shaders
#include "AlphaMapShaderClass.h"
#include "BumpMapShaderClass.h"
#include "DepthShaderClass.h"
#include "HorizontalBlurShaderClass.h"
#include "LightShaderClass.h"
#include "MultiTextureShaderClass.h"
#include "ShadowShaderClass.h"
#include "SoftShadowShaderClass.h"
#include "SpecMapShaderClass.h"
#include "TextureShaderClass.h"
#include "VerticalBlurShaderClass.h"
#include "ColorShaderClass.h"


class ShaderManagerClass
{
public:
	ShaderManagerClass(void);
	ShaderManagerClass(const ShaderManagerClass&);
	~ShaderManagerClass(void);

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();

	bool RenderColorShader(ID3D11DeviceContext*, 
						   int, 
						   D3DXMATRIX, 
						   D3DXMATRIX, 
						   D3DXMATRIX);

	bool RenderAlphaMapShader(ID3D11DeviceContext*, 
							  int, 
							  D3DXMATRIX, 
							  D3DXMATRIX, 
							  D3DXMATRIX, 
							  ID3D11ShaderResourceView**);

	bool RenderBumpMapShader(ID3D11DeviceContext*, 
							 int, 
							 D3DXMATRIX, 
							 D3DXMATRIX, 
							 D3DXMATRIX, 
							 ID3D11ShaderResourceView**, 
							 D3DXVECTOR3, 
							 D3DXVECTOR4);

	bool RenderDepthShader(ID3D11DeviceContext*, 
						   int, 
						   D3DXMATRIX, 
						   D3DXMATRIX, 
						   D3DXMATRIX);

	bool RenderHorizontalBlurShader(ID3D11DeviceContext*, 
									int, 
									D3DXMATRIX, 
									D3DXMATRIX, 
									D3DXMATRIX, 
									ID3D11ShaderResourceView*, 
									float);

	bool RenderLightShader(ID3D11DeviceContext*, 
						   int, 
						   D3DXMATRIX, 
						   D3DXMATRIX, 
						   D3DXMATRIX, 
						   ID3D11ShaderResourceView*, 
						   D3DXVECTOR3, 
						   D3DXVECTOR4, 
						   D3DXVECTOR4, 
						   D3DXVECTOR3, 
						   D3DXVECTOR4, 
						   float);

	bool RenderMultiTextureShader(ID3D11DeviceContext*, 
								  int, 
								  D3DXMATRIX, 
								  D3DXMATRIX, 
								  D3DXMATRIX, 
								  ID3D11ShaderResourceView**);

	bool RenderShadowShader(ID3D11DeviceContext*, 
							int, 
							D3DXMATRIX, 
							D3DXMATRIX, 
							D3DXMATRIX, 
							D3DXMATRIX, 
							D3DXMATRIX, 
							ID3D11ShaderResourceView*, 
							D3DXVECTOR3);

	bool RenderSoftShadowShader(ID3D11DeviceContext*, 
								int, 
								D3DXMATRIX, 
								D3DXMATRIX, 
								D3DXMATRIX, 
								ID3D11ShaderResourceView*, 
								ID3D11ShaderResourceView*, 
								D3DXVECTOR3, 
								D3DXVECTOR4, 
								D3DXVECTOR4);

	bool RenderSpecMapShader(ID3D11DeviceContext*, 
							 int, 
							 D3DXMATRIX, 
							 D3DXMATRIX, 
							 D3DXMATRIX, 
							 ID3D11ShaderResourceView**, 
							 D3DXVECTOR3, 
							 D3DXVECTOR4, 
							 D3DXVECTOR3, 
							 D3DXVECTOR4, 
							 float);

	bool RenderTextureShader(ID3D11DeviceContext*, 
							 int, 
							 D3DXMATRIX, 
							 D3DXMATRIX, 
							 D3DXMATRIX, 
							 ID3D11ShaderResourceView*);

	bool RenderVerticalBlurShader(ID3D11DeviceContext*, 
								  int, 
								  D3DXMATRIX, 
								  D3DXMATRIX, 
								  D3DXMATRIX, 
								  ID3D11ShaderResourceView*, 
								  float);

private:
	ColorShaderClass*			m_ColorShader;
	AlphaMapShaderClass*		m_AlphaMapShader;
	BumpMapShaderClass*			m_BumpMapShader;
	DepthShaderClass*			m_DepthShader;
	HorizontalBlurShaderClass*	m_HorizontalBlurShader;
	LightShaderClass*			m_LightShader;
	MultiTextureShaderClass*	m_MultiTextureShader;
	ShadowShaderClass*			m_ShadowShader;
	SoftShadowShaderClass*		m_SoftShadowShader;
	SpecMapShaderClass*			m_SpecMapShader;
	TextureShaderClass*			m_TextureShader;
	VerticalBlurShaderClass*	m_VerticalBlurShader;
};

#endif

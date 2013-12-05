#ifndef _SHADERMANAGERCLASS_H_
#define _SHADERMANAGERCLASS_H_

#include "d3dclass.h"

//shaders
#include "AlphaMapShaderClass.h"
#include "BumpMapShaderClass.h"
#include "DepthShaderClass.h"
#include "LightShaderClass.h"
#include "MultiTextureShaderClass.h"
#include "ShadowShaderClass.h"
#include "SoftShadowShaderClass.h"
#include "SpecMapShaderClass.h"
#include "TextureShaderClass.h"

class ShaderManagerClass
{
public:
	ShaderManagerClass(void);
	ShaderManagerClass(const ShaderManagerClass&);
	~ShaderManagerClass(void);

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();

	bool RenderAlphaMapShader(ID3D11DeviceContext*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D11ShaderResourceView**);
	bool RenderBumpMapShader(ID3D11DeviceContext*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D11ShaderResourceView**, 
							 D3DXVECTOR3, D3DXVECTOR4);
	bool RenderDepthShader(ID3D11DeviceContext*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX);
	bool RenderLightShader(ID3D11DeviceContext*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D11ShaderResourceView*, 
						   D3DXVECTOR3, D3DXVECTOR4, D3DXVECTOR4, D3DXVECTOR3, D3DXVECTOR4, float);
	bool RenderMultiTextureShader(ID3D11DeviceContext*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D11ShaderResourceView**);
	bool RenderShadowShader(ID3D11DeviceContext*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, 
							ID3D11ShaderResourceView*, D3DXVECTOR3);
	bool RenderSoftShadowShader(ID3D11DeviceContext*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D11ShaderResourceView*, 
								ID3D11ShaderResourceView*, D3DXVECTOR3, D3DXVECTOR4, D3DXVECTOR4);
	bool RenderSpecMapShader(ID3D11DeviceContext*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D11ShaderResourceView**, 
							 D3DXVECTOR3, D3DXVECTOR4, D3DXVECTOR3, D3DXVECTOR4, float);
	bool RenderTextureShader(ID3D11DeviceContext*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D11ShaderResourceView*);

private:
	AlphaMapShaderClass* m_AlphaMapShader;
	BumpMapShaderClass* m_BumpMapShader;
	DepthShaderClass* m_DepthShader;
	LightShaderClass* m_LightShader;
	MultiTextureShaderClass* m_MultiTextureShader;
	ShadowShaderClass* m_ShadowShader;
	SoftShadowShaderClass* m_SoftShadowShader;
	SpecMapShaderClass* m_SpecMapShader;
	TextureShaderClass* m_TextureShader;
};

#endif


		// Render the model using the specular map shader.
		//result = m_SpecMapShader->Render(m_D3D->GetDeviceContext(), (*it)->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		//		(*it)->GetTextureArray(), m_Light->GetDirection(), m_Light->GetDiffuseColor(), 
		//		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		//
		//if(!result)
		//{
		//	return false;
		//}

		// Render the model using the shadow shader.
		//result = m_ShadowShader->Render(m_D3D->GetDeviceContext(), (*it)->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, lightViewMatrix, 
		//			lightProjectionMatrix, (*it)->GetTexture(), m_RenderTexture->GetShaderResourceView(), m_Light->GetPosition(),
	//				m_Light->GetAmbientColor(), m_Light->GetDiffuseColor());

		// Render the model using the specular map shader.
	//m_SpecMapShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		//		m_Model->GetTextureArray(), m_Light->GetDirection(), m_Light->GetDiffuseColor(), 
			//	m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

		//// Render the model using the bump map shader.
	//m_BumpMapShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
	//			m_Model->GetTextureArray(), m_Light->GetDirection(), m_Light->GetDiffuseColor());

	//// Render the model using the alpha map shader.
	//m_AlphaMapShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
	//			 m_Model->GetTextureArray());

	//// Render the model using the multitexture shader.
	//m_MultiTextureShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
	//			     m_Model->GetTextureArray());


	//// Render the model using the light shader.
	//result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
	//			       m_Model->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), 
	//			       m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

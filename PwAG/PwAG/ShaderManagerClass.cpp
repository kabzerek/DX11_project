#include "ShaderManagerClass.h"


ShaderManagerClass::ShaderManagerClass(void)
{
	m_ColorShader = 0;
	m_AlphaMapShader = 0;
	m_BumpMapShader = 0;
	m_DepthShader = 0;
	m_HorizontalBlurShader = 0;
	m_LightShader = 0;
	m_MultiTextureShader = 0;
	m_ShadowShader = 0;
	m_SoftShadowShader = 0;
	m_SpecMapShader = 0;
	m_TextureShader = 0;
	m_VerticalBlurShader = 0;
}

ShaderManagerClass::ShaderManagerClass(const ShaderManagerClass& other)
{
}


ShaderManagerClass::~ShaderManagerClass(void)
{
}

bool ShaderManagerClass::Initialize(ID3D11Device* device, HWND hwnd)
{
	bool result;

	/////////////////
	// ColorShader //
	/////////////////
	m_ColorShader = new ColorShaderClass;
	if(!m_ColorShader)
	{
		return false;
	}

	// Initialize the ColorShader object.
	result = m_ColorShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the ColorShader object.", L"Error", MB_OK);
		return false;
	}

	////////////////////
	// AlphaMapShader //
	////////////////////
	// Create AlphaMapShader object.
	m_AlphaMapShader = new AlphaMapShaderClass;
	if(!m_AlphaMapShader)
	{
		return false;
	}

	// Initialize the AlphaMapShader object.
	result = m_AlphaMapShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the AlphaMapShader object.", L"Error", MB_OK);
		return false;
	}

	///////////////////
	// BumpMapShader //
	///////////////////
	// Create BumpMapShader object.
	m_BumpMapShader = new BumpMapShaderClass;
	if(!m_BumpMapShader)
	{
		return false;
	}

	// Initialize the BumpMapShader object.
	result = m_BumpMapShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the BumpMapShader object.", L"Error", MB_OK);
		return false;
	}

	/////////////////
	// DepthShader //
	/////////////////
	// Create DepthShader object.
	m_DepthShader = new DepthShaderClass;
	if(!m_DepthShader)
	{
		return false;
	}

	// Initialize the DepthShader object.
	result = m_DepthShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the DepthShader object.", L"Error", MB_OK);
		return false;
	}

	//////////////////////////
	// HorizontalBlurShader //
	//////////////////////////
	// Create HorizontalBlurShader object.
	m_HorizontalBlurShader = new HorizontalBlurShaderClass;
	if(!m_HorizontalBlurShader)
	{
		return false;
	}

	// Initialize the HorizontalBlurShader object.
	result = m_HorizontalBlurShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the HorizontalBlurShader object.", L"Error", MB_OK);
		return false;
	}

	/////////////////
	// LightShader //
	/////////////////
	// Create LightShader object.
	m_LightShader = new LightShaderClass;
	if(!m_LightShader)
	{
		return false;
	}

	// Initialize the LightShader object.
	result = m_LightShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the LightShader object.", L"Error", MB_OK);
		return false;
	}

	////////////////////////
	// MultiTextureShader //
	////////////////////////
	// Create MultiTextureShader object.
	m_MultiTextureShader = new MultiTextureShaderClass;
	if(!m_MultiTextureShader)
	{
		return false;
	}

	// Initialize the MultiTextureShader object.
	result = m_MultiTextureShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the MultiTextureShader object.", L"Error", MB_OK);
		return false;
	}

	//////////////////
	// ShadowShader //
	//////////////////
	// Create ShadowShader object.
	m_ShadowShader = new ShadowShaderClass;
	if(!m_ShadowShader)
	{
		return false;
	}

	// Initialize the ShadowShader object.
	result = m_ShadowShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the ShadowShader object.", L"Error", MB_OK);
		return false;
	}

	//////////////////////
	// SoftShadowShader //
	//////////////////////
	// Create SoftShadowShader object.
	m_SoftShadowShader = new SoftShadowShaderClass;
	if(!m_SoftShadowShader)
	{
		return false;
	}

	// Initialize the SoftShadowShader object.
	result = m_SoftShadowShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the SoftShadowShader object.", L"Error", MB_OK);
		return false;
	}

	///////////////////
	// SpecMapShader //
	///////////////////
	// Create SpecMapShader object.
	m_SpecMapShader = new SpecMapShaderClass;
	if(!m_SpecMapShader)
	{
		return false;
	}

	// Initialize the SpecMapShader object.
	result = m_SpecMapShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the SpecMapShader object.", L"Error", MB_OK);
		return false;
	}

	///////////////////
	// TextureShader //
	///////////////////
	// Create TextureShader object.
	m_TextureShader = new TextureShaderClass;
	if(!m_TextureShader)
	{
		return false;
	}

	// Initialize the TextureShader object.
	result = m_TextureShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the TextureShader object.", L"Error", MB_OK);
		return false;
	}

	////////////////////////
	// VerticalBlurShader //
	////////////////////////
	// Create VerticalBlurShader object.
	m_VerticalBlurShader = new VerticalBlurShaderClass;
	if(!m_VerticalBlurShader)
	{
		return false;
	}

	// Initialize the VerticalBlurShader object.
	result = m_VerticalBlurShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the VerticalBlurShader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}

void ShaderManagerClass::Shutdown()
{
	// Release the ColorShader object.
	if(m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}

	// Release the AlphaMapShader object.
	if(m_AlphaMapShader)
	{
		m_AlphaMapShader->Shutdown();
		delete m_AlphaMapShader;
		m_AlphaMapShader = 0;
	}

	// Release the BumpMapShader object.
	if(m_BumpMapShader)
	{
		m_BumpMapShader->Shutdown();
		delete m_BumpMapShader;
		m_BumpMapShader = 0;
	}

	// Release the DepthShader object.
	if(m_DepthShader)
	{
		m_DepthShader->Shutdown();
		delete m_DepthShader;
		m_DepthShader = 0;
	}

	// Release the HorizontalBlurShader object.
	if(m_HorizontalBlurShader)
	{
		m_HorizontalBlurShader->Shutdown();
		delete m_HorizontalBlurShader;
		m_HorizontalBlurShader = 0;
	}

	// Release the LightShader object.
	if(m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	// Release the MultiTextureShader object.
	if(m_MultiTextureShader)
	{
		m_MultiTextureShader->Shutdown();
		delete m_MultiTextureShader;
		m_MultiTextureShader = 0;
	}

	// Release the ShadowShader object.
	if(m_ShadowShader)
	{
		m_ShadowShader->Shutdown();
		delete m_ShadowShader;
		m_ShadowShader = 0;
	}

	// Release the SoftShadowShader object.
	if(m_SoftShadowShader)
	{
		m_SoftShadowShader->Shutdown();
		delete m_SoftShadowShader;
		m_SoftShadowShader = 0;
	}

	// Release the SpecMapShader object.
	if(m_SpecMapShader)
	{
		m_SpecMapShader->Shutdown();
		delete m_SpecMapShader;
		m_SpecMapShader = 0;
	}

	// Release the TextureShader object.
	if(m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	// Release the VerticalBlurShader object.
	if(m_VerticalBlurShader)
	{
		m_VerticalBlurShader->Shutdown();
		delete m_VerticalBlurShader;
		m_VerticalBlurShader = 0;
	}

	return;
}

bool ShaderManagerClass::RenderColorShader(ID3D11DeviceContext* deviceContext, 
										   int indexCount, 
										   D3DXMATRIX worldMatrix, 
										   D3DXMATRIX viewMatrix, 
										   D3DXMATRIX projectionMatrix)
{
	bool result;

	// Render the model using ColorShader.
	result = m_ColorShader->Render(deviceContext, 
								   indexCount, 
								   worldMatrix, 
								   viewMatrix, 
								   projectionMatrix);
	if(!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderAlphaMapShader(ID3D11DeviceContext* deviceContext, 
											  int indexCount, 
											  D3DXMATRIX worldMatrix, 
											  D3DXMATRIX viewMatrix, 
											  D3DXMATRIX projectionMatrix, 
											  ID3D11ShaderResourceView** textureArray)
{
	bool result;

	// Render the model using AlphaMapShader.
	result = m_AlphaMapShader->Render(deviceContext, 
									  indexCount, 
									  worldMatrix, 
									  viewMatrix, 
									  projectionMatrix, 
									  textureArray);
	if(!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderBumpMapShader(ID3D11DeviceContext* deviceContext, 
											 int indexCount, 
											 D3DXMATRIX worldMatrix, 
											 D3DXMATRIX viewMatrix, 
											 D3DXMATRIX projectionMatrix, 
											 ID3D11ShaderResourceView** textureArray, 
											 D3DXVECTOR3 lightDirection,
											 D3DXVECTOR4 diffuseColor)
{
	bool result;

	// Render the model using BumpMapShader.
	result = m_BumpMapShader->Render(deviceContext, 
									 indexCount, 
									 worldMatrix, 
									 viewMatrix, 
									 projectionMatrix, 
									 textureArray, 
									 lightDirection, 
									 diffuseColor);
	if(!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderDepthShader(ID3D11DeviceContext* deviceContext, 
										   int indexCount, 
										   D3DXMATRIX worldMatrix, 
										   D3DXMATRIX viewMatrix, 
										   D3DXMATRIX projectionMatrix)
{
	bool result;

	// Render the model using DepthShader.
	result = m_DepthShader->Render(deviceContext, 
								   indexCount, 
								   worldMatrix, 
								   viewMatrix, 
								   projectionMatrix);
	if(!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderHorizontalBlurShader(ID3D11DeviceContext* deviceContext, 
													int indexCount, 
													D3DXMATRIX worldMatrix, 
													D3DXMATRIX viewMatrix, 
													D3DXMATRIX projectionMatrix, 
													ID3D11ShaderResourceView* texture, 
													float screenWidth)
{
	bool result;

	// Render the model using HorizontalBlurShader.
	result = m_HorizontalBlurShader->Render(deviceContext, 
											indexCount, 
											worldMatrix, 
											viewMatrix, 
											projectionMatrix,
											texture,
											screenWidth);
	if(!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderLightShader(ID3D11DeviceContext* deviceContext, 
										   int indexCount, 
										   D3DXMATRIX worldMatrix, 
										   D3DXMATRIX viewMatrix, 
										   D3DXMATRIX projectionMatrix, 
										   ID3D11ShaderResourceView* texture, 
										   D3DXVECTOR3 lightDirection, 
										   D3DXVECTOR4 ambientColor,
										   D3DXVECTOR4 diffuseColor, 
										   D3DXVECTOR3 cameraPosition, 
										   D3DXVECTOR4 specularColor, 
										   float specularPower)
{
	bool result;

	// Render the model using LightShader.
	result = m_LightShader->Render(deviceContext, 
								   indexCount, 
								   worldMatrix, 
								   viewMatrix, 
								   projectionMatrix, 
								   texture, 
								   lightDirection, 
								   ambientColor, 
								   diffuseColor, 
								   cameraPosition, 
								   specularColor, 
								   specularPower);
	if(!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderMultiTextureShader(ID3D11DeviceContext* deviceContext, 
												  int indexCount, 
												  D3DXMATRIX worldMatrix, 
												  D3DXMATRIX viewMatrix, 
												  D3DXMATRIX projectionMatrix, 
												  ID3D11ShaderResourceView** textureArray)
{
	bool result;

	// Render the model using MultiTextureShader.
	result = m_MultiTextureShader->Render(deviceContext, 
										  indexCount, 
										  worldMatrix, 
										  viewMatrix, 
										  projectionMatrix, 
										  textureArray);
	if(!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderShadowShader(ID3D11DeviceContext* deviceContext, 
											int indexCount, 
											D3DXMATRIX worldMatrix, 
											D3DXMATRIX viewMatrix, 
											D3DXMATRIX projectionMatrix, 
											D3DXMATRIX lightViewMatrix, 
											D3DXMATRIX lightProjectionMatrix, 
											ID3D11ShaderResourceView* depthMapTexture, 
											D3DXVECTOR3 lightPosition)
{
	bool result;

	// Render the model using ShadowShader.
	result = m_ShadowShader->Render(deviceContext, 
									indexCount, 
									worldMatrix, 
									viewMatrix, 
									projectionMatrix, 
									lightViewMatrix, 
									lightProjectionMatrix, 
									depthMapTexture, 
									lightPosition);
	if(!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderSoftShadowShader(ID3D11DeviceContext* deviceContext, 
												int indexCount, 
												D3DXMATRIX worldMatrix, 
												D3DXMATRIX viewMatrix, 
												D3DXMATRIX projectionMatrix, 
												ID3D11ShaderResourceView* texture, 
												ID3D11ShaderResourceView* shadowTexture, 
												D3DXVECTOR3 lightPosition, 
												D3DXVECTOR4 ambientColor, 
												D3DXVECTOR4 diffuseColor)
{
	bool result;

	// Render the model using SoftShadowShader.
	result = m_SoftShadowShader->Render(deviceContext, 
										indexCount, 
										worldMatrix, 
										viewMatrix, 
										projectionMatrix, 
										texture, 
										shadowTexture, 
										lightPosition, 
										ambientColor, 
										diffuseColor);
	if(!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderSpecMapShader(ID3D11DeviceContext* deviceContext, 
											 int indexCount, 
											 D3DXMATRIX worldMatrix, 
											 D3DXMATRIX viewMatrix, 
											 D3DXMATRIX projectionMatrix, 
											 ID3D11ShaderResourceView** textureArray, 
											 D3DXVECTOR3 lightDirection,
											 D3DXVECTOR4 diffuseColor, 
											 D3DXVECTOR3 cameraPosition, 
											 D3DXVECTOR4 specularColor, 
											 float specularPower)
{
	bool result;

	// Render the model using SpecMapShader.
	result = m_SpecMapShader->Render(deviceContext, 
									 indexCount, 
									 worldMatrix, 
									 viewMatrix, 
									 projectionMatrix, 
									 textureArray, 
									 lightDirection, 
									 diffuseColor, 
									 cameraPosition, 
									 specularColor, 
									 specularPower);
	if(!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderTextureShader(ID3D11DeviceContext* deviceContext, 
											 int indexCount, 
											 D3DXMATRIX worldMatrix, 
											 D3DXMATRIX viewMatrix, 
											 D3DXMATRIX projectionMatrix, 
											 ID3D11ShaderResourceView* texture)
{
	bool result;

	// Render the model using TextureShader.
	result = m_TextureShader->Render(deviceContext, 
									 indexCount, 
									 worldMatrix, 
									 viewMatrix, 
									 projectionMatrix, 
									 texture);
	if(!result)
	{
		return false;
	}

	return true;
}

bool ShaderManagerClass::RenderVerticalBlurShader(ID3D11DeviceContext* deviceContext, 
												  int indexCount, 
												  D3DXMATRIX worldMatrix, 
												  D3DXMATRIX viewMatrix, 
												  D3DXMATRIX projectionMatrix, 
												  ID3D11ShaderResourceView* texture, 
												  float screenHeight)
{
	bool result;

	// Render the model using VerticalBlurShader.
	result = m_VerticalBlurShader->Render(deviceContext, 
										  indexCount, 
										  worldMatrix, 
										  viewMatrix, 
										  projectionMatrix,
										  texture,
										  screenHeight);
	if(!result)
	{
		return false;
	}

	return true;
}

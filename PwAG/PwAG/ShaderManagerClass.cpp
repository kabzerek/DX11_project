#include "ShaderManagerClass.h"


ShaderManagerClass::ShaderManagerClass(void)
{
	m_AlphaMapShader = 0;
	m_BumpMapShader = 0;
	m_DepthShader = 0;
	m_LightShader = 0;
	m_MultiTextureShader = 0;
	m_ShadowShader = 0;
	m_SoftShadowShader = 0;
	m_SpecMapShader = 0;
	m_TextureShader = 0;
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
}

void ShaderManagerClass::Shutdown()
{
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

	return;
}
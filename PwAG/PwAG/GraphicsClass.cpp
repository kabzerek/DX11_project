#include "GraphicsClass.h"


GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	//m_Model = 0;
	//m_LightShader = 0;
	m_Light = 0;	
	//m_MultiTextureShader = 0;
	//m_AlphaMapShader = 0;
	//m_BumpMapShader = 0;
	m_SpecMapShader = 0;
	m_RenderTexture = 0;
	//m_DebugWindow = 0;
	//m_TextureShader = 0;
	m_DepthShader = 0;	
	m_ShadowShader = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;


	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -50.0f);
	
	// Create the model object.

	//result = m_Model->Initialize(m_D3D->GetDevice(), "data/square.DAE", L"data/stone01.dds", 
	//			     L"data/dirt01.dds", L"data/alpha01.dds");

	ModelClass* box1 = new ModelClass;
	if(!box1)
	{
		return false;
	}
	// Initialize the model object.
	result = box1->Initialize(m_D3D->GetDevice(), "../PwAG/data/cube.DAE", L"../PwAG/data/stone02.dds", 
												  L"../PwAG/data/bump02.dds", L"../PwAG/data/spec02.dds",
												  aiVector3D(-4.0f, 0.0f, 0.0f));
	
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_Models.push_back(box1);

	ModelClass* box2 = new ModelClass;
	if(!box2)
	{
		return false;
	}
	// Initialize the model object.
	result = box2->Initialize(m_D3D->GetDevice(), "../PwAG/data/sphere.DAE", L"../PwAG/data/stone02.dds", 
												  L"../PwAG/data/bump02.dds", L"../PwAG/data/spec02.dds",
												  aiVector3D(1.25f, 0.50f, 0.5f));
	
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_Models.push_back(box2);

	ModelClass* box3 = new ModelClass;
	if(!box3)
	{
		return false;
	}
	// Initialize the model object.
	result = box3->Initialize(m_D3D->GetDevice(), "../PwAG/data/cube.DAE", L"../PwAG/data/stone02.dds", 
												  L"../PwAG/data/bump02.dds", L"../PwAG/data/spec02.dds",
												  aiVector3D(0.0f, 0.0f, 0.0f));
	
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_Models.push_back(box3);

	ModelClass* grnd = new ModelClass;
	if(!grnd)
	{
		return false;
	}
	// Initialize the model object.
	result = grnd->Initialize(m_D3D->GetDevice(), "../PwAG/data/scene1.DAE", L"../PwAG/data/stone01.dds", 
												  L"../PwAG/data/bump02.dds", L"../PwAG/data/spec02.dds",
												  aiVector3D(0.0f, 0.0f, 0.0f));
	
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_Models.push_back(grnd);

	// Create the specular map shader object.
	m_SpecMapShader = new SpecMapShaderClass;
	if(!m_SpecMapShader)
	{
		return false;
	}
	// Initialize the specular map shader object.
	result = m_SpecMapShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the specular map shader object.", L"Error", MB_OK);
		return false;
	}

	//// Create the bump map shader object.
	//m_BumpMapShader = new BumpMapShaderClass;
	//if(!m_BumpMapShader)
	//{
	//	return false;
	//}

	//// Initialize the bump map shader object.
	//result = m_BumpMapShader->Initialize(m_D3D->GetDevice(), hwnd);
	//if(!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the bump map shader object.", L"Error", MB_OK);
	//	return false;
	//}


	//// Create the alpha map shader object.
	//m_AlphaMapShader = new AlphaMapShaderClass;
	//if(!m_AlphaMapShader)
	//{
	//	return false;
	//}

	//// Initialize the alpha map shader object.
	//result = m_AlphaMapShader->Initialize(m_D3D->GetDevice(), hwnd);
	//if(!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the alpha map shader object.", L"Error", MB_OK);
	//	return false;
	//}

	// Create the multitexture shader object.
	//m_MultiTextureShader = new MultiTextureShaderClass;
	//if(!m_MultiTextureShader)
	//{
	//	return false;
	//}

	//// Initialize the multitexture shader object.
	//result = m_MultiTextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	//if(!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the multitexture shader object.", L"Error", MB_OK);
	//	return false;
	//}
	
	// Create the render to texture object.
	m_RenderTexture = new RenderTextureClass;
	if(!m_RenderTexture)
	{
		return false;
	}

	// Initialize the render to texture object.
	result = m_RenderTexture->Initialize(m_D3D->GetDevice(), SHADOWMAP_WIDTH, SHADOWMAP_HEIGHT, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		return false;
	}

	// Create the debug window object.
	//m_DebugWindow = new DebugWindowClass;
	//if(!m_DebugWindow)
	//{
	//	return false;
	//}

	//// Initialize the debug window object.
	//result = m_DebugWindow->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, 100, 100);
	//if(!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the debug window object.", L"Error", MB_OK);
	//	return false;
	//}

	//// Create the texture shader object.
	//m_TextureShader = new TextureShaderClass;
	//if(!m_TextureShader)
	//{
	//	return false;
	//}

	//// Initialize the texture shader object.
	//result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	//if(!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
	//	return false;
	//}

	//// Create the light shader object.
	//m_LightShader = new LightShaderClass;
	//if(!m_LightShader)
	//{
	//	return false;
	//}

	//// Initialize the light shader object.
	//result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	//if(!result)
	//{
	//	MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
	//	return false;
	//}

	//Create the light object.
	m_Light = new LightClass;
	if(!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	// Initialize the light object.
	//m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(0.0f, 0.0f, 1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(16.0f);

	m_Light->SetLookAt(0.0f, 0.0f, 0.0f);
	m_Light->GenerateProjectionMatrix(SCREEN_DEPTH, SCREEN_NEAR);

	// Create the render to texture object.
	m_RenderTexture = new RenderTextureClass;
	if(!m_RenderTexture)
	{
		return false;
	}

	// Initialize the render to texture object.
	result = m_RenderTexture->Initialize(m_D3D->GetDevice(), SHADOWMAP_WIDTH, SHADOWMAP_HEIGHT, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the render to texture object.", L"Error", MB_OK);
		return false;
	}

	// Create the depth shader object.
	m_DepthShader = new DepthShaderClass;
	if(!m_DepthShader)
	{
		return false;
	}

	// Initialize the depth shader object.
	result = m_DepthShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the depth shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the shadow shader object.
	m_ShadowShader = new ShadowShaderClass;
	if(!m_ShadowShader)
	{
		return false;
	}

	// Initialize the shadow shader object.
	result = m_ShadowShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the shadow shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the specular map shader object.
	if(m_SpecMapShader)
	{
		m_SpecMapShader->Shutdown();
		delete m_SpecMapShader;
		m_SpecMapShader = 0;
	}
		// Release the shadow shader object.
	if(m_ShadowShader)
	{
		m_ShadowShader->Shutdown();
		delete m_ShadowShader;
		m_ShadowShader = 0;
	}

	// Release the depth shader object.
	if(m_DepthShader)
	{
		m_DepthShader->Shutdown();
		delete m_DepthShader;
		m_DepthShader = 0;
	}

	// Release the render to texture object.
	if(m_RenderTexture)
	{
		m_RenderTexture->Shutdown();
		delete m_RenderTexture;
		m_RenderTexture = 0;
	}
	//// Release the texture shader object.
	//if(m_TextureShader)
	//{
	//	m_TextureShader->Shutdown();
	//	delete m_TextureShader;
	//	m_TextureShader = 0;
	//}

	//// Release the debug window object.
	//if(m_DebugWindow)
	//{
	//	m_DebugWindow->Shutdown();
	//	delete m_DebugWindow;
	//	m_DebugWindow = 0;
	//}

	// Release the render to texture object.
	if(m_RenderTexture)
	{
		m_RenderTexture->Shutdown();
		delete m_RenderTexture;
		m_RenderTexture = 0;
	}

	// Release the bump map shader object.
	//if(m_BumpMapShader)
	//{
	//	m_BumpMapShader->Shutdown();
	//	delete m_BumpMapShader;
	//	m_BumpMapShader = 0;
	//}

	// Release the alpha map shader object.
	//if(m_AlphaMapShader)
	//{
	//	m_AlphaMapShader->Shutdown();
	//	delete m_AlphaMapShader;
	//	m_AlphaMapShader = 0;
	//}

	// Release the multitexture shader object.
	//if(m_MultiTextureShader)
	//{
	//	m_MultiTextureShader->Shutdown();
	//	delete m_MultiTextureShader;
	//	m_MultiTextureShader = 0;
	//}

	// Release the light object.
	//if(m_Light)
	//{
	//	delete m_Light;
	//	m_Light = 0;
	//}

	//// Release the light shader object.
	//if(m_LightShader)
	//{
	//	m_LightShader->Shutdown();
	//	delete m_LightShader;
	//	m_LightShader = 0;
	//}

	// Release the model objects.
	std::vector<ModelClass*>::iterator it;
	for(it = m_Models.begin(); it != m_Models.end(); ++it)
	{
		if((*it))
		{
			(*it)->Shutdown();
			delete (*it);
			(*it) = 0;
		}
	}
	m_Models.clear();

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;
}


bool GraphicsClass::Frame(float posX, float posY, float posZ, float rotX, float rotY, float rotZ)
{
	bool result;
	static float lightPositionX = -5.0f;


	// Set the position of the camera.
	m_Camera->SetPosition(posX, posY, posZ);
	m_Camera->SetRotation(rotX, rotY, rotZ);

	// Update the position of the light each frame.
	lightPositionX += 0.05f;
	if(lightPositionX > 5.0f)
	{
		lightPositionX = -5.0f;
	}

	// Update the position of the light.
	m_Light->SetPosition(lightPositionX, 8.0f, -5.0f);
	
	// Render the graphics scene.
	result = Render();
	if(!result)
	{
		return false;
	}

	return true;
}


bool GraphicsClass::RenderSceneToTexture()
{
	D3DXMATRIX worldMatrix, lightViewMatrix, lightProjectionMatrix, translateMatrix;
	float posX, posY, posZ;
	bool result;


	// Set the render target to be the render to texture.
	m_RenderTexture->SetRenderTarget(m_D3D->GetDeviceContext());

	// Clear the render to texture.
	m_RenderTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the light view matrix based on the light's position.
	m_Light->GenerateViewMatrix();

	// Get the world matrix from the d3d object.
	m_D3D->GetWorldMatrix(worldMatrix);

	// Get the view and orthographic matrices from the light object.
	m_Light->GetViewMatrix(lightViewMatrix);
	m_Light->GetProjectionMatrix(lightProjectionMatrix);

	std::vector<ModelClass*>::iterator it;
	for(it = m_Models.begin(); it != m_Models.end(); ++it)
	{
		// Setup the translation matrix for the cube model.
		(*it)->GetPosition(posX, posY, posZ);
		D3DXMatrixTranslation(&worldMatrix, posX, posY, posZ);

		// Render the model with the depth shader.
		(*it)->Render(m_D3D->GetDeviceContext());
		result = m_DepthShader->Render(m_D3D->GetDeviceContext(), (*it)->GetIndexCount(), worldMatrix, lightViewMatrix, lightProjectionMatrix);
		if(!result)
		{
			return false;
		}

		// Reset the world matrix.
		m_D3D->GetWorldMatrix(worldMatrix);
	}

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_D3D->SetBackBufferRenderTarget();

	// Reset the viewport back to the original.
	m_D3D->ResetViewport();

	return true;
}


bool GraphicsClass::Render()
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, translateMatrix;
	D3DXMATRIX lightViewMatrix, lightProjectionMatrix;
	bool result;
	float posX, posY, posZ;

	// First render the scene to a texture.
	result = RenderSceneToTexture();
	if(!result)
	{
		return false;
	}

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Generate the light view matrix based on the light's position.
	m_Light->GenerateViewMatrix();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// Get the light's view and projection matrices from the light object.
	m_Light->GetViewMatrix(lightViewMatrix);
	m_Light->GetProjectionMatrix(lightProjectionMatrix);

	std::vector<ModelClass*>::iterator it;
	for(it = m_Models.begin(); it != m_Models.end(); ++it)
	{
		// Setup the translation matrix for the cube model.
		(*it)->GetPosition(posX, posY, posZ);
		D3DXMatrixTranslation(&worldMatrix, posX, posY, posZ);
	
		// Put the cube model vertex and index buffers on the graphics pipeline to prepare them for drawing.
		//m_Model->Render(m_D3D->GetDeviceContext());

		(*it)->Render(m_D3D->GetDeviceContext());

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
		//result = m_ShadowShader->Render(m_D3D->GetDeviceContext(), m_CubeModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, lightViewMatrix, 
        //            lightProjectionMatrix, m_RenderTexture->GetShaderResourceView(), m_Light->GetPosition());

		//if(!result)
		//{
		//	return false;
		//}
	
	
		// Reset the world matrix.
		m_D3D->GetWorldMatrix(worldMatrix);
	}

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}
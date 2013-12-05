#include "GraphicsClass.h"


GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	//m_Model = 0;
	m_Light = 0;	
	m_RenderTexture = 0;
	//m_DebugWindow = 0;

	m_ShaderManager = 0;

	m_BlackWhiteRenderTexture = 0;
	m_DownSampleTexure = 0;
	m_SmallWindow = 0;
	m_HorizontalBlurTexture = 0;
	m_VerticalBlurTexture = 0;
	m_UpSampleTexure = 0;
	m_FullScreenWindow = 0;
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
	int downSampleWidth, downSampleHeight;

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

	// Create the shader manager object.
	m_ShaderManager = new ShaderManagerClass;
	if(!m_ShaderManager)
	{
		return false;
	}

	// Initialize the shader manager object.
	result = m_ShaderManager->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the shader manager object.", L"Error", MB_OK);
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

	//Create the light object.
	m_Light = new LightClass;
	if(!m_Light)
	{
		return false;
	}

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

	// Create the black and white render to texture object.
	m_BlackWhiteRenderTexture = new RenderTextureClass;
	if(!m_BlackWhiteRenderTexture)
	{
		return false;
	}

	// Initialize the black and white render to texture object.
	result = m_BlackWhiteRenderTexture->Initialize(m_D3D->GetDevice(), SHADOWMAP_WIDTH, SHADOWMAP_HEIGHT, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the black and white render to texture object.", L"Error", MB_OK);
		return false;
	}

	// Set the size to sample down to.
	downSampleWidth = SHADOWMAP_WIDTH / 2;
	downSampleHeight = SHADOWMAP_HEIGHT / 2;

	// Create the down sample render to texture object.
	m_DownSampleTexure = new RenderTextureClass;
	if(!m_DownSampleTexure)
	{
		return false;
	}

	// Initialize the down sample render to texture object.
	result = m_DownSampleTexure->Initialize(m_D3D->GetDevice(), downSampleWidth, downSampleHeight, 100.0f, 1.0f);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the down sample render to texture object.", L"Error", MB_OK);
		return false;
	}

	// Create the small ortho window object.
	m_SmallWindow = new OrthoWindowClass;
	if(!m_SmallWindow)
	{
		return false;
	}

	// Initialize the small ortho window object.
	result = m_SmallWindow->Initialize(m_D3D->GetDevice(), downSampleWidth, downSampleHeight);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the small ortho window object.", L"Error", MB_OK);
		return false;
	}

	// Create the horizontal blur render to texture object.
	m_HorizontalBlurTexture = new RenderTextureClass;
	if(!m_HorizontalBlurTexture)
	{
		return false;
	}

	// Initialize the horizontal blur render to texture object.
	result = m_HorizontalBlurTexture->Initialize(m_D3D->GetDevice(), downSampleWidth, downSampleHeight, SCREEN_DEPTH, 0.1f);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the horizontal blur render to texture object.", L"Error", MB_OK);
		return false;
	}

	// Create the vertical blur render to texture object.
	m_VerticalBlurTexture = new RenderTextureClass;
	if(!m_VerticalBlurTexture)
	{
		return false;
	}

	// Initialize the vertical blur render to texture object.
	result = m_VerticalBlurTexture->Initialize(m_D3D->GetDevice(), downSampleWidth, downSampleHeight, SCREEN_DEPTH, 0.1f);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the vertical blur render to texture object.", L"Error", MB_OK);
		return false;
	}

	// Create the up sample render to texture object.
	m_UpSampleTexure = new RenderTextureClass;
	if(!m_UpSampleTexure)
	{
		return false;
	}

	// Initialize the up sample render to texture object.
	result = m_UpSampleTexure->Initialize(m_D3D->GetDevice(), SHADOWMAP_WIDTH, SHADOWMAP_HEIGHT, SCREEN_DEPTH, 0.1f);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the up sample render to texture object.", L"Error", MB_OK);
		return false;
	}

	// Create the full screen ortho window object.
	m_FullScreenWindow = new OrthoWindowClass;
	if(!m_FullScreenWindow)
	{
		return false;
	}

	// Initialize the full screen ortho window object.
	result = m_FullScreenWindow->Initialize(m_D3D->GetDevice(), SHADOWMAP_WIDTH, SHADOWMAP_HEIGHT);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the full screen ortho window object.", L"Error", MB_OK);
		return false;
	}

	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the full screen ortho window object.
	if(m_FullScreenWindow)
	{
		m_FullScreenWindow->Shutdown();
		delete m_FullScreenWindow;
		m_FullScreenWindow = 0;
	}

	// Release the up sample render to texture object.
	if(m_UpSampleTexure)
	{
		m_UpSampleTexure->Shutdown();
		delete m_UpSampleTexure;
		m_UpSampleTexure = 0;
	}

	// Release the vertical blur render to texture object.
	if(m_VerticalBlurTexture)
	{
		m_VerticalBlurTexture->Shutdown();
		delete m_VerticalBlurTexture;
		m_VerticalBlurTexture = 0;
	}

	// Release the horizontal blur render to texture object.
	if(m_HorizontalBlurTexture)
	{
		m_HorizontalBlurTexture->Shutdown();
		delete m_HorizontalBlurTexture;
		m_HorizontalBlurTexture = 0;
	}

	// Release the down sample render to texture object.
	if(m_DownSampleTexure)
	{
		m_DownSampleTexure->Shutdown();
		delete m_DownSampleTexure;
		m_DownSampleTexure = 0;
	}

	// Release the black and white render to texture.
	if(m_BlackWhiteRenderTexture)
	{
		m_BlackWhiteRenderTexture->Shutdown();
		delete m_BlackWhiteRenderTexture; 
		m_BlackWhiteRenderTexture = 0;
	}
	// Release the render to texture object.
	if(m_RenderTexture)
	{
		m_RenderTexture->Shutdown();
		delete m_RenderTexture;
		m_RenderTexture = 0;
	}

	// Release the light object.
	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

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

	// Release the shader manager object.
	if(m_ShaderManager)
	{
		m_ShaderManager->Shutdown();
		delete m_ShaderManager;
		m_ShaderManager = 0;
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
	static bool side = false;
	static float lightPositionX = -5.0f;


	// Set the position of the camera.
	m_Camera->SetPosition(posX, posY, posZ);
	m_Camera->SetRotation(rotX, rotY, rotZ);

	// Update the position of the light each frame.
	if (side)
			lightPositionX -= 0.05f;
	else
			lightPositionX += 0.05f;

	
	if(side && (lightPositionX <= -5.0f))
	{
		side = !side;
	}
	else if(!side && (lightPositionX >= 5.0f))
	{
		side = !side;
	}
	// Update the position of the light.
	m_Light->SetPosition(lightPositionX, 7.0f, -5.0f);
	
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
		result = m_ShaderManager->RenderDepthShader(m_D3D->GetDeviceContext(), (*it)->GetIndexCount(), worldMatrix, lightViewMatrix, lightProjectionMatrix);
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

bool GraphicsClass::RenderBlackAndWhiteShadows()
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, translateMatrix;
	D3DXMATRIX lightViewMatrix, lightProjectionMatrix;
	float posX, posY, posZ;
	bool result;


	// Set the render target to be the render to texture.
	m_BlackWhiteRenderTexture->SetRenderTarget(m_D3D->GetDeviceContext());

	// Clear the render to texture.
	m_BlackWhiteRenderTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

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

		// Render the model with the depth shader.
		(*it)->Render(m_D3D->GetDeviceContext());
		result = m_ShaderManager->RenderShadowShader(m_D3D->GetDeviceContext(), (*it)->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, lightViewMatrix,
					lightProjectionMatrix, m_RenderTexture->GetShaderResourceView(), m_Light->GetPosition());
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

bool GraphicsClass::DownSampleTexture()
{
	D3DXMATRIX worldMatrix, baseViewMatrix, orthoMatrix;
	bool result;

	// Set the render target to be the render to texture.
	m_DownSampleTexure->SetRenderTarget(m_D3D->GetDeviceContext());

	// Clear the render to texture.
	m_DownSampleTexure->ClearRenderTarget(m_D3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world and view matrices from the camera and d3d objects.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetBaseViewMatrix(baseViewMatrix);
	
	// Get the ortho matrix from the render to texture since texture has different dimensions being that it is smaller.
	m_DownSampleTexure->GetOrthoMatrix(orthoMatrix);

	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();

	// Put the small ortho window vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_SmallWindow->Render(m_D3D->GetDeviceContext());

	// Render the small ortho window using the texture shader and the render to texture of the scene as the texture resource.
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_SmallWindow->GetIndexCount(), worldMatrix, baseViewMatrix, orthoMatrix, 
									 m_BlackWhiteRenderTexture->GetShaderResourceView());
	if(!result)
	{
		return false;
	}

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();
	
	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_D3D->SetBackBufferRenderTarget();

	// Reset the viewport back to the original.
	m_D3D->ResetViewport();

	return true;
}

bool GraphicsClass::RenderHorizontalBlurToTexture()
{
	D3DXMATRIX worldMatrix, baseViewMatrix, orthoMatrix;
	float screenSizeX;
	bool result;


	// Store the screen width in a float that will be used in the horizontal blur shader.
	screenSizeX = (float)(SHADOWMAP_WIDTH / 2);
	
	// Set the render target to be the render to texture.
	m_HorizontalBlurTexture->SetRenderTarget(m_D3D->GetDeviceContext());

	// Clear the render to texture.
	m_HorizontalBlurTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world and view matrices from the camera and d3d objects.
	m_Camera->GetBaseViewMatrix(baseViewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);

	// Get the ortho matrix from the render to texture since texture has different dimensions.
	m_HorizontalBlurTexture->GetOrthoMatrix(orthoMatrix);

	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();

	// Put the small ortho window vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_SmallWindow->Render(m_D3D->GetDeviceContext());
	
	// Render the small ortho window using the horizontal blur shader and the down sampled render to texture resource.
	result = m_ShaderManager->RenderHorizontalBlurShader(m_D3D->GetDeviceContext(), m_SmallWindow->GetIndexCount(), worldMatrix, baseViewMatrix, orthoMatrix,
						m_DownSampleTexure->GetShaderResourceView(), screenSizeX);
	if(!result)
	{
		return false;
	}

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_D3D->SetBackBufferRenderTarget();

	// Reset the viewport back to the original.
	m_D3D->ResetViewport();
	
	return true;
}

bool GraphicsClass::RenderVerticalBlurToTexture()
{
	D3DXMATRIX worldMatrix, baseViewMatrix, orthoMatrix;
	float screenSizeY;
	bool result;


	// Store the screen height in a float that will be used in the vertical blur shader.
	screenSizeY = (float)(SHADOWMAP_HEIGHT / 2);

	// Set the render target to be the render to texture.
	m_VerticalBlurTexture->SetRenderTarget(m_D3D->GetDeviceContext());

	// Clear the render to texture.
	m_VerticalBlurTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world and view matrices from the camera and d3d objects.
	m_Camera->GetBaseViewMatrix(baseViewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);

	// Get the ortho matrix from the render to texture since texture has different dimensions.
	m_VerticalBlurTexture->GetOrthoMatrix(orthoMatrix);

	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();

	// Put the small ortho window vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_SmallWindow->Render(m_D3D->GetDeviceContext());
	
	// Render the small ortho window using the vertical blur shader and the horizontal blurred render to texture resource.
	result = m_ShaderManager->RenderVerticalBlurShader(m_D3D->GetDeviceContext(), m_SmallWindow->GetIndexCount(), worldMatrix, baseViewMatrix, orthoMatrix,
					      m_HorizontalBlurTexture->GetShaderResourceView(), screenSizeY);
	if(!result)
	{
		return false;
	}

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_D3D->SetBackBufferRenderTarget();

	// Reset the viewport back to the original.
	m_D3D->ResetViewport();
	
	return true;
}

bool GraphicsClass::UpSampleTexture()
{
	D3DXMATRIX worldMatrix, baseViewMatrix, orthoMatrix;
	bool result;


	// Set the render target to be the render to texture.
	m_UpSampleTexure->SetRenderTarget(m_D3D->GetDeviceContext());

	// Clear the render to texture.
	m_UpSampleTexure->ClearRenderTarget(m_D3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world and view matrices from the camera and d3d objects.
	m_Camera->GetBaseViewMatrix(baseViewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);

	// Get the ortho matrix from the render to texture since texture has different dimensions.
	m_UpSampleTexure->GetOrthoMatrix(orthoMatrix);

	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();

	// Put the full screen ortho window vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_FullScreenWindow->Render(m_D3D->GetDeviceContext());

	// Render the full screen ortho window using the texture shader and the small sized final blurred render to texture resource.
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_FullScreenWindow->GetIndexCount(), worldMatrix, baseViewMatrix, orthoMatrix,
					 m_VerticalBlurTexture->GetShaderResourceView());
	if(!result)
	{
		return false;
	}

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();
	
	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_D3D->SetBackBufferRenderTarget();

	// Reset the viewport back to the original.
	m_D3D->ResetViewport();

	return true;
}

bool GraphicsClass::Render2DTextureScene()
{
	D3DXMATRIX worldMatrix, viewMatrix, orthoMatrix;
	bool result;


	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(1.0f, 0.0f, 0.0f, 0.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and ortho matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);

	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();

	// Put the full screen ortho window vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_FullScreenWindow->Render(m_D3D->GetDeviceContext());

	// Render the full screen ortho window using the texture shader and the full screen sized blurred render to texture resource.
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_FullScreenWindow->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, 
					 m_UpSampleTexure->GetShaderResourceView());
	if(!result)
	{
		return false;
	}

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();
	
	// Present the rendered scene to the screen.
	m_D3D->EndScene();

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

	// Next render the shadowed scene in black and white.
	result = RenderBlackAndWhiteShadows();
	if(!result)
	{
		return false;
	}

	// Then down sample the black and white scene texture.
	result = DownSampleTexture();
	if(!result)
	{
		return false;
	}

	// Perform a horizontal blur on the down sampled texture.
	result = RenderHorizontalBlurToTexture();
	if(!result)
	{
		return false;
	}

	// Now perform a vertical blur on the texture.
	result = RenderVerticalBlurToTexture();
	if(!result)
	{
		return false;
	}

	// Finally up sample the final blurred render to texture that can now be used in the soft shadow shader.
	result = UpSampleTexture();
	if(!result)
	{
		return false;
	}


	//// Render the blurred up sampled render texture to the screen.
	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Generate the light view matrix based on the light's position.
	//m_Light->GenerateViewMatrix();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// Get the light's view and projection matrices from the light object.
	//m_Light->GetProjectionMatrix(lightProjectionMatrix);

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
		result = m_ShaderManager->RenderSpecMapShader(m_D3D->GetDeviceContext(), (*it)->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
				(*it)->GetTextureArray(), m_Light->GetDirection(), m_Light->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

		if(!result)
		{
			return false;
		}		
		
		// Render the model using the shadow shader.
		//result = m_ShadowManager->RenderSoftShadowShader(m_D3D->GetDeviceContext(), (*it)->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		//					m_Light->GetAmbientColor(), m_Light->GetDiffuseColor());
		if(!result)
		{
			return false;
		}
	
	
		// Reset the world matrix.
		m_D3D->GetWorldMatrix(worldMatrix);
	}
	// Present the rendered scene to the screen.
	m_D3D->EndScene();
	

	return true;
}
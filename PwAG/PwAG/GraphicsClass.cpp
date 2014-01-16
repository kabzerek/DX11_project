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
	m_DownSampleTexture = 0;
	m_SmallWindow = 0;
	m_HorizontalBlurTexture = 0;
	m_VerticalBlurTexture = 0;
	m_UpSampleTexture = 0;
	m_FullScreenWindow = 0;
	m_Text = 0;

	m_dynamicsWorld = 0;

	m_debugMode = btIDebugDraw::DBG_NoDebug;
	bool m_isDebug = false;
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
	D3DXMATRIX baseViewMatrix;
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

	// Initialize a base view matrix with the camera for 2D user interface rendering.
	m_Camera->SetPosition(0.0f, 0.0f, -15.0f);
	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -20.0f);
	m_Camera->RenderBaseViewMatrix();
	
	// Create physics world
	InitializePhysics();

	// Create the model object.
	EngineObjectClass* box1 = new EngineObjectClass;
	if(!box1)
	{
		return false;
	}
	// Initialize the model object.
	result = box1->Initialize(m_D3D->GetDevice(), "../PwAG/data/cube.DAE", L"../PwAG/data/stone02.dds", 
												  L"../PwAG/data/bump02.dds", L"../PwAG/data/spec02.dds",
												  aiVector3D(-4.0f, 5.0f, 0.0f), aiVector3D(0.0f,0.0f,0.0f),
												  "Box", 
												   1.f, 1.f, 1.f,  //size
												  1.0f,				 //mass
												  0.1f, 0.1f, 0.1f); //inertia
	
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_dynamicsWorld->addRigidBody(box1->m_rigidBody);
	m_EngineObjects.push_back(box1);

	EngineObjectClass* box1b = new EngineObjectClass;
	if(!box1)
	{
		return false;
	}
	// Initialize the model object.
	result = box1b->Initialize(m_D3D->GetDevice(), "../PwAG/data/cube.DAE", L"../PwAG/data/stone02.dds", 
												  L"../PwAG/data/bump02.dds", L"../PwAG/data/spec02.dds",
												  aiVector3D(-8.5f, 3.0f, 0.0f), aiVector3D(0.0f, 0.0f, 0.0f), 
												  "Box", 
												   1.f, 1.f, 1.f,  //size
												  1.0f,				 //mass
												  0.1f, 0.1f, 0.1f); //inertia
	
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_dynamicsWorld->addRigidBody(box1b->m_rigidBody);
	m_EngineObjects.push_back(box1b);

	EngineObjectClass* box1c = new EngineObjectClass;
	if(!box1)
	{
		return false;
	}
	// Initialize the model object.
	result = box1c->Initialize(m_D3D->GetDevice(), "../PwAG/data/cube.DAE", L"../PwAG/data/stone02.dds", 
												  L"../PwAG/data/bump02.dds", L"../PwAG/data/spec02.dds",
												  aiVector3D(-7.0f, 5.0f, 0.0f), aiVector3D(0.0f, 0.0f, 0.0f), 
												  "Box", 
												   1.f, 1.f, 1.f,  //size
												  1.0f,				 //mass
												  0.1f, 0.1f, 0.1f); //inertia
	
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_dynamicsWorld->addRigidBody(box1c->m_rigidBody);
	m_EngineObjects.push_back(box1c);

	EngineObjectClass* sphere = new EngineObjectClass;
	if(!sphere)
	{
		return false;
	}
	// Initialize the model object.
	result = sphere->Initialize(m_D3D->GetDevice(), "../PwAG/data/sphere.DAE", L"../PwAG/data/stone02.dds", 
												  L"../PwAG/data/bump02.dds", L"../PwAG/data/spec02.dds",
												  aiVector3D(1.8f, 5.50f, 0.5f), aiVector3D(0.0f, 0.0f, 0.0f), 
												  "Sphere", 
												  1.f,				 //radius
												  2.0f,				 //mass
												  0.1f, 0.1f, 0.1f); //inertia
	
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_dynamicsWorld->addRigidBody(sphere->m_rigidBody);
	m_EngineObjects.push_back(sphere);

	EngineObjectClass* box3 = new EngineObjectClass;
	if(!box3)
	{
		return false;
	}
	// Initialize the model object.
	result = box3->Initialize(m_D3D->GetDevice(), "../PwAG/data/cube.DAE", L"../PwAG/data/stone02.dds", 
												  L"../PwAG/data/bump02.dds", L"../PwAG/data/spec02.dds",
												  aiVector3D(0.0f, 5.0f, 0.0f), aiVector3D(0.0f, 0.0f, 0.0f), 
												  "Box", 
												  1.f, 1.f, 1.f,  //size
												  10.0f,				 //mass
												  0.1f, 0.1f, 0.1f); //inertia
	
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_dynamicsWorld->addRigidBody(box3->m_rigidBody);
	m_EngineObjects.push_back(box3);

	EngineObjectClass* box4 = new EngineObjectClass;
	if(!box3)
	{
		return false;
	}
	// Initialize the model object.
	result = box4->Initialize(m_D3D->GetDevice(), "../PwAG/data/cube.DAE", L"../PwAG/data/stone02.dds", 
												  L"../PwAG/data/bump02.dds", L"../PwAG/data/spec02.dds",
												  aiVector3D(0.0f, 7.5f, 0.2f), aiVector3D(0.0f, 0.0f, 0.0f), 
												  "Box", 
												  1.f, 1.f, 1.f,  //size
												  15.0f,				 //mass
												  0.1f, 0.1f, 0.1f); //inertia
	
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_dynamicsWorld->addRigidBody(box4->m_rigidBody);
	m_EngineObjects.push_back(box4);

	EngineObjectClass* grnd = new EngineObjectClass;
	if(!grnd)
	{
		return false;
	}
	// Initialize the model object.
	result = grnd->Initialize(m_D3D->GetDevice(), "../PwAG/data/scene1.DAE", L"../PwAG/data/stone01.dds", 
												  L"../PwAG/data/bump02.dds", L"../PwAG/data/spec02.dds",
												  aiVector3D(0.0f, 0.0f, -2.0f), aiVector3D(0.0f, 0.0f, 0.0f), 
												  "StaticPlane",
												  0.0f, 1.0f, 0.0f,
												  1.0f);
	
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_dynamicsWorld->addRigidBody(grnd->m_rigidBody);
	m_EngineObjects.push_back(grnd);

	//Create the light object.
	m_Light = new LightClass;
	if(!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	//m_Light->SetAmbientColor(0.6f, 0.6f, 0.2f, 1.0f);
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
	m_DownSampleTexture = new RenderTextureClass;
	if(!m_DownSampleTexture)
	{
		return false;
	}

	// Initialize the down sample render to texture object.
	result = m_DownSampleTexture->Initialize(m_D3D->GetDevice(), downSampleWidth, downSampleHeight, 100.0f, 1.0f);
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
	m_UpSampleTexture = new RenderTextureClass;
	if(!m_UpSampleTexture)
	{
		return false;
	}

	// Initialize the up sample render to texture object.
	result = m_UpSampleTexture->Initialize(m_D3D->GetDevice(), SHADOWMAP_WIDTH, SHADOWMAP_HEIGHT, SCREEN_DEPTH, 0.1f);
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

	// Create the text object.
	m_Text = new TextClass;
	if(!m_Text)
	{
		return false;
	}

	// Initialize the text object.
	result = m_Text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}

	return true;
}


void GraphicsClass::Shutdown()
{
	ShutdownPhysics();

	// Release the text object.
	if(m_Text)
	{
		m_Text->Shutdown();
		delete m_Text;
		m_Text = 0;
	}

	// Release the full screen ortho window object.
	if(m_FullScreenWindow)
	{
		m_FullScreenWindow->Shutdown();
		delete m_FullScreenWindow;
		m_FullScreenWindow = 0;
	}

	// Release the up sample render to texture object.
	if(m_UpSampleTexture)
	{
		m_UpSampleTexture->Shutdown();
		delete m_UpSampleTexture;
		m_UpSampleTexture = 0;
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
	if(m_DownSampleTexture)
	{
		m_DownSampleTexture->Shutdown();
		delete m_DownSampleTexture;
		m_DownSampleTexture = 0;
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
	std::vector<EngineObjectClass*>::iterator it;
	for(it = m_EngineObjects.begin(); it != m_EngineObjects.end(); ++it)
	{
		if((*it))
		{
			(*it)->Shutdown();
			delete (*it);
			(*it) = 0;
		}
	}
	m_EngineObjects.clear();

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


bool GraphicsClass::Frame(float posX, float posY, float posZ, float rotX, float rotY, float rotZ, bool uptd)
{
	bool result;
	static bool side = false;
	static float lightPositionX = -5.0f;

	if(uptd)
	{
		m_dynamicsWorld->stepSimulation(1/60.0f, 10);

		std::vector<EngineObjectClass*>::iterator it;
		for(it = m_EngineObjects.begin(); it != m_EngineObjects.end(); ++it)
		{
			(*it)->Update();
		}
	}

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
	

	m_dynamicsWorld->debugDrawWorld();
	// Render the graphics scene.
	result = Render();
	if(!result)
	{
		return false;
	}

	std::vector<PhysicsDebugObjectClass*>::iterator dIt;
	for(dIt = m_DebugObjects.begin(); dIt != m_DebugObjects.end(); ++dIt)
	{
		(*dIt)->Shutdown();
	}
	m_DebugObjects.clear();

	return true;
}

bool GraphicsClass::SetWireframe()
{
	return m_D3D->SetWireframe();
}


bool GraphicsClass::RenderSceneToTexture()
{
	D3DXMATRIX worldMatrix, lightViewMatrix, lightProjectionMatrix, translateMatrix, transformMatrix;
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

	std::vector<EngineObjectClass*>::iterator it;
	for(it = m_EngineObjects.begin(); it != m_EngineObjects.end(); ++it)
	{
	
		// Setup the translation matrix for the cube model.
		//(*it)->m_model->GetPosition(posX, posY, posZ);
		//D3DXMatrixTranslation(&worldMatrix, posX, posY, posZ);

		//m_Camera->GetViewMatrix(viewMatrix);
		m_D3D->GetWorldMatrix(worldMatrix);
		transformMatrix = worldMatrix;

		D3DXMatrixAffineTransformation(&transformMatrix, 1.0f, &(*it)->m_model->GetPosition(), &(*it)->m_model->GetRotation(),  &(*it)->m_model->GetPosition());
		//m_D3D->GetProjectionMatrix(projectionMatrix);

		// Render the model with the depth shader.
		(*it)->m_model->Render(m_D3D->GetDeviceContext());
		result = m_ShaderManager->RenderDepthShader(m_D3D->GetDeviceContext(), (*it)->m_model->GetIndexCount(), transformMatrix, lightViewMatrix, lightProjectionMatrix);
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
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, translateMatrix, transformMatrix;
	D3DXMATRIX lightViewMatrix, lightProjectionMatrix;
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
	
	std::vector<EngineObjectClass*>::iterator it;
	for(it = m_EngineObjects.begin(); it != m_EngineObjects.end(); ++it)
	{
		// Setup the translation matrix for the cube model.
		//(*it)->m_model->GetPosition(posX, posY, posZ);
		//D3DXMatrixTranslation(&worldMatrix, posX, posY, posZ);

		//m_Camera->GetViewMatrix(viewMatrix);
		m_D3D->GetWorldMatrix(worldMatrix);
		transformMatrix = worldMatrix;

		D3DXMatrixAffineTransformation(&transformMatrix, 1.0f, &(*it)->m_model->GetPosition(), &(*it)->m_model->GetRotation(),  &(*it)->m_model->GetPosition());
		//m_D3D->GetProjectionMatrix(projectionMatrix);

		// Render the model with the depth shader.
		(*it)->m_model->Render(m_D3D->GetDeviceContext());
		result = m_ShaderManager->RenderShadowShader(m_D3D->GetDeviceContext(), (*it)->m_model->GetIndexCount(), transformMatrix, viewMatrix, projectionMatrix, lightViewMatrix,
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
	m_DownSampleTexture->SetRenderTarget(m_D3D->GetDeviceContext());

	// Clear the render to texture.
	m_DownSampleTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world and view matrices from the camera and d3d objects.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetBaseViewMatrix(baseViewMatrix);
	
	// Get the ortho matrix from the render to texture since texture has different dimensions being that it is smaller.
	m_DownSampleTexture->GetOrthoMatrix(orthoMatrix);

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
						m_DownSampleTexture->GetShaderResourceView(), screenSizeX);
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
	m_UpSampleTexture->SetRenderTarget(m_D3D->GetDeviceContext());

	// Clear the render to texture.
	m_UpSampleTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world and view matrices from the camera and d3d objects.
	m_Camera->GetBaseViewMatrix(baseViewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);

	// Get the ortho matrix from the render to texture since texture has different dimensions.
	m_UpSampleTexture->GetOrthoMatrix(orthoMatrix);

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
					 m_UpSampleTexture->GetShaderResourceView());
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
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	D3DXMATRIX transformMatrix, translationMatrix, rotationMatrix;
	D3DXMATRIX lightViewMatrix, lightProjectionMatrix;
	bool result;


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
	m_D3D->BeginScene(0.3f, 0.3f, 0.3f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();
	
	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);
	
	std::vector<EngineObjectClass*>::iterator it;
	for(it = m_EngineObjects.begin(); it != m_EngineObjects.end(); ++it)
	{
		transformMatrix = worldMatrix;
		D3DXMatrixAffineTransformation(&transformMatrix, 1.0f, &(*it)->m_model->GetPosition(), &(*it)->m_model->GetRotation(),  &(*it)->m_model->GetPosition());
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
		(*it)->m_model->Render(m_D3D->GetDeviceContext());

		result = m_ShaderManager->RenderSoftShadowShader(m_D3D->GetDeviceContext(), (*it)->m_model->GetIndexCount(), transformMatrix, viewMatrix, projectionMatrix, 
                                        (*it)->m_model->GetTexture(), m_UpSampleTexture->GetShaderResourceView(), m_Light->GetPosition(), 
                                        m_Light->GetAmbientColor(), m_Light->GetDiffuseColor());
		//result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), (*it)->m_model->GetIndexCount(), transformMatrix, viewMatrix, projectionMatrix, 
        //                               (*it)->m_model->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), 
        //                               m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		//result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), (*it)->m_model->GetIndexCount(), transformMatrix, viewMatrix, projectionMatrix, 
        //                               (*it)->m_model->GetTexture());

		if(!result)
		{
			return false;
		}
	
	
		// Reset the world matrix.
		m_D3D->GetWorldMatrix(worldMatrix);
	}

	std::vector<PhysicsDebugObjectClass*>::iterator dIt;
	for(dIt = m_DebugObjects.begin(); dIt != m_DebugObjects.end(); ++dIt)
	{
		transformMatrix = worldMatrix;
		//D3DXMatrixAffineTransformation(&transformMatrix, 1.0f, &(*it)->m_model->GetPosition(), &(*it)->m_model->GetRotation(),  &(*it)->m_model->GetPosition());

		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
		(*dIt)->Render(m_D3D->GetDeviceContext());

		result = m_ShaderManager->RenderColorShader(m_D3D->GetDeviceContext(), 2, transformMatrix, viewMatrix, projectionMatrix);

		if(!result)
		{
			return false;
		}
	
	
		// Reset the world matrix.
		m_D3D->GetWorldMatrix(worldMatrix);
	}

	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();

	// Turn on the alpha blending before rendering the text.
	m_D3D->TurnOnAlphaBlending();

	// Render the text strings.
	result = m_Text->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	if(!result)
	{
		return false;
	}

	// Turn off alpha blending after rendering the text.
	m_D3D->TurnOffAlphaBlending();

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();

	// Present the rendered scene to the screen.
	m_D3D->EndScene();
	
	return true;
}

void GraphicsClass::SetSentence(int i, std::string text)
{
	m_Text->SetSentence(i, text);
}

bool GraphicsClass::InitializePhysics(void)
{
	///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
    btDefaultCollisionConfiguration* m_collisionConfiguration = new btDefaultCollisionConfiguration;
	if(!m_collisionConfiguration)
		return false;

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	btCollisionDispatcher* m_dispatcher = new	btCollisionDispatcher(m_collisionConfiguration);
	if(!m_dispatcher)
		return false;

    ///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	btBroadphaseInterface* m_broadphase = new btDbvtBroadphase;
    if(!m_broadphase)
		return false;

    ///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
    btSequentialImpulseConstraintSolver* m_solver = new btSequentialImpulseConstraintSolver;
	if(!m_solver)
		return false;

    // The world.
	m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration);
	if(!m_dynamicsWorld)
		return false;

    m_dynamicsWorld->setGravity(btVector3(0,-10,0));
	m_dynamicsWorld->setDebugDrawer(this);

	return true;
}

void GraphicsClass::ShutdownPhysics()
{
	if(m_dynamicsWorld)
		delete m_dynamicsWorld;
	m_dynamicsWorld = 0;
}

void GraphicsClass::GetPos(float& m_x, float& m_y, float& m_z, float& g_x, float& g_y, float& g_z, float& m_d_x, float& m_d_y, float& m_d_z)
{
	m_x = m_EngineObjects[0]->m_model->GetPosition().x;
	m_y = m_EngineObjects[0]->m_model->GetPosition().y;
	m_z = m_EngineObjects[0]->m_model->GetPosition().z;

	g_x = m_EngineObjects[1]->m_model->GetPosition().x;
	g_y = m_EngineObjects[1]->m_model->GetPosition().y;
	g_z = m_EngineObjects[1]->m_model->GetPosition().z;

	btTransform transform;
	m_EngineObjects[2]->m_rigidBody->getMotionState()->getWorldTransform(transform);

	m_d_z = m_EngineObjects[0]->m_collisionShape->getMargin();

	m_d_x = transform.getOrigin().getX();
	m_d_y = transform.getOrigin().getY();
	//m_d_z = transform.getOrigin().getZ();
}

void GraphicsClass::drawLine(const btVector3 &from, const btVector3 &to, const btVector3 &color)
{
	D3DXVECTOR3 dxFrom(from.x(), from.y(), from.z());
	D3DXVECTOR3 dxTo(to.x(), to.y(), to.z());
	D3DXVECTOR3 dxColor(color.x(), color.y(), color.z());
	m_DebugObjects.push_back(new PhysicsDebugObjectClass);
	m_DebugObjects.back()->Initialize(m_D3D->GetDevice(), dxFrom, dxTo, dxColor);

	return;
}

void GraphicsClass::ToggleDebugMode(void)
{
	m_isDebug = !m_isDebug;

	if(m_isDebug)
		m_debugMode = btIDebugDraw::DBG_DrawWireframe;
	else
		m_debugMode = btIDebugDraw::DBG_NoDebug;
}

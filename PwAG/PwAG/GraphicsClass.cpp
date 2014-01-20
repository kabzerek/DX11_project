#include "GraphicsClass.h"


GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	//m_Model = 0;
	m_Light = 0;	
	m_RenderTexture = 0;
	//m_DebugWindow = 0;
	m_Bitmap = 0;

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

	m_isHanging = false;
	m_isPhysics = false;
	//SetSentence(1, "Physics OFF");
	//SetSentence(2, "No Link");

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
	// Box 1 //
	m_EngineObjects.push_back(new EngineObjectClass);
	result = m_EngineObjects.back()->Initialize(m_D3D->GetDevice(), "../PwAG/data/cube.DAE", L"../PwAG/data/stone02.dds", 
																	L"../PwAG/data/dirt01.dds", L"../PwAG/data/spec02.dds",
																	aiVector3D(-10.0f, 2.0f, 10.0f), aiVector3D(0.0f, 0.0f, 0.0f),
																	"Box", 
																	1.f, 1.f, 1.f,			//size
																	1.0f,					//mass
																	0.1f, 0.1f, 0.1f,		//inertia
																	shaders_types::AlphaMapShader);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_dynamicsWorld->addRigidBody(m_EngineObjects.back()->m_rigidBody);

	// Box 2 //
	m_EngineObjects.push_back(new EngineObjectClass);
	result = m_EngineObjects.back()->Initialize(m_D3D->GetDevice(), "../PwAG/data/cube.DAE", L"../PwAG/data/stone02.dds", 
																	L"../PwAG/data/dirt01.dds", L"../PwAG/data/spec02.dds",
																	aiVector3D(-10.0f, 5.5f, 10.0f), aiVector3D(0.0f, 0.0f, 0.0f),
																	"Box", 
																	1.f, 1.f, 1.f,			//size
																	1.0f,					//mass
																	0.1f, 0.1f, 0.1f,		//inertia
																	shaders_types::MultiTextureShader);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_dynamicsWorld->addRigidBody(m_EngineObjects.back()->m_rigidBody);

	// Box 3 //
	m_EngineObjects.push_back(new EngineObjectClass);
	result = m_EngineObjects.back()->Initialize(m_D3D->GetDevice(), "../PwAG/data/cube.DAE", L"../PwAG/data/stone02.dds", 
																	L"../PwAG/data/bump02.dds", L"../PwAG/data/spec02.dds",
																	aiVector3D(-8.0f, 2.0f, 4.0f), aiVector3D(0.0f, 0.0f, 0.0f),
																	"Box", 
																	1.f, 1.f, 1.f,			//size
																	1.0f,					//mass
																	0.1f, 0.1f, 0.1f,		//inertia
																	shaders_types::SoftShadowShader);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_dynamicsWorld->addRigidBody(m_EngineObjects.back()->m_rigidBody);

	// Sphere 1 //
	m_EngineObjects.push_back(new EngineObjectClass);
	result = m_EngineObjects.back()->Initialize(m_D3D->GetDevice(), "../PwAG/data/sphere.DAE", L"../PwAG/data/stone02.dds", 
																	L"../PwAG/data/bump02.dds", L"../PwAG/data/spec02.dds",
																	aiVector3D(6.0f, 3.0f, 2.0f), aiVector3D(0.0f, 0.0f, 0.0f), 
																	"Sphere", 
																	1.f,					//radius
																	2.0f,					//mass
																	0.1f, 0.1f, 0.1f,		//inertia
																	shaders_types::SoftShadowShader);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_dynamicsWorld->addRigidBody(m_EngineObjects.back()->m_rigidBody);

	// Box 4 //
	m_EngineObjects.push_back(new EngineObjectClass);
	result = m_EngineObjects.back()->Initialize(m_D3D->GetDevice(), "../PwAG/data/cube.DAE", L"../PwAG/data/stone02.dds", 
																	L"../PwAG/data/bump02.dds", L"../PwAG/data/spec02.dds",
																	aiVector3D(7.0f, 3.0f, 7.0f), aiVector3D(0.0f, 0.0f, 0.0f),
																	"Box", 
																	1.f, 1.f, 1.f,			//size
																	1.0f,					//mass
																	0.1f, 0.1f, 0.1f,		//inertia
																	shaders_types::SpecMapShader);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_dynamicsWorld->addRigidBody(m_EngineObjects.back()->m_rigidBody);

	// Box 5 //
	m_EngineObjects.push_back(new EngineObjectClass);
	result = m_EngineObjects.back()->Initialize(m_D3D->GetDevice(), "../PwAG/data/cube.DAE", L"../PwAG/data/stone02.dds", 
																	L"../PwAG/data/bump02.dds", L"../PwAG/data/spec02.dds",
																	aiVector3D(8.5f, 6.0f, 6.0f), aiVector3D(0.5f, 0.0f, 0.0f),
																	"Box", 
																	1.f, 1.f, 1.f,			//size
																	1.0f,					//mass
																	0.1f, 0.1f, 0.1f,		//inertia
																	shaders_types::SpecMapShader);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_dynamicsWorld->addRigidBody(m_EngineObjects.back()->m_rigidBody);

	// Ragdoll //	
	m_Ragdoll = new RagdollClass;
	if(!m_Ragdoll)
	{
		return false;
	}
	// Initialize the model object.
	result = m_Ragdoll->Initialize(m_D3D->GetDevice(), "../PwAG/data/Wariat_001.dae", L"../PwAG/data/seafloor.dds", 
													   L"../PwAG/data/bump02.dds", L"../PwAG/data/spec02.dds",
													   aiVector3D(1.0f, 5.0f, 2.0f), aiVector3D(0.0f, 0.0f, 0.0f),
													   "Ragdoll",
													   shaders_types::SoftShadowShader);
	for(int i = 0; i < num_bones; ++i)
		m_dynamicsWorld->addRigidBody(m_Ragdoll->m_rigidBodys[i]);

	//m_dynamicsWorld->addRigidBody(m_Ragdoll->m_rigidBodys[m_Ragdoll->Head]);
	//m_dynamicsWorld->addRigidBody(m_Ragdoll->m_rigidBodys[m_Ragdoll->Neck]);
	//m_dynamicsWorld->addRigidBody(m_Ragdoll->m_rigidBodys[m_Ragdoll->Spine2]);
	//m_dynamicsWorld->addRigidBody(m_Ragdoll->m_rigidBodys[m_Ragdoll->Spine1]);
	//m_dynamicsWorld->addRigidBody(m_Ragdoll->m_rigidBodys[m_Ragdoll->Spine0]);

	//m_dynamicsWorld->addRigidBody(m_Ragdoll->m_rigidBodys[m_Ragdoll->RArm0]);
	//m_dynamicsWorld->addRigidBody(m_Ragdoll->m_rigidBodys[m_Ragdoll->RArm1]);
	//m_dynamicsWorld->addRigidBody(m_Ragdoll->m_rigidBodys[m_Ragdoll->RArm2]);
	//m_dynamicsWorld->addRigidBody(m_Ragdoll->m_rigidBodys[m_Ragdoll->RHand]);

	//m_dynamicsWorld->addRigidBody(m_Ragdoll->m_rigidBodys[m_Ragdoll->LArm0]);
	//m_dynamicsWorld->addRigidBody(m_Ragdoll->m_rigidBodys[m_Ragdoll->LArm1]);
	//m_dynamicsWorld->addRigidBody(m_Ragdoll->m_rigidBodys[m_Ragdoll->LArm2]);
	//m_dynamicsWorld->addRigidBody(m_Ragdoll->m_rigidBodys[m_Ragdoll->LHand]);

	//m_dynamicsWorld->addRigidBody(m_Ragdoll->m_rigidBodys[m_Ragdoll->RLeg0]);
	//m_dynamicsWorld->addRigidBody(m_Ragdoll->m_rigidBodys[m_Ragdoll->RLeg1]);
	//m_dynamicsWorld->addRigidBody(m_Ragdoll->m_rigidBodys[m_Ragdoll->RLeg2]);
	//m_dynamicsWorld->addRigidBody(m_Ragdoll->m_rigidBodys[m_Ragdoll->RFoot]);

	//m_dynamicsWorld->addRigidBody(m_Ragdoll->m_rigidBodys[m_Ragdoll->LLeg0]);
	//m_dynamicsWorld->addRigidBody(m_Ragdoll->m_rigidBodys[m_Ragdoll->LLeg1]);
	//m_dynamicsWorld->addRigidBody(m_Ragdoll->m_rigidBodys[m_Ragdoll->LLeg2]);
	//m_dynamicsWorld->addRigidBody(m_Ragdoll->m_rigidBodys[m_Ragdoll->LFoot]);

	for(int i = 0; i < num_joints; ++i)
		m_dynamicsWorld->addConstraint(m_Ragdoll->m_joints[i], true);

	//m_dynamicsWorld->addConstraint(m_Ragdoll->m_joints[m_Ragdoll->Head_to_Neck], true);
	//m_dynamicsWorld->addConstraint(m_Ragdoll->m_joints[m_Ragdoll->Neck_to_Spine2], true);
	//m_dynamicsWorld->addConstraint(m_Ragdoll->m_joints[m_Ragdoll->Spine2_to_Spine1], true);
	//m_dynamicsWorld->addConstraint(m_Ragdoll->m_joints[m_Ragdoll->Spine1_to_Spine0], true);
	//m_dynamicsWorld->addConstraint(m_Ragdoll->m_joints[m_Ragdoll->Spine1_to_RArm0], true);
	//m_dynamicsWorld->addConstraint(m_Ragdoll->m_joints[m_Ragdoll->Spine1_to_LArm0], true);
	//m_dynamicsWorld->addConstraint(m_Ragdoll->m_joints[m_Ragdoll->RArm0_to_RArm1], true);
	//m_dynamicsWorld->addConstraint(m_Ragdoll->m_joints[m_Ragdoll->LArm0_to_LArm1], true);
	//m_dynamicsWorld->addConstraint(m_Ragdoll->m_joints[m_Ragdoll->RArm1_to_RArm2], true);
	//m_dynamicsWorld->addConstraint(m_Ragdoll->m_joints[m_Ragdoll->LArm1_to_LArm2], true);
	//m_dynamicsWorld->addConstraint(m_Ragdoll->m_joints[m_Ragdoll->RArm2_to_RHand], true);
	//m_dynamicsWorld->addConstraint(m_Ragdoll->m_joints[m_Ragdoll->LArm2_to_LHand], true);
	//m_dynamicsWorld->addConstraint(m_Ragdoll->m_joints[m_Ragdoll->Spine0_to_RLeg0], true);
	//m_dynamicsWorld->addConstraint(m_Ragdoll->m_joints[m_Ragdoll->Spine0_to_LLeg0], true);
	//m_dynamicsWorld->addConstraint(m_Ragdoll->m_joints[m_Ragdoll->RLeg0_to_RLeg1], true);
	//m_dynamicsWorld->addConstraint(m_Ragdoll->m_joints[m_Ragdoll->LLeg0_to_LLeg1], true);
	//m_dynamicsWorld->addConstraint(m_Ragdoll->m_joints[m_Ragdoll->RLeg1_to_RLeg2], true);
	//m_dynamicsWorld->addConstraint(m_Ragdoll->m_joints[m_Ragdoll->LLeg1_to_LLeg2], true);
	//m_dynamicsWorld->addConstraint(m_Ragdoll->m_joints[m_Ragdoll->RLeg2_to_RFoot], true);
	//m_dynamicsWorld->addConstraint(m_Ragdoll->m_joints[m_Ragdoll->LLeg2_to_LFoot], true);

	// Ground //
	m_EngineObjects.push_back(new EngineObjectClass);
	result = m_EngineObjects.back()->Initialize(m_D3D->GetDevice(), "../PwAG/data/Plane.dae", L"../PwAG/data/dirt01.dds", 
																	L"../PwAG/data/bump02.dds", L"../PwAG/data/spec02.dds",
																	aiVector3D(0.0f, 0.0f, 0.0f), aiVector3D(0.0f, 0.0f, 0.0f), 
																	"StaticPlane",
																	0.0f, 1.0f, 0.0f,
																	0.0f,
																	shaders_types::SoftShadowShader);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_dynamicsWorld->addRigidBody(m_EngineObjects.back()->m_rigidBody);

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

	
	// Create the texture shader object.
	m_TextureShader = new TextureShaderClass;
	if(!m_TextureShader)
	{
		return false;
	}
	
	// Initialize the texture shader object.
	result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}


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

	
	// Create the bitmap object.
	m_Bitmap = new BitmapClass;
	if(!m_Bitmap)
	{
		return false;
	}

	// Initialize the bitmap object.
	result = m_Bitmap->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, L"../PwAG/data/mouse.dds", 32, 32);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
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

	// Release the bitmap object.
	if(m_Bitmap)
	{
		m_Bitmap->Shutdown();
		delete m_Bitmap;
		m_Bitmap = 0;
	}
	// Release the texture shader object.
	if(m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

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


bool GraphicsClass::Frame(float posX, float posY, float posZ, float rotX, float rotY, float rotZ, int mouseX, int mouseY)
{
	bool result;
	static bool side = false;
	static float lightPositionX = -5.0f;

	if(m_isPhysics)
	{
		m_dynamicsWorld->stepSimulation(1/60.0f, 10);

		std::vector<EngineObjectClass*>::iterator it;
		for(it = m_EngineObjects.begin(); it != m_EngineObjects.end(); ++it)
		{
			if((*it)->m_rigidBody)
				(*it)->Update();
		}

		m_Ragdoll->m_model->ShutdownBuffers();
		//m_Ragdoll->Update();
		m_Ragdoll->m_model->InitializeBuffers(m_D3D->GetDevice());
	}

	// Set the position of the camera.
	m_Camera->SetPosition(posX, posY, posZ);
	m_Camera->SetRotation(rotX, rotY, rotZ);

	// Set the position of the mouse.
	m_mouseX = mouseX;
	m_mouseY = mouseY;

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
	m_Light->SetPosition(lightPositionX, 14.0f, -5.0f);
	

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

		D3DXMatrixAffineTransformation(&transformMatrix, 1.0f, &D3DXVECTOR3(0.0f,0.0f,0.0f), &(*it)->m_model->GetRotation(),  &(*it)->m_model->GetPosition());
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

	m_D3D->GetWorldMatrix(worldMatrix);
	transformMatrix = worldMatrix;

	D3DXMatrixAffineTransformation(&transformMatrix, 1.0f, &D3DXVECTOR3(0.0f,0.0f,0.0f), &m_Ragdoll->m_model->GetRotation(),  &m_Ragdoll->m_model->GetPosition());
	//m_D3D->GetProjectionMatrix(projectionMatrix);

	// Render the model with the depth shader.
	m_Ragdoll->m_model->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderDepthShader(m_D3D->GetDeviceContext(), m_Ragdoll->m_model->GetIndexCount(), transformMatrix, lightViewMatrix, lightProjectionMatrix);
	if(!result)
	{
		return false;
	}

	// Reset the world matrix.
	m_D3D->GetWorldMatrix(worldMatrix);

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

		D3DXMatrixAffineTransformation(&transformMatrix, 1.0f, &D3DXVECTOR3(0.0f,0.0f,0.0f), &(*it)->m_model->GetRotation(),  &(*it)->m_model->GetPosition());
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

	m_D3D->GetWorldMatrix(worldMatrix);
	transformMatrix = worldMatrix;

	D3DXMatrixAffineTransformation(&transformMatrix, 1.0f, &D3DXVECTOR3(0.0f,0.0f,0.0f), &m_Ragdoll->m_model->GetRotation(),  &m_Ragdoll->m_model->GetPosition());
	//m_D3D->GetProjectionMatrix(projectionMatrix);

	// Render the model with the depth shader.
	m_Ragdoll->m_model->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderShadowShader(m_D3D->GetDeviceContext(), m_Ragdoll->m_model->GetIndexCount(), transformMatrix, viewMatrix, projectionMatrix, lightViewMatrix,
				lightProjectionMatrix, m_RenderTexture->GetShaderResourceView(), m_Light->GetPosition());
	if(!result)
	{
		return false;
	}

	// Reset the world matrix.
	m_D3D->GetWorldMatrix(worldMatrix);

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
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix, baseViewMatrix;
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
	m_Camera->GetBaseViewMatrix(baseViewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);
	
	std::vector<EngineObjectClass*>::iterator it;
	for(it = m_EngineObjects.begin(); it != m_EngineObjects.end(); ++it)
	{
		transformMatrix = worldMatrix;
		D3DXMatrixAffineTransformation(&transformMatrix, 1.0f, &D3DXVECTOR3(0.0f,0.0f,0.0f), &(*it)->m_model->GetRotation(),  &(*it)->m_model->GetPosition());
		// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
		(*it)->m_model->Render(m_D3D->GetDeviceContext());

		result = RenderShaders(m_D3D->GetDeviceContext(), (*it)->m_model, transformMatrix, viewMatrix, projectionMatrix, (*it)->m_shaderType);

		if(!result)
		{
			return false;
		}
	
	
		// Reset the world matrix.
		m_D3D->GetWorldMatrix(worldMatrix);
	}

	transformMatrix = worldMatrix;
	D3DXMatrixAffineTransformation(&transformMatrix, 1.0f, &D3DXVECTOR3(0.0f,0.0f,0.0f), &m_Ragdoll->m_model->GetRotation(),  &m_Ragdoll->m_model->GetPosition());
	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Ragdoll->m_model->Render(m_D3D->GetDeviceContext());

	result = RenderShaders(m_D3D->GetDeviceContext(), m_Ragdoll->m_model, transformMatrix, viewMatrix, projectionMatrix, m_Ragdoll->m_shaderType);

	if(!result)
	{
		return false;
	}
	
	
	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();

	// Turn on the alpha blending before rendering the text.
	m_D3D->TurnOnAlphaBlending();

	// Render the mouse cursor with the texture shader.
	result = m_Bitmap->Render(m_D3D->GetDeviceContext(), m_mouseX, m_mouseY);
	if(!result) 
	{ 
		return false; 
	}
	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Bitmap->GetIndexCount(), worldMatrix, baseViewMatrix, orthoMatrix, m_Bitmap->GetTexture());
	if(!result) 
	{
		return false;
	}
	
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

	// Reset the world matrix.
	m_D3D->GetWorldMatrix(worldMatrix);

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


	// Present the rendered scene to the screen.
	m_D3D->EndScene();
	
	return true;
}

void GraphicsClass::SetSentence(int i, std::string text)
{
	m_Text->SetSentence(i, text);
}

bool GraphicsClass::RenderShaders(ID3D11DeviceContext* device, ModelClass* model, D3DXMATRIX transformMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix, int shaderType)
{
	switch(shaderType)
	{
	case shaders_types::AlphaMapShader:
		{
			return m_ShaderManager->RenderAlphaMapShader(device, model->GetIndexCount(), transformMatrix, viewMatrix, projectionMatrix,
														 model->GetTextureArray());
			break;
		}
	case shaders_types::BumpMapShader:
		{
			return m_ShaderManager->RenderBumpMapShader(device, model->GetIndexCount(), transformMatrix, viewMatrix, projectionMatrix,
														model->GetTextureArray(), m_Light->GetDirection(), m_Light->GetDiffuseColor());
			break;
		}
	case shaders_types::MultiTextureShader:
		{
			return m_ShaderManager->RenderMultiTextureShader(device, model->GetIndexCount(), transformMatrix, viewMatrix, projectionMatrix,
															 model->GetTextureArray());
			break;
		}
	case shaders_types::SoftShadowShader:
		{
			return m_ShaderManager->RenderSoftShadowShader(device, model->GetIndexCount(), transformMatrix, viewMatrix, projectionMatrix, 
														   model->GetTexture(), m_UpSampleTexture->GetShaderResourceView(), m_Light->GetPosition(), 
														   m_Light->GetAmbientColor(), m_Light->GetDiffuseColor());
			break;
		}
	case shaders_types::SpecMapShader:
		{
			return m_ShaderManager->RenderSpecMapShader(device, model->GetIndexCount(), transformMatrix, viewMatrix, projectionMatrix,
														model->GetTextureArray(), m_Light->GetDirection(), m_Light->GetDiffuseColor(),
														m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
			break;
		}
	default:
		{
			return m_ShaderManager->RenderSoftShadowShader(device, model->GetIndexCount(), transformMatrix, viewMatrix, projectionMatrix, 
														   model->GetTexture(), m_UpSampleTexture->GetShaderResourceView(), m_Light->GetPosition(), 
														   m_Light->GetAmbientColor(), m_Light->GetDiffuseColor());
			break;
		}
	}

	return true;
}

bool GraphicsClass::InitializePhysics(void)
{
	///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
    btDefaultCollisionConfiguration* m_collisionConfiguration = new btDefaultCollisionConfiguration;
	if(!m_collisionConfiguration)
		return false;

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	btCollisionDispatcher* m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
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
	if(m_Ragdoll)
	{
		for(int i = 0; i < num_joints; ++i)
			m_dynamicsWorld->removeConstraint(m_Ragdoll->m_joints[i]);

		for(int i = 0; i < num_bones; ++i)
			m_dynamicsWorld->removeRigidBody(m_Ragdoll->m_rigidBodys[i]);

		m_Ragdoll->Shutdown();
		delete m_Ragdoll;
	}
	m_Ragdoll = 0;

	if(m_dynamicsWorld)
		delete m_dynamicsWorld;
	m_dynamicsWorld = 0;
}

void GraphicsClass::GetPos(float& m_x, float& m_y, float& m_z, float& g_x, float& g_y, float& g_z, float& m_d_x, float& m_d_y, float& m_d_z)
{
	//m_x = m_EngineObjects[0]->m_model->GetPosition().x;
	//m_y = m_EngineObjects[0]->m_model->GetPosition().y;
	//m_z = m_EngineObjects[0]->m_model->GetPosition().z;

	//g_x = m_EngineObjects[1]->m_model->GetPosition().x;
	//g_y = m_EngineObjects[1]->m_model->GetPosition().y;
	//g_z = m_EngineObjects[1]->m_model->GetPosition().z;

	//btTransform transform;
	//m_EngineObjects[2]->m_rigidBody->getMotionState()->getWorldTransform(transform);

	//m_d_z = m_EngineObjects[0]->m_collisionShape->getMargin();

	//m_d_x = transform.getOrigin().getX();
	//m_d_y = transform.getOrigin().getY();
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

void GraphicsClass::TogglePhysics(void)
{
	m_isPhysics = !m_isPhysics;
	if(m_isPhysics)
		SetSentence(1,"Physics ON");
	else
		SetSentence(1,"Physics OFF");
}


void GraphicsClass::TestIntersection(int mouseX, int mouseY, int screenWidth, int screenHeight, bool isPressed)
{
	D3DXMATRIX viewMatrix, projectionMatrix, viewProjectionMatrix, inverseViewProjectionMatrix;
	D3DXVECTOR3 rayFrom, rayTo;
	D3DXVECTOR3 coord;
	btRigidBody* pBody = NULL; 
	//bool intersect, result;

	//// Get the inverse of the view matrix.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	D3DXMatrixMultiply(&viewProjectionMatrix, &viewMatrix, &projectionMatrix);
	D3DXMatrixInverse(&inverseViewProjectionMatrix, NULL, &viewProjectionMatrix);

	//m_Camera->GetViewMatrix(viewMatrix);
	//m_Camera->GetBaseViewMatrix(baseViewMatrix);
	//D3DXMatrixInverse(&inverseViewMatrix, NULL, &viewMatrix);
	
	//rayFrom = m_Camera->GetPosition();
	
	// Find screen coordinates normalized to -1,1
	coord.x =  ( ( ( 2.0f *((float)mouseX  / (float)screenWidth) ) - 1.f ));
	coord.y = -( ( ( 2.0f *((float)mouseY  / (float)screenHeight)) - 1.f ));
	coord.z = 1.0f;

	//SetSentence(4, "mouseX = " + to_string(mouseX));
	//SetSentence(5, "cx = " + to_string(coord.x));
	//SetSentence(6, "mouseY = " + to_string(mouseY));
	//SetSentence(7, "cy = " + to_string(coord.y));
	//SetSentence(8, "Width = " + to_string(screenWidth));
	//SetSentence(9, "Height = " + to_string(screenHeight));
			
	// Back project the ray from screen to the far clip plane
	//coord.x /= viewMatrix._11; 
	//coord.y /= viewMatrix._22;

	
	//coord*=1000;


	//D3DXVec3TransformCoord(&coord, &coord, &inverseViewMatrix);
			
	//rayTo = coord;

	D3DXVECTOR3 near_vec(coord.x, coord.y, 0.0f);
	D3DXVECTOR3 far_vec(coord.x, coord.y, 1.0f);

	D3DXVec3TransformCoord(&rayFrom, &near_vec, &inverseViewProjectionMatrix);
	D3DXVec3TransformCoord(&rayTo, &far_vec, &inverseViewProjectionMatrix);
			
	btVector3 btRayFrom = btVector3(rayFrom.x, rayFrom.y, rayFrom.z);
	btVector3 btRayTo = btVector3(rayTo.x, rayTo.y, rayTo.z);

	//drawLine(btRayFrom, btRayTo, btVector3(1.0f, 0.0f, 0.0f));

	SetSentence(4, "fx = " + to_string(rayFrom.x));
	SetSentence(5, "fy = " + to_string(rayFrom.y));
	SetSentence(6, "fz = " + to_string(rayFrom.z));

	SetSentence(7, "tx = " + to_string(rayTo.x));
	SetSentence(8, "ty = " + to_string(rayTo.y));
	SetSentence(9, "tz = " + to_string(rayTo.z));
	
	if(!m_isHanging)
	{
		if(isPressed)
		{
			//Need to pick up the object now (if raycast hits)

			btCollisionWorld::ClosestRayResultCallback rayCallback(btRayFrom,btRayTo);
			m_dynamicsWorld->rayTest(btRayFrom, btRayTo, rayCallback);
			if (rayCallback.hasHit())
			{
				pBody =  btRigidBody::upcast((btRigidBody*)rayCallback.m_collisionObject);
				if (pBody != NULL) //&& pPhysicsData)
				{
					// Code for adding a constraint from Bullet Demo's DemoApplication.cpp
					if (!(pBody->isStaticObject() || pBody->isKinematicObject()))
					{
						m_pickedBody = pBody;
						m_pickedBody->setActivationState(DISABLE_DEACTIVATION);

						m_pickPos = rayCallback.m_hitPointWorld;

						btVector3 localPivot = pBody->getCenterOfMassTransform().inverse() * m_pickPos;
							
						btTransform tr;
						tr.setIdentity();
						tr.setOrigin(localPivot);

						btGeneric6DofConstraint* dof6 = new btGeneric6DofConstraint(*pBody, tr, false);
						dof6->setLinearLowerLimit(btVector3(0,0,0));
						dof6->setLinearUpperLimit(btVector3(0,0,0));
						dof6->setAngularLowerLimit(btVector3(0,0,0));
						dof6->setAngularUpperLimit(btVector3(0,0,0));
							
						m_dynamicsWorld->addConstraint(dof6);
						m_pickConstraint = dof6;
						dof6->setParam(BT_CONSTRAINT_STOP_CFM,0.8f,0);
						dof6->setParam(BT_CONSTRAINT_STOP_CFM,0.8f,1);
						dof6->setParam(BT_CONSTRAINT_STOP_CFM,0.8f,2);
						dof6->setParam(BT_CONSTRAINT_STOP_CFM,0.8f,3);
						dof6->setParam(BT_CONSTRAINT_STOP_CFM,0.8f,4);
						dof6->setParam(BT_CONSTRAINT_STOP_CFM,0.8f,5);
							
						dof6->setParam(BT_CONSTRAINT_STOP_ERP,0.1f,0);
						dof6->setParam(BT_CONSTRAINT_STOP_ERP,0.1f,1);
						dof6->setParam(BT_CONSTRAINT_STOP_ERP,0.1f,2);
						dof6->setParam(BT_CONSTRAINT_STOP_ERP,0.1f,3);
						dof6->setParam(BT_CONSTRAINT_STOP_ERP,0.1f,4);
						dof6->setParam(BT_CONSTRAINT_STOP_ERP,0.1f,5);

						//save mouse position for dragging
						m_pickDist = (m_pickPos - btRayFrom).length();

						m_isHanging = true;
						SetSentence(2, "Linked!");
					}
				}
			}
		}
	}
	else
	{		
		if(isPressed)
		{
			SetSentence(3,"LMB pressed");
	
			//The object is picked already, we need to maintain the constraint
			btGeneric6DofConstraint* pickCon = static_cast<btGeneric6DofConstraint*>(m_pickConstraint);
			if (pickCon)
			{
				//keep it at the same picking distance            
				btVector3 btRayFrom = btVector3(rayFrom.x, rayFrom.y, rayFrom.z);
				btVector3 btRayTo = btVector3(rayTo.x, rayTo.y, rayTo.z);
				btVector3 oldPivotInB = pickCon->getFrameOffsetA().getOrigin();

				btVector3 newPivotB;

				btVector3 dir = btRayTo - btRayFrom;
				dir.normalize();
				dir *= m_pickDist;

				newPivotB = btRayFrom + dir;

				pickCon->getFrameOffsetA().setOrigin(newPivotB);
				SetSentence(2, "Still linked!");
			}

		}
		else
		{
			SetSentence(3,"LMB not pressed");
			//The object has to be unpicked - need to release the constraint

			if (m_pickConstraint && m_dynamicsWorld)
			{
				m_dynamicsWorld->removeConstraint(m_pickConstraint);
				delete m_pickConstraint;
				m_pickConstraint = NULL;
				m_pickedBody->setDeactivationTime( 0.f );
				m_pickedBody = NULL;

				m_isHanging = false;
				SetSentence(2,"No Link!");
			}
		}
		
	}


	//if(intersect == true)
	//{
	//	// If it does intersect then set the intersection to "yes" in the text string that is displayed to the screen.
	//	SetSentence(10, "Intersection");
	//}
	//else
	//{
	//	// If not then set the intersection to "No".
	//	SetSentence(10, "No intersection");
	//}

	return;
}


bool GraphicsClass::RaySphereIntersect(D3DXVECTOR3 rayOrigin, D3DXVECTOR3 rayDirection, float radius)
{
	float a, b, c, discriminant;


	// Calculate the a, b, and c coefficients.
	a = (rayDirection.x * rayDirection.x) + (rayDirection.y * rayDirection.y) + (rayDirection.z * rayDirection.z);
	b = ((rayDirection.x * rayOrigin.x) + (rayDirection.y * rayOrigin.y) + (rayDirection.z * rayOrigin.z)) * 2.0f;
	c = ((rayOrigin.x * rayOrigin.x) + (rayOrigin.y * rayOrigin.y) + (rayOrigin.z * rayOrigin.z)) - (radius * radius);

	// Find the discriminant.
	discriminant = (b * b) - (4 * a * c);

	// if discriminant is negative the picking ray missed the sphere, otherwise it intersected the sphere.
	if (discriminant < 0.0f)
	{
		return false;
	}

	return true;
}

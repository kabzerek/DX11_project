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
	m_Camera->SetPosition(0.0f, 0.0f, -500.0f);
	
	// Create the model object.

	//result = m_Model->Initialize(m_D3D->GetDevice(), "data/square.DAE", L"data/stone01.dds", 
	//			     L"data/dirt01.dds", L"data/alpha01.dds");

	ModelClass* box1 = new ModelClass;
	if(!box1)
	{
		return false;
	}
	// Initialize the model object.
	result = box1->Initialize(m_D3D->GetDevice(), "../PwAG/data/square.DAE", L"../PwAG/data/stone02.dds", 
												  L"../PwAG/data/bump02.dds", L"../PwAG/data/spec02.dds",
												  aiVector3D(-100.0f, -50.0f, 0.0f));
	
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
	result = box2->Initialize(m_D3D->GetDevice(), "../PwAG/data/square.DAE", L"../PwAG/data/stone02.dds", 
												  L"../PwAG/data/bump02.dds", L"../PwAG/data/spec02.dds",
												  aiVector3D(125.0f, 25.0f, 50.0f));
	
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
	result = box3->Initialize(m_D3D->GetDevice(), "../PwAG/data/square.DAE", L"../PwAG/data/stone02.dds", 
												  L"../PwAG/data/bump02.dds", L"../PwAG/data/spec02.dds",
												  aiVector3D(0.0f, 100.0f, 250.0f));
	
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_Models.push_back(box3);

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


	//	// Create the light shader object.
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
	//// Create the texture shader object.
	//m_LightShader = new LightShaderClass;
	//if(!m_LightShader)
	//{
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


bool GraphicsClass::Frame(int mouseX, int mouseY)
{
	bool result;

	static float rotation = 0.0f;

	//int mouseX, int mouseY

	rotation += (float)D3DX_PI * 0.007f;
	if(rotation > 360.0f)
	{
		rotation -= 360.0f;
	}
	
	// Render the graphics scene.
	result = Render(rotation);
	if(!result)
	{
		return false;
	}

	return true;
}


bool GraphicsClass::Render(float rotation)
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix;
	bool result;


	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// Rotate the world matrix by the rotation value so that the triangle will spin.
	D3DXMatrixRotationY(&worldMatrix, rotation);

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	//m_Model->Render(m_D3D->GetDeviceContext());

	std::vector<ModelClass*>::iterator it;
	for(it = m_Models.begin(); it != m_Models.end(); ++it)
	{
		(*it)->Render(m_D3D->GetDeviceContext());

		// Render the model using the specular map shader.
		m_SpecMapShader->Render(m_D3D->GetDeviceContext(), (*it)->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
				(*it)->GetTextureArray(), m_Light->GetDirection(), m_Light->GetDiffuseColor(), 
				m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	}
	
	//// Render the model using the specular map shader.
	//m_SpecMapShader->Render(m_D3D->GetDeviceContext(), m_Models[0]->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
	//			m_Models[0]->GetTextureArray(), m_Light->GetDirection(), m_Light->GetDiffuseColor(), 
	//			m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

	//// Render the model using the bump map shader.
	//m_BumpMapShader->Render(m_D3D->GetDeviceContext(), m_Models[1]->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
	//			m_Models[1]->GetTextureArray(), m_Light->GetDirection(), m_Light->GetDiffuseColor());

	//// Render the model using the alpha map shader.
	//m_AlphaMapShader->Render(m_D3D->GetDeviceContext(), m_Models[2]->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
	//			 m_Models[2]->GetTextureArray());

	//// Render the model using the multitexture shader.
	//m_MultiTextureShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
	//			     m_Model->GetTextureArray());


	//// Render the model using the light shader.
	//result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
	//			       m_Model->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), 
	//			       m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	//if(!result)
	//{
	//	return false;
	//}

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}
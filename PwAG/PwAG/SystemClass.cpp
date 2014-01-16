#include "SystemClass.h"


SystemClass::SystemClass()
{
	m_Input = 0;
	m_Graphics = 0;
	m_Timer = 0;
	m_Position = 0;
	m_TimeElapsed = 0.0f;
	m_MaxInputTestTime = 1.0f;
	m_WFPressed = false;
}


SystemClass::SystemClass(const SystemClass& other)
{
}


SystemClass::~SystemClass()
{
}


bool SystemClass::Initialize()
{
	int screenWidth, screenHeight;
	bool result;


	// Initialize the width and height of the screen to zero before sending the variables into the function.
	screenWidth = 0;
	screenHeight = 0;

	// Initialize the windows api.
	InitializeWindows(screenWidth, screenHeight);

	// Create the input object.  This object will be used to handle reading the keyboard input from the user.
	m_Input = new InputClass;
	if(!m_Input)
	{
		return false;
	}

	// Initialize the input object.
	result = m_Input->Initialize(m_hinstance, m_hwnd, screenWidth, screenHeight);
	if(!result)
	{
		MessageBox(m_hwnd, L"Could not initialize the input object.", L"Error", MB_OK);
		return false;
	}

	// Create the graphics object.  This object will handle rendering all the graphics for this application.
	m_Graphics = new GraphicsClass;
	if(!m_Graphics)
	{
		return false;
	}

	// Initialize the graphics object.
	result = m_Graphics->Initialize(screenWidth, screenHeight, m_hwnd);
	if(!result)
	{
		return false;
	}
	
	// Create the timer object.
	m_Timer = new TimerClass;
	if(!m_Timer)
	{
		return false;
	}

	// Initialize the timer object.
	result = m_Timer->Initialize();
	if(!result)
	{
		MessageBox(m_hwnd, L"Could not initialize the timer object.", L"Error", MB_OK);
		return false;
	}

	// Create the position object.
	m_Position = new PositionClass;
	if(!m_Position)
	{
		return false;
	}

	// Set the initial position of the viewer to the same as the initial camera position.
	m_Position->SetPosition(-20.0f, 20.0f, -30.0f);
	m_Position->SetRotation(40.0f, 35.0f, 0.0f);

	return true;
}


void SystemClass::Shutdown()
{
	// Release the position object.
	if(m_Position)
	{
		delete m_Position;
		m_Position = 0;
	}

	// Release the timer object.
	if(m_Timer)
	{
		delete m_Timer;
		m_Timer = 0;
	}

	// Release the graphics object.
	if(m_Graphics)
	{
		m_Graphics->Shutdown();
		delete m_Graphics;
		m_Graphics = 0;
	}

	// Release the input object.
	if(m_Input)
	{
		delete m_Input;
		m_Input = 0;
	}

	// Shutdown the window.
	ShutdownWindows();
	
	return;
}


void SystemClass::Run()
{
	MSG msg;
	bool done, result;


	// Initialize the message structure.
	ZeroMemory(&msg, sizeof(MSG));
	
	// Loop until there is a quit message from the window or the user.
	done = false;
	while(!done)
	{
		// Handle the windows messages.
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// If windows signals to end the application then exit out.
		if(msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			// Otherwise do the frame processing.
			result = Frame();
			if(!result)
			{
				done = true;
			}
		}

	}

	return;
}


bool SystemClass::Frame()
{
	bool result;
	float posX, posY, posZ, rotX, rotY, rotZ;


	// Read the user input.
	result = m_Input->Frame();
	if(!result)
	{
		return false;
	}
	
	// Check if the user pressed escape and wants to exit the application.
	if(m_Input->IsEscapePressed() == true)
	{
		return false;
	}

	// Update the system stats.
	m_Timer->Frame();

	// Do the frame input processing.
	result = HandleInput(m_Timer->GetTime());
	if(!result)
	{
		return false;
	}

	// Get the view point position/rotation.
	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);

	// Set sentences
	float m_x, m_y, m_z, g_x, g_y, g_z, d_x, d_y, d_z;
	m_Graphics->GetPos(m_x, m_y, m_z, g_x, g_y, g_z, d_x, d_y, d_z);

	m_Graphics->SetSentence(0, "m_x: " + std::to_string(m_x));
	m_Graphics->SetSentence(1, "m_y: " + std::to_string(m_y));
	m_Graphics->SetSentence(2, "m_z: " + std::to_string(m_z));

	m_Graphics->SetSentence(3, "g_x: " + std::to_string(g_x));
	m_Graphics->SetSentence(4, "g_y: " + std::to_string(g_y));
	m_Graphics->SetSentence(5, "g_z: " + std::to_string(g_z));
	m_Graphics->SetSentence(6, "");

	m_Graphics->SetSentence(7, "d_x: " + std::to_string(d_x));
	m_Graphics->SetSentence(8, "d_y: " + std::to_string(d_y));
	m_Graphics->SetSentence(9, "d_z: " + std::to_string(d_z));

	// Do the frame processing for the graphics object.
	bool uptd = false;
	if(m_Input->IsUPressed() == true)
	{
		uptd = true;
	}

	result = m_Graphics->Frame(posX, posY, posZ, rotX, rotY, rotZ, uptd);
	uptd = false;
	if(!result)
	{
		return false;
	}

	return true;
}


bool SystemClass::HandleInput(float frameTime)
{
	bool keyDown;
	bool result = true;

	/****************************************
	 * W = UpArrow		=> MoveForward		*
	 * S = DownArrow	=> MoveDownward		*
	 * A = LeftArrow	=> MoveLeftward		*
	 * D = RightArrow	=> MoveRightward	*
	 *										*
	 * Q = PgUp			=> MoveUpward		*
	 * Z = PgDown		=> MoveDownward		*
	 *										*
	 * MouseRightButton (hold) => Turn		*
	 ****************************************/
	
	// Set the frame time for calculating the updated position.
	m_Position->SetFrameTime(frameTime);

	// Handle the input.
	//keyDown = m_Input->IsLeftPressed();
	//m_Position->TurnLeft(keyDown);

	//keyDown = m_Input->IsRightPressed();
	//m_Position->TurnRight(keyDown);

	//keyDown = m_Input->IsUpPressed();
	//m_Position->MoveForward(keyDown);

	//keyDown = m_Input->IsDownPressed();
	//m_Position->MoveBackward(keyDown);

	//keyDown = m_Input->IsAPressed();
	//m_Position->MoveUpward(keyDown);

	//keyDown = m_Input->IsZPressed();
	//m_Position->MoveDownward(keyDown);

	//keyDown = m_Input->IsPgUpPressed();
	//m_Position->LookUpward(keyDown);

	//keyDown = m_Input->IsPgDownPressed();
	//m_Position->LookDownward(keyDown);
	
	keyDown = (m_Input->IsLeftPressed() || m_Input->IsAPressed());
	m_Position->MoveLeftward(keyDown);

	keyDown = (m_Input->IsRightPressed() || m_Input->IsDPressed());
	m_Position->MoveRightward(keyDown);

	keyDown = (m_Input->IsUpPressed() || m_Input->IsWPressed());
	m_Position->MoveForward(keyDown);

	keyDown = (m_Input->IsDownPressed() || m_Input->IsSPressed());
	m_Position->MoveBackward(keyDown);

	keyDown = (m_Input->IsPgUpPressed() || m_Input->IsQPressed());
	m_Position->MoveUpward(keyDown);

	keyDown = (m_Input->IsPgDownPressed() || m_Input->IsZPressed());
	m_Position->MoveDownward(keyDown);

	keyDown = m_Input->IsMouseRightPressed();
	int deltaX, deltaY;
	m_Input->GetMouseDelta(deltaX, deltaY);
	m_Position->Turn(keyDown, deltaX, deltaY);

	m_TimeElapsed += frameTime * 0.001f;
	if(m_TimeElapsed >= (m_MaxInputTestTime * 0.1f))
	{
		if(m_Input->IsRPressed())
		{
			m_WFPressed = true;
		}
		if(m_Input->IsTPressed())
		{
			m_WirePressed = true;
		}
	}
	if(m_TimeElapsed >= m_MaxInputTestTime)
	{
		if(m_WFPressed)
			result = m_Graphics->SetWireframe();
		if(m_WirePressed)
			m_Graphics->ToggleDebugMode();

		m_TimeElapsed = 0.0f;
		m_WFPressed = false;
		m_WirePressed = false;
	}

	return result;
}


LRESULT CALLBACK SystemClass::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	return DefWindowProc(hwnd, umsg, wparam, lparam);
}


void SystemClass::InitializeWindows(int& screenWidth, int& screenHeight)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;


	// Get an external pointer to this object.	
	ApplicationHandle = this;

	// Get the instance of this application.
	m_hinstance = GetModuleHandle(NULL);

	// Give the application a name.
	m_applicationName = L"Engine";

	// Setup the windows class with default settings.
	wc.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc   = WndProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = m_hinstance;
	wc.hIcon		 = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm       = wc.hIcon;
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize        = sizeof(WNDCLASSEX);
	
	// Register the window class.
	RegisterClassEx(&wc);

	// Determine the resolution of the clients desktop screen.
	screenWidth  = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	// Setup the screen settings depending on whether it is running in full screen or in windowed mode.
	if(FULL_SCREEN)
	{
		// If full screen set the screen to maximum size of the users desktop and 32bit.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize       = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth  = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;			
		dmScreenSettings.dmFields     = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Change the display settings to full screen.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// Set the position of the window to the top left corner.
		posX = posY = 0;
	}
	else
	{
		// If windowed then set it to 800x600 resolution.
		screenWidth  = 800;
		screenHeight = 600;

		// Place the window in the middle of the screen.
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth)  / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	// Create the window with the screen settings and get the handle to it.
	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName, 
						    WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
						    posX, posY, screenWidth, screenHeight, NULL, NULL, m_hinstance, NULL);

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	// Hide the mouse cursor.
	ShowCursor(false);

	return;
}


void SystemClass::ShutdownWindows()
{
	// Show the mouse cursor.
	ShowCursor(true);

	// Fix the display settings if leaving full screen mode.
	if(FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	// Remove the window.
	DestroyWindow(m_hwnd);
	m_hwnd = NULL;

	// Remove the application instance.
	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = NULL;

	// Release the pointer to this class.
	ApplicationHandle = NULL;

	return;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch(umessage)
	{
		// Check if the window is being destroyed.
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

		// Check if the window is being closed.
		case WM_CLOSE:
		{
			PostQuitMessage(0);		
			return 0;
		}

		// All other messages pass to the message handler in the system class.
		default:
		{
			return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
		}
	}
}
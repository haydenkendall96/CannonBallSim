#include "ConsoleGameEngine.h"
#include <iostream>
#include "CannonBall.h"
#include "Land.h"

float fTheta;
int gravity = 5;
CannonBall ball;
Land land;

ConsoleGameEngine::ConsoleGameEngine()
{
	m_nScreenWidth = 80;
	m_nScreenHeight = 30;

	m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	m_hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);

	std::memset(m_keyNewState, 0, 256 * sizeof(short));
	std::memset(m_keyOldState, 0, 256 * sizeof(short));
	std::memset(m_keys, 0, 256 * sizeof(sKeyState));

	m_bEnableSound = false;

	m_sAppName = L"Default";

	ball.Init(this, 117, 0, 10);
	land.Init(this, 0, 235, 10, 255);

}

ConsoleGameEngine::~ConsoleGameEngine()
{
	SetConsoleActiveScreenBuffer(m_hOriginalConsole);
	delete[] m_bufScreen;
}

int ConsoleGameEngine::ConstructConsole(int width, int height, int fontw, int fonth)
{
	if (m_hConsole == INVALID_HANDLE_VALUE)
		return Error(L"Bad Handle");

	m_nScreenWidth = width;
	m_nScreenHeight = height;

	m_rectWindow = { 0, 0, 1, 1 };
	SetConsoleWindowInfo(m_hConsole, TRUE, &m_rectWindow);

	// Set the size of the screen buffer
	COORD coord = { (short)m_nScreenWidth, (short)m_nScreenHeight };
	if (!SetConsoleScreenBufferSize(m_hConsole, coord))
		Error(L"SetConsoleScreenBufferSize");

	// Assign screen buffer to the console
	if (!SetConsoleActiveScreenBuffer(m_hConsole))
		return Error(L"SetConsoleActiveScreenBuffer");

	// Set the font size now that the screen buffer has been assigned to the console
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = fontw;
	cfi.dwFontSize.Y = fonth;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;

	wcscpy_s(cfi.FaceName, L"Consolas");
	if (!SetCurrentConsoleFontEx(m_hConsole, false, &cfi))
		return Error(L"SetCurrentConsoleFontEx");

	// Get screen buffer info and check the maximum allowed window size. Return
	// error if exceeded, so user knows their dimensions/fontsize are too large
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(m_hConsole, &csbi))
		return Error(L"GetConsoleScreenBufferInfo");
	if (m_nScreenHeight > csbi.dwMaximumWindowSize.Y)
		return Error(L"Screen Height / Font Height Too Big");
	if (m_nScreenWidth > csbi.dwMaximumWindowSize.X)
		return Error(L"Screen Width / Font Width Too Big");

	// Set Physical Console Window Size
	m_rectWindow = { 0, 0, (short)(m_nScreenWidth - 1), (short)(m_nScreenHeight - 1) };
	if (!SetConsoleWindowInfo(m_hConsole, TRUE, &m_rectWindow))
		return Error(L"SetConsoleWindowInfo");

	// Set flags to allow mouse input		
	if (!SetConsoleMode(m_hConsoleIn, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT))
		return Error(L"SetConsoleMode");

	// Allocate memory for screen buffer
	m_bufScreen = new CHAR_INFO[m_nScreenWidth * m_nScreenHeight];
	memset(m_bufScreen, 0, sizeof(CHAR_INFO) * m_nScreenWidth * m_nScreenHeight);

	SetConsoleCtrlHandler((PHANDLER_ROUTINE)CloseHandler, TRUE);
	return 1;
}

void ConsoleGameEngine::Draw(int x, int y, short c, short col)
{
	if (x >= 0 && x < m_nScreenWidth && y >= 0 && y < m_nScreenHeight)
	{
		m_bufScreen[y * m_nScreenWidth + x].Char.UnicodeChar = c;
		m_bufScreen[y * m_nScreenWidth + x].Attributes = col;
	}
}

void ConsoleGameEngine::Fill(int x1, int y1, int x2, int y2, short c, short col)
{
	Clip(x1, y1);
	Clip(x2, y2);
	for (int x = x1; x < x2; x++)
		for (int y = y1; y < y2; y++)
			Draw(x, y, c, col);
}

void ConsoleGameEngine::DrawString(int x, int y, std::wstring c, short col)
{
	for (size_t i = 0; i < c.size(); i++)
	{
		m_bufScreen[y * m_nScreenWidth + x + i].Char.UnicodeChar = c[i];
		m_bufScreen[y * m_nScreenWidth + x + i].Attributes = col;
	}
}

void ConsoleGameEngine::DrawStringAlpha(int x, int y, std::wstring c, short col)
{
	for (size_t i = 0; i < c.size(); i++)
	{
		if (c[i] != L' ')
		{
			m_bufScreen[y * m_nScreenWidth + x + i].Char.UnicodeChar = c[i];
			m_bufScreen[y * m_nScreenWidth + x + i].Attributes = col;
		}
	}
}

void ConsoleGameEngine::Clip(int& x, int& y)
{
	if (x < 0) x = 0;
	if (x >= m_nScreenWidth) x = m_nScreenWidth;
	if (y < 0) y = 0;
	if (y >= m_nScreenHeight) y = m_nScreenHeight;
}

void ConsoleGameEngine::DrawLine(int x1, int y1, int x2, int y2, short c, short col) 
{
	int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
	dx = x2 - x1; dy = y2 - y1;
	dx1 = abs(dx); dy1 = abs(dy);
	px = 2 * dy1 - dx1;	py = 2 * dx1 - dy1;
	if (dy1 <= dx1)
	{
		if (dx >= 0)
		{
			x = x1; y = y1; xe = x2;
		}
		else
		{
			x = x2; y = y2; xe = x1;
		}

		Draw(x, y, c, col);

		for (i = 0; x < xe; i++)
		{
			x = x + 1;
			if (px < 0)
				px = px + 2 * dy1;
			else
			{
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) y = y + 1; else y = y - 1;
				px = px + 2 * (dy1 - dx1);
			}
			Draw(x, y, c, col);
		}
	}
	else
	{
		if (dy >= 0)
		{
			x = x1; y = y1; ye = y2;
		}
		else
		{
			x = x2; y = y2; ye = y1;
		}

		Draw(x, y, c, col);

		for (i = 0; y < ye; i++)
		{
			y = y + 1;
			if (py <= 0)
				py = py + 2 * dx1;
			else
			{
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) x = x + 1; else x = x - 1;
				py = py + 2 * (dx1 - dy1);
			}
			Draw(x, y, c, col);
		}
	}
}

void ConsoleGameEngine::DrawCircle(int xc, int yc, int r, short c, short col)
{
	int x = 0;
	int y = r;
	int p = 3 - 2 * r;
	if (!r) return;

	while (y >= x) // only formulate 1/8 of circle
	{
		Draw(xc - x, yc - y, c, col);//upper left left
		Draw(xc - y, yc - x, c, col);//upper upper left
		Draw(xc + y, yc - x, c, col);//upper upper right
		Draw(xc + x, yc - y, c, col);//upper right right
		Draw(xc - x, yc + y, c, col);//lower left left
		Draw(xc - y, yc + x, c, col);//lower lower left
		Draw(xc + y, yc + x, c, col);//lower lower right
		Draw(xc + x, yc + y, c, col);//lower right right
		if (p < 0) p += 4 * x++ + 6;
		else p += 4 * (x++ - y--) + 10;
	}
}

void ConsoleGameEngine::FillCircle(int xc, int yc, int r, short c, short col)
{
	// Taken from wikipedia
	int x = 0;
	int y = r;
	int p = 3 - 2 * r;
	if (!r) return;

	auto drawline = [&](int sx, int ex, int ny)
		{
			for (int i = sx; i <= ex; i++)
				Draw(i, ny, c, col);
		};

	while (y >= x)
	{
		// Modified to draw scan-lines instead of edges
		drawline(xc - x, xc + x, yc - y);
		drawline(xc - y, xc + y, yc - x);
		drawline(xc - x, xc + x, yc + y);
		drawline(xc - y, xc + y, yc + x);
		if (p < 0) p += 4 * x++ + 6;
		else p += 4 * (x++ - y--) + 10;
	}
}

void ConsoleGameEngine::DrawRect(int x, int y, int l, int w, short c, short col)
{
	DrawLine(x, y, x + w, y);
	DrawLine(x, y, x, y + l);
	DrawLine(x + w, y, x + w, y + l);
	DrawLine(x + w, y + l, x, y+l);
}

void ConsoleGameEngine::Start()
{
	// Start the thread
	m_bAtomActive = true;
	std::thread t = std::thread(&ConsoleGameEngine::GameThread, this);

	// Wait for thread to be exited
	t.join();
}

int ConsoleGameEngine::ScreenWidth()
{
	return m_nScreenWidth;
}

int ConsoleGameEngine::ScreenHeight()
{
	return m_nScreenHeight;
}

bool ConsoleGameEngine::OnUserCreate()
{
	return true;
}

void ConsoleGameEngine::GameThread() 
{
	// Create user resources as part of this thread
	if (!OnUserCreate())
		m_bAtomActive = false;


	auto tp1 = std::chrono::system_clock::now();
	auto tp2 = std::chrono::system_clock::now();

	while (m_bAtomActive)
	{
		// Run as fast as possible
		while (m_bAtomActive)
		{
			// Handle Timing
			tp2 = std::chrono::system_clock::now();
			std::chrono::duration<float> elapsedTime = tp2 - tp1;
			tp1 = tp2;
			float fElapsedTime = elapsedTime.count();

			// Handle Keyboard Input
			for (int i = 0; i < 256; i++)
			{
				m_keyNewState[i] = GetAsyncKeyState(i);

				m_keys[i].bPressed = false;
				m_keys[i].bReleased = false;

				if (m_keyNewState[i] != m_keyOldState[i])
				{
					if (m_keyNewState[i] & 0x8000)
					{
						m_keys[i].bPressed = !m_keys[i].bHeld;
						m_keys[i].bHeld = true;
					}
					else
					{
						m_keys[i].bReleased = true;
						m_keys[i].bHeld = false;
					}
				}

				m_keyOldState[i] = m_keyNewState[i];
			}

			// Handle Mouse Input - Check for window events
			INPUT_RECORD inBuf[32];
			DWORD events = 0;
			GetNumberOfConsoleInputEvents(m_hConsoleIn, &events);
			if (events > 0)
				ReadConsoleInput(m_hConsoleIn, inBuf, events, &events);

			// Handle Frame Update
			if (!OnUserUpdate(fElapsedTime))
				m_bAtomActive = false;

			// Update Title & Present Screen Buffer
			wchar_t s[256];
			swprintf_s(s, 256, L"OneLoneCoder.com - Console Game Engine - %s - FPS: %3.2f", m_sAppName.c_str(), 1.0f / fElapsedTime);
			SetConsoleTitle(s);
			WriteConsoleOutput(m_hConsole, m_bufScreen, { (short)m_nScreenWidth, (short)m_nScreenHeight }, { 0,0 }, &m_rectWindow);
		}

		// Allow the user to free resources if they have overrided the destroy function
		if (OnUserDestroy())
		{
			// User has permitted destroy, so exit and clean up
			delete[] m_bufScreen;
			SetConsoleActiveScreenBuffer(m_hOriginalConsole);
			m_cvGameFinished.notify_one();
		}
		else
		{
			// User denied destroy for some reason, so continue running
			m_bAtomActive = true;
		}
	}
}

int ConsoleGameEngine::Error(const wchar_t* msg)
{
	wchar_t buf[256];
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buf, 256, NULL);
	SetConsoleActiveScreenBuffer(m_hOriginalConsole);
	wprintf(L"ERROR: %s\n\t%s\n", msg, buf);
	return 0;
}

BOOL ConsoleGameEngine::CloseHandler(DWORD evt)
{
	if (evt == CTRL_CLOSE_EVENT)
	{
		m_bAtomActive = false;

		// Wait for thread to be exited
		std::unique_lock<std::mutex> ul(m_muxGame);
		m_cvGameFinished.wait(ul);
	}
	return true;
}


// Optional for clean up 
bool ConsoleGameEngine::OnUserDestroy()
{
	return true;
}

//Handle sim logic here
bool ConsoleGameEngine::OnUserUpdate(float fElapsedTime)
{
	Fill(0, 0, ScreenWidth(), ScreenHeight(), 0x2588, 0x0000);
	fTheta += 1.0f * fElapsedTime;

	if (m_keys[VK_LEFT].bHeld)
	{
		ball.SetXPos(ball.getXPos() - 1);
	}
	if (m_keys[VK_RIGHT].bHeld)
	{
		ball.SetXPos(ball.getXPos() + 1);
	}

	if (m_keys[VK_UP].bHeld && ball.getYPos() > 10)
	{
		ball.SetYPos(ball.getYPos() - 1);
	}
	else
	{
		if (ball.getYPos() < 223)
		{
			ball.SetYPos(ball.getYPos() + (gravity * fTheta));
		}
	}

	if (m_keys[VK_UP].bReleased)
	{
		fTheta = 0;
	}
	
	ball.Draw();
	land.Draw();

	return true;
}
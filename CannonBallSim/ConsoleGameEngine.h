#pragma once
#pragma comment(lib, "winmm.lib")

#ifndef UNICODE
#error Please enable UNICODE for your compiler! VS: Project Properties -> General -> \
Character Set -> Use Unicode. Thanks! - Javidx9
#endif

#include <windows.h>

#include <iostream>
#include <chrono>
#include <vector>
#include <list>
#include <thread>
#include <atomic>
#include <condition_variable>

class ConsoleGameEngine
{
public:
	ConsoleGameEngine();

	int ConstructConsole(int width, int height, int fontw, int fonth);

	virtual void Draw(int x, int y, short c = 0x2588, short col = 0x000F);
	void Fill(int x1, int y1, int x2, int y2, short c = 0x2588, short col = 0x000F);
	void DrawString(int x, int y, std::wstring c, short col = 0x000F);
	void DrawStringAlpha(int x, int y, std::wstring c, short col = 0x000F);
	void Clip(int& x, int& y);
	void DrawLine(int x1, int y1, int x2, int y2, short c = 0x2588, short col = 0x000F);


	void DrawCircle(int xc, int yc, int r, short c = 0x2588, short col = 0x000F);

	void FillCircle(int xc, int yc, int r, short c = 0x2588, short col = 0x000F);

	void Start();

	int ScreenWidth();
	int ScreenHeight();

	// User MUST OVERRIDE THESE!!
	virtual bool OnUserCreate();
	virtual bool OnUserUpdate(float fElapsedTime);

	// Optional for clean up 
	virtual bool OnUserDestroy();


	~ConsoleGameEngine();


private:
	void GameThread();
	

protected:
	int Error(const wchar_t* msg);

	static BOOL CloseHandler(DWORD evt);

protected:
	int m_nScreenWidth;
	int m_nScreenHeight;
	CHAR_INFO* m_bufScreen;
	std::wstring m_sAppName;
	HANDLE m_hOriginalConsole;
	CONSOLE_SCREEN_BUFFER_INFO m_OriginalConsoleInfo;
	HANDLE m_hConsole;
	HANDLE m_hConsoleIn;
	SMALL_RECT m_rectWindow;
	short m_keyOldState[256] = { 0 };
	short m_keyNewState[256] = { 0 };
	bool m_mouseOldState[5] = { 0 };
	bool m_mouseNewState[5] = { 0 };
	bool m_bConsoleInFocus = true;
	bool m_bEnableSound = false;

	// These need to be static because of the OnDestroy call the OS may make. The OS
	// spawns a special thread just for that
	static std::atomic<bool> m_bAtomActive;
	static std::condition_variable m_cvGameFinished;
	static std::mutex m_muxGame;
};


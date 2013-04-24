
#include "Game.h"
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <string>

#ifdef _DEBUG
	#include "vld.h"
#endif

void showWin32Console()
{
	static const WORD MAX_CONSOLE_LINES = 500;
	int hConHandle;
	long lStdHandle;
	CONSOLE_SCREEN_BUFFER_INFO coninfo;
	FILE *fp;
	// allocate a console for this app
	AllocConsole();
	// set the screen buffer to be big enough to let us scroll text
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
	coninfo.dwSize.Y = MAX_CONSOLE_LINES;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),
		coninfo.dwSize);
	// redirect unbuffered STDOUT to the console
	lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen( hConHandle, "w" );
	*stdout = *fp;
	setvbuf( stdout, NULL, _IONBF, 0 );
	// redirect unbuffered STDIN to the console
	lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen( hConHandle, "r" );
	*stdin = *fp;
	setvbuf( stdin, NULL, _IONBF, 0 );
	// redirect unbuffered STDERR to the console
	lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen( hConHandle, "w" );
	*stderr = *fp;
	setvbuf( stderr, NULL, _IONBF, 0 );
	// make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog
	// point to console as well
	std::ios::sync_with_stdio();
}


#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif
 
#ifdef __cplusplus
extern "C" {
#endif
 
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
		showWin32Console();
        // Create application object
        //Application app;
		Game app;
		
        try {
            app.run();
        } catch( Ogre::Exception& e ) {
			std::cout << " ! Exception : An exception has occurred: " <<
            e.getFullDescription().c_str() << std::endl;

//#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBoxA( NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
//#else

//#endif
        } 
		catch( AbstractException&)	{
			
		}
		catch(My_Exception& exc)
		{
			  MessageBoxA( NULL, exc.what(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
		}
		catch(std::exception& exc)
		{
			MessageBoxA( NULL, exc.what(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
		}
		FreeConsole();
        return 0;
    }
	

#ifdef __cplusplus
}
#endif
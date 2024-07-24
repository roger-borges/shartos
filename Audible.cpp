#include "Audible.h"


audible::audible()
{
	//object::addType(std::string("audible"));

	// COM setup.
	HRESULT CoInitializeEx( void *pvReserved, DWORD dwCoInit );
	
	//get the current time and assign it to this->time here

	// Create the performance object.
	CoCreateInstance(CLSID_DirectMusicPerformance, NULL, CLSCTX_INPROC,
						IID_IDirectMusicPerformance8, (void**) &_performance);

	// Handle to active window.
	HWND hwnd = ::GetActiveWindow();

	// Initialize audio.
	_performance->InitAudio(
			NULL,			// No interface needed.
			NULL,			// No interface needed.
			hwnd,			// Handle to the window.
			DMUS_APATH_DYNAMIC_3D,//DMUS_APATH_SHARED_STEREOPLUSREVERB,	// Default audiopath.
			64,				// 64 channels allocated to the audiopath.
			DMUS_AUDIOF_ALL,		// Allow all synthesizer features.
			NULL			//Default audio parameters.
		);// End initialize audio.

//	loadSound("laser.wav");
//	startSound("laser.wav");
	loadMusic("battle.mid");
	startMusic("battle.mid");
}

// Sound system destructor
audible::~audible()
{
	// Shut down the performance object
	_performance->CloseDown();
	// Release the loader object
	_loader->Release();
	// Release the performance object
	_performance->Release();

	for(std::map<std::string, IDirectMusicSegment8*>::iterator itr=_music.begin(); itr!=_music.end(); ++itr)
	{
		(*itr).second->Release();
	}
	for(std::map<std::string, IDirectMusicSegment8*>::iterator itr=_sound.begin(); itr!=_sound.end(); ++itr)
	{
		(*itr).second->Release();
	}
	
	// Uninitialize Com
	CoUninitialize();
}

// Music Loader
void audible::loadMusic(const std::string& bgmusic)
{
	// Create loader
	CoCreateInstance(CLSID_DirectMusicLoader, NULL, CLSCTX_INPROC,
						 IID_IDirectMusicLoader8, (void**) &_loader);
	// Create music segment
	CoCreateInstance(CLSID_DirectMusicSegment, NULL, CLSCTX_INPROC, 
						IID_IDirectMusicSegment8, (void**) &_music[bgmusic]);

	// Define the search path
	char SearchPath[MAX_PATH];
	WCHAR wSearchPath[MAX_PATH];

	// Get the directory for the music
	GetCurrentDirectory(MAX_PATH, SearchPath);
	std::string current_directory(SearchPath);
	current_directory += "\\Load\\Music\\";
	strcpy(SearchPath, current_directory.c_str());

	// Converts character array to WCHAR array for the search path
	MultiByteToWideChar(CP_ACP, 0, SearchPath, -1, wSearchPath, MAX_PATH);

	// Set the search directory enabling all music types
	_loader->SetSearchDirectory(GUID_DirectMusicAllTypes, wSearchPath, FALSE);

	// Set the file to be played
	char filename[MAX_PATH] = "battle.mid";//Battle.mid
	WCHAR wfilename[MAX_PATH];

	// Converts chracter array to WCHAR array for the file name.
	MultiByteToWideChar(CP_ACP, 0, filename, -1, wfilename, MAX_PATH);

	// If object fails to load, display message.
	if(FAILED(_loader->LoadObjectFromFile(
	   CLSID_DirectMusicSegment,	// Class identifier.
	   IID_IDirectMusicSegment8,	// ID of desired interface.
	   wfilename,					// Filename.
	   (void**) &_music[bgmusic])))		// Pointer that receives interface.
	{
		MessageBox( NULL, "Media not found, sample will now quit.",
					"Shartos Music", MB_OK );
	}// Message in case file isn't found.

	// Download the music's band.
	_music[bgmusic]->Download(_performance);
	// Loop the music.
	_music[bgmusic]->SetRepeats(DMUS_SEG_REPEAT_INFINITE);
}

// Start playing the music.
void audible::startMusic(const std::string& seg_name)
{
	_performance->PlaySegmentEx(
		_music[seg_name],	// Segment to play.
		NULL,		// Used for songes; not implemented.
		NULL,		// For transitions.
		0,			// Flags.
		0,			// Start time; 0 is immediate.
		NULL,		// Pointer that receives segment state.
		NULL,		// Object to stop.
		NULL		// Audiopath, if not default.
	);

	_current_music = "Battle.mid";
}

// Stop playing the music.
void audible::stopMusic()
{
	_performance->Stop(
		NULL,	// Stop all segments.
		NULL,	// Stop all segment states.
		0,		// Do it immediately.
		0		// Flags.
	);
}

const std::string audible::getMusic()
{
	return _current_music;
}

void audible::loadSound(const std::string& act_sound)
{
	// Create loader.
	CoCreateInstance(CLSID_DirectMusicLoader, NULL, CLSCTX_INPROC,
						 IID_IDirectMusicLoader8, (void**) &_loader);
	// Create sound segment.
	CoCreateInstance(CLSID_DirectMusicSegment, NULL, CLSCTX_INPROC, 
						IID_IDirectMusicSegment8, (void**) &_sound[act_sound]);

	// Define the music.
	char SearchPath[MAX_PATH];
	WCHAR wSearchPath[MAX_PATH];

	// Get the directory for the music.
	GetCurrentDirectory(MAX_PATH, SearchPath);
	std::string current_directory(SearchPath);
	current_directory += "\\Load\\Sound\\";
	strcpy(SearchPath, current_directory.c_str());

	// Converts character array to WCHAR array for the search path.
	MultiByteToWideChar(CP_ACP, 0, SearchPath, -1, wSearchPath, MAX_PATH);

	// Set the search directory enabling all music types.
	_loader->SetSearchDirectory(GUID_DirectMusicAllTypes, wSearchPath, FALSE);

	// Set the file to be played.
	char filename[MAX_PATH];// = "laer.wav";
		strcpy(filename,act_sound.c_str());//copy the passed in value(act_sound) into the filename variable
	//char filename[MAX_PATH];
	WCHAR wfilename[MAX_PATH];

	//filename[MAX_PATH] = "explosion.wav";
	//WCHAR wfilename[MAX_PATH];

	// Converts chracter array to WCHAR array for the file name.
	MultiByteToWideChar(CP_ACP, 0, filename, -1, wfilename, MAX_PATH);

	// If object fails to load, display message.
	if(FAILED(_loader->LoadObjectFromFile(
	   CLSID_DirectMusicSegment,	// Class identifier.
	   IID_IDirectMusicSegment8,	// ID of desired interface.
	   wfilename,					// Filename.
	   (void**) &_sound[act_sound])))		// Pointer that receives interface.
	{
		MessageBox( NULL, "Media not found, sample will now quit.",
					"Shartos sound", MB_OK );
	}// Message in case file isn't found.

	// Download the sound's band.
	_sound[act_sound]->Download(_performance);
	// Loop the sound
	//_sound[act_sound]->SetRepeats(DMUS_SEG_REPEAT_INFINITE);

	/*
	//Sound #2
	// Set the file to be played
	filename[MAX_PATH] = "laser.wav";
	//WCHAR wfilename[MAX_PATH];

	// Converts chracter array to WCHAR array for the file name.
	MultiByteToWideChar(CP_ACP, 0, filename, -1, wfilename, MAX_PATH);

	// If object fails to load, display message.
	if(FAILED(_loader->LoadObjectFromFile(
	   CLSID_DirectMusicSegment,	// Class identifier.
	   IID_IDirectMusicSegment8,	// ID of desired interface.
	   wfilename,					// Filename.
	   (void**) &_sound[act_sound])))		// Pointer that receives interface.
	{
		MessageBox( NULL, "Media not found, sample will now quit.",
					"Shartos sound", MB_OK );
	}// Message in case file isn't found.

	// Download the sound's band.
	_sound[act_sound]->Download(_performance);
	// Loop the sound
	_sound[act_sound]->SetRepeats(DMUS_SEG_REPEAT_INFINITE);

*/

}

// Start playing the sound.
void audible::startSound(const std::string& sound_name)
{
	_performance->PlaySegmentEx(
		_sound[sound_name],	// Segment to play.
		NULL,		// Used for songes; not implemented.
		NULL,		// For transitions.
		DMUS_SEGF_SECONDARY,			// Flags.
		0,			// Start time; 0 is immediate.
		NULL,		// Pointer that receives segment state.
		NULL,		// Object to stop.
		NULL		// Audiopath, if not default.
	);
}
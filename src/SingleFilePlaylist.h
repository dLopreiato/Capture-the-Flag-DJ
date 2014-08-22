#ifndef INCLUDED_SINGLE_FILE_PLAYLIST
#define INCLUDED_SINGLE_FILE_PLAYLIST
#include "IPlaylist.h"
#include <string>
#include <irrKlang.h>

class SingleFilePlaylist : public IPlaylist {
public:
    SingleFilePlaylist(irrklang::ISoundEngine* engine, char* filename);
    ~SingleFilePlaylist();
    Music* GetNextMusic();
private:
    char* filename_;
    irrklang::ISoundEngine* engine_;
};

#endif
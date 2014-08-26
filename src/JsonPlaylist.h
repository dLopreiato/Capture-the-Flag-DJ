#ifndef INCLUDED_JSON_PLAYLIST
#define INCLUDED_JSON_PLAYLIST
#include "IPlaylist.h"
#include <irrKlang.h>
#include "document.h"

class JsonPlaylist : public IPlaylist {
public:
    JsonPlaylist(irrklang::ISoundEngine* engine, char* jsonFile);
    ~JsonPlaylist();
    Music* GetNextMusic();
private:
    unsigned int nextSong_;
    rapidjson::Document playlist_;
    char* jsonFile_;
    char* jsonContents_;
    irrklang::ISoundEngine* engine_;
};

#endif
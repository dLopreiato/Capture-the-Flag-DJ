#ifndef INCLUDED_SINGLE_FILE_PLAYLIST
#define INCLUDED_SINGLE_FILE_PLAYLIST
#include "IPlaylist.h"
#include <string>

class SingleFilePlaylist : public IPlaylist {
public:
    SingleFilePlaylist(const std::string& filename);
    ~SingleFilePlaylist();
    MusicMetadata* GetNextMusic();
private:
    std::string filename_;
    MusicMetadata* nextMusic_;
};

#endif
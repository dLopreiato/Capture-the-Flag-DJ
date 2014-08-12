#include "SingleFilePlaylist.h"

SingleFilePlaylist::SingleFilePlaylist(const std::string& filename) : filename_(filename) {
    sf::Music* nextMusicObject = new sf::Music();
    nextMusicObject->openFromFile(filename);
    nextMusic_ = new MusicMetadata(nextMusicObject);
}

SingleFilePlaylist::~SingleFilePlaylist() {
    delete nextMusic_->music;
    delete nextMusic_;
}

MusicMetadata* SingleFilePlaylist::GetNextMusic() {
    // hold onto the value we'll return, but first we'll queue up the next song
    MusicMetadata* returningValue = nextMusic_;

    sf::Music* nextMusicObject = new sf::Music();
    nextMusicObject->openFromFile(filename_);
    nextMusic_ = new MusicMetadata(nextMusicObject);

    return returningValue;
}
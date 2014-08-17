#include "SingleFilePlaylist.h"

SingleFilePlaylist::SingleFilePlaylist(const std::string& filename) : filename_(filename) {
    sf::Music* nextMusicObject = new sf::Music();
    nextMusicObject->openFromFile(filename);
}

SingleFilePlaylist::~SingleFilePlaylist() {
}

MusicMetadata* SingleFilePlaylist::GetNextMusic() {
    sf::Music* nextMusicObject = new sf::Music();
    nextMusicObject->openFromFile(filename_);
    return new MusicMetadata(nextMusicObject);
}
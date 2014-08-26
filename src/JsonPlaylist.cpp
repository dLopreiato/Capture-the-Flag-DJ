#include "JsonPlaylist.h"
#include "rapidjson.h"
#include "document.h"
#include <fstream>

JsonPlaylist::JsonPlaylist(irrklang::ISoundEngine* engine, char* jsonFile) : engine_(engine),
    jsonFile_(jsonFile), nextSong_(0) {
    std::ifstream fStream;
    fStream.open(jsonFile_, std::fstream::in | std::fstream::binary);
    if (fStream.fail()) {
        throw "Oh Fuck.";
    }
    fStream.seekg(0, std::ios::end);
    int length = (int)(fStream.tellg());
    fStream.seekg(0, std::ios::beg);
    jsonContents_ = new char[length];
    fStream.read(jsonContents_, length);
    jsonContents_[length] = '\0';
    fStream.close();
    if (playlist_.Parse<0>(jsonContents_).HasParseError()) {
        throw "Nope. Not valid.";
    }
}

JsonPlaylist::~JsonPlaylist() {
    delete jsonContents_;
}

Music* JsonPlaylist::GetNextMusic() {
    Music* returnValue = new Music(engine_->play2D(
        playlist_["songs"][nextSong_]["path"].GetString(), false, true, true));
    nextSong_++;
    if (nextSong_ >= playlist_["songs"].Size())
        nextSong_ = 0;
    return returnValue;
}
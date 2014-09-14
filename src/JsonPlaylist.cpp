#include "JsonPlaylist.h"
#include "rapidjson.h"
#include "document.h"
#include <fstream>
#include <exception>

JsonPlaylist::JsonPlaylist(irrklang::ISoundEngine* engine, char* jsonFile) : engine_(engine),
    jsonFile_(jsonFile), nextSong_(0) {
    std::ifstream fStream;
    fStream.open(jsonFile_, std::fstream::in | std::fstream::binary);
    if (fStream.fail()) {
        throw "This has broken.";
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

Music* JsonPlaylist::GetNextMusic() {
    irrklang::ISound* sound = nullptr;
    unsigned int loopingPoint = nextSong_;

    // sets the looping point variable to the song index previous to what comes next
    loopingPoint = (loopingPoint == 0) ? (playlist_["songs"].Size() - 1) : (loopingPoint - 1);

    // as long as we don't have a sound, and we didn't just loop through the entire list
    bool shouldContinueLooping = true;
    while (shouldContinueLooping) {
        sound = engine_->play2D(playlist_["songs"][nextSong_]["path"].GetString(), false, true,
            true);

        nextSong_++;
        if (nextSong_ >= playlist_["songs"].Size())
            nextSong_ = 0;

        shouldContinueLooping = sound == nullptr && loopingPoint != nextSong_;
    }

    if (sound == nullptr)
        throw std::exception("This playlist contains no valid songs.");

    return new Music(sound);
}
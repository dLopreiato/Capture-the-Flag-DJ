#ifndef INCLUDED_MUSIC_METADATA
#define INCLUDED_MUSIC_METADATA
#include <SFML\Audio\Music.hpp>


struct MusicMetadata {

    MusicMetadata(sf::Music* musicP) {
        music = musicP;
        wasStarted = false;
        fadeInOffset = sf::microseconds(0);
        fadeOutOffset = musicP->getDuration();
        pauseMarker = sf::microseconds(0);
    }

    MusicMetadata(MusicMetadata& copy) {
        music = copy.music;
        wasStarted = copy.wasStarted;
        fadeInOffset = copy.fadeInOffset;
        fadeOutOffset = copy.fadeOutOffset;
        pauseMarker = copy.pauseMarker;
    }

    /* The pointer to the Music that this refers to. */
    sf::Music* music;

    /* True if the Music has been started at some point. */
    bool wasStarted;
    
    /* The time the song should start fading in at. */
    sf::Time fadeInOffset;

    /* The time the song should be finished fading out by. */
    sf::Time fadeOutOffset;

    /* The time the song was paused, and should be reset to before it's unpaused. */
    sf::Time pauseMarker; // This field allows for fading in and out of pauses.

    /* Updates the pauseMarker to the current time marker. */
    void UpdatePauseMarker() {
        pauseMarker = music->getPlayingOffset();
    }

    /* Sets the Music position offset to the value of the pause marker. */
    void SetToPauseMarker() {
        music->setPlayingOffset(pauseMarker);
    }

    /* Gets the amount of time that remains before the song should be completely stopped. */
    sf::Time GetTimeToEnd() {
        return fadeOutOffset - music->getPlayingOffset();
    }

    /* True if the song is in a state where it should be disposed. */
    bool IsFinished() {
        return (music->getStatus() == sf::Music::Stopped) ||
            (music->getPlayingOffset() >= fadeOutOffset);
    }
};

#endif
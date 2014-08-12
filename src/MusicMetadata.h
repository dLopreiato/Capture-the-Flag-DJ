#ifndef INCLUDED_MUSIC_METADATA
#define INCLUDED_MUSIC_METADATA
#include <SFML\Audio\Music.hpp>


struct MusicMetadata {

    MusicMetadata(sf::Music* musicP) {
        music = musicP;
        wasStarted = false;
        fadeInOffset = sf::microseconds(0);
        fadeOutOffset = sf::microseconds(0);
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
    
    /* The time the song should be at full fade by. */
    sf::Time fadeInOffset;

    /* The time the song should begin to fade out. */
    sf::Time fadeOutOffset;

    /* The time the song was paused, and should be reset to before it's unpaused. */
    sf::Time pauseMarker; // This field allows for fading in and out of pauses.
};

#endif
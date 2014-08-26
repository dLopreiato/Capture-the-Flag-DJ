#ifndef INCLUDED_MUSIC_MANAGER
#define INCLUDED_MUSIC_MANAGER
#include <vector>
#include "MusicContext.h"
#include "IPlaylist.h"
#include <SFML/System/Clock.hpp>

typedef unsigned int PlaylistID;


class MusicManager {
public: 
	/* Constructs a MusicManager. MusicManger starts paused. */
	MusicManager(sf::Time fadeDuration = sf::milliseconds(1300));

	/* Destructs the MusicManager. */
	~MusicManager();

	/* Must be called regularly in order to do proper functionality. */
	void Update(sf::Time elapsedTime);
	
    /* Returns the current context */
    const MusicContext* GetContext();

    /* If true, all music will pause. If false, all music will unpause. */
    void SetPause(bool paused);

    /* If true, all music will go to a lower volume (for easier voice over).
       If false, volume will be set to full. */
    void SetLowVolume(bool lowVolume);

    /* Ends the current song playing, and plays the next song. */
    void NextSong();

    /* Sets the next song to be played to be pulled from the specified playlist. */
    void SetNextPlaylist(PlaylistID playlistId);

    /* Adds a playlist to the MusicManager, and returns an identifier to */
    PlaylistID AddPlaylist(IPlaylist* playlist);

private:

    void ClearPrevious();
    void StartCurrent();
    float AdjustFader(float currentVolume, float goalVolume, sf::Time elapsedTime,
        float lowestVolume, float highestVolume);
    
    Music* currentMusic_;
    float currentPauseFader_;
    float currentTalkFader_;
    float currentTimeFader_;
    sf::Time defaultFadeDuration_;
    float goalPauseFader_;
    float goalTalkFader_;
    MusicContext musicContext_;
    PlaylistID nextPlaylist_;
    bool paused_;
    std::vector<IPlaylist*> playlists_;
    Music* previousMusic_;
    float previousTimeFader_;
    
};

#endif
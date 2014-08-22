#ifndef INCLUDED_MUSIC
#define INCLUDED_MUSIC
#include <irrKlang.h>
#include <SFML\System\Time.hpp>

class Music {
public:
	/* Constructs a Music from an ISound. */
	Music(irrklang::ISound* sound, sf::Time startOffset = sf::microseconds(0), sf::Time finishOffset = sf::microseconds(0));
	/* Destructs a Music. */
	~Music();
	
	/* Changes the Music volume. 0.0f is no volume. 1.0f is full volume. */
	void SetVolume(float volume);
	/* Returns the volume of this Music. */
	float GetVolume();
	/* Plays the song. */
	void Play();
	/* Pauses the song. */
	void Pause();
	/* Moves the song playing position to the given time. */
	void SetPlayPosition(sf::Time time);
	/* Returns the current playing position.*/
	sf::Time GetPlayPosition();
	/* Sets the pause marker to the current time. */
	void UpdatePauseMarker();
	/* Sets the music position to the last time UpdatePauseMarker was called. */
	void SetToPauseMarker();
	/* Returns the amount of time that remains before the song should be completely stopped. */
	sf::Time GetTimeToEnd();
	/* Returns true if the song is in a state where it should be disposed. */
	bool IsFinished();

private:
	irrklang::ISound* sound_;
	irrklang::ik_u32 pauseMarker_;
	irrklang::ik_u32 startOffset_;
	irrklang::ik_u32 finishOffset_;
};

#endif
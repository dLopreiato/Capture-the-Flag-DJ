#include "Music.h"

Music::Music(irrklang::ISound* sound, sf::Time startOffset, sf::Time finishOffset) {
	sound_ = sound;
	startOffset_ = startOffset.asMilliseconds();
	sound_->setPlayPosition(startOffset_);
	finishOffset_ = (finishOffset == sf::microseconds(0)) ? (sound_->getPlayLength()) : (finishOffset.asMilliseconds());
}

Music::~Music() {
    sound_->stop();
	sound_->drop();
	delete sound_;
}

void Music::SetVolume(float volume) {
	sound_->setVolume(volume);
}

float Music::GetVolume() {
	return sound_->getVolume();
}

void Music::Play() {
	sound_->setIsPaused(false);
}

void Music::Pause() {
	sound_->setIsPaused();
}

void Music::SetPlayPosition(sf::Time time) {
	sound_->setPlayPosition(time.asMilliseconds());
}

sf::Time Music::GetPlayPosition() {
	return sf::milliseconds(sound_->getPlayPosition());
}

void Music::UpdatePauseMarker() {
	pauseMarker_ = sound_->getPlayPosition();
}

void Music::SetToPauseMarker() {
	sound_->setPlayPosition(pauseMarker_);
}

sf::Time Music::GetTimeToEnd() {
    return sf::milliseconds(finishOffset_ - sound_->getPlayPosition());
}

bool Music::IsFinished() {
	return sound_->isFinished() || (sound_->getPlayPosition() >= finishOffset_);
}
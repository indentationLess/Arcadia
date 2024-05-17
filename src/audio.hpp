#include <SFML/Audio.hpp>
#include <memory>
class SoundEffect {
public:
  SoundEffect(const std::string &filePath) {
    if (!m_buffer.loadFromFile(filePath)) {
      // Handle error
    }
    m_sound.setBuffer(m_buffer);
  }

  void play() { m_sound.play(); }

  void pause() { m_sound.pause(); }

  void stop() { m_sound.stop(); }

  bool isPlaying() const { return m_sound.getStatus() == sf::Sound::Playing; }

  void setVolume(float volume) { m_sound.setVolume(volume); }

  void setPitch(float pitch) { m_sound.setPitch(pitch); }

  void setLoop(bool loop) { m_sound.setLoop(loop); }

private:
  sf::SoundBuffer m_buffer;
  sf::Sound m_sound;
  
};
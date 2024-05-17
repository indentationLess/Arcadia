#include <SFML/Graphics.hpp>

class ScoreRenderer {
public:
  ScoreRenderer(sf::Font &font, unsigned int size, sf::Color color, float x,
                float y)
      : m_text("", font, size) {
    m_text.setFillColor(color);
    m_text.setPosition(x, y);
    m_score = 0;
  }

  void setPosition(float x, float y) { m_text.setPosition(x, y); }

  void setColor(sf::Color color) { m_text.setFillColor(color); }

  void setCharacterSize(unsigned int size) { m_text.setCharacterSize(size); }

  void setScore(int score) {
    m_score = score;
    updateText();
  }

  void addToScore(int points) {
    m_score += points;
    updateText();
  }

  void draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_text, states);
  }
  int m_score;

private:
  void updateText() { m_text.setString(std::to_string(m_score)); }

  sf::Text m_text;
};
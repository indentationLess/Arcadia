#include <SFML/Graphics.hpp>

class AIBat {
private:
    sf::Vector2f aiBatPosition;
    double aiBatSpeed = 0.25f;
    sf::RectangleShape aiBatObject;

public:
    AIBat(double x, double y);
    sf::Vector2f getAIBatPosition();
    sf::RectangleShape getAIBatObject();
    sf::FloatRect getAIBatFloatRect();
    void moveAIBatLeft();
    void moveAIBatRight();
    void update();
    void AIBatSpeedReverse();
};
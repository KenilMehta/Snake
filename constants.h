
namespace constants{
    constexpr int windowsWidth = 500;
    constexpr int windowsHeight = 500;
    constexpr int radius = 10;
    const sf::Color BodyColor{sf::Color::Red};
    const sf::Color FruitColor{sf::Color::Green};
    const sf::Color FruitInsideBody{sf::Color::Blue};
    enum directions{
        up = 0,
        down = 1,
        left = 2,
        right = 3,
        noInput = 4
    };
}

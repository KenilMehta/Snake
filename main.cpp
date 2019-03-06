#include "Snake.h"
#include <stdlib.h>
#include <thread>
#include <time.h>
using namespace std;

sf::CircleShape createFruit(const Snake & s,const sf::Color & color){
    srand(time(NULL));
    int x;
    int y;
    while(true){
        x = rand() % constants::windowsWidth;
        y = rand() % constants::windowsHeight;
        if(!s.isPointInsideSnake(x,y)){
            break;
        }
    }
    return s.createSnakeBodyElement(x,y,color);
}

int main(){


    sf::RenderWindow window{{constants::windowsWidth,constants::windowsHeight},"Snake"};
    window.setFramerateLimit(60);

    Snake snake;
    bool isEaten = true;
    sf::CircleShape fruit;
    while(true){
        window.clear(sf::Color::Black);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) break;

        if(isEaten){
            fruit = createFruit(snake,sf::Color::Green);
            isEaten = false;
        }

        window.draw(fruit);

        if(!snake.update(fruit,isEaten)){
            break;
        }
        snake.display(window);

        window.display();
       // std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
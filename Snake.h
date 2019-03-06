#include <SFML/Graphics.hpp>
#include <deque>
#include <unordered_set>
#include "constants.h"

#include <iostream>

struct Hasher{
    float operator()(const sf::CircleShape & circle) const {
        const auto & x = circle.getPosition().x;
        const auto & y = circle.getPosition().y;

        return constants::windowsHeight*y + x;
    }
};
struct AreEqualCircles{
    bool operator()(const sf::CircleShape & c1,const sf::CircleShape & c2) const {
        return (c1.getPosition().x == c2.getPosition().x) && (c1.getPosition().y == c2.getPosition().y);
    }
};

class Snake {

private:
    std::deque<sf::CircleShape> body_;
    std::unordered_set<sf::CircleShape,Hasher,AreEqualCircles> points_;
    constants::directions dir_;
public:

    Snake(){
        dir_ = constants::directions::noInput;
        auto  head = createSnakeBodyElement(constants::windowsWidth/2,constants::windowsHeight/2);
        body_.push_front(createSnakeBodyElement(constants::windowsWidth/2,constants::windowsHeight/2));
        points_.insert(head);
    }

    bool isPointInsideSnake(int x,int y) const noexcept{
        return points_.find(createSnakeBodyElement(x,y)) != points_.end();
    }

    bool move(){

        const auto head = body_.front();
        sf::Vector2f newHead;
        switch (dir_){
            case constants::directions::left:
                newHead.x = head.getPosition().x - 2;
                if(newHead.x < 0){
                    newHead.x = constants::windowsWidth;
                }
                newHead.y = head.getPosition().y;
                break;

            case constants::directions::right:
                newHead.x = head.getPosition().x + 2;
                if(newHead.x > constants::windowsWidth){
                    newHead.x = 0;
                }
                newHead.y = head.getPosition().y;
                break;

            case constants::directions::up:
                newHead.x = head.getPosition().x;
                newHead.y = head.getPosition().y - 2;
                if(newHead.y < 0 ){
                    newHead.y = constants::windowsHeight;
                }
                break;

            case constants::directions::down:
                newHead.x = head.getPosition().x;
                newHead.y = head.getPosition().y + 2;
                if(newHead.y > constants::windowsHeight){
                    newHead.y = 0;
                }
                break;

            case constants::directions::noInput:
                return true;

        }
        if(isColliding(newHead)){
            return false;
        }

        points_.insert(createSnakeBodyElement(newHead.x,newHead.y));
        body_.push_front(createSnakeBodyElement(newHead.x,newHead.y));

        auto tail = body_.back();
        if(isTailFood()){
            body_.back().setFillColor(constants::BodyColor);
        }else{
            points_.erase(tail);
            body_.pop_back();
        }
        return true;
    }

    bool isTailFood() const noexcept{
        return body_.back().getFillColor() == constants::FruitInsideBody;
    }

    sf::CircleShape createSnakeBodyElement(int x,int y,const sf::Color color = constants::BodyColor) const noexcept{
        sf::CircleShape shape;
        shape.setPosition(x,y);
        shape.setRadius(constants::radius);
        shape.setFillColor(color);
        shape.setOrigin(constants::radius,constants::radius);
        return shape;
    }

    void display(sf::RenderWindow & window) const noexcept{
        for(const auto & point:body_ ){
            window.draw(point);
        }
    }

    void takeUserInput(){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) ){
            dir_ = constants::directions::left;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            dir_ = constants::directions::right;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
            dir_ = constants::directions::up;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){
            dir_ = constants::directions::down;
        }
    }

    bool update(const sf::CircleShape  & fruit,bool  &isEaten) {
        takeUserInput();
        if(!move()){
            return false;
        }
        tryEatFruit(fruit,isEaten);
        return true;
    }

    void tryEatFruit(const sf::CircleShape  & fruit,bool  &isEaten){
        auto & head = body_.front();
        /*std::cout<<head.getPosition().x<<" "<<head.getPosition().y<<"\n";
        std::cout<<fruit.getPosition().x<<" "<<fruit.getPosition().y<<"\n";
        std::cout<<"\n";*/

        if(areIntersecting(head,fruit)){
            head.setFillColor(constants::FruitInsideBody);
            isEaten = true;
        }
    }

    bool areIntersecting(const sf::CircleShape & c1,const sf::CircleShape & c2){
        float x1 = c1.getPosition().x;
        float y1 = c1.getPosition().y;
        float x2 = c2.getPosition().x;
        float y2 = c2.getPosition().y;

        int d = abs(static_cast<int>(x1-x2)) + abs(static_cast<int>(y1-y2));
        if(d < 2*constants::radius){
            return true;
        }
        return false;
    }

    bool isCollidingWithWall(const sf::Vector2f & newHead) const noexcept{

        if(newHead.x == constants::windowsWidth || newHead.x== -1 || newHead.y == constants::windowsHeight || newHead.y == -1){
            return false;
        }
        return false;
    }

    bool isSelfColliding(const sf::Vector2f & newHead) const noexcept{

        if(points_.find(createSnakeBodyElement(newHead.x,newHead.y)) != points_.end()){
            return true;
        }
        return false;
    }

    bool isColliding(const sf::Vector2f & newHead) const noexcept {
        return isSelfColliding(newHead) || isCollidingWithWall(newHead);
    }
};


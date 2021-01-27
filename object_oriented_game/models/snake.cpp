#include "../header/snake.hpp"


Snake::Snake()
{
    direction = STOP;
    body.push_back({5, 5});
}

Snake::Snake(coord startPosition)
{
    direction = STOP;
    body.push_back(startPosition);
}

coord Snake::getHead()
{
    return body.back();
}

coord Snake::getNextCoord(){
    coord head = getHead();

    switch (direction)
    {
    case TOP:
        head.second -= 1;
        break;
    case DOWN:
        head.second += 1;
        break;
    case LEFT:
        head.first -= 1;
        break;
    case RIGHT:
        head.first += 1;
        break;
    case STOP:
        break;
    }

    return head;
}

bool Snake::isStopped()
{
    return direction == STOP;
}

bool Snake::isSnakeBody(coord position)
{
    for(int i = 0; i < body.size(); i++)
    {
        if(body[i].first == position.first && body[i].second == position.second)
        {
            return true;
        }
    }

    return false;
}

void Snake::changeDirection(snakeDirections new_direction)
{
    direction = new_direction;
}

void Snake::eatApple(coord apple){
    body.push_back(apple);
}

void Snake::step(){
    body.push_back(getNextCoord());
    body.erase(body.begin());
}
#include <vector>
#define coord std::pair<int, int>

enum snakeDirections{STOP = 0, LEFT, TOP, RIGHT, DOWN};

class Snake{
    snakeDirections direction;
    std::vector<coord> body;

    public:
        Snake();
        Snake(coord startPosition);

        coord getHead();
        coord getNextCoord();

        bool isStopped();
        bool isSnakeBody(coord position);
        
        void changeDirection(snakeDirections direction);
        void eatApple(coord apple);
        void step();
};
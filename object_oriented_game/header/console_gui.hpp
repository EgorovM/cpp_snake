#include <ncurses.h>
#include <string>
#include "../models/snake.cpp"

#define coord std::pair<int, int>

enum SPEED{LOW=200, MEDIUM=100, HIGH=50};

struct Apple
{
    coord position;
    
    public:
        void setPosition(coord newPosition);
        bool isApple(coord currPosition);
};


class GUI{
    int width, height;
    int speed;
    bool running;
    int score = 0;
    Snake snake;
    Apple apple;
    bool isGameOver();
    void setup();
    void draw();
    void input();
    void logic();
    coord generateNewApple();

    public:
        GUI();
        GUI(int widthIn, int heightIn);
        void run();
};

#include "../header/console_gui.hpp"

bool Apple::isApple(coord currPosition)
{
    return currPosition == position;
}

void Apple::setPosition(coord newPosition)
{
    position = newPosition;
}

GUI::GUI()
{
    width = 20;
    height = 20;
}

GUI::GUI(int widthIn, int heightIn)
{
    width = widthIn;
    height = heightIn;
}

bool GUI::isGameOver()
{
    coord head = snake.getNextCoord();
    int x = head.first; int y = head.second;

    return (
        snake.isSnakeBody(head) 
        || x == 0 || x == width - 1 
        || y == 0 || y == height - 1);
}

coord GUI::generateNewApple(){
    int appleX = 1 + rand() % (width - 2);
    int appleY = 1 + rand() % (height - 2);

    apple.setPosition({appleX, appleY});

    if(snake.isSnakeBody({appleX, appleY})){
        generateNewApple();
    }

    return {appleX, appleY};
}

void GUI::setup(){
    initscr();
    cbreak();
    noecho();

    running = true;
    speed = LOW;

    snake = Snake({5, 5});
    apple = Apple();
    generateNewApple();
}

void GUI::draw(){
    clear();
    printw("a, w, d, s - contol your snake\npress x - to exit\n");
    const std::string scoreString = "your score: " + std::to_string(score) + "\n";
    printw(scoreString.data());

    for(int i = 0; i < width; i++)
    {
        printw("#");
    }
    printw("\n");

    for(int i = 1; i < width-1; i++)
    {
        for(int j = 0; j < height; j++)
        {
            if(j == 0 || j == width - 1)
            {
                printw("#");
            }else if(apple.isApple({j, i})){
                printw("A");
            }else if(snake.isSnakeBody({j, i})){
                printw("S");
            }else{
                printw(" ");
            }
        }
        
        printw("\n");
    }

    for(int i = 0; i < width; i++){
        printw("#");
    }
    refresh();
}

void GUI::input(){
    timeout(speed);
    int ch = getch();

    if (ch == ERR) {
        return;
    }

    switch(ch)
    {
        case 'x':
            running = false;
            break;
        case 'a':
            snake.changeDirection(LEFT);
            break;
        case 'w':
            snake.changeDirection(TOP);
            break;
        case 'd':
            snake.changeDirection(RIGHT);
            break;
        case 's':
            snake.changeDirection(DOWN);
            break;
    }
}

void GUI::logic(){
    coord nextCoord = snake.getNextCoord();

    if(snake.isStopped()) return;

    if(isGameOver()){
        clear();
        printw("You losed\n");
        printw("Your score %d\n", score);
        printw("Press anykey to exit\n");

        timeout(-1);
        getch();
        running = false;
    }
    else if(apple.isApple(nextCoord)){
        snake.eatApple(nextCoord);
        generateNewApple();
        score++;

        if(score > 10){
            speed = HIGH;
        }
        else if(score > 5){
            speed = MEDIUM;
        }
    }

    snake.step();
}

void GUI::run(){
    setup();

    while(running)
    {
        draw();
        input();
        logic();
    }
}
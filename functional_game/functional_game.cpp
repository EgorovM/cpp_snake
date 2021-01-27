#include "functional_game.hpp"

bool running;

int width = 20, height = 20;
int score = 0;

int appleX, appleY;
std::vector<std::pair<int, int>> body;
enum snakeDirection{STOP=0, LEFT, TOP, RIGHT, BOTTOM};
int speed = 200;

snakeDirection currentDirection;


bool isSnakeBody(int x, int y){
    for(int i = 0; i < body.size(); i++){
        if(body[i].first == x && body[i].second == y) 
            return true;
    }

    return false;
}

void Setup()
{   
    initscr();
    cbreak();
    noecho();

    running = true;
    body.push_back({width / 2 - 1, height / 2 - 1});
    appleX = rand() % width;
    appleY = rand() % height;
}

void Draw()
{
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
            }else if(i == appleY && j == appleX){
                printw("A");
            }else if(isSnakeBody(j, i)){
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


void Input()
{
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
            currentDirection = LEFT;
            break;
        case 'w':
            currentDirection = TOP;
            break;
        case 'd':
            currentDirection = RIGHT;
            break;
        case 's':
            currentDirection = BOTTOM;
            break;
    }
}

void Logic()
{
    std::pair<int, int> head = body.back();

    switch (currentDirection)
    {
        case TOP:
            head.second -= 1;
            break;
        case LEFT:
            head.first -= 1;
            break;
        case RIGHT:
            head.first += 1;
            break;
        case BOTTOM:
            head.second += 1;
            break;
        case STOP:
            return;
    }

    if(isGameOver(head)){
        clear();
        printw("You losed\n");
        printw("Your score %d\n", score);
        printw("Press anykey to exit\n");

        timeout(-1);
        getch();
        running = false;
    }
    else if(eatApple(head)){
        generateApple();
        score++;

        if(score > 10){
            speed = 50;
        }
        else if(score > 5){
            speed = 100;
        }
    }else{
        body.erase(body.begin());
    }
    
    body.push_back(head);
}

bool eatApple(std::pair<int, int> head){
    return head.first == appleX && head.second == appleY;
}

bool isGameOver(std::pair<int, int> head){
    int x = head.first, y = head.second;

    return isSnakeBody(x, y) || x == 0 || x == width - 1 || y == 0 || y == height - 1;
}

void generateApple(){
    appleY = 1 + rand() % (height - 2);
    appleX = 1 + rand() % (width - 2);

    if(isSnakeBody(appleX, appleY)) generateApple();
}

int main()
{
    Setup();

    while(running)
    {
        Draw();
        Input();
        Logic();
    }

    endwin();

    return 0;
}
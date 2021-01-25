#include <ncurses.h>
#include <vector>
#include <string> 
#include <algorithm>


void Setup();
void Draw();
void Input();
void Logic();
void generateApple();
bool eatApple(std::pair<int, int> head);
bool isGameOver(std::pair<int, int> head);
void isSnakeBody();
int main();

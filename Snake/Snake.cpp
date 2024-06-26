#include "Snake.h"
#include <conio.h>
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

Snake::Snake() {
    gameOver = false;
    dir = STOP;
    width = 20;
    height = 20;
    score = 0;
    speed = 100;
    tail_length = 0;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    for (int i = 0; i < 400; ++i) {
        tailX[i] = 0;
        tailY[i] = 0;
    }
}

void Snake::Draw() {
    system("cls");
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout << "#";
            if (i == y && j == x)
                cout << "O";
            else if (i == fruitY && j == fruitX)
                cout << "F";
            else {
                bool print = false;
                for (int k = 0; k < tail_length; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }

            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
    cout << "Score:" << score << endl;
}

void Snake::Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'f':
            gameOver = true;
            break;
        }
    }
}

void Snake::Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < tail_length; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    if (x >= width || x < 0 || y >= height || y < 0) {
        gameOver = true;
        return;
    }

    for (int i = 0; i < tail_length; i++) {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
    }

    if (x == fruitX && y == fruitY) {
        score += 5;
        tail_length++;
        fruitX = rand() % width;
        fruitY = rand() % height;
    }
}

void Snake::Run() {
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        this_thread::sleep_for(chrono::milliseconds(250));
    }
}

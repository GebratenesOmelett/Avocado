// Avocado.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//
#include <conio.h>
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_UP 72
#define N 40
#define NUMOFSTARS 100

class Ludzik {
public:
    int point = 0;
    int y[3];
    int x;
    Ludzik(Ludzik &ludzik) {
        this->y[0] = ludzik.y[0];
        this->y[1] = ludzik.y[1];
        this->y[2] = ludzik.y[2];
        this->x = ludzik.x;
    }
    Ludzik(int y, int x) {
        this->y[0] = y;
        this->y[1] = y+1;
        this->y[2] = y+2;
        this->x = x;
    }
    void goRight() {
        this->x++;
    }
    void goLeft() {
        this->x--;
    }
    void addPoint(){
        this->point++;
    }
    void ludzikPrintPoints() {
        std::cout << "Points " << this->point << std::endl;
    }

};


class Space {
public:
    char space[N][N];
    int randNum[NUMOFSTARS];


    Space() {
        //srand(time(0));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                space[i][j] = ' ';
            }
        }
        //Star placement
        for (int i = 0; i < NUMOFSTARS; i++) {
            int xRand = rand() % (N + 1);
            int yRand = rand() % (N + 1);
            space[yRand][xRand] = '+';
        }
    }
    ~Space() {

    }
    void printTable() {

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                std::cout << space[i][j] << " ";
            }
            std::cout << std::endl;
        }
        //moveTable();

    }
    void addedP(Ludzik &ludzik) {
        if (space[ludzik.y[0]][ludzik.x] == '+') {
            ludzik.addPoint();
        }
        if (space[ludzik.y[1]][ludzik.x] == '+') {
            ludzik.addPoint();
        }
        if (space[ludzik.y[2]][ludzik.x] == '+') {
            ludzik.addPoint();
        }
    }

    void setLudzik(Ludzik &ludzik) {
        space[ludzik.y[0]][ludzik.x] = '#';
        space[ludzik.y[1]][ludzik.x] = '#';
        space[ludzik.y[2]][ludzik.x] = '#';
    };
    void setSpace(Ludzik &ludzik) {
        space[ludzik.y[0]][ludzik.x] = ' ';
        space[ludzik.y[1]][ludzik.x] = ' ';
        space[ludzik.y[2]][ludzik.x] = ' ';
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (space[i][j] == '#') {
                    space[i][j] = ' ';
                }
            }
        }
    };

    void moveTable() {
        char temp[N];

        for (int j = 0; j < N; ++j) {
            temp[j] = space[N - 1][j];
        }

        for (int i = N - 1; i > 0; --i) {
            for (int j = 0; j < N; ++j) {
                space[i][j] = space[i - 1][j];
            }
        }

        for (int j = 0; j < N; ++j) {
            space[0][j] = temp[j];
        }
    };


};


class Movement {

public:
    Movement() {};
    void getMove(Ludzik &ludzik) {
        if (GetKeyState(VK_LEFT) & 0x8000) {
            ludzik.goLeft();
        }
        if (GetKeyState(VK_RIGHT) & 0x8000) {
            ludzik.goRight();
        }
    }


};

int main()
{
    Space space;
    Ludzik player(20,20);
    Ludzik prev = player;
    space.setLudzik(player);
    Movement movement;
    int c = 0;

    while (1) {
        player.ludzikPrintPoints();
        space.printTable();
        space.moveTable();
        //c = _getch();
        prev = player;
        movement.getMove(player);
        space.addedP(player);
        //Sleep(100);//ms
        space.setSpace(prev);
        space.setLudzik(player);
        system("cls");

    }
    return 0;
}


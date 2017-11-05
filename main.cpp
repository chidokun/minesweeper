#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdio>

#define N_ROW 40
#define N_COL 50
#define N_BOMB 100
using namespace std;

int random(int a, int b)
{
    return a + rand() % (b - a + 1);
}

void initializeBomb(int* bombX, int* bombY)
{
    srand(time(NULL));

    int i = 0;
    while (i < N_BOMB)
    {
        int x = random(0, N_COL - 1);
        int y = random(0, N_ROW - 1);
        int j = 0;
        while (j < i && !(bombX[j] == x && bombY[j] == y)) j++;
        if(j == i)
        {
            bombX[i] = x;
            bombY[i] = y;
            i++;
        }
    }
}

bool isBomb(int* bombX, int* bombY, int x, int y)
{
    for(int i = 0; i < N_BOMB; i++)
        if(x == bombX[i] && y == bombY[i])
            return true;
    return false;
}

void generateNumberArray(int arr[][N_COL], int* bombX, int* bombY)
{
    int x_mark[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
    int y_mark[] = { -1, -1, -1, 0, 0, 1, 1, 1 };

    for(int i = 0; i < N_BOMB; ++i)
        for(int j = 0; j < 8; ++j)
        {
            int x_check = bombX[i] + x_mark[j];
            int y_check = bombY[i] + y_mark[j];
            if ((x_check >= 0 && x_check < N_COL) && (y_check >= 0 && y_check < N_ROW))
                arr[y_check][x_check]++;
        }
}

void display(int arr[][N_COL], int* bombX, int* bombY)
{
    for(int i = 0; i < N_ROW; ++i)
    {
        for(int j = 0; j < N_COL; ++j)
        {
            if(isBomb(bombX,bombY,j,i))
                printf("%-2c", '*');
            else if (arr[i][j] == 0)
                printf("%-2c", '.');
            else
                printf("%-2d", arr[i][j]);
        }
        printf("\n");
    }
}

void displayBomb(int* bombX, int* bombY)
{
    for(int i = 0; i < N_BOMB; ++i)
        printf("%d;%d ", bombX[i], bombY[i]);
    cout << endl;
}

int main()
{
    int numberArray[N_ROW][N_COL] = {0};
    int bombX[N_BOMB] = {0};
    int bombY[N_BOMB] = {0};

    initializeBomb(bombX, bombY);

    generateNumberArray(numberArray, bombX, bombY);

    //displayBomb(bombX, bombY);

    display(numberArray, bombX, bombY);

    return 0;
}

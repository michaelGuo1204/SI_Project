#include <cstdio>
#include <ctime>
#include <cstdlib>

int main()
{
    srand(time(NULL));

    int objectsNumber = 64 * 1024;
    int knapsackSize = 1024 * 1024 * 1024;
    printf("%d %d\n", objectsNumber, knapsackSize);
    while(objectsNumber--)
    {
        int v = rand() % 128;
        int w = rand() % 512;
        printf("%d %d\n", w, v);
    }

    return 0;
}
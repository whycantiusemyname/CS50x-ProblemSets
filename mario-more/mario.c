#include <cs50.h>
#include <stdio.h>

void PrintLayer(int LayerNum, int TotalLayer);
int main(void)
{
    int Height;
    do
    {
        Height = get_int("Height: ");
    }
    while (Height <= 0 || Height > 8);
    for (int Layer = 0; Layer < Height; Layer++)
    {
        PrintLayer(Layer + 1, Height);
    }
}

void PrintLayer(int LayerNum, int TotalLayer)
{
    for (int i = 0; i < TotalLayer; i++)
    {
        if (TotalLayer - i > LayerNum)
        {
            printf(" ");
        }
        else
        {
            printf("#");
        }
    }
    printf("  ");
    for (int j = 0; j < LayerNum; j++)
    {
        printf("#");
    }
    printf("\n");
}

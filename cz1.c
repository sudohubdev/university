#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct BrandDatas
{
    int day;
    char brand[10];
    float firstValue;
    float secondValue;
    int volume;
} brandDatas;
void writeHighestVolumeData(brandDatas *highestVolume, char *pole);
int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("Wrong parameteres\n");
        exit(1);
    }
    // The actual code
    int n = atoi(argv[2]);
    // int n = 5;
    char t[20];
    char **pole = (char **)malloc(n * sizeof(char *));
    memset(pole, 0, n * sizeof(char *));
    brandDatas brandWithTheHighestVolume;
    int occasionsOfHighestVolume = 0;
    // the actual code
    strcpy(t, argv[1]);
    // strcpy(t, "TSLA");
    for (int i = 0; i < (n); i++) // шо за i < (n - 1)? або i < n або i <= (n - 1), не путай. там був нуль
    {
        pole[i] = (char *)malloc(100 * sizeof(char *));
        memset(pole[i], 0, 100 * sizeof(char *));
        fgets(pole[i], 100, stdin);
        pole[i] = strtok(pole[i], "\n");
        int turn = 0;
        char *copiedPole = (char *)malloc(99 * sizeof(char)); // не було (char *)
        memset(copiedPole, 0, 99 * sizeof(char));
        strcpy(copiedPole, pole[i]);
        char *modifiedPole = strtok(copiedPole, ",");
        char nameOfBrand[20];
        while (modifiedPole)
        {
            switch (turn)
            {
            case 0:
                break; // цифирка
            case 1:    // бренд
                strcpy(nameOfBrand, modifiedPole);
                if (occasionsOfHighestVolume == 0 && strcmp(modifiedPole, t) == 0)
                {
                    char copiedPole1[99];
                    strcpy(copiedPole1, pole[i]);
                    writeHighestVolumeData(&brandWithTheHighestVolume, copiedPole1);
                    occasionsOfHighestVolume++;
                }
                break;
            case 2: // число
                break;
            case 3: // число
                break;
            case 4: // огромне число
                if (atoi(modifiedPole) > brandWithTheHighestVolume.volume && occasionsOfHighestVolume != 0 && strcmp(nameOfBrand, t) == 0)
                {
                    char copiedPole1[99];
                    strcpy(copiedPole1, pole[i]);
                    writeHighestVolumeData(&brandWithTheHighestVolume, copiedPole1);
                }
                break;
            }
            turn++;
            modifiedPole = strtok(NULL, ",");
        }
        free(copiedPole);
    }
    if (occasionsOfHighestVolume == 0)
    {
        printf("Ticker %s was not found\n</div>\n<ul>\n", t);
    }
    else
    {
        printf("<h1>%s: highest volume</h1>\n<div>Day: %d</div>\n",
               brandWithTheHighestVolume.brand, brandWithTheHighestVolume.day);
        printf("<div>Start price: %.2f</div>\n<div>End price: %.2f</div>\n",
               brandWithTheHighestVolume.firstValue, brandWithTheHighestVolume.secondValue);
        printf("<div>Volume: %d</div>\n</div>\n<ul>\n", brandWithTheHighestVolume.volume);
    }
    for (int i = (n - 1); i >= 0; i--)
    {
        brandDatas currentStruct;
        writeHighestVolumeData(&currentStruct, pole[i]); // тут прога натикається на нуль
        if (strcmp(currentStruct.brand, t) == 0)
        {
            printf("<li><b>");
        }
        else
        {
            printf("<li>");
        }
        printf("Day: %d, ticker: %s, start: %.2f, end: %.2f, diff: %.2f, volume: %d",
               currentStruct.day, currentStruct.brand, currentStruct.firstValue, currentStruct.secondValue,
               currentStruct.secondValue - currentStruct.firstValue, currentStruct.volume);
        if (strcmp(currentStruct.brand, t) == 0)
        {
            printf("</b></li>\n");
        }
        else
        {
            printf("</li>\n");
        }
    }
    printf("</ul>\n</body>\n</html>\n");
    for (int i = 0; i < n; i++)
    {
        free(pole[i]);
    }
    free(pole);
    return 0;
}
void writeHighestVolumeData(brandDatas *currentStruct, char *pole)
{
    int turn = 0;
    char *modifiedPole = strtok(pole, ",");
    while (modifiedPole)
    {
        switch (turn)
        {
        case 0:
            currentStruct->day = atoi(modifiedPole);
            break;
        case 1:
            strcpy(currentStruct->brand, modifiedPole);
            break;
        case 2:
            currentStruct->firstValue = atof(modifiedPole);
            break;
        case 3:
            currentStruct->secondValue = atof(modifiedPole);
            break;
        case 4:
            currentStruct->volume = atoi(modifiedPole);
            break;
        }
        turn++;
        modifiedPole = strtok(NULL, ",");
    }
}
// Modelovanie a simulacia:
// jednoducha implementacia dopravneho prudu
// Juraj Stefanovic, Bratislava
// zdrojovy text na volne pouzitie
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define DIM 2000 // dlzka cesty
#define AA 100   // pozorovany interval cesty AA,BB
#define BB 170
char road[DIM], road_delta[DIM]; // stav cesty a stav cesty v case T+delta
// generovanie nahodneho celeho cisla z intervalu <0,base>
int randint(int base)
{
    return ((int)((double)(rand()) / RAND_MAX * (base)));
}
// inicializacia cesty
void roadinit(void)
{
    int i;
    for (i = 0; i < DIM; i++)
        road[i] = road_delta[i] = ' ';
    // znak medzera ' ' znamena prazdny element cesty bez auta
}
// jednoducha vizualizacia hustoty premavky na ceste
void showroad(void)
{
    int i, sector = 0;
    printf("\n\nsituacia na celej ceste:\n<");
    for (i = 0; i < DIM; i++)
    {
        if (road[i] != ' ')
            sector++; // na tomto mieste auto je
        if (0 == i % 50 && i != 0)
        // za kazdy usek o dlzke (napriklad) 50 spocitame auta a ukazeme hustotu
        {
            if (sector >= 0 && sector < 5)
                printf(".");
            // nizka hustota na jednotku dlzky
            if (sector >= 5 && sector < 10)
                printf("-");
            if (sector >= 10 && sector < 15)
                printf("+"); // prostredna hustota
            if (sector >= 15 && sector < 20)
                printf("*");
            if (sector >= 20 && sector <= 25)
                printf("@"); // vysoka hustota
            sector = 0;
        }
    }
    printf(">\n");
}
// vizualizacia useku cesty <a,b>
void showpart(int a, int b)
{
    int i;
    printf("\n\ncast cesty:\n<");
    for (i = a; i < DIM && i < b; i++)
        printf("%c", road[i]);
    printf(">\n");
}

// prichod auta na zaciatok cesty
void carcoming(void)
{
    static int i = 0;
    if (road_delta[0] != ' ')
        return; // zaciatok cesty je este obsadeny
    if (!randint(100) > 10)
        return; // pravdepodobnost ze nic teraz neprislo
    road_delta[0] = 'a' + i;
    // kazde nove auto ma priradene ine pismeno, aby sa dalo lepsie pozorovat co sa deje
    if (i < 25)
        i++;
    else
        i = 0;
    return;
}
// zistenie vzdialenosti k najblizsiemu autu vpredu
int cardistance(int position)
{
    int i;
    for (i = position + 1; i < DIM; i++)
        if (road[i] != ' ')
            return (i);
    return (DIM);
}
// elementarny krok vpred pre auto na danej pozicii
int cargoing(int position)
{
    int next, gt;
    next = cardistance(position);
    if (road[position] != ' ')
    {
        if (position > DIM - 1)
        {
            road_delta[position] = ' '; // opustenie cesty na konci
            return (position + 1);
        }
        // od aktualnej pozicie sa posunieme nejakou rychlostou vpred:
        gt = position + (int)((1 + randint(3)));
        // ak je pred nami auto, stopneme tesne za nim:
        if (gt >= next)
            gt = next - 1;
        road_delta[gt] = road_delta[position];
        // citali sme z "road", ale zapisujeme do "road_delta"
        road_delta[position] = ' ';
        return (next);
    }
    return (next);
}
// ked mame vyrobeny stav cesty v case T+delta, tak ho prekopirujeme do stavu v (novom) case T
void timestep(void)
{
    int i;
    for (i = 0; i < DIM; i++)
        road[i] = road_delta[i];
}

void main(void)
{
    int position, i, x;
    time_t t;
    printf("zaciatok simulacie\n\n");
    srand((unsigned)time(&t)); // inicializacia generatora nahodnych cisiel
    roadinit();
    showpart(0, 50);
    for (x = 0; x < 50; x++)
    {
        for (i = 0; i < 10; i++)
        {
            carcoming(); // prichod auta na zaciatok
            // vykonaj elementarny pohyb vsetkych aut:
            for (position = 0; position < DIM; position = cargoing(position))
                ;
            timestep();       // vymen T za T+delta
            showpart(AA, BB); // ukaz detailne cast cesty
            showroad();       // vizualizuj celu cestu
        }
        printf("\n\npress Enter");
        (void)getchar();
    }
    return;
}
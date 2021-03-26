#include<stdio.h>
int main (void)
{
    FILE *HighArq;
    int MaiorPont1, MaiorPont2, MaiorPont3, i;
    char CharMaiorPont1[100], CharMaiorPont2[100], CharMaiorPont3[100];
    char Nome1[6], Nome2[6], Nome3[6];

    HighArq = fopen("HighScores1.txt", "r");
    if(HighArq == NULL)
        printf("deu ruim!");

    fscanf(HighArq, "%d", &MaiorPont1);
    fscanf(HighArq, "%d", &MaiorPont2);
    fscanf(HighArq, "%d", &MaiorPont3);
    fscanf(HighArq, "%s", &Nome1);
    fscanf(HighArq, "%s", &Nome2);
    fscanf(HighArq, "%s", &Nome3);

    printf("%d\n", MaiorPont1);
    printf("%d\n", MaiorPont2);
    printf("%d\n", MaiorPont3);
    printf("%s\n", Nome1);
    printf("%s\n", Nome2);
    printf("%s\n", Nome3);

    fclose(HighArq);

    HighArq = fopen("HighScores1.txt", "r+");
    if(HighArq == NULL)
        printf("deu ruim!");

    gets(Nome1);
    fprintf(HighArq, "%s\n", Nome1);

    fclose(HighArq);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define maxbrPokusaja 6

FILE* openFile (char* filename, char* mode, int exitCode);
int pogrBrKar (char* kombinacija, int brKar);
int pogresanKarakter (char* kombinacija, char* dozvoljeniKarakteri, int brKar);
int staraKomb(char* postojeceKomb [maxbrPokusaja], char* kombinacija, int brPokusaja);
int provjera(char* resenje, char* kombinacija);
int brPogodjenih(char* resenje, char* kombinacija, int brKar);
int naMjestu(char* resenje, char* kombinacija, int brPogodj, int brKar);


int main (int argc, char* argv[])
{

	//FILE* in;
	int i;
	char* kombinacija;
	char* postojeceKomb [maxbrPokusaja];
	char* resenje;
	char* dozvoljeniKarakteri;
	int brPokusaja = 0;
	int rezultatProvjere;
	int brPogodj;
	int brKar = 0, brKar1 = 0;

	srand(time(NULL));

	//in = openFile(argv[1], "r", 1);

	/*
	fseek(in, 0, SEEK_END);
	brKar = ftell(in) - 1;
	rewind(in);
	*/
	do
	{	printf("Unesite duzinu kombinacije ");
		scanf("%d", &brKar);
	} while (brKar < 1);

	do
	{	printf("Unesite broj dozvoljenih karaktera MIN (%d) ", brKar);
		scanf("%d", &brKar1);
	}while(brKar1 < brKar);

	dozvoljeniKarakteri = (char*)malloc(brKar1 * sizeof(char));

	do
	{	printf("Unesite dozvoljene karaktere ");
		scanf("%s", dozvoljeniKarakteri);
		dozvoljeniKarakteri[brKar1] = '\0';
	}while(strlen(dozvoljeniKarakteri) < brKar1);

	//brKar = strlen(resenje);
	resenje = (char*)malloc(brKar * sizeof(char));

	for (i=0; i<brKar; i++)
	{
	    int key = rand() % (int)(sizeof(dozvoljeniKarakteri) -1);
	    resenje[i] = dozvoljeniKarakteri[key];
	}
	resenje[brKar] = '\0';

	//fscanf(in,"%s %s", resenje, dozvoljeniKarakteri);

	//printf("\nDozvoljeni karakteri su = %s, resenje= %s\n", dozvoljeniKarakteri, resenje);

	kombinacija = (char*)malloc(brKar * sizeof(char));


	for (i = 0; i < maxbrPokusaja; i++)
	{
		postojeceKomb[i] = (char*)malloc(brKar * sizeof(char));
	}

	printf("\n\t\tUnesite vasu kombinaciju\n");

	do
	{
		do
		{
			//__fpurge(stdin);
			scanf("%s", kombinacija);

			strcpy(postojeceKomb[brPokusaja], kombinacija);

			if(staraKomb(postojeceKomb, kombinacija, brPokusaja))
			{
				printf("To ste vec jednom unijeli!\n");
			}

		}while (pogrBrKar(kombinacija, brKar) || pogresanKarakter(kombinacija, dozvoljeniKarakteri, brKar) || staraKomb(postojeceKomb, kombinacija, brPokusaja));

		brPokusaja++;
		rezultatProvjere = provjera(resenje, kombinacija);
		brPogodj = brPogodjenih(resenje, kombinacija, brKar);

		if (rezultatProvjere != 1)
		{
			printf("\t\tNetacno! ");
			printf("Preostali broj pokusaja:%d \n", maxbrPokusaja - brPokusaja);
			printf("\t\tBroj pogodjenih karaktera je: %d\n",brPogodj);
			printf("\t\tBroj karaktera na mjestu: %d\n",naMjestu(resenje, kombinacija, brPogodj, brKar));
		}

	}while(brPokusaja < maxbrPokusaja && rezultatProvjere != 1);

	if (rezultatProvjere == 1)
	{
		printf("\nBRAVO! Pogodili ste!\n");

	}
	else
	{
		printf("Niste pogodili\n=====================\n");
		printf("Tacno rjesenje je: %s\n=====================\n", resenje);
	}

	free(resenje);
	free(dozvoljeniKarakteri);
	free(kombinacija);
	for (i = 0; i < maxbrPokusaja; i++)
	{
		free(postojeceKomb[i]);
	}

    scanf("%d");
	//fclose(in);

	return 0;
}

FILE* openFile (char* filename, char* mode, int exitCode)
{
	FILE* fp;
	fp = fopen(filename, mode);

	if (fp == NULL)
	{
		printf("Greska pri otvaranju fajla\n");
		exit (exitCode);
	}

	return fp;
}

int pogrBrKar (char* kombinacija, int brKar)
{

	if(strlen(kombinacija) != brKar)
	{
		printf("Unjeli ste pogresnu duzinu\n");
		return 1;
	}

	return 0;
}

int pogresanKarakter (char* kombinacija, char* dozvoljeniKarakteri, int brKar)
{
	int i, j, br=0;
	int broj = strlen(dozvoljeniKarakteri);

	for (i=0; i<brKar; i++)
	{
		for (j=0; j<broj; j++)
		{
			if(kombinacija[i] == dozvoljeniKarakteri[j])
			{
				br++;
				break;
			}

		}
	}

	if (br != brKar)
	{
		printf("Unjeli ste pogresan karakter\n");
		return 1;
	}

	return 0;
}

int staraKomb(char* postojeceKomb [maxbrPokusaja], char* kombinacija, int brPokusaja)
{

	int i = 0;
	int br = 0;

	for (i=0; i<brPokusaja; i++)
	{
		if (!strcmp(postojeceKomb[i], kombinacija))
		{
           		br = 1;
           		break;
		}
	}

	return br;
}

int provjera(char* resenje, char* kombinacija)
{
    int rezultatProvjere;

    if (!strcmp(resenje,kombinacija))
    {
        rezultatProvjere = 1;
    }
    else
    {
        rezultatProvjere = 0;
    }
    return rezultatProvjere;
}

int brPogodjenih(char* resenje, char* kombinacija, int brKar)
{
	int i, j, br=0, br1=0;
	char* resenje1;
	resenje1 = (char*)malloc(brKar * sizeof(char));
	strcpy(resenje1, resenje);

	for (i=0; i<brKar; i++)
	{
		for (j=0; j<brKar; j++)
		{
			if(resenje1[j] == kombinacija[i])  //3535   3355   3333   2222  2112
			{
				resenje1[j]=' ';
				br++;
				break;
			}
		}
	}

	for (i=0; i<brKar; i++)
	{
		if(resenje[i] == kombinacija[i])
		{
			br1++;
		}
	}

	if(br<br1)
	{
		return br1;
	}

	free(resenje1);
	return br;
}

int naMjestu(char* resenje, char* kombinacija, int brPogodj, int brKar)
{
	int i, br = 0;

	for (i=0; i<brKar; i++)
	{
		if(resenje[i] == kombinacija[i])
		{
			br++;
		}
	}
	if(br > brPogodj)
	{
		return brPogodj;
	}
	else
	{
		return br;
	}
}



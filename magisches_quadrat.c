// Magisches Quadrat nach der Brute-Force-Methode ermitteln
// Autor: Fabian Prestros
// Datum: 19.08.2020

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int einlesen(char koef[29])
{
	int num;		// Einzulesende Zahl
	int chk = 0;	// R�ckgabewert zur Fehlermeldung

	do				// In einer Schleife einlesen, bis eine korrekte Zahl eingelesen wurde
	{
		printf("%s = ", koef);
		chk = scanf_s("%d", &num);
		while (getchar() != '\n');		// Tastaturpuffer leeren.
		if ((chk == 0) || (num <= 0))	// Fehlermeldung, wenn Zahl kleiner gleich 0 und R�ckgabewert = 0 => scanf_s meldet, dass keine Zahl eingegeben wurde.
			printf("Bite geben Sie eine Nat\x81rliche Zahl ein!\n");
	} while ((chk == 0) || (num <= 0));	// Schleifendurchlauf, bis kein Fehler mehr vorliegt.
	return num;
}

int zufallszahl(int max)
{
	int random_number = 0;

	//rand() liefert Wert zwischen 0 und RAND_MAX
	//RAND_MAX = 0x7FFF = 32767 (ist eine Konstante)
	random_number = rand();

	//Modulo Operator (%) gint den Divisionsrest zur�ck
	random_number = random_number % (max + 1); // Werte von 0 bis max + 1
	
	return random_number;
}

erzeugen(int neu[80][80], int maxQuadrat, int maxZahl)
{
	int x, y;

	// Zufallszahlen werden elementweise in das Magische Quadrat eingef�llt. Dazu werden zwei verschachtelte FOR-Schleifen verwendet.
	for (y = 0; y < maxQuadrat; y++)
	{
		for (x = 0; x < maxQuadrat; x++)
		neu[y][x] = zufallszahl(maxZahl);	// Variable "maxZahl" gibt die gr��tm�gliche Zufallszahl an.
	}
}



int pruefen(int pruefling[80][80], int maxQuadrat)
{
	int x, y, summe = 0, psumme = 0, okay = 1;
	
	// Die Summe des Magischen Quadrates wird als Reihensumme der 1. Zeile berechnet.
	for (x = 0; x < maxQuadrat; x++)
		summe = summe + pruefling[0][x];
	
	// �berpr�fen, ob die Reihensumme der anderen Zeilen der Summe entspricht
	for (y = 1; y < maxQuadrat; y++)
	{
		psumme = 0;
		for (x = 0; x < maxQuadrat; x++)
			psumme = psumme + pruefling[y][x];
		if (summe != psumme)
			okay = 0;
	}

	// �berpr�fen, ob die Reihensumme der Spalten der Summe entspricht
	for (x = 0; x < maxQuadrat; x++)
	{
		psumme = 0;
		for (y = 0; y < maxQuadrat; y++)
			psumme = psumme + pruefling[y][x];
		if (summe != psumme)
			okay = 0;
	}

	// �berpr�fen, ob die Reihensumme der 1. Hauptdiagonale der Summe entspricht
	psumme = 0;
	for (x = 0; x < maxQuadrat; x++)
		psumme = psumme + pruefling[x][x];
	if (summe != psumme)
		okay = 0;

	// �berpr�fen, ob die Reihensumme der 2. Hauptdiagonale der Summe entspricht
	psumme = 0;
	for (x = 0; x < maxQuadrat; x++)
		psumme = psumme + pruefling[3 - x][x];
	if (summe != psumme)
		okay = 0;

	if (okay == 0)
		summe = 0;
	return summe;
}

ausgabe(int feld[80][80], int maxQuadrat)
{
	int x, y;

	// Das Magisches Quadrat wird elementweise am Display ausgeben. Dazu werden zwei verschachtelte FOR-Schleifen verwendet.
	for(y = 0; y < maxQuadrat; y++)
	{
		for (x = 0; x < maxQuadrat; x++)
			printf("%d\t", feld[y][x]);
		printf("\n");
	}
}

int main()
{
	int maxQuadrat, maxZahl, MagischesQuadrat;
	int quadrat[80][80];
	clock_t start_t, end_t, clock_cycles;
	double clock_speed;

	//srand() initialisiert den Zufallsgenerator. Das darf nur einmal im Programm geschehen.
	//clock() lieferte die Anzahl der Ticks seit dem Programmstart zur�ck, diese Anzahl wird als Seed des Zufallsgenerator verwendet.
	srand(clock());

	maxQuadrat = einlesen("Gr\x94\xe1 \be des Quadrats in Zeichen");	// Einlesen der Gr��e des Quadrats
	// maxQuadrat = 4;														// F�r das Testen mit dem Yang-Hui-Quadrat
	maxZahl = einlesen("Gr\x94\xe1te Zufallszahl");						// Einlesen der gr��tm�glichen Zufallszahl
	printf("\n");

	start_t = clock();													// Einlesen der Startzeit

	do
	{
		erzeugen(quadrat, maxQuadrat, maxZahl);						// Quadrat mit Zufallszahlen bef�llen
	
		/*
		// Yang-Hui-Quadrat zum Testen: 
		quadrat.MagischesQuadrat[0][0] = 16;	quadrat.MagischesQuadrat[0][1] = 5;		quadrat.MagischesQuadrat[0][2] = 9;		quadrat.MagischesQuadrat[0][3] = 4;
		quadrat.MagischesQuadrat[1][0] = 2;		quadrat.MagischesQuadrat[1][1] = 11;	quadrat.MagischesQuadrat[1][2] = 7;		quadrat.MagischesQuadrat[1][3] = 14;
		quadrat.MagischesQuadrat[2][0] = 3;		quadrat.MagischesQuadrat[2][1] = 10;	quadrat.MagischesQuadrat[2][2] = 6;		quadrat.MagischesQuadrat[2][3] = 15;
		quadrat.MagischesQuadrat[3][0] = 13;	quadrat.MagischesQuadrat[3][1] = 8;		quadrat.MagischesQuadrat[3][2] = 12;	quadrat.MagischesQuadrat[3][3] = 1;
		*/

		MagischesQuadrat = pruefen(quadrat, maxQuadrat);				// Pr�fen, ob ein Magisches Quadrat vorliegt
	} while (MagischesQuadrat == 0);
	
	end_t = clock();													// Einlesen, wenn das Programm fertig wurde
	
	// Ausf�hrungszeit berechenen
	clock_cycles = end_t - start_t;
	clock_speed = ((double)end_t - (double)start_t) / CLOCKS_PER_SEC;	
	
	printf("Ausf\x81hrungsdauer = %lf s\n", clock_speed);				// Ausf�hrungszeit ausgeben

	printf("Summe = %d\n\n", MagischesQuadrat);
	ausgabe(quadrat, maxQuadrat);										// Magisches Quadrat ausgeben
}
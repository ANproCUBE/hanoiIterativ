/*
	Anforderung an den Algorithmus:
Es existieren drei Stangen. Bei der linken Stange befinden sich z.B. drei Scheiben mit abnehmendem Durchmesser nach oben.
Bei der mittleren sowie der rechten Stange sind keine Scheiben gestapelt.
Das Ziel ist es, alle Scheiben der linken Stange in der richtigen Reihenfolge bei der rechten Stange zu stapeln.
Bedingungen:
Es darf nur eine Scheibe auf einmal bewegt werden. Es darf zu keinem Zeitpunkt eine gr��ere Scheibe auf einer kleineren Platz finden.


	L�sungsansatz:
Die Stangen sind bei einer geraden Anzahl von Scheiben im Uhrzeigersinn (von oben betrachtet) "auf einem Kreis" angeordnet.
Bei einer ungeraden Anzahl -> gegen den Uhrzeigersinn.

> Die Iteration muss so lange erfolgen, bis die 1. und 2. Stange keine Scheiben mehr enthalten.
> Es wird immer erst die kleinste Scheibe bewegt. Wenn m�glich, wird daraufhin eine der anderen Scheiben bewegt.

Die kleinste Scheibe rotiert somit fix bei jedem Zug und in Relation zu der darauf folgenden Stellung der Scheiben wird ein m�glicher Zug
mit einer der anderen Scheiben gesucht.
Wichtig ist, dass die Rotation bei gerader Scheibenzahl im Uhrzeigersinn, sonst gegen den Uhrzeigersinn zu erfolgen hat.
*/

#include <stdio.h>
#include <conio.h> //getch()
#include <iostream> //memset()

//Gibt aktuellen Stand am Bildschirm aus
void printStangen(int len, int* arr)
{
	for (int i = 0; i < len; i++)
	{
		if (i == len / 3 || i == len / 3 * 2)
		{
			printf(" ");
		}

		printf("%d", arr[i]);
	}
	printf("\n");
}
//Gibt die Position der 1. Scheibe im Stangen-Array zur�ck
int searchIndex(int len, int* arr, int ges)
{
	for (int i = 0; i < len; i++)
		if (arr[i] == ges)
			return i;

	return -1;
}
//Pr�ft, ob bestimmte Scheibe bei bestimmter Stange abgelegt werden kann
int searchNextAvailable(int len, int* arr, int pos, int check)
{
	for (int i = 0; i < len / 3; i++) //len/3 = Anzahl der Pl�tze auf einer Stange
	{
		if (arr[pos] > check && arr[pos + 1] == 0) //Zahl an aktueller Stelle gr��er als check und n�chste Stelle = 0
		{
			return pos + 1;
		}
		else if (arr[pos] == 0) //Unterste Ebene der Stange bereits frei
		{
			return pos;
		}
		else if (arr[pos + 1] == 0) //Die vorherigen Bedingungen wurden nicht erf�llt und es folgt keine Zahl mehr
		{
			return -1;
		}
		else
			pos++;
	}
}
//Gibt den Index der Position zur�ck, an welche die Erste Scheibe gesetzt werden kann
int calcFreePosFirst(int ind, int* arr)
{
	do {
		if (arr[ind] == 0)
			return ind;
		else
			ind++;
	} while (arr[ind] != 1);
}
void main()
{
	const int anzSch = 3; //Anzahl der Scheiben
	const int lenArr = anzSch * 3; //L�nge des ganzen Arrays (alle 3 St�be)
	int index = 0; //Hilfsvariable
	int tempStor = 0, tempStor2 = 0, tempStor3 = 0; //Hilfsvariablen
	int fillHelp = anzSch; //Hilfsvariable zum bef�llen der 1. S�ule
	int sum = 0; //Kontrollsumme zur Pr�fung, ob Stange 1 und 2 leer sind
	int zugCounter = 0; //Anzahl der ben�tigten Z�ge
	int stangen[lenArr]; //Stangen-Array -> Anzahl der Scheiben * 3, weil 3 Stangen

	//Aufbau des Arrays "Stange" bei 3 Scheiben - gef�llt mit den Startwerten
	//Alle drei Stangen werden in einem einzigen int-Array gespeichert
	//						---------------------------------------
	//      Beschreibung	|  Stange 1 ||  Stange 2 ||  Stange 3 |       
	//      Wert			| 3 | 2 | 1 || 0 | 0 | 0 || 0 | 0 | 0 |       
	//      Index			| 0 | 1 | 2 || 3 | 4 | 5 || 6 | 7 | 8 |       
	//						---------------------------------------

	memset(stangen, 0, sizeof(int) * lenArr); //Ganzes Array auf 0 setzen
	for (int i = 0; i < anzSch; i++) //Die erste Stange mit den Scheiben "f�llen"
	{
		stangen[i] = fillHelp;
		fillHelp--; //Counter verringert sich pro Iteration -> z.B. 3,2,1
	}

	printf("\nTuerme von Hanoi - Iterativer Loesungsansatz \nAnzahl der Scheiben: %d\n\nAusgangsposition\n", anzSch);
	printStangen(lenArr, stangen);
	printf("--------------------------------------------\n");

	while (1)
	{
		printf("\n");

		//------------------------------------------------------------------------------------------
		//Berechnung, ob 1. und 2. Stange leer sind:
		//Alle elemente der beiden Arrays summieren -> Summe von leeren Pl�tzen (Platzhalter 0) => 0
		//------------------------------------------------------------------------------------------

		for (int i = 0; i < (lenArr / 3) * 2; i++)
			sum += stangen[i];
		if (sum == 0) //Summe 0 -> Beide Stangen leer -> aus while() ausbrechen
			break;
		else
			sum = 0;


		if (anzSch % 2 == 0) //Pr�ft, ob Scheibenzahl gerade
		{
			//-----------------------------------------------------------------------------------------------
			//Die 1. Scheibe muss bei jedem Zug um 1 io Uhrzeigersinn (gerade Scheibenzahl) verschoben werden
			//-----------------------------------------------------------------------------------------------

			index = searchIndex(lenArr, stangen, 1);
			if (index <= ((lenArr / 3) - 1)) //Scheibe 1 auf 1. Stange -> auf 2. Stange schieben
			{
				stangen[index] = 0; //Alte Position auf 0 setzen
				index = lenArr / 3; //Neuer Index -> 1. Position auf neuer Stange (2)
				stangen[calcFreePosFirst(index, stangen)] = 1; //Freie Position auf 2. Stange auf 1 setzen
				printStangen(lenArr, stangen);
				zugCounter++;
			}
			else if (index >= (lenArr / 3) && index < (lenArr / 3) * 2) //Scheibe 1 auf 2. Stange -> auf 3. Stange schieben
			{
				stangen[index] = 0;
				index = (lenArr / 3) * 2;
				stangen[calcFreePosFirst(index, stangen)] = 1;
				printStangen(lenArr, stangen);
				zugCounter++;
			}
			else if (index >= (lenArr / 3) * 2) //Scheibe 1 auf 3. Stange -> auf 1. Stange schieben
			{
				stangen[index] = 0;
				index = 0;
				stangen[calcFreePosFirst(index, stangen)] = 1;
				printStangen(lenArr, stangen);
				zugCounter++;
			}

			//-------------------------------------------------------------------------------
			//Wenn es m�glich ist, eine Scheibe au�er der 1. zu verschieben, wird das gemacht
			//-------------------------------------------------------------------------------

			index = searchIndex(lenArr, stangen, 1); //Suche nach Position Scheibe 1
			for (int i = 0; i < lenArr; i++)
			{
				if (stangen[i] != 0 && stangen[i] != 1)
				{
					if (stangen[i + 1] == 0) //N�chstes Element ist 0
					{
						tempStor = searchNextAvailable(lenArr, stangen, 0, stangen[i]); //Ist Platz auf der 1. Stange?
						tempStor2 = searchNextAvailable(lenArr, stangen, lenArr / 3, stangen[i]); //Ist Platz auf der 2. Stange?
						tempStor3 = searchNextAvailable(lenArr, stangen, (lenArr / 3) * 2, stangen[i]); //Ist Platz auf der 2. Stange?

						if (tempStor > -1)
						{
							stangen[tempStor] = stangen[i];
							stangen[i] = 0;
							printStangen(lenArr, stangen);
							zugCounter++;
							break; //Nur eine Scheibe/Zug bewegen -> aus for() ausbrechen
						}
						else if (tempStor2 > -1)
						{
							stangen[tempStor2] = stangen[i];
							stangen[i] = 0;
							printStangen(lenArr, stangen);
							zugCounter++;
							break;
						}
						else if (tempStor3 > -1)
						{
							stangen[tempStor3] = stangen[i];
							stangen[i] = 0;
							printStangen(lenArr, stangen);
							zugCounter++;
							break;
						}
					}
				}
			}
		}
		else
		{
			//--------------------------------------------------------------------------------------------------------
			//Die 1. Scheibe muss bei jedem Zug um 1 gegen den Uhrzeigersinn (ungerade Scheibenzahl) verschoben werden
			//--------------------------------------------------------------------------------------------------------

			index = searchIndex(lenArr, stangen, 1);
			if (index <= ((lenArr / 3) - 1)) //Scheibe 1 auf 1. Stange -> auf 3. Stange schieben
			{
				stangen[index] = 0;
				index = (lenArr / 3) * 2;
				stangen[calcFreePosFirst(index, stangen)] = 1;
				printStangen(lenArr, stangen);
				zugCounter++;
			}
			else if (index >= (lenArr / 3) && index < (lenArr / 3) * 2) //Scheibe 1 auf 2. Stange -> auf 1. Stange schieben
			{
				stangen[index] = 0;
				index = 0;
				stangen[calcFreePosFirst(index, stangen)] = 1;
				printStangen(lenArr, stangen);
				zugCounter++;
			}
			else if (index >= (lenArr / 3) * 2) //Scheibe 1 auf 3. Stange -> auf 2. Stange schieben
			{
				stangen[index] = 0;
				index = lenArr / 3;
				stangen[calcFreePosFirst(index, stangen)] = 1;
				printStangen(lenArr, stangen);
				zugCounter++;
			}

			//-------------------------------------------------------------------------------
			//Wenn es m�glich ist, eine Scheibe au�er der 1. zu verschieben, wird das gemacht
			//-------------------------------------------------------------------------------

			index = searchIndex(lenArr, stangen, 1);
			for (int i = 0; i < lenArr; i++)
			{
				if (stangen[i] != 0 && stangen[i] != 1)
				{
					if (stangen[i + 1] == 0)
					{
						tempStor = searchNextAvailable(lenArr, stangen, 0, stangen[i]);
						tempStor2 = searchNextAvailable(lenArr, stangen, lenArr / 3, stangen[i]);
						tempStor3 = searchNextAvailable(lenArr, stangen, (lenArr / 3) * 2, stangen[i]);

						if (tempStor > -1)
						{
							stangen[tempStor] = stangen[i];
							stangen[i] = 0;
							printStangen(lenArr, stangen);
							zugCounter++;
							break;
						}
						else if (tempStor2 > -1)
						{
							stangen[tempStor2] = stangen[i];
							stangen[i] = 0;
							printStangen(lenArr, stangen);
							zugCounter++;
							break;
						}
						else if (tempStor3 > -1)
						{
							stangen[tempStor3] = stangen[i];
							stangen[i] = 0;
							printStangen(lenArr, stangen);
							zugCounter++;
							break;
						}
					}
				}
			}
		}
	}

	printf("--------------------------------------------\n");
	printf("Berechnung beendet\nBenoetigte Zuege: %d (=2^n-1)", zugCounter);
	_getch();
}





/*
T�rme von Hanoi - rekursiver L�sungsansatz


#include <stdio.h>
#include <conio.h>
#include <iostream>

void tuerme(int von, int auf, int anz)
{
	if (anz == 1)
	{
		printf("%d -> %d\n", von, auf);
		return;
	}

	int frei = 3 - (von + auf);
	tuerme(von, frei, anz - 1);
	std::cout << von << " -> " << auf << std::endl;
	tuerme(frei, auf, anz - 1);
}

void main()
{
	tuerme(0, 2, 3);
	_getch();
}

*/
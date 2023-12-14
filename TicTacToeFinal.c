//Tic Tac Toe Spiel
//Ein Tic Tac Toe Spiel, bei dem der Benutzer gegen einen Computer spielt. Der Benutzer hat den ersten ZUg und nutzt "X", der Computer w�hlt zuf�llige Felder aus und spielt mit "O". Bei drei gleichen Symbolen in einer Reihe ist das Spiel gewonnen, dabei ist egal ob vertikal, horizontal oder diagonal. Wenn es keinen Gewinner gibt, wird das Spiel als unentschieden gewertet.
//Nele Hetzer, Anna Katharina Becker, Finn-Niklas Zymelka
//14.12.2023
//9

#define _CRT_SECURE_NO_WARNINGS                                                 //Warnungen werden unterdr�ckt 
#include <stdio.h>                                                              //Bibliotheken
#include <stdlib.h>                                                             //srand, rand
#include <time.h>                                                               //time(Funktionen zu Daten und Zeiten)


//Funktionsdeklarationen
void FeldZur�cksetzen(char Spielfeld[3][3]);                                    //bei neuem Spielstart und ung�ltiger Eingabe wird das Spielfeld zur�ckgesetzt
void SpielFeldAusgeben(char Spielfeld[3][3]);                                   //Ausgabe des Spielfeldes
int FreieFelder�berpr�fen(char Spielfeld[3][3]);                                //pr�fen, ob/wie viele Felder frei sind, f�r jedes gesetzte Symbol ein Feld weniger frei 
void SpielerZug(char Spielfeld[3][3], char SPIELER);                            //vom Benutzer eingegebene Werte werden �perpr�ft auf G�ltigkeit
void ComputerZug(char Spielfeld[3][3], char COMPUTER, char SPIELER);            //zuf�lliges Feld wird generiert, auf Verf�gbarkeit gepr�ft
char Gewinner�berpr�fung(char Spielfeld[3][3]);                                 //�berp�fen auf 3 Gleiche (Reihe, Spalte, Diagonale)
void AusgabeGewinner(char winner, char SPIELER, char COMPUTER);                 //Pr�fen Gewinner Spieler oder Computer, Ausgabe an Nutzer

//Hauptfunktion
int main(void)
{
    char Gewinner = ' ';                                                        //Definition Variable Gewinner , vorerst leer 
    char R�ckgabe = ' ';                                                        //Speicher f�r Nutzerabfrage am Ende
    char SPIELER = 'X';                                                         //Symbolzuweisung f�r Spieler
    char COMPUTER = 'O';                                                        //Symbolzuweisung f�r Computer 
    char Spielfeld[3][3];                                                       //Array Spielfeld, f�r 3 Zeilen, 3 Spalten
    /*srand(1);*/                                                               //randomisierung wird ausgesetzt, Keine zuf�lligen Felder mehr vom Computer (Reproduktion Spielabl�ufe)

    printf("\n\n");
    printf("In diesem Programm koennen Sie gegen einen Computer Tic Tac Toe spielen.\n");
    printf("Gespielt wird nach den klassichen Regeln. Sie haben den ersten  Zug und spielen mit dem Symbol X. Der Compu\n");
    printf("Sie waehlen nacheinander die Reihe und dann die Spalte wo Sie ihr X plazieren wollen.\nBei drei Kreuzen in einer Reihe gewinnen Sie, dabei ist egal ob horizontal, vertikal oder diagonal.\n\n\n");

    do
    {
        Gewinner = ' ';                                                         //Anforderung, w�hrend Gewinner und R�ckgabe leer l�uft Schleife durch 
        R�ckgabe = ' ';
        FeldZur�cksetzen(Spielfeld);                                            //vorerst leeres Spielfeld

        while (Gewinner == ' ' && FreieFelder�berpr�fen(Spielfeld) != 0)        //wenn kein Gewiner und freie Felder verf�gbar 
        {                                   
            SpielFeldAusgeben(Spielfeld);                                       //aktuelles Spielfeld wird ausgegeben 

            SpielerZug(Spielfeld, SPIELER);                                     //Spieler ist am Zug 
            Gewinner = Gewinner�berpr�fung(Spielfeld);                          //Gewinner�berpr�fung 
            if (Gewinner != ' ' || FreieFelder�berpr�fen(Spielfeld) == 0)       //wenn Gewinner existiert oder keine freien Spielfelder 
            {
                break;                                                          //Spielrunde wird beendet 
            }

            ComputerZug(Spielfeld, COMPUTER, SPIELER);                          //Computer ist am Zug 
            Gewinner = Gewinner�berpr�fung(Spielfeld);                          //Gewinner�berpr�fung 
            if (Gewinner != ' ' || FreieFelder�berpr�fen(Spielfeld) == 0)       //wenn Gewinner existiert oder keine freien Spielfelder
            {
                break;                                                          //Spielrunde wird beendet 
            }
        }

        SpielFeldAusgeben(Spielfeld);                                           //aktualisiertes Spielfeld ausgeben
        AusgabeGewinner(Gewinner, SPIELER, COMPUTER);                           //Gewinnerausgabe

        printf("\n\nWuerden sie gerne noch einmal Spielen ?(Ja/Nein): ");           //Abfrage an Nutzer, erneute Spielrunde
        getchar();                                                              //  ?? (�berpr�fung auf character)
        scanf("%c", &R�ckgabe);                                                 //Character wird eingescannt und in "R�ckgabe" gespeichert

    } while (R�ckgabe == 'Ja' || R�ckgabe == 'ja');                             //wenn ja eingegeben erneute Spielrunde

    printf("Vielen Dank f�rs Spielen, wir hoffen sie hatten Spa�!\n");          //bei allem anderen Ausgabe an Nutzer und Spielende

    return 0;
}

//ausgelagerte Funktionen
void FeldZur�cksetzen(char Spielfeld[3][3])                                     //Funktionsdeklaration
{

    for (int i = 0; i < 3; i++)                                                 //Definitionsbereich f�r x
    {
        for (int j = 0; j < 3; j++)                                             //Definitionsbereich f�r y
        {
            Spielfeld[i][j] = ' ';                                              //2 dimensionaler Array, erst Zeilen(x) dann Spalten(y)
        }
    }
}


void SpielFeldAusgeben(char Spielfeld[3][3])                                    
{
    printf(" %c | %c | %c ", Spielfeld[0][0], Spielfeld[0][1], Spielfeld[0][2]);        //Spielfeldausgabe mit Platzhaltern
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", Spielfeld[1][0], Spielfeld[1][1], Spielfeld[1][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", Spielfeld[2][0], Spielfeld[2][1], Spielfeld[2][2]);
    printf("\n\n");
}

int FreieFelder�berpr�fen(char Spielfeld[3][3])
{
    int freeSpaces = 9;                                                         //Anzahl freie Felder vorerst 9

    for (int i = 0; i < 3; i++)                                                 //Definition Wertebereich der �berpr�fung 
    {
        for (int j = 0; j < 3; j++)
        {
            if (Spielfeld[i][j] != ' ')                                         //wenn Spielfeld nicht leer 
            {                                                                   
                freeSpaces--;                                                   //freie Felder werden reduziert
            }
        }
    }
    return freeSpaces;                                                          //aktualisierter Wert wird zur�ckgegeben 
}




void SpielerZug(char Spielfeld[3][3], char SPIELER)                             
{
    int x;                                                                      //Definieren der Vabriablen
    int y;
    char ch;
    int retVal1, retVal2;
    int korrekteEingabe;

    do
    {
        korrekteEingabe = 1;                                                    //true false Bedingung wird gestartet 1 = true

        printf("Waehle eine Reihe von 1-3: ");                                  //Ausgabe an den Benutzer 
        retVal1 = scanf("%d%c", &x, &ch);                                       //gescannter Wert wird in retval gespeichert 
        x--;                                                                    //eingescannter Wert wird reduziert um 1 (3 wird zur 2. Ponsition im Array)
        printf("Waehle eine Spalte von 1-3: ");                                 // -"- f�r y
        retVal2 = scanf("%d%c", &y, &ch);
        y--;

        if (retVal1 != 2 || retVal2 != 2 || ch != '\n' || x < 0 || x >= 3 || y < 0 || y >= 3 || Spielfeld[x][y] != ' ')     //�berpr�fung der vom Nutzer eingebebenen Werte
        {
            korrekteEingabe = 0;                                                //korrekte Eingabe ist false, keine g�ltige Eingabe
            printf("Ungueltige Eingabe! Bitte geben Sie eine gueltige Zeile und Spalte an.\n"); //Ausgabe an Nutzer 
            while (getchar() != '\n');                                          //liest solange alle char bis zu dem Absatz
        }
        else
        {
            Spielfeld[x][y] = SPIELER;                                          //nach Pr�fung der Eingabe neue Abspeicherung
        }
    } while (!korrekteEingabe);                                                 //Negation korrekte Eingabe false , Schleife l�uft erneut durch 
}




void ComputerZug(char Spielfeld[3][3], char COMPUTER, char SPIELER)             //Funktionsdeklaration Computerzug
{
    srand(unsigned int time(0));                                                //Zufallsgenerator wird auf Null gesetzt, zuf�llige Zahlen werden generiert
    int x;
    int y;

    if (FreieFelder�berpr�fen(Spielfeld) > 0)                                   //wenn mehr freie Felder gr��er als null vorhanden sind
    {
        do
        {
            x = rand() % 3;                                                     //3 zuf�llige Werte durch Modulorechnung
            y = rand() % 3;
        } while (Spielfeld[x][y] != ' ');                                       //w�hrend Spielfeldposition nicht leer ist, wird Schleife wiederholt solange bis freies Feld

        Spielfeld[x][y] = COMPUTER;                                             //im SPielfeld wird der Zug des Computers gespeichert mit Symbol O
    }
    else
    {
        AusgabeGewinner(' ', SPIELER, COMPUTER);                                //sobald alle Felder belegt > Gewinnerpr�fung 

    }
}

/*void ComputerZug(char Spielfeld[3][3], char COMPUTER,char SPIELER)            //f�r nicht zuf�llige Z�ge des Computers 
{                                                                               //ohne srand -> Randomisierung wird rausgenommen

    int x;
    int y;

    if (FreieFelder�berpr�fen(Spielfeld) > 0)
    {
        do
        {
            x = rand() % 3;
            y = rand() % 3;
        } while (Spielfeld[x][y] != ' ');

        Spielfeld[x][y] = COMPUTER;
    }
    else
    {
        AusgabeGewinner(' ',SPIELER,COMPUTER);

    }
}*/


char Gewinner�berpr�fung(char Spielfeld[3][3])                                  
{
                                                                                //�berpr�fung der Reihe
    for (int i = 0; i < 3; i++)
    {
        if (Spielfeld[i][0] == Spielfeld[i][1] && Spielfeld[i][0] == Spielfeld[i][2])   //Bedingung f�r alle einer Reihe, x Wert festgelegt 
        {
            return Spielfeld[i][0];                                             //zur�ckgeben aktuelles Spielfeld unver�ndert ???
        }
    }
                                                                                //�berpr�fung in Spalten
    for (int i = 0; i < 3; i++)
    {
        if (Spielfeld[0][i] == Spielfeld[1][i] && Spielfeld[0][i] == Spielfeld[2][i])   //Bedingung f�r alle einer Spalte, y Wert festgelegt 
        {
            return Spielfeld[0][i];
        }
    }
                                                                                //�berpr�fung diagonalen
    if (Spielfeld[0][0] == Spielfeld[1][1] && Spielfeld[0][0] == Spielfeld[2][2])
    {
        return Spielfeld[0][0];
    }
    if (Spielfeld[0][2] == Spielfeld[1][1] && Spielfeld[0][2] == Spielfeld[2][0])
    {
        return Spielfeld[0][2];
    }

    return ' ';
}


void AusgabeGewinner(char winner, char SPIELER, char COMPUTER)              //Der Gewinner wird ausgegeben
{

    if (winner == SPIELER)                                                  //wenn der Gewinner der Spieler ist
    {
        printf("Sie haben gewonnen, f�hlen sie sich jetzt toll?!\n");       //Ausgabe an den Nutzer 
    }
    else if (winner == COMPUTER)                                            //Gewinner ist Computer 
    {
        printf("Leider Verloren du looser!\n");                             //Ausgabe an Nutzer Verloren
    }
    else {
        printf("Gleichstand, n�chstes mal wirds besser!\n");                //Unentschieden
    }

}
//Tic Tac Toe Spiel
//Ein Tic Tac Toe Spiel, bei dem der Benutzer gegen einen Computer spielt. Der Benutzer hat den ersten ZUg und nutzt "X", der Computer wählt zufällige Felder aus und spielt mit "O". Bei drei gleichen Symbolen in einer Reihe ist das Spiel gewonnen, dabei ist egal ob vertikal, horizontal oder diagonal. Wenn es keinen Gewinner gibt, wird das Spiel als unentschieden gewertet.
//Nele Hetzer, Anna Katharina Becker, Finn-Niklas Zymelka
//14.12.2023
//9

#define _CRT_SECURE_NO_WARNINGS                                                 //Warnungen werden unterdrückt 
#include <stdio.h>                                                              //Bibliotheken
#include <stdlib.h>                                                             //srand, rand
#include <time.h>                                                               //time(Funktionen zu Daten und Zeiten)


//Funktionsdeklarationen
void FeldZurücksetzen(char Spielfeld[3][3]);                                    //bei neuem Spielstart und ungültiger Eingabe wird das Spielfeld zurückgesetzt
void SpielFeldAusgeben(char Spielfeld[3][3]);                                   //Ausgabe des Spielfeldes
int FreieFelderÜberprüfen(char Spielfeld[3][3]);                                //prüfen, ob/wie viele Felder frei sind, für jedes gesetzte Symbol ein Feld weniger frei 
void SpielerZug(char Spielfeld[3][3], char SPIELER);                            //vom Benutzer eingegebene Werte werden üperprüft auf Gültigkeit
void ComputerZug(char Spielfeld[3][3], char COMPUTER, char SPIELER);            //zufälliges Feld wird generiert, auf Verfügbarkeit geprüft
char GewinnerÜberprüfung(char Spielfeld[3][3]);                                 //Überpüfen auf 3 Gleiche (Reihe, Spalte, Diagonale)
void AusgabeGewinner(char winner, char SPIELER, char COMPUTER);                 //Prüfen Gewinner Spieler oder Computer, Ausgabe an Nutzer

//Hauptfunktion
int main(void)
{
    char Gewinner = ' ';                                                        //Definition Variable Gewinner , vorerst leer 
    char Rückgabe = ' ';                                                        //Speicher für Nutzerabfrage am Ende
    char SPIELER = 'X';                                                         //Symbolzuweisung für Spieler
    char COMPUTER = 'O';                                                        //Symbolzuweisung für Computer 
    char Spielfeld[3][3];                                                       //Array Spielfeld, für 3 Zeilen, 3 Spalten
    /*srand(1);*/                                                               //randomisierung wird ausgesetzt, Keine zufälligen Felder mehr vom Computer (Reproduktion Spielabläufe)

    printf("\n\n");
    printf("In diesem Programm koennen Sie gegen einen Computer Tic Tac Toe spielen.\n");
    printf("Gespielt wird nach den klassichen Regeln. Sie haben den ersten  Zug und spielen mit dem Symbol X. Der Compu\n");
    printf("Sie waehlen nacheinander die Reihe und dann die Spalte wo Sie ihr X plazieren wollen.\nBei drei Kreuzen in einer Reihe gewinnen Sie, dabei ist egal ob horizontal, vertikal oder diagonal.\n\n\n");

    do
    {
        Gewinner = ' ';                                                         //Anforderung, während Gewinner und Rückgabe leer läuft Schleife durch 
        Rückgabe = ' ';
        FeldZurücksetzen(Spielfeld);                                            //vorerst leeres Spielfeld

        while (Gewinner == ' ' && FreieFelderÜberprüfen(Spielfeld) != 0)        //wenn kein Gewiner und freie Felder verfügbar 
        {                                   
            SpielFeldAusgeben(Spielfeld);                                       //aktuelles Spielfeld wird ausgegeben 

            SpielerZug(Spielfeld, SPIELER);                                     //Spieler ist am Zug 
            Gewinner = GewinnerÜberprüfung(Spielfeld);                          //Gewinnerüberprüfung 
            if (Gewinner != ' ' || FreieFelderÜberprüfen(Spielfeld) == 0)       //wenn Gewinner existiert oder keine freien Spielfelder 
            {
                break;                                                          //Spielrunde wird beendet 
            }

            ComputerZug(Spielfeld, COMPUTER, SPIELER);                          //Computer ist am Zug 
            Gewinner = GewinnerÜberprüfung(Spielfeld);                          //Gewinnerüberprüfung 
            if (Gewinner != ' ' || FreieFelderÜberprüfen(Spielfeld) == 0)       //wenn Gewinner existiert oder keine freien Spielfelder
            {
                break;                                                          //Spielrunde wird beendet 
            }
        }

        SpielFeldAusgeben(Spielfeld);                                           //aktualisiertes Spielfeld ausgeben
        AusgabeGewinner(Gewinner, SPIELER, COMPUTER);                           //Gewinnerausgabe

        printf("\n\nWuerden sie gerne noch einmal Spielen ?(Ja/Nein): ");           //Abfrage an Nutzer, erneute Spielrunde
        getchar();                                                              //  ?? (überprüfung auf character)
        scanf("%c", &Rückgabe);                                                 //Character wird eingescannt und in "Rückgabe" gespeichert

    } while (Rückgabe == 'Ja' || Rückgabe == 'ja');                             //wenn ja eingegeben erneute Spielrunde

    printf("Vielen Dank fürs Spielen, wir hoffen sie hatten Spaß!\n");          //bei allem anderen Ausgabe an Nutzer und Spielende

    return 0;
}

//ausgelagerte Funktionen
void FeldZurücksetzen(char Spielfeld[3][3])                                     //Funktionsdeklaration
{

    for (int i = 0; i < 3; i++)                                                 //Definitionsbereich für x
    {
        for (int j = 0; j < 3; j++)                                             //Definitionsbereich für y
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

int FreieFelderÜberprüfen(char Spielfeld[3][3])
{
    int freeSpaces = 9;                                                         //Anzahl freie Felder vorerst 9

    for (int i = 0; i < 3; i++)                                                 //Definition Wertebereich der Überprüfung 
    {
        for (int j = 0; j < 3; j++)
        {
            if (Spielfeld[i][j] != ' ')                                         //wenn Spielfeld nicht leer 
            {                                                                   
                freeSpaces--;                                                   //freie Felder werden reduziert
            }
        }
    }
    return freeSpaces;                                                          //aktualisierter Wert wird zurückgegeben 
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
        printf("Waehle eine Spalte von 1-3: ");                                 // -"- für y
        retVal2 = scanf("%d%c", &y, &ch);
        y--;

        if (retVal1 != 2 || retVal2 != 2 || ch != '\n' || x < 0 || x >= 3 || y < 0 || y >= 3 || Spielfeld[x][y] != ' ')     //Überprüfung der vom Nutzer eingebebenen Werte
        {
            korrekteEingabe = 0;                                                //korrekte Eingabe ist false, keine gültige Eingabe
            printf("Ungueltige Eingabe! Bitte geben Sie eine gueltige Zeile und Spalte an.\n"); //Ausgabe an Nutzer 
            while (getchar() != '\n');                                          //liest solange alle char bis zu dem Absatz
        }
        else
        {
            Spielfeld[x][y] = SPIELER;                                          //nach Prüfung der Eingabe neue Abspeicherung
        }
    } while (!korrekteEingabe);                                                 //Negation korrekte Eingabe false , Schleife läuft erneut durch 
}




void ComputerZug(char Spielfeld[3][3], char COMPUTER, char SPIELER)             //Funktionsdeklaration Computerzug
{
    srand(unsigned int time(0));                                                //Zufallsgenerator wird auf Null gesetzt, zufällige Zahlen werden generiert
    int x;
    int y;

    if (FreieFelderÜberprüfen(Spielfeld) > 0)                                   //wenn mehr freie Felder größer als null vorhanden sind
    {
        do
        {
            x = rand() % 3;                                                     //3 zufällige Werte durch Modulorechnung
            y = rand() % 3;
        } while (Spielfeld[x][y] != ' ');                                       //während Spielfeldposition nicht leer ist, wird Schleife wiederholt solange bis freies Feld

        Spielfeld[x][y] = COMPUTER;                                             //im SPielfeld wird der Zug des Computers gespeichert mit Symbol O
    }
    else
    {
        AusgabeGewinner(' ', SPIELER, COMPUTER);                                //sobald alle Felder belegt > Gewinnerprüfung 

    }
}

/*void ComputerZug(char Spielfeld[3][3], char COMPUTER,char SPIELER)            //für nicht zufällige Züge des Computers 
{                                                                               //ohne srand -> Randomisierung wird rausgenommen

    int x;
    int y;

    if (FreieFelderÜberprüfen(Spielfeld) > 0)
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


char GewinnerÜberprüfung(char Spielfeld[3][3])                                  
{
                                                                                //Überprüfung der Reihe
    for (int i = 0; i < 3; i++)
    {
        if (Spielfeld[i][0] == Spielfeld[i][1] && Spielfeld[i][0] == Spielfeld[i][2])   //Bedingung für alle einer Reihe, x Wert festgelegt 
        {
            return Spielfeld[i][0];                                             //zurückgeben aktuelles Spielfeld unverändert ???
        }
    }
                                                                                //Überprüfung in Spalten
    for (int i = 0; i < 3; i++)
    {
        if (Spielfeld[0][i] == Spielfeld[1][i] && Spielfeld[0][i] == Spielfeld[2][i])   //Bedingung für alle einer Spalte, y Wert festgelegt 
        {
            return Spielfeld[0][i];
        }
    }
                                                                                //überprüfung diagonalen
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
        printf("Sie haben gewonnen, fühlen sie sich jetzt toll?!\n");       //Ausgabe an den Nutzer 
    }
    else if (winner == COMPUTER)                                            //Gewinner ist Computer 
    {
        printf("Leider Verloren du looser!\n");                             //Ausgabe an Nutzer Verloren
    }
    else {
        printf("Gleichstand, nächstes mal wirds besser!\n");                //Unentschieden
    }

}
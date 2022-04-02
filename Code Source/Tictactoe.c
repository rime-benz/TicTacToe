#include "Tictactoe.h"


int rowNumber=3;
int difficulty=1;
int robot=1;
int pawnShape1='O';
int pawnShape2='X';
int pawnColor1=15;
int pawnColor2=15;
int choose;
int player;
int success1=0;
int success2=0;
int PartPlayer1=0;
int PartPlayer2=0;
int moves1=0;
int moves2=0;
char person[]="player";
char gameDifficulty[10]="easy";
time_t t;


void GameMenu()
{
    char Row;
    int choice, out = 1, gameMode;

    do
    {   /*Affichage du menu principal*/
        printf("\t\t Menu of Tic-Tac-Toe\n");
        printf("\nYou are currently in mode: %dx%d, player vs %s, %s \n", rowNumber,rowNumber,person,gameDifficulty);
        printf("\nType 1 to play\n");
        printf("Type 2 to access the choice of the number of Rows\n");
        printf("Type 3 to access the pawn customization options\n");
        printf("Type 4 to access the choice of game mode\n");
        printf("Type 5 to access the choice of difficulty\n");
        printf("Type 6 to access statistics\n");
        printf("Type 7 to re-view the last part\n");
        printf("Type 8 to load a game\n");
        printf("Type 9 to read the rules\n");
        printf("Type 10 to stop the game\n\n");
        scanf("%d", &choice);
        switch(choice)
        {
        case 1:
            moves1=0;
            moves2=0;
            printf("\n\n To quit insert 0 in row or column\n");
            PartPlayer1++; /*Incrémenter le nombre de partie jouée par le joueur 1*/
            if(robot==1) /*Si le joueur ne joue pas contre l'ordi alors*/
            {
                PartPlayer2++; /*Incrémenter le nombre de partie jouée par le joueur 2*/
            }
            SwitchPlayer(); /*La partie commence*/
            break;
            out = 0;
        case 2:
            Row = RowsNumber(); /*Choix format de la grille*/
            printf("\nYou have chosen %d Rows\n\n", Row);
            break;
        case 3:
            PawnChoice(); /*Personnaliser les pions (du joueur 1/2 au choix)*/
            break;
        case 4:
            gameMode = GameMode(); /*Choix du mode du jeu (contre joueur ou ordi*/
            printf("\nYou have chosen the mode: %d\n\n", gameMode);
            break;
        case 5:
            GameDifficulty(); /*Choix de la difficulté du jeu*/
            printf("\nYou chose the difficulty : %s\n\n", gameDifficulty);
            break;
        case 6:
            Statistics(success1, success2, PartPlayer1, PartPlayer2,moves1,moves2); /*Affiche les statistiques du/des joueur(s)*/
            break;
        case 7:
            ReviewPart(); /*Affiche la dernière partie jouée si elle existe*/
            break;
        case 8:
            LoadPart(); /*Charge une partie si elle existe*/
            break;
        case 9:
            Rules(); /*Affiche les régles du jeu*/
            break;
        case 10:
            out = 0;
            exit(0); /*Quitter le jeu*/
            break;
        default:
            out=0;
            exit(0);
            break;
        }
    }
    while(out != 0); /*Le menu reste afficher tant que le joueur n'a pas choisi une commande */
}

void Grid (int Grd[rowNumber][rowNumber],int pawnShape1,int pawnShape2,int pawnColor1,int pawnColor2)
{
    int i=0,j=0,h=0;
    printf ("\n  ");
    for (h=0;h<rowNumber;h++)
    {
        if(h<10)
        {
            printf ("  %d ",h+1); /*Numéroter les colonnes*/
        }
    }
    printf("\n");
    printf("  ");
    for (int h=0;h<4*rowNumber;h++)
    {
        printf ("-"); /*Définit la borne supérieure horizontale de la grille*/
    }
    printf ("-\n");
    for (i=0;i<rowNumber;i++)
    {
        printf("%d ",i+1); /*Numéroter les lignes*/
        for (j=0;j<rowNumber;j++)
        {
            printf("|"); /*Définit les bornes verticales des cases*/
            switch(Grd[i][j])
            {
                    case 0: /*Case vide*/
                        printf("   ");
                        break;
                    case 1: /*Case occupée par joueur 1*/
                        Color(pawnColor1, 0);
                        printf(" %c ",pawnShape1);
                        Color(15, 0);
                        break;
                    case 2: /*case occupée par joueur 2*/
                        Color(pawnColor2, 0);
                        printf(" %c ",pawnShape2);
                        Color(15, 0);
                        break;
            }
        }
        printf ("|\n"); /*Définit la dernière borne verticale de chaque ligne de la grille*/
        printf("  ");
        for (int h=0;h<4*rowNumber;h++)
        {
        printf ("-"); /*Définit la borne horizontale  de chaque ligne de la grille*/
        }
    printf ("-\n");
    }
}

int SwitchPlayer()
{
    FILE *Sfile = NULL;
    int Grd [rowNumber][rowNumber];
    int player=1;
    memset (Grd, 0, (rowNumber*rowNumber)*sizeof (int)); /*Réinitialise le bloc mémoire*/
    Grid (Grd,pawnShape1,pawnShape2,pawnColor1,pawnColor2);
    Sfile = fopen("Save.txt", "w+");
    fclose(Sfile);
    do
    {
        Game (Grd, player);
        if ( player==1 )
        {
            player=2; /*On passe à l'autre joueur*/
        }
        else
        {
            player=1;
        }
    }
    while (( !WinGame(Grd,player)) && (!EqualGame (Grd))); /*Tant que la partie n'est pas finie*/
    {
        return 0;
    }
}

int RowsNumber()
{
    rowNumber=3;
    int out = 1;
    do
    {
        printf("\nThis game supported between 3 and 10 rows / columns \n");
        printf("\nEnter the number of Rows you want for your grid : ");
        scanf("%d", &rowNumber);

        if(rowNumber > 2 && rowNumber <= 10 )
            {out = 0;}
        else
        {
            printf("\nThe number entered is incorrect !"); /*le jeu est limité au format 10*10*/
            out = 1;
        }
    }
    while(out != 0);
    return rowNumber;
}

void PawnChoice()
{
    int out = 1, choice;
    do
    {
        printf("\n\tChoice of player customization :");
        printf("\nType 1 to customize player 1");
        printf("\nType 2 to customize player 2");
        printf("\nType 3 to return to the previous menu\n\n");
        scanf("%d", &choice);
        switch(choice)
        {
        case 1:
            printf("\nYou have chosen player 1\n"); /*Personnaliser le pion du joueur 1*/
            ChoicePawnPlayer1(pawnShape1,pawnColor1);
            break;
        case 2:
            printf("\nYou have chosen player 2\n");
            ChoicePawnPlayer2(pawnShape2,pawnColor2); /*Personnaliser le pion du joueur 2*/
            break;
        case 3:
            out = 0;
            break;
        default:
            out = 1;
        }
    }
    while (out != 0);
}


int PawnShape()
{
    int TicTacToeChoice, out = 1;
    do
    {
        printf("\n\tChoice of pawn shape :\n");
        printf("Type 1 for a circle : O\n");
        printf("Type 2 for a cross : X\n");
        printf("Type 3 for a plus : +\n");
        printf("Type 4 for a dollar sign : $\n");
        printf("Type 5 for an 'at' sign : @\n");
        printf("Type 6 to go back\n\n");
        scanf("%d", &TicTacToeChoice);

        switch(TicTacToeChoice)
        {
        case 1:
            if(choose==1)
            {
               pawnShape1='O';
            }
            else{pawnShape2='O';}
            out = 0;
            break;
        case 2:
            if(choose==1)
            {
               pawnShape1='X';
            }
            else{pawnShape2='X';}
            out = 0;
            break;
        case 3:
            if(choose==1)
            {
               pawnShape1='+';
            }
            else{pawnShape2='+';}
            out = 0;
            break;
        case 4:
            if(choose==1)
            {
               pawnShape1='$';
            }
            else{pawnShape2='$';}
            out = 0;
            break;
        case 5:
            if(choose==1)
            {
               pawnShape1='@';
            }
            else{pawnShape2='@';}
            out = 0;
            break;
        case 6:
            out = 0;
            break;
        default:
            printf("\nThe chosen shape is not available !\n\n");
            if(choose==1) /*Si les deux joueurs ne veulent pas personnaliser les pions alors ils auront automatiquement O et X*/
            {
               pawnShape1='O';
            }
            else{pawnShape2='X';}
            out = 0;
            break;
        }
    }
    while(out != 0);
    if(choose==1)
    {
        return pawnShape1;
    }
    else
    {
        return pawnShape2;
    }
    return 0;
}


void Color(int txtColor,int backColor) /*fonction d'affichage des couleurs*/
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle,backColor*16+txtColor);
}

int PawnColor()
{
    int TicTacToeChoice, out = 1;
    do
    {
        printf("\n\t Choice of pawn color\n");
        printf("Type 1 for a  ");
        Color(1, 0);
        printf("dark blue pawn\n");
        Color(15, 0);
        printf("Type 2 for a ");
        Color(2, 0);
        printf("dark green pawn\n");
        Color(15, 0);
        printf("Type 3 for a ");
        Color(3, 0);
        printf("turquoise pawn\n");
        Color(15, 0);
        printf("Type 4 for a ");
        Color(4, 0);
        printf("dark red pawn\n");
        Color(15, 0);
        printf("Type 5 for a ");
        Color(5, 0);
        printf("purple pawn\n");
        Color(15, 0);
        printf("Type 6 for an ");
        Color(6, 0);
        printf("orange pawn\n");
        Color(15, 0);
        printf("Type 7 for a ");
        Color(7, 0);
        printf("light grey pawn\n");
        Color(15, 0);
        printf("Type 8 for a ");
        Color(8, 0);
        printf("dark grey pawn\n");
        Color(15, 0);
        printf("Type 9 for a ");
        Color(9, 0);
        printf("light blue pawn\n");
        Color(15, 0);
        printf("Type 10 for a ");
        Color(10, 0);
        printf("light green pawn\n");
        Color(15, 0);
        printf("Type 11 for a ");
        Color(11, 0);
        printf("sky blue pawn\n");
        Color(15, 0);
        printf("Type 12 for a ");
        Color(12, 0);
        printf("light red pawn\n");
        Color(15, 0);
        printf("Type 13 for a ");
        Color(13, 0);
        printf("magenta pawn\n");
        Color(15, 0);
        printf("Type 14 for a ");
        Color(14, 0);
        printf("yellow pawn\n");
        Color(15, 0);
        printf("Type 15 for a white pawn\n\n");
        scanf("%d", &TicTacToeChoice);

        switch(TicTacToeChoice)
        {
        case 1:
            printf("You chose the color number : ");
            Color(TicTacToeChoice, 0);
            printf("%d\n\n", TicTacToeChoice);
            Color(15, 0);
            if(choose==1)
            {
               pawnColor1=1;
            }
            else{pawnColor2=1;}
            out = 0;
            break;
        case 2:
            printf("You chose the color number : ");
            Color(TicTacToeChoice, 0);
            printf("%d\n\n", TicTacToeChoice);
            Color(15, 0);
            if(choose==1)
            {
               pawnColor1=2;
            }
            else{pawnColor2=2;}
            out = 0;
            break;
        case 3:
            printf("You chose the color number : ");
            Color(TicTacToeChoice, 0);
            printf("%d\n\n", TicTacToeChoice);
            Color(15, 0);
            if(choose==1)
            {
               pawnColor1=3;
            }
            else{pawnColor2=3;}
            out = 0;
            break;
        case 4:
            printf("You chose the color number : ");
            Color(TicTacToeChoice, 0);
            printf("%d\n\n", TicTacToeChoice);
            Color(15, 0);
            if(choose==1)
            {
               pawnColor1=4;
            }
            else{pawnColor2=4;}
            out = 0;
            break;
        case 5:
            printf("You chose the color number : ");
            Color(TicTacToeChoice, 0);
            printf("%d\n\n", TicTacToeChoice);
            Color(15, 0);
            if(choose==1)
            {
               pawnColor1=5;
            }
            else{pawnColor2=5;}
            out = 0;
            break;
        case 6:
            printf("You chose the color number : ");
            Color(TicTacToeChoice, 0);
            printf("%d\n\n", TicTacToeChoice);
            Color(15, 0);
            if(choose==1)
            {
               pawnColor1=6;
            }
            else{pawnColor2=6;}
            out = 0;
            break;
        case 7:
            printf("You chose the color number : ");
            Color(TicTacToeChoice, 0);
            printf("%d\n\n", TicTacToeChoice);
            Color(15, 0);
            if(choose==1)
            {
               pawnColor1=7;
            }
            else{pawnColor2=7;}
            out = 0;
            break;
        case 8:
            printf("You chose the color number : ");
            Color(TicTacToeChoice, 0);
            printf("%d\n\n", TicTacToeChoice);
            Color(15, 0);
            if(choose==1)
            {
               pawnColor1=8;
            }
            else{pawnColor2=8;}
            out = 0;
            break;
        case 9:
            printf("You chose the color number : ");
            Color(TicTacToeChoice, 0);
            printf("%d\n\n", TicTacToeChoice);
            Color(15, 0);
            if(choose==1)
            {
               pawnColor1=9;
            }
            else{pawnColor2=9;}
            out = 0;
            break;
        case 10:
            printf("You chose the color number : ");
            Color(TicTacToeChoice, 0);
            printf("%d\n\n", TicTacToeChoice);
            Color(15, 0);
            if(choose==1)
            {
               pawnColor1=10;
            }
            else{pawnColor2=10;}
            out = 0;
            break;
        case 11:
            printf("You chose the color number : ");
            Color(TicTacToeChoice, 0);
            printf("%d\n\n", TicTacToeChoice);
            Color(15, 0);
            if(choose==1)
            {
               pawnColor1=11;
            }
            else{pawnColor2=11;}
            out = 0;
            break;
        case 12:
            printf("You chose the color number : ");
            Color(TicTacToeChoice, 0);
            printf("%d\n\n", TicTacToeChoice);
            Color(15, 0);
            if(choose==1)
            {
               pawnColor1=12;
            }
            else{pawnColor2=12;}
            out = 0;
            break;
        case 13:
            printf("You chose the color number : ");
            Color(TicTacToeChoice, 0);
            printf("%d\n\n", TicTacToeChoice);
            Color(15, 0);
            if(choose==1)
            {
               pawnColor1=13;
            }
            else{pawnColor2=13;}
            out = 0;
            break;
        case 14:
            printf("You chose the color number : ");
            Color(TicTacToeChoice, 0);
            printf("%d\n\n", TicTacToeChoice);
            Color(15, 0);
            if(choose==1)
            {
               pawnColor1=14;
            }
            else{pawnColor2=14;}
            out = 0;
            break;
        case 15:
            printf("\nYou chose the color number : ");
            Color(TicTacToeChoice, 0);
            printf("%d\n\n", TicTacToeChoice);
            Color(15, 0);
            if(choose==1)
            {
               pawnColor1=15;
            }
            else{pawnColor2=15;}
            out = 0;
            break;
        default:
            printf("The chosen Color is not available !\n\n");
            out = 1;
            break;
        }
    }
    while(out != 0);
    return TicTacToeChoice;
}

void ChoicePawnPlayer1(int pawnShape1, int pawnColor1)
{
    int out = 1, choice;
    do
    {
        printf("\n\tPawn choice");
        printf("\nType 1 to choose the pawn form");
        printf("\nType 2 to choose the pawn color");
        printf("\nType 3 to return to the previous menu\n\n");
        scanf("%d", &choice);

        switch(choice)
        {
        case 1:
            choose=1;
            pawnShape1 = PawnShape();
            printf("\nYou chose the pawn : %c\n", pawnShape1);
            break;
        case 2:
            choose=1;
            pawnColor1 = PawnColor();
            break;
        case 3:
            out = 0;
            break;
        default:
            out = 1;
        }
    }
    while (out != 0);
}

void ChoicePawnPlayer2(int pawnShape2, int pawnColor2)
{
    int out = 1, choice;
    do
    {
        printf("\n\tPawn choice");
        printf("\nType 1 to choose the pawn form");
        printf("\nType 2 to choose the pawn color");
        printf("\nType 3 to return to the previous menu\n\n");
        scanf("%d", &choice);

        switch(choice)
        {
        case 1:
            choose=2;
            pawnShape2 = PawnShape();
            printf("\nYou chose the pawn : %c\n", pawnShape2);
            break;
        case 2:
            choose=2;
            pawnColor2 = PawnColor();
            break;
        case 3:
            out = 0;
            break;
        default:
            out = 1;
        }
    }
    while (out != 0);
}

int GameMode()
{
    int Choice, out = 1;
    do
    {
        printf("\n\tChoice of game mode :\n");
        printf("Type 1 to play against another player \n");
        printf("Type 2 to play against an AI\n");
        printf("Type 3 to go back\n\n");

        scanf("%d", &Choice);
        switch(Choice)
        {
        case 1:
            robot = 1;
            out = 0;
            break;
        case 2:
            robot = 2;
            out = 0;
            break;
        case 3:
            out = 0;
            break;
        default:
            printf("\nThe chosen game mode is not available !\n\n");
            out = 1;
            break;
        }
    }
    while(out != 0);
    if(robot==1)
    {
        person[0]='j';
        person[1]='o';
        person[2]='u';
        person[3]='e';
        person[4]='u';
        person[5]='r';
        person[6]='\0';
    }
    if(robot==2)
    {
        person[0]='o';
        person[1]='r';
        person[2]='d';
        person[3]='i';
        person[4]='\0';
    }
    return robot;
}

int GameDifficulty()
{
    int Choice, out = 1;
    do
    {
        printf("\n\tChoice of game difficulty :\n");
        printf("Type 1 for for an easy Game \n");
        printf("Type 2 for a medium difficulty Game\n");
        printf("Type 3 for for a high difficulty Game\n");
        printf("Type 4 to go back\n\n");

        scanf("%d", &Choice);
        switch(Choice)
        {
        case 1:
            difficulty = 1;
            gameDifficulty[0]='e';
            gameDifficulty[1]='a';
            gameDifficulty[2]='s';
            gameDifficulty[3]='y';
            gameDifficulty[4]='\0';
            out = 0;
            break;
        case 2:
            difficulty = 2;
            gameDifficulty[0]='m';
            gameDifficulty[1]='e';
            gameDifficulty[2]='d';
            gameDifficulty[3]='i';
            gameDifficulty[4]='u';
            gameDifficulty[5]='m';
            gameDifficulty[6]='\0';
            out = 0;
            break;
        case 3:
            difficulty = 3;
            gameDifficulty[0]='d';
            gameDifficulty[1]='i';
            gameDifficulty[2]='f';
            gameDifficulty[3]='f';
            gameDifficulty[4]='i';
            gameDifficulty[5]='c';
            gameDifficulty[6]='u';
            gameDifficulty[7]='l';
            gameDifficulty[8]='t';
            gameDifficulty[9]='\0';
            out = 0;
            break;
        case 4:
            out = 0;
            break;
        default:
            printf("\nThe Game difficulty chosen is not available !\n\n");
            out = 1;
            break;
        }
    }
    while(out != 0);
    return difficulty;
}

void Statistics(int success1,int success2,int PartPlayer1,int PartPlayer2,int moves1, int moves2)
{
    int out = 1,choice;
    do
    {
        printf("\n\tStatistics");
        printf("\nStatistics person 1 :\n");
        printf("\n\tGames played : %d\n", PartPlayer1);
        printf("\n\tGames won : %d\n", success1);
        printf("\n\tMoves from the last part: %d\n", moves1);
        printf("\nStatistics person 2 :\n");
        printf("\n\tGames played : %d\n", PartPlayer2);
        printf("\n\tGames won : %d\n", success2);
        printf("\n\tMoves from the last part: %d\n", moves2);
        printf("\nType 1 to return to the previous menu\n\n");
        scanf("%d", &choice);
        switch(choice)
        {
        case 1:
            out=0;
            break;
        default:
            out = 1;
        }
    }
    while (out != 0);
}

void ReviewPart()
{
    int a;
    int positionX=0,positionY=0;
    int correct=FALSE;
    FILE * Freview = NULL;
    int player = 1;
    int Grd [rowNumber][rowNumber];
    memset (Grd, 0, (rowNumber*rowNumber)*sizeof (int)); /*réinitialise le block mémoire*/
    Freview = fopen("Save.txt", "r");
    rewind(Freview); /*le pointeur pointe vers tête du fichier pour commencer la lecture*/

    if (Freview != NULL)
    {
        while(fscanf(Freview, "%d %d", &positionX, &positionY)!= EOF) /*Tant que le pointeur ne pointe pas sur le "END OF FILE"*/
        {
            do
            {
                printf ("person %d\n",player);
                Grd[positionX-1][positionY-1]=player; /*voir case 0,1,2*/
                correct=TRUE;
            }
            while (!correct);
            {
                Grid (Grd,pawnShape1,pawnShape2,pawnColor1,pawnColor2);
            }
            if ( player==1 )
            {
                player=2;
            }
            else
            {
                player=1;
            }
        }
    }
    else
    {
        printf("There is no game to review");
    }
    fclose(Freview);
    printf("\nType 0 to return to the previous menu\n");
    scanf("%d",&a);
    printf("\n");
    if (a==0)
    {
        GameMenu();
    }
}

void LoadPart()
{
    FILE * Freview;
    int positionX=0, positionY=0;
    int correct=FALSE;
    int Vreview=TRUE;
    int player = 1;
    int Grd [rowNumber][rowNumber];
    memset (Grd, 0, (rowNumber*rowNumber)*sizeof (int));
    Freview = fopen("Save.txt", "r+");
    rewind(Freview); /*le pointeur pointe vers la tête du fichier*/

    if (Freview != NULL)
    {
        while(fscanf(Freview, "%d %d", &positionX, &positionY) != EOF)
        {
            do
            {
                printf ("person %d\n",player);
                Grd[positionX-1][positionY-1]=player;
                correct=TRUE;
            }
            while (!correct);
            {
                Grid (Grd,pawnShape1,pawnShape2,pawnColor1,pawnColor2);
            }
            if ( player==1 )
            {
                player=2;
            }
            else
            {
                player=1;
            }
        }
    }
    else{printf("There is no game to load.");}
    fclose(Freview);
    do
    {
        if(WinGame(Grd,player)|| EqualGame(Grd))
        {
            Vreview=FALSE;
            PawnChoice();
            return;
        }
        if(Vreview==TRUE)
        {
            Game(Grd,player);
        }
        if( player==1 )
        {
            player=2;
        }
        else
        {
            player=1;
        }
    }
    while((!WinGame(Grd,player) && Vreview==TRUE) || (!EqualGame(Grd) && Vreview==TRUE));
    return;
}

void Rules()
{
    int out = 1,choice;
    do
    {
        printf("\nTic-Tac-Toe is a game of reflection involving two players in turn and the goal of each player is to be the first creating an alignment on a grid.\nThe size of the grid is not defined, so it is possible to vary it to change the difficulty of the game.\nThe first who manages to align 3 of their symbols horizontally, vertically or diagonally wins the game.\n");
        printf("\nTo quit type 1\n");
        scanf("%d", &choice);
        switch(choice)
        {
        case 1:
            out=0;
            break;
        default:
            out = 1;
        }
    }
    while(out != 0);
}

int Data(char *data)
{
    int X;
    int Y=0;
    do
    {
        printf ("%s", data); /*afficher le joueur qui joue*/
        scanf("%d",&X); /*attribuer valeur pour ligne ou colonne (à modifier)*/
        Y=1;
    }
    while (((( X >1) && (Y==0) && (X <rowNumber) ))); /*lorque valeur n'est pas dans 1<valeur<rowNumber on redemande la saisie de donnée*/
    Y=1;
    return (X); /*afficher la valeur entrée*/
}

void BackUp(FILE * Fbackup, int positionX, int positionY)
{
    Fbackup = fopen("Save.txt", "a");
    if (Fbackup == NULL)
    {
        printf("Unable to open backup file"); /*On affiche un message d'erreur si le fichier ne s'ouvre pas*/
    }
    else
    {
        fprintf(Fbackup, "%d %d\n", positionX, positionY);
    }
    fclose(Fbackup);
}

int random() {
    srand(time(NULL));
    int randomNumber= (rand()%rowNumber);
    return randomNumber;
}


void Game (int Grd[rowNumber][rowNumber], int player)
{
    int positionX=1,positionY=1;
    int k=0;
    int correct=FALSE; /*FALSE tant que le jeu n'est pas fini*/
    int test=FALSE; /*FALSE tant que le robot n'a pas encore jouer*/
    int secondTest=TRUE; /*TRUE tant que le robot n'a ni gagné la partie ni contré l'adversaire */
    int thirdTest=TRUE; /*TRUE tant que le robot n'a pas gagné la partie*/
    int blockTest=TRUE; /*TRUE tant que le robot n'a pas contré l'adversaire*/
    FILE * Fbackup=NULL;
    do /*Tant que le correct=FALSE*/
    {
        if(player==1 || (player==2 && robot==1))
        {
            printf("person %d\n",player);
            positionX= Data ("Row : ");
            positionY= Data ("Column : ");
            while ((positionX>rowNumber || positionY>rowNumber)&& positionX!=0 && positionY!=0)
            {
                printf("\nThe number entered is incorrect ! enter another one !!\n");
                positionX= Data ("Row : ");
                positionY= Data ("Column : ");
            }
            if ((positionX==0 || positionY==0))
            {
                GameMenu();
                correct=TRUE;
            }
            if ( Grd[positionX-1][positionY-1]>0 )
            {
                printf ("Occupied box !\n");
            }
            if ( Grd[positionX-1][positionY-1]==0 )
            {
                if(player==1)
                {
                    moves1++;
                }
                if(player==2)
                {
                    moves2++;
                }
                Grd[positionX-1][positionY-1]=player;
                correct=TRUE;
                BackUp(Fbackup, positionX, positionY); /*sauvegarder la position du pion*/
                Sleep(500);
            }
        }
        if(player==2 && robot==2)
        {
            do /*Tant que le test = FALSE*/
            {
                for(int i=0;i<rowNumber;i++)
                {
                    for(int j=0;j<rowNumber;j++)
                    {

/*Techniques pour gagner*/

        /*Sur les colonnes*/
                        if(Grd[i][j]==2 && Grd[i][j]==Grd[i+1][j] && Grd[i-1][j]==0 && i-1>=0 && thirdTest==TRUE && difficulty==3)
                        {
                            Grd[i-1][j]=2; /*Completer une case vide en début de colonne pour gagner*/
                            secondTest=FALSE;
                            correct=TRUE;
                            test=TRUE;
                            thirdTest=FALSE;
                            BackUp(Fbackup, i, j+1); /*sauvegarder la position du pion*/
                        }
                        if(Grd[i][j]==2 && Grd[i][j]==Grd[i+2][j] && Grd[i+1][j]==0 && i+2<rowNumber && thirdTest==TRUE && difficulty==3)
                        {
                            Grd[i+1][j]=2; /*Completer une case vide au milieu de colonne pour gagner*/
                            secondTest=FALSE;
                            correct=TRUE;
                            test=TRUE;
                            thirdTest=FALSE;
                            BackUp(Fbackup, i+2, j+1); /*sauvegarder la position du pion*/
                        }
                        if(Grd[i][j]==2 && Grd[i][j]==Grd[i+1][j] && Grd[i+2][j]==0 && i+2<rowNumber && thirdTest==TRUE  && difficulty==3)
                        {
                            Grd[i+2][j]=2; /*Completer une case vide en fin de colonne pour gagner*/
                            secondTest=FALSE;
                            correct=TRUE;
                            test=TRUE;
                            thirdTest=FALSE;
                            BackUp(Fbackup, i+3, j+1); /*sauvegarder la position du pion*/
                        }

        /*Sur les lignes*/
                        if(Grd[i][j+1]==2 && Grd[i][j+1]==Grd[i][j+2] && Grd[i][j]==0 && j+2<rowNumber && thirdTest==TRUE && difficulty==3)
                        {
                            Grd[i][j]=2; /*Completer une case vide en début de ligne pour gagner*/
                            secondTest=FALSE;
                            correct=TRUE;
                            test=TRUE;
                            thirdTest=FALSE;
                            BackUp(Fbackup, i+1, j+1); /*sauvegarder la position du pion*/
                        }
                        if(Grd[i][j]==2 && Grd[i][j]==Grd[i][j+2] && Grd[i][j+1]==0 && j+2<rowNumber && thirdTest==TRUE && difficulty==3)
                        {
                            Grd[i][j+1]=2; /*Completer une case vide en milieu de ligne pour gagner*/
                            secondTest=FALSE;
                            correct=TRUE;
                            test=TRUE;
                            thirdTest=FALSE;
                            BackUp(Fbackup, i+1, j+2); /*sauvegarder la position du pion*/
                        }
                        if(Grd[i][j]==2 && Grd[i][j]==Grd[i][j+1] && Grd[i][j+2]==0 && j+2<rowNumber && thirdTest==TRUE && difficulty==3)
                        {
                            Grd[i][j+2]=2; /*Completer une case vide en fin de ligne pour gagner*/
                            secondTest=FALSE;
                            correct=TRUE;
                            test=TRUE;
                            thirdTest=FALSE;
                            BackUp(Fbackup, i+1, j+3); /*sauvegarder la position du pion*/
                        }

        /*Sur la diagonale de gauche à droite*/
                        if(Grd[i][j]==2 && Grd[i][j]==Grd[i-1][j-1] && Grd[i-2][j-2]==0 && j-1>=0 && j-2>=0 && i-2>=0 && thirdTest==TRUE && difficulty==3)
                        {
                            Grd[i+2][j-2]=2; /*Completer une case vide en début de la diagonale (de gauche à droite) pour gagner*/
                            secondTest=FALSE;
                            correct=TRUE;
                            test=TRUE;
                            thirdTest=FALSE;
                            BackUp(Fbackup, i-1, j-1); /*sauvegarder la position du pion*/
                        }
                        if(Grd[i][j]==2 && Grd[i][j]==Grd[i-2][j-2] && Grd[i-1][j-1]==0 && j-2>=0 && i-2>=0 && thirdTest==TRUE && difficulty==3)
                        {
                            Grd[i-1][j-1]=2;  /*Completer une case vide en milieu de la diagonale (de gauche à droite) pour gagner*/
                            secondTest=FALSE;
                            correct=TRUE;
                            test=TRUE;
                            thirdTest=FALSE;
                            BackUp(Fbackup, i, j); /*sauvegarder la position du pion*/
                        }
                        if(Grd[i][j]==2 && Grd[i][j]==Grd[i+1][j+1] && Grd[i+2][j+2]==0 && j+2<rowNumber && i+2<rowNumber && thirdTest==TRUE && difficulty==3)
                        {
                            Grd[i+2][j+2]=2; /*Completer une case vide en fin de la diagonale (de gauche à droite) pour gagner*/
                            secondTest=FALSE;
                            correct=TRUE;
                            test=TRUE;
                            thirdTest=FALSE;
                            BackUp(Fbackup, i+3, j+3); /*sauvegarder la position du pion*/
                        }

        /*Sur la diagonale de droite à gauche*/
                        if(Grd[i][j]==2 && Grd[i][j]==Grd[i-1][j+1] && Grd[i-2][j+2]==0 && j+1<rowNumber && j+2<rowNumber && i-2>=0 && thirdTest==TRUE && difficulty==3)
                        {
                            Grd[i+2][j-2]=2; /*Completer une case vide en début de la diagonale (de droite à gauche) pour gagner*/
                            secondTest=FALSE;
                            correct=TRUE;
                            test=TRUE;
                            thirdTest=FALSE;
                            BackUp(Fbackup, i-1, j+3); /*sauvegarder la position du pion*/
                        }
                        if(Grd[i][j]==2 && Grd[i][j]==Grd[i-2][j+2] && Grd[i-1][j+1]==0 && j+2<=rowNumber && i-2>=0 && thirdTest==TRUE && difficulty==3)
                        {
                            Grd[i-1][j+1]=2; /*Completer une case vide en milieu de la diagonale (de droite à gauche) pour gagner*/
                            secondTest=FALSE;
                            correct=TRUE;
                            test=TRUE;
                            thirdTest=FALSE;
                            BackUp(Fbackup, i, j+2); /*sauvegarder la position du pion*/
                        }
                        if(Grd[i][j]==2 && Grd[i][j]==Grd[i+1][j-1] && Grd[i+2][j-2]==0 && j-1>=0 && j-2>=0 && i+1<rowNumber && thirdTest==TRUE && difficulty==3)
                        {
                            Grd[i+2][j-2]=2; /*Completer une case vide en fin de la diagonale (de droite à gauche) pour gagner*/
                            secondTest=FALSE;
                            correct=TRUE;
                            test=TRUE;
                            thirdTest=FALSE;
                            BackUp(Fbackup, i+3, j-1); /*sauvegarder la position du pion*/
                        }

/*Techniques pour empêcher le joueur de gagner*/

        /*Sur les colonnes*/
                        if(Grd[i][j]==1 && Grd[i][j]==Grd[i+1][j] && Grd[i-1][j]==0 && i-1>=0 && blockTest==TRUE && thirdTest==TRUE && difficulty>1)//test pour bloquer une colonne au dessus
                        {
                            Grd[i-1][j]=2; /*Completer une case vide en début de colonne pour empêcher le joueur de gagner*/
                            blockTest=FALSE;
                            secondTest=FALSE;
                            correct=TRUE;
                            test=TRUE;
                            BackUp(Fbackup, i, j+1); /*sauvegarder la position du pion*/
                        }
                        if(Grd[i][j]==1 && Grd[i][j]==Grd[i+2][j] && Grd[i+1][j]==0 && blockTest==TRUE && thirdTest==TRUE && difficulty>1)//test pour bloquer une colonne trouée
                        {
                            Grd[i+1][j]=2; /*Completer une case vide en milieu de colonne pour empêcher le joueur de gagner*/
                            blockTest=FALSE;
                            secondTest=FALSE;
                            correct=TRUE;
                            test=TRUE;
                            BackUp(Fbackup, i+2, j+1); /*sauvegarder la position du pion*/
                        }
                        if(Grd[i][j]==1 && Grd[i][j]==Grd[i+1][j] && Grd[i+2][j]==0 && i+2<rowNumber && blockTest==TRUE && thirdTest==TRUE && difficulty>1)//test pour bloquer une colonne en dessous
                        {
                            Grd[i+2][j]=2; /*Completer une case vide en fin de colonne pour empêcher le joueur de gagner*/
                            blockTest=FALSE;
                            secondTest=FALSE;
                            correct=TRUE;
                            test=TRUE;
                            BackUp(Fbackup, i+3, j+1); /*sauvegarder la position du pion*/
                        }

        /*Sur les lignes*/
                        if(Grd[i][j]==1 && Grd[i][j]==Grd[i][j+1] && Grd[i][j-1]==0 && j-1>=0 && blockTest==TRUE && thirdTest==TRUE && difficulty>1)//test pour bloquer une ligne gauche
                        {
                            Grd[i][j-1]=2; /*Completer une case vide en début de ligne pour empêcher le joueur de gagner*/
                            blockTest=FALSE;
                            secondTest=FALSE;
                            correct=TRUE;
                            test=TRUE;
                            BackUp(Fbackup, i+1, j); /*sauvegarder la position du pion*/
                        }
                        if(Grd[i][j]==1 && Grd[i][j]==Grd[i][j+2] && Grd[i][j+1]==0 && blockTest==TRUE && thirdTest==TRUE && difficulty>1)//test pour bloquer une ligne trouée
                        {
                            Grd[i][j+1]=2;  /*Completer une case vide en milieu de ligne pour empêcher le joueur de gagner*/
                            blockTest=FALSE;
                            secondTest=FALSE;
                            correct=TRUE;
                            test=TRUE;
                            BackUp(Fbackup, i+1, j+2); /*sauvegarder la position du pion*/
                        }
                        if(Grd[i][j]==1 && Grd[i][j]==Grd[i][j+1] && Grd[i][j+2]==0 && j+2<rowNumber && blockTest==TRUE && thirdTest==TRUE && difficulty>1)//test pour bloquer une Row droite
                        {
                            Grd[i][j+2]=2; /*Completer une case vide en fin de ligne pour empêcher le joueur de gagner*/
                            blockTest=FALSE;
                            secondTest=FALSE;
                            correct=TRUE;
                            test=TRUE;
                            BackUp(Fbackup, i+1, j+3); /*sauvegarder la position du pion*/
                        }

        /*Sur la diagonale de gauche à droite*/
                        if(Grd[i][j]==1 && Grd[i][j]==Grd[i-1][j-1] && Grd[i-2][j-2]==0 && j-2>=0 && i-2>=0 && blockTest==TRUE && thirdTest==TRUE && difficulty>1)//test pour bloquer une diagonale haut gauche
                        {
                            Grd[i-2][j-2]=2; /*Completer une case vide en début de la diagonale (de gauche à droite) pour empêcher le joueur de gagner*/
                            blockTest=FALSE;
                            secondTest=FALSE;
                            correct=TRUE;
                            test=TRUE;
                            BackUp(Fbackup, i-1, j-1); /*sauvegarder la position du pion*/
                        }
                        if(Grd[i][j]==1 && Grd[i][j]==Grd[i-2][j-2] && Grd[i-1][j-1]==0 && j-2>=0 && i-2>=0 && blockTest==TRUE && thirdTest==TRUE && difficulty>1)//test pour bloquer une diagonale milieu gauche
                        {
                            Grd[i-1][j-1]=2; /*Completer une case vide en milieu de la diagonale (de gauche à droite) pour empêcher le joueur de gagner*/
                            blockTest=FALSE;
                            secondTest=FALSE;
                            correct=TRUE;
                            test=TRUE;
                            BackUp(Fbackup, i, j); /*sauvegarder la position du pion*/
                        }
                        if(Grd[i][j]==1 && Grd[i][j]==Grd[i+1][j+1] && Grd[i+2][j+2]==0 && j+2<rowNumber && i+2<rowNumber && blockTest==TRUE && thirdTest==TRUE && difficulty>1)//test pour bloquer une diagonale bas droite
                        {
                            Grd[i+2][j+2]=2; /*Completer une case vide en fin de la diagonale (de gauche à droite) pour empêcher le joueur de gagner*/
                            blockTest=FALSE;
                            secondTest=FALSE;
                            correct=TRUE;
                            test=TRUE;
                            BackUp(Fbackup, i+3, j+3); /*sauvegarder la position du pion*/
                        }

        /*Sur la diagonale de droite à gauche*/
                        if(Grd[i][j]==1 && Grd[i][j]==Grd[i-1][j+1] && Grd[i-2][j+2]==0 && j+2<rowNumber && i-2>=0 && blockTest==TRUE && thirdTest==TRUE && difficulty>1)//test pour bloquer une diagonale haut droite
                        {
                            Grd[i-2][j+2]=2; /*Completer une case vide en début de la diagonale (de droite à gauche) pour empêcher le joueur de gagner*/
                            blockTest=FALSE;
                            secondTest=FALSE;
                            correct=TRUE;
                            test=TRUE;
                            BackUp(Fbackup, i-1, j+3); /*sauvegarder la position du pion*/
                        }
                        if(Grd[i][j]==1 && Grd[i][j]==Grd[i-2][j+2] && Grd[i-1][j+1]==0 && j+2<rowNumber && i-2>=0 && blockTest==TRUE && thirdTest==TRUE && difficulty>1)//test pour bloquer une diagonale milieu droite
                        {
                            Grd[i-1][j+1]=2; /*Completer une case vide en milieu de la diagonale (de droite à gauche) pour empêcher le joueur de gagner*/
                            blockTest=FALSE;
                            secondTest=FALSE;
                            correct=TRUE;
                            test=TRUE;
                            BackUp(Fbackup, i, j+2); /*sauvegarder la position du pion*/
                        }
                        if(Grd[i][j]==1 && Grd[i][j]==Grd[i+1][j-1] && Grd[i+2][j-2]==0 && j-2>=0 && i+2<rowNumber && blockTest==TRUE && thirdTest==TRUE && difficulty>1)//test pour bloquer une diagonale bas gauche
                        {
                            Grd[i+2][j-2]=2; /*Completer une case vide en fin de la diagonale (de droite à gauche) pour empêcher le joueur de gagner*/
                            blockTest=FALSE;
                            secondTest=FALSE;
                            correct=TRUE;
                            test=TRUE;
                            BackUp(Fbackup, i+3, j-1); /*sauvegarder la position du pion*/
                        }

                    }
                }
                while(secondTest==TRUE) /*Le robot n'a ni contré son adversaire ni gagné la partie*/
                {
                    positionX=random();
                    Sleep(1000);
                    positionY=random();
                    if(Grd[positionX][positionY]==0)
                        {
                            Grd[positionX][positionY]=2;
                            BackUp(Fbackup, positionX+1,positionY+1); /*sauvegarder la position du pion*/
                            secondTest=FALSE;
                            correct=TRUE;
                            test=TRUE;
                        }
                        else
                        {
                            positionX=random();
                            Sleep(1000);
                            positionY=random();
                        }
                }
            } while (!test);
        }
    }while (!correct);
    Grid  (Grd,pawnShape1,pawnShape2,pawnColor1,pawnColor2);
}

int WinGame (int Grd[rowNumber][rowNumber],int player)
{
    for ( int i=0; i<=rowNumber; i++)
    {
        for (int j=0; j<rowNumber-2;j++)
            if (( Grd[i][j] >0) && ( Grd[i][j] == Grd[i][j+1] ) && ( Grd[i][j+1] == Grd[i][j+2] )) /*Vérifier si plusieurs cases d'une même ligne sont remplies*/
            {
                if(player==1)
                {
                    player=2;
                    printf("The player %d won\n\n",player);
                    success2++;
                    player=1;
                    return TRUE;
                }
                if(player==2)
                {
                    player=1;
                    printf("The player %d won\n\n",player);
                    success1++;
                    player=2;
                    return TRUE;
                }
            }
    }
    for ( int i=0; i<rowNumber-2; i++)
    {
        for (int j=0; j<rowNumber;j++)
        {
            if (( Grd[i][j] >0) && ( Grd[i][j] == Grd[i+1][j] ) && ( Grd[i+1][j] == Grd[i+2][j] )) /*Vérifier si plusieurs cases d'une même colonne sont remplies*/
            {
                if(player==1)
                {
                    player=2;
                    printf("The player %d won\n\n",player);
                    success2++;
                    player=1;
                    return TRUE;
                }
                if(player==2)
                {
                    player=1;
                    printf("The player %d won\n\n",player);
                    success1++;
                    player=2;
                    return TRUE;
                }
            }
        }
    }
    for ( int i=0; i<rowNumber-2; i++)
    {
        for (int j=0; j<rowNumber-2;j++)
            if (( Grd[i][j] >0) && ( Grd[i][j] == Grd[i+1][j+1] ) && ( Grd[i+1][j+1] == Grd[i+2][j+2])) /*Si plusieurs cases de la diagonale de gauche à droite sont remplies*/
            {
                if(player==1)
                {
                    player=2;
                    printf("The player %d won\n\n",player);
                    success2++;
                    player=1;
                    return TRUE;
                }
                if(player==2)
                {
                    player=1;
                    printf("The player %d won\n\n",player);
                    success1++;
                    player=2;
                    return TRUE;
                }
            }
    }
    for ( int i=2; i<rowNumber; i++)
    {
        for (int j=0; j<rowNumber-2;j++)
            if (( Grd[i][j] >0) && ( Grd[i][j] == Grd[i-1][j+1] ) && ( Grd[i-1][j+1] == Grd[i-2][j+2])) /*Si plusieurs cases de la diagonale de droite à gauche sont remplies*/
            {
                if(player==1)
                {
                    player=2;
                    printf("The player %d won\n\n",player);
                    success2++;
                    player=1;
                    return TRUE;
                }
                if(player==2)
                {
                    player=1;
                    printf("The player %d won\n\n",player);
                    success1++;
                    player=2;
                    return TRUE;
                }
            }
    }
    return FALSE; /*Si personne ne gagne alors la partie continue*/
}

int EqualGame(int Grd[rowNumber][rowNumber])
{
    int i=0,j=0;
    for (i=0;i<rowNumber;i++)
    {
        for (j=0;j<rowNumber;j++)
        {
            if (Grd[i][j]==0) /*S'il y a encore des cases vides*/
            {
                return FALSE;/*le jeu continue*/
            }
        }
    }
    puts("Equal Score");
    return TRUE; /*fin du jeu*/
}



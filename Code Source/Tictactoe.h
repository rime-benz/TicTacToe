#ifndef PROJECT_TICTACTOE_INCLUDED
#define PROJECT_TICTACTOE_INCLUDED

#endif // PROJECT_TICTACTOE_INCLUDED


#include <stdio.h>
#include <string.h>
#include <windows.h>
#include<time.h>

#define TRUE 1
#define FALSE 0

void GameMenu();/*Fonction affichant le menu principale du jeu (regroupe tout les menus)*/

void Grid();/*Fonction permettant de dessiner la grille avec la taille choisie par le joueur*/

int SwitchPlayer();/*Fonction permettant de poser la grille,l'enregistrer dans le fichier Save et switcher d'un joueur � l'autre tant que la partie n'est pas termin�e*/

int RowsNumber();/*Fonction permettant de choisir le nombre de lignes*/

//Fonction personnalisation pion
void PawnChoice();/*Fonction permetttant de choisir le pion (forme et couleur)*/
void Color();/*Fonction permettant l'affichage des couleurs*/
int PawnColor();    /*Fonction qui d�finit les couleurs possibles du pion*/
int PawnShape();/*Fonction qui d�finit les formes possibles du pion*/
void ChoicePawnPlayer1();/*Fonction permetttant de choisir le pion du joueur 1 (forme et couleur)*/
void ChoicePawnPlayer2();/*Fonction permetttant de choisir le pion du joueur 2 (forme et couleur)*/

int GameMode();/*Fonction permettant de choisir l'adversaire*/

int GameDifficulty();/*Fonction permettant de choisir le niveau de difficult�*/

void Statistics();/*Fonction affichant les statistiques des parties jou�es*/

void ReviewPart();/*Fonction permettant de revoir la derni�re partie jou�e*/

void LoadPart();/*Fonction permettant de charger une partie (si on l'a commenc� sans l'avoir fini)*/

void Rules();/*Fonction affichant les r�gles du jeu*/

int Data();/*Fonction permettant d'entrer le num�ro de la ligne/la colonne afin de d�poser votre pion*/
void BackUp();/*Fonction permettant l'enregistrement de la position du pion de chacun des deux joueurs afin de sauvgarder la partie*/
int random();/*Fonction permettant de choisir un nombre al�atoire entre 0 et un nombre fix�*/

void Game ();/*Fonction du jeu*/
int WinGame ();/*Fonction v�rifiant si un des deux joueurs a gagn� et le d�clare*/
int EqualGame ();/*Fonction fixant les conditions de fin du jeu*/



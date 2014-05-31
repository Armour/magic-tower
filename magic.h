#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include <bios.h>
#include "graphics.h" 

void Run(char);
void Esc(void);
void Magic(void);
void Quit(void);
void Shop(void);
void Help(void);
void Ending(void);
void Welcome(void);
void Info_Prep(void);
void Select_Sex(void);
void Set_Memory(void);
void Tips_Oldman(void);
void Tips_Sorceress(void);
void Load_Memory(void);
void Monster_Book(void);
void Monster_Fight(int);
void Monster_Defeated(void);
void Map_Prep(void);
void Map_Print(void);
void Upstairs(void);
void Downstairs(void);

int Load_24bit_Bmp(int, int, char *);



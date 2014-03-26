#include<stdio.h>
#include<stdlib.h>
#include<dos.h>
#include<conio.h>
#include<time.h>
#include"graphics.h" 

#define green 2
#define yellow 14
#define white 15
#define red 4

void run(char);
void init(void);
void prep(void);
void work(void);
void look(void);
void shop(void);
void quit(void);
void book(void);
void print(void);
void fighting(int);
void defeated(void);
void Upstairs(void);
void Downstairs(void);

int Player_hp, Player_attack, Player_defend, Player_money, Player_exp, Player_level;
int now_I, now_J, now_floor;
int key_num_yellow, key_num_blue, key_num_red;
int Exp_Need, Sword, Shield, Books;
int check_map[16][16], now_map[16][16], map[5][16][16];
int HP[100], Attack[100], Defend[100], Money[100], Exp[100];

int main(void)
{
	init();
	prep();
	work();
	return 0;
}

void init(void)
{
	int i, j, t;	
	FILE *fp;
	fp = fopen("map.txt","r");
	for (t=1; t<=4; t++)
		for (i=1; i<=14; i++)
			for (j=1; j<=14; j++)
				fscanf(fp,"%d",&map[t][i][j]);
	fclose(fp);
}

void prep(void)
{
	int i,j;
	int driver=0, mode=VESA_1024x768x8bit;
   	initgraph(&driver, &mode, "");
	
	Player_hp     = 150;
	Player_attack = 13;
	Player_defend = 10;
	Player_money   = 0;
	Player_exp     = 0;
	Player_level   = 0;

	now_I   = 13;
	now_J   = 7;
	now_floor = 1;
	
	key_num_yellow = 0;
	key_num_blue   = 0;
	key_num_red    = 0;
	
	Exp_Need = 5;
	Sword    = 0;
	Shield   = 0;
	Books    = 0;
	
	//textbackground(black);
	clrscr();
	//cursoroff;
	memset(now_map,0,sizeof(now_map));
	memset(check_map,0,sizeof(check_map));
	for (i=1; i<=14; i++)
		for (j=1; j<=14; j++)
			now_map[i][j] = map[1][i][j];
}

void work(void)
{
	char ch;
	while (1) {
		print();
		ch = bioskey(0);
		if (ch == 'b') book();
			else if (ch == 'i') look(); 
				else if (ch == 'q') quit();
					else run(ch);
	}
}

void look(void)
{
	char ch;
	
	clrscr();
	
	gotoxy(1,10);
	printf("                ");
	textcolor(yellow);
	printf("Yellow Key:    %d\n",key_num_yellow);
	
	gotoxy(1,12);
	printf("                ");
	textcolor(123);
	printf("Blue Key:      %d\n",key_num_blue);
	
	gotoxy(1,14);
	printf("                ");
	textcolor(red);
	printf("Red Key:       %d\n",key_num_red);
	
	gotoxy(1,17);
	textcolor(green);
	printf("                ");
	printf("HP:  %d         ",Player_hp);
	printf("Attack:  %d         ",Player_attack);
	printf("Defend:  %d         ",Player_defend);
	
	gotoxy(1,19);
	textcolor(white);
	printf("                ");
	printf("Lv:  %d         ",Player_level);
	printf("Money:  %d         ",Player_money);
	printf("Exp:  %d         ",Player_exp);
	
	gotoxy(1,21);
	printf("                ");
	printf("Next Level:  %d         ",Exp_Need-Player_exp);

	gotoxy(20,25);
	printf("     Please enter \'e\' to exit.     ");
	
	while (1) {
		ch = bioskey(0);
		if (ch == 'e'){
			quit();
			exit(0);
		}
	}
	
}

void shop(void)
{
	char ch;
	while (1){
		clrscr();
		gotoxy(3,8);
		textcolor(yellow);
		printf("   Shop:\'\'Player_money! Money! Give me your money!!!\'\'\n\n");
		printf("       1.Hp + 30     Cost 50\n\n");
		printf("       2.Attack + 2     Cost 50\n\n");
		printf("       3.Defend + 1     Cost 50\n\n");
		printf("       4.Yellow Key + 1     Cost 40\n\n");
		printf("       5.Blue Key + 1     Cost 120\n\n");
		printf("       6.Red Key + 1      Cost 300\n\n");
		gotoxy(10,23);
		printf("Your Money: %d",Player_money);
		gotoxy(20,28);
		printf("     Please enter \'e\' to exit.    ");
		
		ch = bioskey(0);
		if (ch == '1' && Player_money >= 50){
			Player_money-=50;
			Player_hp+=30;
			printf("    HP + 30 ~   OK!\n");
		}	else 
		if (ch == '2' && Player_money >= 50){
			Player_money-=50;
			Player_attack+=2;
			printf("    Attack + 2 ~   OK!\n");
		}	else
		if (ch == '3' && Player_money >= 50){
			Player_money-=50;
			Player_defend+=1;
			printf("    Defend + 1 ~   OK!\n");
		}	else
		if (ch == '4' && Player_money >= 40){
			Player_money-=40;
			key_num_yellow+=1;
			printf("    Yellow Key + 1 ~   OK!\n");
		}	else
		if (ch == '5' && Player_money >= 120){
			Player_money-=120;
			key_num_blue+=1;
			printf("    Blue Key + 1 ~   OK!\n");
		}	else
		if (ch == '6' && Player_money >= 300){
			Player_money-=300;
			key_num_red+=1;
			printf("    Red Key + 1 ~   OK!\n");
		}
		gotoxy(10,23);
		printf("Your Money:  %d",Player_money);
		if (ch == 'e')	break;	
	}	
	quit();
}

void book(void)
{
	char ch;
	if (Books) {
		clrscr();
		textcolor(yellow);
		gotoxy(2,2);	printf(" --- ");
		gotoxy(2,3);	printf("|o o|");
		gotoxy(2,4);	printf("|___|");
    	gotoxy(10,3);	printf(" HP: %d     Attack: %d     Defend: %d",HP[11],Attack[11],Defend[11]);
		gotoxy(2,6);	printf(" --- ");
		gotoxy(2,7);	printf("|o o|");
		gotoxy(2,8);	printf("\\_o_/");
    	gotoxy(10,7);	printf(" HP: %d     Attack: %d     Defend: %d",HP[12],Attack[12],Defend[12]);
		gotoxy(2,10);	printf(" === ");
		gotoxy(2,11);	printf("(o o)");
		gotoxy(2,12);	printf("\\_^_/");
    	gotoxy(10,11);	printf(" HP: %d     Attack: %d     Defend: %d",HP[13],Attack[13],Defend[13]);
		gotoxy(2,14);	printf("/---\\");
		gotoxy(2,15);	printf("|o o|");
		gotoxy(2,16);	printf("v^^^v");
    	gotoxy(10,15);	printf(" HP: %d     Attack: %d     Defend: %d",HP[14],Attack[14],Defend[14]);
		gotoxy(2,18);	printf(" \\^/ ");
		gotoxy(2,19);	printf("<o o>");
		gotoxy(2,20);	printf("V\\x/V");
    	gotoxy(10,19);	printf(" HP: %d     Attack: %d     Defend: %d",HP[15],Attack[15],Defend[15]);
		gotoxy(2,22);	printf("UUUUU");
		gotoxy(2,23);	printf("|o o|");
		gotoxy(2,24);	printf("-----");
    	gotoxy(10,23);	printf(" HP: %d     Attack: %d     Defend: %d",HP[16],Attack[16],Defend[16]);
		gotoxy(2,26);	printf("Y M Y");
		gotoxy(2,27);	printf("[o o]");
		gotoxy(2,28);	printf("XXXXX");
    	gotoxy(10,27);	printf(" HP: %d     Attack: %d     Defend: %d",HP[17],Attack[17],Defend[17]);
		gotoxy(20,40);
		printf("     Please enter \'e\' to exit.   \n");
	}
}

void fighting(int m)
{
	int i, r, damage, random;
	int Miss, Bow;
	int Monster_HP, Monster_Attack, Monster_Defend;
	clrscr();
	srand((unsigned)time(NULL));
	Monster_HP = HP[m];
	Monster_Attack = Attack[m];
	Monster_Defend = Defend[m];
	textcolor(yellow);
	for (i=1; i<=30; i++) printf("-");
	for (i=1; i<=15; i++) printf(" ");
	for (i=1; i<=30; i++) printf("-");
	gotoxy(1,2);	printf("|                            | ppp   k  k   |                             |");
	gotoxy(1,3);	printf("|                            | p  p  k k    |                             |");
	gotoxy(1,4);	printf("|                            | ppp   kk     |                             |");
	gotoxy(1,5);	printf("|                            | p     k k    |                             |");
	gotoxy(1,6);	printf("|                            | p     k  k   |                             |");
	printf("\n");
	for (i=1; i<=30; i++) printf("-");
	for (i=1; i<=15; i++) printf(" ");
	for (i=1; i<=30; i++) printf("-");
	printf("\n");
	
	gotoxy(1,9);
	textcolor(white);
	printf("       %d                          %d",Monster_HP,Player_hp);
	while (1) {
		random = 1+ rand() % 100;
		if (random < Miss && random > Bow){
			damage = Player_attack - Monster_Defend;
			if (damage < 0) damage = 0;
			Monster_HP-=damage;
			if (Monster_HP < 0) Monster_HP = 0;
			printf("       %d                    ",Monster_HP);
		}
		if (random >= Miss){
			printf("       %d        Miss...     ",Monster_HP);
		}
		if (random <= Bow){
			damage = floor((Player_attack - Monster_Defend)*1.5);
			if (damage < 0) damage = 0;
			Monster_HP -= damage;
			if (Monster_HP < 0) Monster_HP = 0;
			printf("       %d        Bow...      ",Monster_HP);
		}
		if (Monster_HP <= 0) break;
		//delay(200);
		random = 1+ rand() % 100;
		
		
		
	}
		
	Player_money += Money[m];
	Player_exp += Exp[m];
	
}

void defeated(void)
{
	clrscr();
	gotoxy(32,20);
	printf("You Lost .... TAT\n");
	getchar();
	exit(0);
}

void Upstairs(void)
{
	int i, j;
	clrscr();
	for (i=1; i<=14; i++)
		for (j=1; j<=14; j++){
			map[now_floor][i][j] = now_map[i][j];
			now_map[i][j] = map [now_floor+1][i][j] ;
			check_map[i][j] = 0;
		}
	now_floor++; 
	print();
}

void Downstairs(void)
{
	int i, j;
	clrscr();
	for (i=1; i<=14; i++)
		for (j=1; j<=14; j++){
			map[now_floor][i][j] = now_map[i][j];
			now_map[i][j] = map [now_floor-1][i][j] ;
			check_map[i][j] = 0;
		}
	now_floor--; 
	print();
}

void run(char ch)
{
	if (ch == 'w'){
		switch (now_map[now_I-1][now_J]){
			case 1:
			case 2:
				check_map[now_I-1][now_J] = 0;
				check_map[now_I  ][now_J] = 0;
				now_map[now_I-1][now_J] = 1;
				now_map[now_I  ][now_J] = 0;
				now_I--;
				break;
			case 3:
				if (key_num_yellow > 0)
				{
					key_num_yellow--;
					check_map[now_I-1][now_J] = 0;
					check_map[now_I  ][now_J] = 0;
					now_map[now_I-1][now_J] = 1;
					now_map[now_I  ][now_J] = 0;
					now_I--; 
				}
				break;
			case 4:
				if (key_num_blue > 0)
				{
					key_num_blue--;
					check_map[now_I-1][now_J] = 0;
					check_map[now_I  ][now_J] = 0;
					now_map[now_I-1][now_J] = 1;
					now_map[now_I  ][now_J] = 0;
					now_I--; 
				}
				break;
			case 5:
				if (key_num_red > 0)
				{
					key_num_red--;
					check_map[now_I-1][now_J] = 0;
					check_map[now_I  ][now_J] = 0;
					now_map[now_I-1][now_J] = 1;
					now_map[now_I  ][now_J] = 0;
					now_I--; 
				}
				break;
			case 6:
				key_num_yellow++;
				check_map[now_I-1][now_J] = 0;
				check_map[now_I  ][now_J] = 0;
				now_map[now_I-1][now_J] = 1;
				now_map[now_I  ][now_J] = 0;
				now_I--; 
				break;
			case 7:
				key_num_blue++;
				check_map[now_I-1][now_J] = 0;
				check_map[now_I  ][now_J] = 0;
				now_map[now_I-1][now_J] = 1;
				now_map[now_I  ][now_J] = 0;
				now_I--; 
				break;
			case 8:
				key_num_red++;
				check_map[now_I-1][now_J] = 0;
				check_map[now_I  ][now_J] = 0;
				now_map[now_I-1][now_J] = 1;
				now_map[now_I  ][now_J] = 0;
				now_I--; 
				break;
			case 11:
			case 12:
			case 13:
			case 14:
			case 15:
			case 16:
			case 17:
				check_map[now_I-1][now_J] = 0;
				check_map[now_I  ][now_J] = 0;
                fighting(now_map[now_I-1][now_J]);
				now_map[now_I-1][now_J] = 1;
				now_map[now_I  ][now_J] = 0;
				now_I--; 
				break;
			case 30:
				check_map[now_I-1][now_J] = 0;
				check_map[now_I  ][now_J] = 0;
				now_map[now_I-1][now_J] = 1;
				now_map[now_I  ][now_J] = 0;
				now_I--;
				Player_hp+=30;
				break;	
			case 31:
				check_map[now_I-1][now_J] = 0;
				check_map[now_I  ][now_J] = 0;
				now_map[now_I-1][now_J] = 1;
				now_map[now_I  ][now_J] = 0;
				now_I--;
				Sword = 1;
                Player_attack+=10;
				break;
			case 32:
				check_map[now_I-1][now_J] = 0;
				check_map[now_I  ][now_J] = 0;
				now_map[now_I-1][now_J] = 1;
				now_map[now_I  ][now_J] = 0;
				now_I--;
                Player_attack+=3;
				break;
			case 33:
				check_map[now_I-1][now_J] = 0;
				check_map[now_I  ][now_J] = 0;
				now_map[now_I-1][now_J] = 1;
				now_map[now_I  ][now_J] = 0;
				now_I--;
                Player_defend+=8;
				break;
			case 35:
				check_map[now_I-1][now_J] = 0;
				check_map[now_I  ][now_J] = 0;
				now_map[now_I-1][now_J] = 1;
				now_map[now_I  ][now_J] = 0;
				now_I--;
                Books = 1;
				break;
			case 51:
				shop();
				break;
			case 80:
				Upstairs();
				break;
			case 90:
				Downstairs();	
				break;
		}
	};
	if (ch == 's'){
		switch (now_map[now_I+1][now_J]){
			case 1:
			case 2:
				check_map[now_I+1][now_J] = 0;
				check_map[now_I  ][now_J] = 0;
				now_map[now_I+1][now_J] = 1;
				now_map[now_I  ][now_J] = 0;
				now_I++;
				break;
			case 3:
				if (key_num_yellow > 0)
				{
					key_num_yellow--;
					check_map[now_I+1][now_J] = 0;
					check_map[now_I  ][now_J] = 0;
					now_map[now_I+1][now_J] = 1;
					now_map[now_I  ][now_J] = 0;
					now_I++; 
				}
				break;
			case 4:
				if (key_num_blue > 0)
				{
					key_num_blue--;
					check_map[now_I+1][now_J] = 0;
					check_map[now_I  ][now_J] = 0;
					now_map[now_I+1][now_J] = 1;
					now_map[now_I  ][now_J] = 0;
					now_I++; 
				}
				break;
			case 5:
				if (key_num_red > 0)
				{
					key_num_red--;
					check_map[now_I+1][now_J] = 0;
					check_map[now_I  ][now_J] = 0;
					now_map[now_I+1][now_J] = 1;
					now_map[now_I  ][now_J] = 0;
					now_I++; 
				}
				break;
			case 6:
				key_num_yellow++;
				check_map[now_I+1][now_J] = 0;
				check_map[now_I  ][now_J] = 0;
				now_map[now_I+1][now_J] = 1;
				now_map[now_I  ][now_J] = 0;
				now_I++; 
				break;
			case 7:
				key_num_blue++;
				check_map[now_I+1][now_J] = 0;
				check_map[now_I  ][now_J] = 0;
				now_map[now_I+1][now_J] = 1;
				now_map[now_I  ][now_J] = 0;
				now_I++; 
				break;
			case 8:
				key_num_red++;
				check_map[now_I+1][now_J] = 0;
				check_map[now_I  ][now_J] = 0;
				now_map[now_I+1][now_J] = 1;
				now_map[now_I  ][now_J] = 0;
				now_I++; 
				break;
			case 11:
			case 12:
			case 13:
			case 14:
			case 15:
			case 16:
			case 17:
				check_map[now_I+1][now_J] = 0;
				check_map[now_I  ][now_J] = 0;
                fighting(now_map[now_I+1][now_J]);
				now_map[now_I+1][now_J] = 1;
				now_map[now_I  ][now_J] = 0;
				now_I++; 
				break;
			case 30:
				check_map[now_I+1][now_J] = 0;
				check_map[now_I  ][now_J] = 0;
				now_map[now_I+1][now_J] = 1;
				now_map[now_I  ][now_J] = 0;
				now_I++;
				Player_hp+=30;
				break;
			case 31:
				check_map[now_I+1][now_J] = 0;
				check_map[now_I  ][now_J] = 0;
				now_map[now_I+1][now_J] = 1;
				now_map[now_I  ][now_J] = 0;
				now_I++;
				Sword = 1;
                Player_attack+=10;
				break;
			case 32:
				check_map[now_I+1][now_J] = 0;
				check_map[now_I  ][now_J] = 0;
				now_map[now_I+1][now_J] = 1;
				now_map[now_I  ][now_J] = 0;
				now_I++;
                Player_attack+=3;
				break;
			case 33:
				check_map[now_I+1][now_J] = 0;
				check_map[now_I  ][now_J] = 0;
				now_map[now_I+1][now_J] = 1;
				now_map[now_I  ][now_J] = 0;
				now_I++;
                Player_defend+=8;
				break;
			case 35:
				check_map[now_I+1][now_J] = 0;
				check_map[now_I  ][now_J] = 0;
				now_map[now_I+1][now_J] = 1;
				now_map[now_I  ][now_J] = 0;
				now_I++;
                Books = 1;
				break;
			case 51:
				shop();
				break;
			case 80:
				Upstairs();
				break;
			case 90:
				Downstairs();	
				break;
		}
	};
	if (ch == 'a'){
		switch (now_map[now_I][now_J-1]){
			case 1:
			case 2:
				check_map[now_I][now_J-1] = 0;
				check_map[now_I][now_J  ] = 0;
				now_map[now_I][now_J-1] = 1;
				now_map[now_I][now_J  ] = 0;
				now_J--;
				break;
			case 3:
				if (key_num_yellow > 0)
				{
					key_num_yellow--;
					check_map[now_I][now_J-1] = 0;
					check_map[now_I][now_J  ] = 0;
					now_map[now_I][now_J-1] = 1;
					now_map[now_I][now_J  ] = 0;
					now_J--;
				}
				break;
			case 4:
				if (key_num_blue > 0)
				{
					key_num_blue--;
					check_map[now_I][now_J-1] = 0;
					check_map[now_I][now_J  ] = 0;
					now_map[now_I][now_J-1] = 1;
					now_map[now_I][now_J  ] = 0;
					now_J--;
				}
				break;
			case 5:
				if (key_num_red > 0)
				{
					key_num_red--;
					check_map[now_I][now_J-1] = 0;
					check_map[now_I][now_J  ] = 0;
					now_map[now_I][now_J-1] = 1;
					now_map[now_I][now_J  ] = 0;
					now_J--;
				}
				break;
			case 6:
				key_num_yellow++;
				check_map[now_I][now_J-1] = 0;
				check_map[now_I][now_J  ] = 0;
				now_map[now_I][now_J-1] = 1;
				now_map[now_I][now_J  ] = 0;
				now_J--;
				break;
			case 7:
				key_num_blue++;
				check_map[now_I][now_J-1] = 0;
				check_map[now_I][now_J  ] = 0;
				now_map[now_I][now_J-1] = 1;
				now_map[now_I][now_J  ] = 0;
				now_J--;
				break;
			case 8:
				key_num_red++;
				check_map[now_I][now_J-1] = 0;
				check_map[now_I][now_J  ] = 0;
				now_map[now_I][now_J-1] = 1;
				now_map[now_I][now_J  ] = 0;
				now_J--;
				break;
			case 11:
			case 12:
			case 13:
			case 14:
			case 15:
			case 16:
			case 17:
				check_map[now_I][now_J-1] = 0;
				check_map[now_I][now_J  ] = 0;
                fighting(now_map[now_I][now_J-1]);
				now_map[now_I][now_J-1] = 1;
				now_map[now_I][now_J  ] = 0;
				now_J--;
				break;
			case 30:
				check_map[now_I][now_J-1] = 0;
				check_map[now_I][now_J  ] = 0;
				now_map[now_I][now_J-1] = 1;
				now_map[now_I][now_J  ] = 0;
				now_J--;
				Player_hp+=30;
				break;
			case 31:
				check_map[now_I][now_J-1] = 0;
				check_map[now_I][now_J  ] = 0;
				now_map[now_I][now_J-1] = 1;
				now_map[now_I][now_J  ] = 0;
				now_J--;
				Sword = 1;
                Player_attack+=10;
				break;
			case 32:
				check_map[now_I][now_J-1] = 0;
				check_map[now_I][now_J  ] = 0;
				now_map[now_I][now_J-1] = 1;
				now_map[now_I][now_J  ] = 0;
				now_J--;
                Player_attack+=3;
				break;
			case 33:
				check_map[now_I][now_J-1] = 0;
				check_map[now_I][now_J  ] = 0;
				now_map[now_I][now_J-1] = 1;
				now_map[now_I][now_J  ] = 0;
				now_J--;
                Player_defend+=8;
				break;
			case 35:
				check_map[now_I][now_J-1] = 0;
				check_map[now_I][now_J  ] = 0;
				now_map[now_I][now_J-1] = 1;
				now_map[now_I][now_J  ] = 0;
				now_J--;
                Books = 1;
				break;
			case 51:
				shop();
				break;
			case 80:
				Upstairs();
				break;
			case 90:
				Downstairs();	
				break;
		}
	}
	if (ch == 'd'){
		switch (now_map[now_I][now_J+1]){
			case 1:
			case 2:
				check_map[now_I][now_J+1] = 0;
				check_map[now_I][now_J  ] = 0;
				now_map[now_I][now_J+1] = 1;
				now_map[now_I][now_J  ] = 0;
				now_J++;
				break;
			case 3:
				if (key_num_yellow > 0)
				{
					key_num_yellow--;
					check_map[now_I][now_J+1] = 0;
					check_map[now_I][now_J  ] = 0;
					now_map[now_I][now_J+1] = 1;
					now_map[now_I][now_J  ] = 0;
					now_J++;
				}
				break;
			case 4:
				if (key_num_blue > 0)
				{
					key_num_blue--;
					check_map[now_I][now_J+1] = 0;
					check_map[now_I][now_J  ] = 0;
					now_map[now_I][now_J+1] = 1;
					now_map[now_I][now_J  ] = 0;
					now_J++;
				}
				break;
			case 5:
				if (key_num_red > 0)
				{
					key_num_red--;
					check_map[now_I][now_J+1] = 0;
					check_map[now_I][now_J  ] = 0;
					now_map[now_I][now_J+1] = 1;
					now_map[now_I][now_J  ] = 0;
					now_J++;
				}
				break;
			case 6:
				key_num_yellow++;
				check_map[now_I][now_J+1] = 0;
				check_map[now_I][now_J  ] = 0;
				now_map[now_I][now_J+1] = 1;
				now_map[now_I][now_J  ] = 0;
				now_J++;
				break;
			case 7:
				key_num_blue++;
				check_map[now_I][now_J+1] = 0;
				check_map[now_I][now_J  ] = 0;
				now_map[now_I][now_J+1] = 1;
				now_map[now_I][now_J  ] = 0;
				now_J++;
				break;
			case 8:
				key_num_red++;
				check_map[now_I][now_J+1] = 0;
				check_map[now_I][now_J  ] = 0;
				now_map[now_I][now_J+1] = 1;
				now_map[now_I][now_J  ] = 0;
				now_J++;
				break;
			case 11:
			case 12:
			case 13:
			case 14:
			case 15:
			case 16:
			case 17:
				check_map[now_I][now_J+1] = 0;
				check_map[now_I][now_J  ] = 0;
                fighting(now_map[now_I][now_J+1]);
				now_map[now_I][now_J+1] = 1;
				now_map[now_I][now_J  ] = 0;
				now_J++;
				break;
			case 30:
				check_map[now_I][now_J+1] = 0;
				check_map[now_I][now_J  ] = 0;
				now_map[now_I][now_J+1] = 1;
				now_map[now_I][now_J  ] = 0;
				now_J++;
				Player_hp+=30;
				break;
			case 31:
				check_map[now_I][now_J+1] = 0;
				check_map[now_I][now_J  ] = 0;
				now_map[now_I][now_J+1] = 1;
				now_map[now_I][now_J  ] = 0;
				now_J++;
				Sword = 1;
                Player_attack+=10;
				break;
			case 32:
				check_map[now_I][now_J+1] = 0;
				check_map[now_I][now_J  ] = 0;
				now_map[now_I][now_J+1] = 1;
				now_map[now_I][now_J  ] = 0;
				now_J++;
                Player_attack+=3;
				break;
			case 33:
				check_map[now_I][now_J+1] = 0;
				check_map[now_I][now_J  ] = 0;
				now_map[now_I][now_J+1] = 1;
				now_map[now_I][now_J  ] = 0;
				now_J++;
                Player_defend+=8;
				break;
			case 35:
				check_map[now_I][now_J+1] = 0;
				check_map[now_I][now_J  ] = 0;
				now_map[now_I][now_J+1] = 1;
				now_map[now_I][now_J  ] = 0;
				now_J++;
                Books = 1;
				break;
			case 51:
				shop();
				break;
			case 80:
				Upstairs();
				break;
			case 90:
				Downstairs();	
				break;
		}
	}
}

void print(void)
{
	int i, j;
	for (i=1; i<=14; i++)
		for (j=1; j<=14; j++)
			if (!check_map[i][j]){
				switch (now_map[i][j]){
					case 0:
						gotoxy(j*5,i*3  );	printf("     ");
						gotoxy(j*5,i*3+1);	printf("     ");
						gotoxy(j*5,i*3+2);	printf("     ");
						break;
					case 1:
						textcolor(yellow);
						gotoxy(j*5,i*3  );	printf(" ^^^ ");
						gotoxy(j*5,i*3+1);	printf("|o o|");
						gotoxy(j*5,i*3+2);	printf("\\_v_/");
						break;
					case 2:
						textcolor(white);
						gotoxy(j*5,i*3  );	printf("#####");
						gotoxy(j*5,i*3+1);	printf("#####");
						gotoxy(j*5,i*3+2);	printf("#####");
						break;
					case 3:
					case 4:
					case 5:
						if (now_map[i][j] == 3) textcolor(yellow);
							else if (now_map[i][j] == 4) textcolor(123);
								else if (now_map[i][j] == 5) textcolor(red); 
						gotoxy(j*5,i*3  );	printf(" --- ");
						gotoxy(j*5,i*3+1);	printf("/***\\");
						gotoxy(j*5,i*3+2);	printf("|***|");
						break;
					case 6:
					case 7:
					case 8:
						if (now_map[i][j] == 6) textcolor(yellow);
							else if (now_map[i][j] == 7) textcolor(123);
								else if (now_map[i][j] == 8) textcolor(red); 
						gotoxy(j*5,i*3  );	printf(" {O} ");
						gotoxy(j*5,i*3+1);	printf("  H  ");
						gotoxy(j*5,i*3+2);	printf("  F  ");
						break;
					case 11:
						textcolor(5);
						gotoxy(j*5,i*3  );	printf(" --- ");
						gotoxy(j*5,i*3+1);	printf("|o o|");
						gotoxy(j*5,i*3+2);	printf("|___|");
						break;
					case 12:
						textcolor(5);
						gotoxy(j*5,i*3  );	printf(" --- ");
						gotoxy(j*5,i*3+1);	printf("|o o|");
						gotoxy(j*5,i*3+2);	printf("\\_o_/");
						break;
					case 13:
						textcolor(5);
						gotoxy(j*5,i*3  );	printf(" === ");
						gotoxy(j*5,i*3+1);	printf("(o o)");
						gotoxy(j*5,i*3+2);	printf("\\_^_/");
						break;
					case 14:
						textcolor(5);
						gotoxy(j*5,i*3  );	printf("/---\\");
						gotoxy(j*5,i*3+1);	printf("|o o|");
						gotoxy(j*5,i*3+2);	printf("v^^^v");
						break;
					case 15:
						textcolor(5);
						gotoxy(j*5,i*3  );	printf(" \\^/ ");
						gotoxy(j*5,i*3+1);	printf("<o o>");
						gotoxy(j*5,i*3+2);	printf("V\\x/V");
						break;
					case 16:
						textcolor(5);
						gotoxy(j*5,i*3  );	printf("UUUUU");
						gotoxy(j*5,i*3+1);	printf("|o o|");
						gotoxy(j*5,i*3+2);	printf("-----");
						break;
					case 17:
						textcolor(5);
						gotoxy(j*5,i*3  );	printf("Y M Y");
						gotoxy(j*5,i*3+1);	printf("[o o]");
						gotoxy(j*5,i*3+2);	printf("XXXXX");
						break;
					case 30:
						textcolor(green);
						gotoxy(j*5,i*3  );	printf(" || H");
						gotoxy(j*5,i*3+1);	printf("/==\\ ");
						gotoxy(j*5,i*3+2);	printf("\\==/ ");
						break;
					case 31:
						textcolor(green);
						gotoxy(j*5,i*3  );	printf(" A  G");
						gotoxy(j*5,i*3+1);	printf(" H  +");
						gotoxy(j*5,i*3+2);	printf("<H> +");
						break;
					case 32:
						textcolor(green);
						gotoxy(j*5,i*3  );	printf("     ");
						gotoxy(j*5,i*3+1);	printf("     ");
						gotoxy(j*5,i*3+2);	printf(" +3  ");
						break;
					case 33:
						textcolor(green);
						gotoxy(j*5,i*3  );	printf("___ F");
						gotoxy(j*5,i*3+1);	printf("|x| +");
						gotoxy(j*5,i*3+2);	printf("\\_/ +");
						break;
					case 35:
						textcolor(green);
						gotoxy(j*5,i*3  );	printf("c===c");
						gotoxy(j*5,i*3+1);	printf("c ~ |");
						gotoxy(j*5,i*3+2);	printf("c___|");
						break;
					case 50:
						textcolor(green);
						gotoxy(j*5,i*3  );	printf("/====");
						gotoxy(j*5,i*3+1);	printf("|shop");
						gotoxy(j*5,i*3+2);	printf("|____");
						break;
					case 51:
						textcolor(green);
						gotoxy(j*5,i*3  );	printf("=====");
						gotoxy(j*5,i*3+1);	printf(" ___ ");
						gotoxy(j*5,i*3+2);	printf("|___|");
						break;
					case 52:
						textcolor(green);
						gotoxy(j*5,i*3  );	printf("====\\");
						gotoxy(j*5,i*3+1);	printf("shop|");
						gotoxy(j*5,i*3+2);	printf("____|");
						break;
					case 80:
						textcolor(red);
						gotoxy(j*5,i*3  );	printf("^ ^ ^");
						gotoxy(j*5,i*3+1);	printf("| | |");
						gotoxy(j*5,i*3+2);	printf("| | |");
						break; 
					case 90:
						textcolor(red);
						gotoxy(j*5,i*3  );	printf("| | |");
						gotoxy(j*5,i*3+1);	printf("| | |");
						gotoxy(j*5,i*3+2);	printf("v v v");
				}
			}
	memset(check_map,1,sizeof(check_map));
} 

void quit(void)
{
	int i, j;
	for (i=1; i<=14; i++)
		for (j=1; j<=14; j++)
			check_map[i][j] = 0;
	clrscr();
	print();
}

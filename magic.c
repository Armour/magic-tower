#include "magic.h"

int Player_hp, Player_attack, Player_defend, Player_money, Player_exp, Player_level, Player_miss, Player_bow;
int Now_i, Now_j, Now_floor;
int Key_num_yellow, Key_num_blue, Key_num_red;
int Exp_need, Sword, Shield, Books;
int x[5], y[5];
int map_color[103];
int map[10][20][20], now_map[20][20], check_map[20][20];
int Monster_hp[100], Monster_attack[100], Monster_defend[100], Monster_money[100], Monster_exp[100], Monster_miss[100], Monster_bow[100];
char map_str[305][7];
	
int main(void) {
	Info_Prep();
	Map_Prep();
	Magic();
	return 0;
}

void Info_Prep(void) {
	int graphdriver, graphmode;
	graphdriver = DETECT;
	graphmode = VESA_1024x768x8bit;
   	initgraph(&graphdriver, &graphmode, "");
	cleardevice();
	
	Player_hp     = 150;
	Player_attack = 13;
	Player_defend = 10;
	Player_miss    = 8;
	Player_bow	   = 95;
	Player_money   = 10000000;
	Player_exp     = 0;
	Player_level   = 0;

	Now_i   = 13;
	Now_j   = 7;
	Now_floor = 1;
	
	Key_num_yellow = 0;
	Key_num_blue   = 0;
	Key_num_red    = 0;
	
	Exp_need = 5;
	Sword    = 0;
	Shield   = 0;
	Books    = 0;

	x[1] = -1;
	x[2] = 0;
	x[3] = 1;
	x[4] = 0;

	y[1] = 0;
	y[2] = -1;
	y[3] = 0;
	y[4] = 1;
}

void Map_Prep(void) {
	int i, j, floors, ascii = 219;
	char ch = (char)ascii;
	FILE *fp1, *fp2, *fp3, *fp4;

	fp1 = fopen("floors.txt","r");
	for (floors=1; floors<=4; floors++)
		for (i=1; i<=14; i++)
			for (j=1; j<=14; j++) 
				fscanf(fp1,"%d",&map[floors][i][j]);
	fclose(fp1);

	fp2 = fopen("map.txt","r");
	for (i=1; i<=303; i++) 
		fscanf(fp2, "%s", map_str[i]);
	fclose(fp2);

	for (i=0; i<=303; i++)
		for (j=0; j<=4; j++)
			if (map_str[i][j] == '&')
				map_str[i][j] = ' ';
			else if (map_str[i][j] == '2')
				map_str[i][j] = ch;
	
	fp3 = fopen("color.txt","r");
	for (i=0; i<=100; i++)
		fscanf(fp3, "%d", &map_color[i]);
	fclose(fp3);

	fp4 = fopen("monster.txt","r");
	for (i=11; i<=17; i++) {
		fscanf(fp4, "%d", &Monster_hp[i]);
		fscanf(fp4, "%d", &Monster_attack[i]);
		fscanf(fp4, "%d", &Monster_defend[i]);
		fscanf(fp4, "%d", &Monster_money[i]);
		fscanf(fp4, "%d", &Monster_exp[i]);
		fscanf(fp4, "%d", &Monster_miss[i]);
		fscanf(fp4, "%d", &Monster_bow[i]);
	}
	fclose(fp4); 

	memset(now_map,0,sizeof(now_map));
	memset(check_map,0,sizeof(check_map));
	for (i=1; i<=14; i++)
		for (j=1; j<=14; j++)
			now_map[i][j] = map[1][i][j];
}

void Magic(void) {
	char ch;
	Map_Print();
	while (1) {
		ch = bioskey(0);
		if (ch == '`') Esc();			
		if (ch == 'i') Soldier_Info();
		if (ch == 'b') if (Books) Monster_Book();
		if (ch == 'o') Shop();
		if (ch == 'w') Run('w');	
		if (ch == 's') Run('s');	
		if (ch == 'a') Run('a');	
		if (ch == 'd') Run('d');	
	}
}

void Soldier_Info(void) {
	char ch;
	char * str = "temp";
	cleardevice();
	
	setcolor(YELLOW);
	sprintf(str,"                         Yellow Key :%8d", Key_num_yellow);
	outtextxy(1,10+3*11,str);

	setcolor(BLUE);
	sprintf(str,"                         Blue Key   :%8d", Key_num_blue);
	outtextxy(1,10+6*11,str);

	setcolor(RED);
	sprintf(str,"                         Red Key    :%8d", Key_num_red);
	outtextxy(1,10+9*11,str);	
	
	setcolor(GREEN);
	sprintf(str,"          HP:  %8d      Attack:  %8d      Defend:  %8d ", Player_hp, Player_attack, Player_defend);
	outtextxy(1,10+15*11,str);	

	setcolor(CYAN);
	sprintf(str,"          Lv:  %8d      Money :  %8d      Exp   :  %8d ", Player_level, Player_money, Player_exp);
	outtextxy(1,10+21*11,str);	

	setcolor(LIGHTMAGENTA);
	sprintf(str,"                         Next Level:  %8d ", Exp_need-Player_exp);
	outtextxy(1,10+30*11,str);

	setcolor(DARKGRAY);
	outtextxy(1,10+40*11,"                      ( Please enter \'q\' to quit. )     ");
	
	while (1) {
		ch = bioskey(0);
		if (ch == 'q'){
			Quit();
			break;
		}
	}
}

void Shop() {
	char ch;
	char * str = "temp";
	int now_line = 22;
	cleardevice();

	setcolor(WHITE);
	sprintf(str,"       Shop: Soldiers! Money! Money! Give me your money!!!");
	outtextxy(3,10+0*11,str);

	setcolor(GREEN);
	sprintf(str,"            1.Hp + 30            Cost 50");
	outtextxy(3,10+2*11,str);
	sprintf(str,"            2.Attack + 2         Cost 50");
	outtextxy(3,10+4*11,str);
	sprintf(str,"            3.Defend + 1         Cost 50");
	outtextxy(3,10+6*11,str);

	setcolor(YELLOW);
	sprintf(str,"            4.Yellow Key + 1     Cost 40");
	outtextxy(3,10+8*11,str);

	setcolor(BLUE);
	sprintf(str,"            5.Blue Key + 1       Cost 120");
	outtextxy(3,10+10*11,str);
	
	setcolor(RED);
	sprintf(str,"            6.Red Key + 1        Cost 300");
	outtextxy(3,10+12*11,str);

	setcolor(WHITE);
	sprintf(str,"       Your Money: %d",Player_money);
	outtextxy(3,10+14*11,str);

	setcolor(DARKGRAY);
	sprintf(str,"           ( Please enter \'q\' to quit. )   ");
	outtextxy(3,10+18*11,str);
		
	while (1){
		ch = bioskey(0);
		if (ch == '1' && Player_money >= 50){
			Player_money-=50;
			Player_hp += 30;
			setfillstyle(SOLID_FILL,BLACK);
			bar(1,10+now_line*11,500,10+(now_line+3)*11);
			setcolor(GREEN);
			sprintf(str,"            HP + 30 ~          OK!");
			outtextxy(3,10+now_line*11,str);
			now_line += 2;
			if (now_line > 45) now_line = 24;
		}	else 
		if (ch == '2' && Player_money >= 50){
			Player_money-=50;
			Player_attack += 2;
			setfillstyle(SOLID_FILL,BLACK);
			bar(1,10+now_line*11,500,10+(now_line+3)*11);
			setcolor(GREEN);
			sprintf(str,"            Attack + 2 ~       OK!");
			outtextxy(3,10+now_line*11,str);
			now_line += 2;
			if (now_line > 45) now_line = 24;
		}	else
		if (ch == '3' && Player_money >= 50){
			Player_money-=50;
			Player_defend += 1;
			setfillstyle(SOLID_FILL,BLACK);
			bar(1,10+now_line*11,500,10+(now_line+3)*11);
			setcolor(GREEN);
			sprintf(str,"            Defend + 1 ~       OK!");
			outtextxy(3,10+now_line*11,str);
			now_line += 2;
			if (now_line > 45) now_line = 24;
		}	else
		if (ch == '4' && Player_money >= 40){
			Player_money-=40;
			Key_num_yellow += 1;
			setfillstyle(SOLID_FILL,BLACK);
			bar(1,10+now_line*11,500,10+(now_line+3)*11);
			setcolor(YELLOW);
			sprintf(str,"            Yellow Key + 1 ~   OK!");
			outtextxy(3,10+now_line*11,str);
			now_line += 2;
			if (now_line > 45) now_line = 24;
		}	else
		if (ch == '5' && Player_money >= 120){
			Player_money-=120;
			Key_num_blue += 1;
			setfillstyle(SOLID_FILL,BLACK);
			bar(1,10+now_line*11,500,10+(now_line+3)*11);
			setcolor(BLUE);
			sprintf(str,"            Blue Key + 1 ~     OK!");
			outtextxy(3,10+now_line*11,str);
			now_line += 2;
			if (now_line > 45) now_line = 24;
		}	else
		if (ch == '6' && Player_money >= 300){
			Player_money-=300;
			Key_num_red += 1;
			setfillstyle(SOLID_FILL,BLACK);
			bar(1,10+now_line*11,500,10+(now_line+3)*11);
			setcolor(RED);
			sprintf(str,"            Red Key + 1 ~      OK!");
			outtextxy(3,10+now_line*11,str);
			now_line += 2;
			if (now_line > 45) now_line = 24;
		}
		setfillstyle(SOLID_FILL,BLACK);
		bar(3,10+14*11,500,10+17*11);
		setcolor(WHITE);
		sprintf(str,"       Your Money: %d",Player_money);
		outtextxy(3,10+14*11,str);
		if (ch == 'q')	break;	
	}	
	Quit();
}

void Monster_Book(void) {
	int i;
	char ch;
	char * str = "temp";
	cleardevice();
	for (i=11; i<=17; i++) {
		setcolor(MAGENTA);
		sprintf(str,"%s",map_str[i*3+1]);
		outtextxy(1,(i-11)*52+1*12,str);

		sprintf(str,"%s",map_str[i*3+2]);
		outtextxy(1,(i-11)*52+2*12,str);

		sprintf(str,"%s",map_str[i*3+3]);
		outtextxy(1,(i-11)*52+3*12,str);

		setcolor(YELLOW);
		sprintf(str," HP: %d     Attack: %d     Defend: %d",Monster_hp[i],Monster_attack[i],Monster_defend[i]);
		outtextxy(1,(i-11)*52+4*12,str);
	}
	setcolor(DARKGRAY);
	outtextxy(1,450,"     ( Please enter \'q\' to quit. )     ");
	while (1) {
		ch = bioskey(0);
		if (ch == 'q'){
			Quit();
			break;
		}
	}
}

void Monster_Fight(int m) {
	char ch;
	char * str = "temp";
	int i, r, damage, random, now_line;
	int Monster_HP 	   = Monster_hp[m];
	int Monster_Attack = Monster_attack[m];
	int Monster_Defend = Monster_defend[m];
	srand((unsigned)time(NULL));

	cleardevice();
	setcolor(YELLOW);
	sprintf(str,"------------------------------               ------------------------------");
	outtextxy(1,1+0*11,str);
	sprintf(str,"|                            | ppp   k  k   |                             |");
	outtextxy(1,1+1*11,str);
	sprintf(str,"|                            | p  p  k k    |                             |");
	outtextxy(1,1+2*11,str);
	sprintf(str,"|                            | ppp   kk     |                             |");
	outtextxy(1,1+3*11,str);
	sprintf(str,"|                            | p     k  k   |                             |");
	outtextxy(1,1+4*11,str);
	sprintf(str,"------------------------------               ------------------------------");
	outtextxy(1,1+5*11,str);

	setcolor(map_color[m]);
	sprintf(str,"%s",map_str[m*3+1]);
	outtextxy(100,1+1*11,str);
	sprintf(str,"%s",map_str[m*3+2]);
	outtextxy(100,1+2*11,str);
	sprintf(str,"%s",map_str[m*3+3]);
	outtextxy(100,1+3*11,str);

	setcolor(map_color[1]);
	sprintf(str,"%s",map_str[1*3+1]);
	outtextxy(450,1+1*11,str);
	sprintf(str,"%s",map_str[1*3+2]);
	outtextxy(450,1+2*11,str);
	sprintf(str,"%s",map_str[1*3+3]);
	outtextxy(450,1+3*11,str);

	setcolor(WHITE);
	sprintf(str,"                %5d                          %5d",Monster_HP,Player_hp);
	outtextxy(1,1+7*11,str);

	now_line = 1+7*11;

	while (1) {
		now_line+=13;
		if (now_line >= 1+30*11) now_line = 1+8*11;
		setfillstyle(SOLID_FILL,BLACK);
		bar(1,now_line,500,now_line+11);

		random = 1+ rand() % 100;
		if (random < Player_bow && random > Monster_miss[m]){
			damage = Player_attack - Monster_Defend;
			if (damage < 0) damage = 0;
			Monster_HP-=damage;
			if (Monster_HP < 0) Monster_HP = 0;
			setcolor(WHITE);
			sprintf(str,"                %5d                   ",Monster_HP);
			outtextxy(1,now_line,str);
		}
		if (random <= Monster_miss[m]){
			setcolor(LIGHTGREEN);
			sprintf(str,"  Miss...       %5d                   ",Monster_HP);
			outtextxy(1,now_line,str);
		}
		if (random >= Player_bow){
			damage = floor((Player_attack - Monster_Defend)*1.5);
			if (damage < 0) damage = 0;
			Monster_HP -= damage;
			if (Monster_HP < 0) Monster_HP = 0;
			setcolor(LIGHTRED);
			sprintf(str,"  Bow !!!       %5d                   ",Monster_HP);
			outtextxy(1,now_line,str);
		}
		if (Monster_HP <= 0) break;
		delay(200);

		random = 1+ rand() % 100;		
		if (random < Monster_bow[m] && random > Player_miss) {
			damage = Monster_attack[m] - Player_defend;
			if (damage < 0) damage = 0;
			Player_hp-=damage;
			if (Player_hp < 0) Player_hp=0;
			setcolor(WHITE);
			sprintf(str,"                                               %5d                ",Player_hp);
			outtextxy(1,now_line,str);
		}
		if (random <= Player_miss) {
			setcolor(LIGHTGREEN);
			sprintf(str,"                                               %5d         Miss...",Player_hp);
			outtextxy(1,now_line,str);
		}
		if (random >= Monster_bow[m]) {

			damage = floor((Monster_attack[m] - Player_defend)*1.5);
			if (damage < 0) damage = 0;
			Player_hp-=damage;
			if (Player_hp < 0) Player_hp=0;
			setcolor(LIGHTRED);
			sprintf(str,"                                               %5d         Bow !!!",Player_hp);
			outtextxy(1,now_line,str);
		}
		if (Player_hp <= 0) break;
		delay(200);
	}
		
	Player_money  +=  Monster_money[m];
	Player_exp  +=  Monster_exp[m];	

	cleardevice();
	setcolor(RED);
	if (Player_hp <= 0) Monster_Defeated();
	if (Player_hp > 0) {
		sprintf(str,"                                  You Win!!!");
		outtextxy(1,1+7*11,str);
		sprintf(str,"                        You earn %d Money and %d Exp!!      ", Monster_money[m], Monster_exp[m]);
		outtextxy(1,1+10*11,str);
	}
	if (Player_exp >= Exp_need) {
		Player_exp -= Exp_need;
		Exp_need = floor(Exp_need*1.5)+1;
		Player_hp += 10;
		Player_attack += 1;
		Player_defend += 1;
		Player_level += 1;
		sprintf(str,"                                  Level  Up  !!!!");
		outtextxy(1,1+18*11,str);
		sprintf(str,"                         HP+10!    Attak+1!     Defend+1!");
		outtextxy(1,1+21*11,str);
	}

	while (1) {
		ch = bioskey(0);
		if (ch){
			Quit();
			break;
		}
	}
}

void Monster_Defeated(void) {
	cleardevice();
	load_8bit_bmp(1, 1, "defeated.bmp");
	delay(3000);
	cleardevice();
	exit(0);
}

void Run(char ch) {
	int m, k = 1;
	if (ch == 'w') k=1;
	if (ch == 'a') k=2;
	if (ch == 's') k=3;
	if (ch == 'd') k=4;
	switch (now_map[Now_i+x[k]][Now_j+y[k]]){
		case 0:
		case 9:
			check_map[Now_i+x[k]][Now_j+y[k]] = 0;
			check_map[Now_i  ][Now_j] = 0;
			now_map[Now_i+x[k]][Now_j+y[k]] = 1;
			now_map[Now_i  ][Now_j] = 0;
			Now_i+=x[k];
			Now_j+=y[k];
			break;
		case 3:
			if (Key_num_yellow > 0)
			{
				Key_num_yellow--;
				check_map[Now_i+x[k]][Now_j+y[k]] = 0;
				check_map[Now_i  ][Now_j] = 0;
				now_map[Now_i+x[k]][Now_j+y[k]] = 1;
				now_map[Now_i  ][Now_j] = 0;
				Now_i+=x[k];
				Now_j+=y[k];
			}
			break;
		case 4:
			if (Key_num_blue > 0)
			{
				Key_num_blue--;
				check_map[Now_i+x[k]][Now_j+y[k]] = 0;
				check_map[Now_i  ][Now_j] = 0;
				now_map[Now_i+x[k]][Now_j+y[k]] = 1;
				now_map[Now_i  ][Now_j] = 0;
				Now_i+=x[k];
				Now_j+=y[k];
			}
			break;
		case 5:
			if (Key_num_red > 0)
			{
				Key_num_red--;
				check_map[Now_i+x[k]][Now_j+y[k]] = 0;
				check_map[Now_i  ][Now_j] = 0;
				now_map[Now_i+x[k]][Now_j+y[k]] = 1;
				now_map[Now_i  ][Now_j] = 0;
				Now_i+=x[k];
				Now_j+=y[k];
			}
			break;
		case 6:
			Key_num_yellow++;
			check_map[Now_i+x[k]][Now_j+y[k]] = 0;
			check_map[Now_i  ][Now_j] = 0;
			now_map[Now_i+x[k]][Now_j+y[k]] = 1;
			now_map[Now_i  ][Now_j] = 0;
			Now_i+=x[k];
			Now_j+=y[k];
			break;
		case 7:
			Key_num_blue++;
			check_map[Now_i+x[k]][Now_j+y[k]] = 0;
			check_map[Now_i  ][Now_j] = 0;
			now_map[Now_i+x[k]][Now_j+y[k]] = 1;
			now_map[Now_i  ][Now_j] = 0;
			Now_i+=x[k];
			Now_j+=y[k];
			break;
		case 8:
			Key_num_red++;
			check_map[Now_i+x[k]][Now_j+y[k]] = 0;
			check_map[Now_i  ][Now_j] = 0;
			now_map[Now_i+x[k]][Now_j+y[k]] = 1;
			now_map[Now_i  ][Now_j] = 0;
			Now_i+=x[k];
			Now_j+=y[k];
			break;
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
		case 17:
			m = now_map[Now_i+x[k]][Now_j+y[k]];
			check_map[Now_i+x[k]][Now_j+y[k]] = 0;
			check_map[Now_i  ][Now_j] = 0;
			now_map[Now_i+x[k]][Now_j+y[k]] = 1;
			now_map[Now_i  ][Now_j] = 0;
			Now_i+=x[k];
			Now_j+=y[k];
            Monster_Fight(m);
			break;
		case 30:
			check_map[Now_i+x[k]][Now_j+y[k]] = 0;
			check_map[Now_i  ][Now_j] = 0;
			now_map[Now_i+x[k]][Now_j+y[k]] = 1;
			now_map[Now_i  ][Now_j] = 0;
			Now_i+=x[k];
			Now_j+=y[k];
			Player_hp += 30;
			break;	
		case 31:
			check_map[Now_i+x[k]][Now_j+y[k]] = 0;
			check_map[Now_i  ][Now_j] = 0;
			now_map[Now_i+x[k]][Now_j+y[k]] = 1;
			now_map[Now_i  ][Now_j] = 0;
			Now_i+=x[k];
			Now_j+=y[k];
			Sword = 1;
            Player_attack += 10;
			break;
		case 32:
			check_map[Now_i+x[k]][Now_j+y[k]] = 0;
			check_map[Now_i  ][Now_j] = 0;
			now_map[Now_i+x[k]][Now_j+y[k]] = 1;
			now_map[Now_i  ][Now_j] = 0;
			Now_i+=x[k];
			Now_j+=y[k];
            Player_attack += 3;
			break;
		case 33:
			check_map[Now_i+x[k]][Now_j+y[k]] = 0;
			check_map[Now_i  ][Now_j] = 0;
			now_map[Now_i+x[k]][Now_j+y[k]] = 1;
			now_map[Now_i  ][Now_j] = 0;
			Now_i+=x[k];
			Now_j+=y[k];
            Player_defend += 8;
			break;
		case 35:
			check_map[Now_i+x[k]][Now_j+y[k]] = 0;
			check_map[Now_i  ][Now_j] = 0;
			now_map[Now_i+x[k]][Now_j+y[k]] = 1;
			now_map[Now_i  ][Now_j] = 0;
			Now_i+=x[k];
			Now_j+=y[k];
            Books = 1;
			break;
		case 51:
			Shop();
			break;
		case 80:
			Upstairs();
			break;
		case 90:
			Downstairs();	
			break;
	}
	Map_Print();
}

void Map_Print(void) {
	int i,j;
	char * str = "temp";
	for (i=1; i<=14; i++)
		for (j=1; j<=14; j++)
			if (!check_map[i][j]) {
				setcolor(map_color[now_map[i][j]]);
				sprintf(str,"%s",map_str[now_map[i][j]*3+1]);
				outtextxy(j*40,(i-1)*38+00,str);
				sprintf(str,"%s",map_str[now_map[i][j]*3+2]);
				outtextxy(j*40,(i-1)*38+12,str);
				sprintf(str,"%s",map_str[now_map[i][j]*3+3]);
				outtextxy(j*40,(i-1)*38+24,str);
			}
	for (i=1; i<=14; i++)
		for (j=1; j<=14; j++)
			check_map[i][j] = 1;
}

void Upstairs(void) {
	int i, j;
	cleardevice();
	for (i=1; i<=14; i++)
		for (j=1; j<=14; j++){
			map[Now_floor][i][j] = now_map[i][j];
			now_map[i][j] = map[Now_floor+1][i][j] ;
			check_map[i][j] = 0;
		}
	Now_floor++; 
	Map_Print();
}

void Downstairs(void) {
	int i, j;
	cleardevice();
	for (i=1; i<=14; i++)
		for (j=1; j<=14; j++){
			map[Now_floor][i][j] = now_map[i][j];
			now_map[i][j] = map[Now_floor-1][i][j] ;
			check_map[i][j] = 0;
		}
	Now_floor--; 
	Map_Print();
}

void Quit(void) {
	int i, j;
	for (i=1; i<=14; i++)
		for (j=1; j<=14; j++)
			check_map[i][j] = 0;
	cleardevice();
	Map_Print();
}

void Esc() {
	cleardevice();
	exit(0);
}

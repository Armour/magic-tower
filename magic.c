#include "magic.h"

int Player_hp, Player_attack, Player_defend, Player_money, Player_exp, Player_level, Player_miss, Player_bow;
int Now_i, Now_j, Now_floor, Now_towards;
int Key_num_yellow, Key_num_blue, Key_num_red;
int Exp_need, Sword, Shield, Books, Is_girl;
int x[5], y[5];
int Memory_map[11][20][20];
int map[11][20][20], now_map[20][20], check_map[20][20];
int Monster_hp[100], Monster_attack[100], Monster_defend[100], Monster_money[100], Monster_exp[100], Monster_miss[100], Monster_bow[100];
int graphdriver, graphmode;
int speed;

const int QSC = 32;
const int LOWSPEED = 200;
const int MIDSPEED = 150;
const int HIGHSPEED = 110;

int main(void) {
	Info_Prep();
	Map_Prep();
	Welcome();
	return 0;
}

void Info_Prep(void) {
	graphdriver = DETECT;
	graphmode = VESA_1024x768x24bit;
	initgraph(&graphdriver, &graphmode, "");
	cleardevice();

	Player_money   = 0;
	Player_exp     = 0;
	Player_level   = 0;

	Now_i   = 13;
	Now_j   = 7;
	Now_floor = 1;
	Now_towards = 3;

	Key_num_yellow = 0;
	Key_num_blue   = 0;
	Key_num_red    = 0;

	Exp_need = 5;
	Sword    = 0;
	Shield   = 0;
	Books    = 0;

	speed = MIDSPEED;

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
	int i, j, k, floors, ascii = 219;
	char ch = (char)ascii;
	FILE *fp;

	fp = fopen("floors.txt","r");
	for (floors=1; floors<=10; floors++)
		for (i=1; i<=14; i++)
			for (j=1; j<=14; j++)
				fscanf(fp,"%d",&map[floors][i][j]);
	fclose(fp);

	fp = fopen("monster.txt","r");
	for (i=11; i<=23; i++) {
		fscanf(fp, "%d", &Monster_hp[i]);
		fscanf(fp, "%d", &Monster_attack[i]);
		fscanf(fp, "%d", &Monster_defend[i]);
		fscanf(fp, "%d", &Monster_money[i]);
		fscanf(fp, "%d", &Monster_exp[i]);
		fscanf(fp, "%d", &Monster_miss[i]);
		fscanf(fp, "%d", &Monster_bow[i]);
	}
	fclose(fp);

	memset(now_map,0,sizeof(now_map));
	memset(check_map,0,sizeof(check_map));

	for (i=1; i<=14; i++)
		for (j=1; j<=14; j++)
			now_map[i][j] = map[Now_floor][i][j];

	now_map[Now_i][Now_j] = 1;
}

void Welcome(void) {
	char ch;

	Load_24bit_Bmp(180,1,"assets/welcome.bmp");

	while (1) {
		ch = bioskey(0);
		if (ch == '1') {
			cleardevice();
			Select_Sex();
			break;
		}
		if (ch == '2') {
			Load_Memory();
			break;
		}
		if (ch == '3') {
			Esc();
			break;
		}
	}
	Magic();
}

void Select_Sex(void) {
	char ch;
	Load_24bit_Bmp(250,1,"assets/select.bmp");
	while (1) {
		ch = bioskey(0);
		if (ch == '1') {
			Is_girl = 0;
			Player_hp     = 150;   //150
			Player_attack = 14;
			Player_defend = 10;
			Player_miss    = 8;
			Player_bow	   = 93;
			break;
		};
		if (ch == '2') {
			Is_girl = 1;
			Player_hp     = 200;   //200
			Player_attack = 13;
			Player_defend = 10;
			Player_miss    = 18;
			Player_bow	   = 99;
			break;
		}
	}
	cleardevice();
}

void Magic(void) {
	char ch;
	Map_Print();
	while (1) {
		ch = bioskey(0);
		if (ch == '`') Esc();
		//if (ch == 'i') Soldier_Info();
		if (ch == 'b') if (Books) Monster_Book();
		if (ch == 'h') Help();
		if (ch == 'm') Set_Memory();
		if (ch == 'l') Load_Memory();
		if (ch == 'w') Run('w');
		if (ch == 's') Run('s');
		if (ch == 'a') Run('a');
		if (ch == 'd') Run('d');
		if (ch == '1') speed = HIGHSPEED;
		if (ch == '2') speed = MIDSPEED;
		if (ch == '3') speed = HIGHSPEED;
	}
}

/*void Soldier_Info(void) {
	char ch;
	char * str = "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
	cleardevice();

	setcolor(0xEEEE00);
	sprintf(str,"                         Yellow Key :%8d", Key_num_yellow);
	outtextxy(200,10+5*11,str);

	setcolor(0x0000EE);
	sprintf(str,"                         Blue Key   :%8d", Key_num_blue);
	outtextxy(200,10+8*11,str);

	setcolor(0xEE0000);
	sprintf(str,"                         Red Key    :%8d", Key_num_red);
	outtextxy(200,10+11*11,str);

	setcolor(0x00EE00);
	sprintf(str,"          HP:  %8d      Attack:  %8d      Defend:  %8d ", Player_hp, Player_attack, Player_defend);
	outtextxy(185,10+17*11,str);

	setcolor(0x00EEEE);
	sprintf(str,"          Lv:  %8d      Money :  %8d      Exp   :  %8d ", Player_level, Player_money, Player_exp);
	outtextxy(185,10+23*11,str);

	setcolor(0xFF00FF);
	sprintf(str,"                         Next Level:  %8d ", Exp_need-Player_exp);
	outtextxy(200,10+29*11,str);

	setcolor(0x666666);
	outtextxy(200,10+40*11,"                      ( Please enter \'q\' to quit. )     ");

	while (1) {
		ch = bioskey(0);
		if (ch == 'q'){
			Quit();
			break;
		}
	}
}*/

void Help(void) {
	char ch;
	cleardevice();
	Load_24bit_Bmp(250,1,"assets/help.bmp");
	while (1) {
		ch = bioskey(0);
		Quit();
		break;
	}
}

void Shop(void) {
	char ch;
	char * str = "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
	int now_line = 24;
	cleardevice();

	setcolor(0xFFFFFF);
	sprintf(str,"       Shop: Soldiers! Money! Money! Give me your money!!!");
	outtextxy(250,10+0*11,str);

	setcolor(0x00EE00);
	sprintf(str,"            1.Hp + 30            Cost 50");
	outtextxy(250,10+2*11,str);
	sprintf(str,"            2.Attack + 2         Cost 50");
	outtextxy(250,10+4*11,str);
	sprintf(str,"            3.Defend + 1         Cost 50");
	outtextxy(250,10+6*11,str);

	setcolor(0xEEEE00);
	sprintf(str,"            4.Yellow Key + 1     Cost 40");
	outtextxy(250,10+8*11,str);

	setcolor(0x0000EE);
	sprintf(str,"            5.Blue Key + 1       Cost 120");
	outtextxy(250,10+10*11,str);

	setcolor(0xEE0000);
	sprintf(str,"            6.Red Key + 1        Cost 300");
	outtextxy(250,10+12*11,str);

	setcolor(0xFFFFFF);
	sprintf(str,"       Your Money: %d",Player_money);
	outtextxy(250,10+14*11,str);

	setcolor(0x666666);
	sprintf(str,"           ( Please enter \'q\' to quit. )   ");
	outtextxy(250,10+18*11,str);

	while (1){
		ch = bioskey(0);
		if (ch == '1' && Player_money >= 50){
			Player_money-=50;
			Player_hp += 30;
			setfillstyle(SOLID_FILL,BLACK);
			bar(250,10+now_line*11,800,10+(now_line+4)*11);
			setcolor(0x00EE00);
			sprintf(str,"            HP + 30 ~          OK!");
			outtextxy(250,10+now_line*11,str);
			now_line += 2;
			if (now_line > 45) now_line = 24;
		}	else
		if (ch == '2' && Player_money >= 50){
			Player_money-=50;
			Player_attack += 2;
			setfillstyle(SOLID_FILL,BLACK);
			bar(250,10+now_line*11,800,10+(now_line+4)*11+3);
			setcolor(0x00EE00);
			sprintf(str,"            Attack + 2 ~       OK!");
			outtextxy(250,10+now_line*11,str);
			now_line += 2;
			if (now_line > 45) now_line = 24;
		}	else
		if (ch == '3' && Player_money >= 50){
			Player_money-=50;
			Player_defend += 1;
			setfillstyle(SOLID_FILL,BLACK);
			bar(250,10+now_line*11,800,10+(now_line+4)*11+3);
			setcolor(0x00EE00);
			sprintf(str,"            Defend + 1 ~       OK!");
			outtextxy(250,10+now_line*11,str);
			now_line += 2;
			if (now_line > 45) now_line = 24;
		}	else
		if (ch == '4' && Player_money >= 40){
			Player_money-=40;
			Key_num_yellow += 1;
			setfillstyle(SOLID_FILL,BLACK);
			bar(250,10+now_line*11,800,10+(now_line+4)*11+3);
			setcolor(0xEEEE00);
			sprintf(str,"            Yellow Key + 1 ~   OK!");
			outtextxy(250,10+now_line*11,str);
			now_line += 2;
			if (now_line > 45) now_line = 24;
		}	else
		if (ch == '5' && Player_money >= 120){
			Player_money-=120;
			Key_num_blue += 1;
			setfillstyle(SOLID_FILL,BLACK);
			bar(250,10+now_line*11,800,10+(now_line+4)*11+3);
			setcolor(0x0000EE);
			sprintf(str,"            Blue Key + 1 ~     OK!");
			outtextxy(250,10+now_line*11,str);
			now_line += 2;
			if (now_line > 45) now_line = 24;
		}	else
		if (ch == '6' && Player_money >= 300){
			Player_money-=300;
			Key_num_red += 1;
			setfillstyle(SOLID_FILL,BLACK);
			bar(250,10+now_line*11,800,10+(now_line+4)*11+3);
			setcolor(0xEE0000);
			sprintf(str,"            Red Key + 1 ~      OK!");
			outtextxy(250,10+now_line*11,str);
			now_line += 2;
			if (now_line > 45) now_line = 24;
		}	else
		if (ch == '1' || ch == '2' || ch == '3' || ch== '4' || ch =='5' || ch == '6') {
			setfillstyle(SOLID_FILL,BLACK);
			bar(250,10+now_line*11,800,10+(now_line+4)*11+3);
			setcolor(0xFFFFFF);
			sprintf(str,"            Where is your money, shit!");
			outtextxy(250,10+now_line*11,str);
			now_line += 2;
			if (now_line > 45) now_line = 24;
		}
		setfillstyle(SOLID_FILL,BLACK);
		bar(250,10+14*11,800,10+17*11+3);
		setcolor(0xFFFFFF);
		sprintf(str,"       Your Money: %d",Player_money);
		outtextxy(250,10+14*11,str);
		if (ch == 'q')	break;
	}
	Quit();
}

void Set_Memory(void) {
	int i,j,k;
	FILE *fp;
	fp = fopen("memory.txt","w");
	fprintf(fp,"%d\n",Player_hp);
	fprintf(fp,"%d\n",Player_attack);
	fprintf(fp,"%d\n",Player_defend);
	fprintf(fp,"%d\n",Player_money);
	fprintf(fp,"%d\n",Player_exp);
	fprintf(fp,"%d\n",Player_level);
	fprintf(fp,"%d\n",Player_miss);
	fprintf(fp,"%d\n",Player_bow);
	fprintf(fp,"%d\n",Now_i);
	fprintf(fp,"%d\n",Now_j);
	fprintf(fp,"%d\n",Now_floor);
	fprintf(fp,"%d\n",Now_towards);
	fprintf(fp,"%d\n",Key_num_yellow);
	fprintf(fp,"%d\n",Key_num_blue);
	fprintf(fp,"%d\n",Key_num_red);
	fprintf(fp,"%d\n",Exp_need);
	fprintf(fp,"%d\n",Sword);
	fprintf(fp,"%d\n",Shield);
	fprintf(fp,"%d\n",Books);
	fprintf(fp,"%d\n",Is_girl);

	for (i=1; i<=14; i++)
		for (j=1; j<=14; j++)
			map[Now_floor][i][j] = now_map[i][j];

	map[Now_floor][Now_i][Now_j] = 0;

	for (k=1; k<=10; k++)
		for (i=1; i<=14; i++) {
			for (j=1; j<=14; j++)
				fprintf(fp,"%d ",map[k][i][j]);
			fprintf(fp, "\n");
		}
}

void Load_Memory(void) {
	int i,j,k;
	FILE *fp;
	fp = fopen("memory.txt","r");
	fscanf(fp,"%d",&Player_hp);
	fscanf(fp,"%d",&Player_attack);
	fscanf(fp,"%d",&Player_defend);
	fscanf(fp,"%d",&Player_money);
	fscanf(fp,"%d",&Player_exp);
	fscanf(fp,"%d",&Player_level);
	fscanf(fp,"%d",&Player_miss);
	fscanf(fp,"%d",&Player_bow);
	fscanf(fp,"%d",&Now_i);
	fscanf(fp,"%d",&Now_j);
	fscanf(fp,"%d",&Now_floor);
	fscanf(fp,"%d",&Now_towards);
	fscanf(fp,"%d",&Key_num_yellow);
	fscanf(fp,"%d",&Key_num_blue);
	fscanf(fp,"%d",&Key_num_red);
	fscanf(fp,"%d",&Exp_need);
	fscanf(fp,"%d",&Sword);
	fscanf(fp,"%d",&Shield);
	fscanf(fp,"%d",&Books);
	fscanf(fp,"%d",&Is_girl);

	for (k=1; k<=10; k++)
		for (i=1; i<=14; i++)
			for (j=1; j<=14; j++)
				fscanf(fp,"%d",&map[k][i][j]);

	for (i=1; i<=14; i++)
		for (j=1; j<=14; j++){
			check_map[i][j] = 0;
			now_map[i][j] = map[Now_floor][i][j];
		}

	now_map[Now_i][Now_j] = 1;

	cleardevice();
	Map_Print();
}

void Tips_Oldman(void) {
	char ch;
	cleardevice();
	Load_24bit_Bmp(250,1,"assets/tips1.bmp");
	while (1) {
		ch = bioskey(0);
		Quit();
		break;
	}
}

void Tips_Sorceress(void) {
	char ch;
	cleardevice();
	Load_24bit_Bmp(250, 1, "assets/tips2.bmp");
	while (1) {
		ch = bioskey(0);
		Quit();
		break;
	}
}

void Monster_Book(void) {
	int i, j;
	int exist[30];
	char ch;
	char * str = "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
	char * bmpstr = "                                                                                ";
	cleardevice();
	for (i=1; i<=30; i++)
		exist[i] = 0;
	for (i=1; i<=14; i++)
		for (j=1; j<=14; j++)
			if (now_map[i][j] >= 11 && now_map[i][j] <= 22)
				exist[now_map[i][j]] = 1;
	i = 10;
	for (j=11; j<=22; j++)
		if (exist[j]) {
			i++;
			sprintf(bmpstr, "assets/%d.bmp", j);
			Load_24bit_Bmp(50,(i-11)*52+1*12,bmpstr);

			setcolor(0x00EE00);
			sprintf(str," HP: %3d     Attack: %3d     Defend: %3d",Monster_hp[j],Monster_attack[j],Monster_defend[j]);
			outtextxy(100,(i-11)*52+2*12,str);

			setcolor(0xEE0000);
			sprintf(str,"     Miss: %3d%%     Bow: %3d%%",Monster_miss[j],100-Monster_bow[j]);
			outtextxy(430,(i-11)*52+2*12,str);

			setcolor(0xEEEEEE);
			sprintf(str,"     Money: %3d     Exp: %3d",Monster_money[j],Monster_exp[j]);
			outtextxy(650,(i-11)*52+2*12,str);
		}

	while (1) {
		ch = bioskey(0);
		Quit();
		break;
	}
}

void Monster_Fight(int m) {
	char ch;
	char * str = "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
	char * bmpstr = "                                                                                   ";
	int i, r, damage, random, now_line;
	int Monster_HP 	   = Monster_hp[m];
	int Monster_Attack = Monster_attack[m];
	int Monster_Defend = Monster_defend[m];
	srand((unsigned)time(NULL));

	cleardevice();

	Load_24bit_Bmp(165, 1, "assets/fight.bmp");
	Load_24bit_Bmp(528, 1, "assets/fight.bmp");
	Load_24bit_Bmp(458, 20, "assets/vs.bmp");

	sprintf(bmpstr, "assets/%d.bmp", m);
	Load_24bit_Bmp(287,1+1*11+6,bmpstr);

	if (!Is_girl)
		Load_24bit_Bmp(645, 1 + 1 * 11 + 6, "assets/1003.bmp");
	if (Is_girl)
		Load_24bit_Bmp(645, 1 + 1 * 11 + 6, "assets/2003.bmp");
	if (Sword)
		Load_24bit_Bmp(580, 1 + 1 * 11 + 6, "assets/31.bmp");
	if (Shield)
		Load_24bit_Bmp(710, 1 + 1 * 11 + 6, "assets/33.bmp");

	setcolor(0xFFFFFF);
	sprintf(str,"                %5d                          %5d",Monster_HP,Player_hp);
	outtextxy(185,1+7*11,str);

	now_line = 1+7*11;

	while (1) {
		now_line+=13;
		if (now_line >= 1+30*13) now_line = 1+7*11;
		setfillstyle(SOLID_FILL,BLACK);
		bar(185,now_line,800,now_line+13*3-1);

		random = 1+ rand() % 100;
		if (random < Player_bow && random > Monster_miss[m]){
			damage = Player_attack - Monster_Defend;
			if (damage <= 0) damage = 1;
			Monster_HP-=damage;
			if (Monster_HP < 0) Monster_HP = 0;
			setcolor(0xFFFFFF);
			sprintf(str,"                %5d                   ",Monster_HP);
			outtextxy(185,now_line,str);
		}
		if (random <= Monster_miss[m]){
			setcolor(0x7CFC00);
			sprintf(str,"  Miss...       %5d                   ",Monster_HP);
			outtextxy(185,now_line,str);
		}
		if (random >= Player_bow){
			damage = floor((Player_attack - Monster_Defend)*1.5);
			if (damage <= 0) damage = 1;
			Monster_HP -= damage;
			if (Monster_HP < 0) Monster_HP = 0;
			setcolor(0xEE6A50);
			sprintf(str,"  Bow !!!       %5d                   ",Monster_HP);
			outtextxy(185,now_line,str);
		}
		if (Monster_HP <= 0) break;
		delay(speed);

		random = 1+ rand() % 100;
		if (random < Monster_bow[m] && random > Player_miss) {
			damage = Monster_attack[m] - Player_defend;
			if (damage <= 0) damage = 1;
			Player_hp-=damage;
			if (Player_hp < 0) Player_hp=0;
			setcolor(0xFFFFFF);
			sprintf(str,"                                               %5d                ",Player_hp);
			outtextxy(185,now_line,str);
		}
		if (random <= Player_miss) {
			setcolor(0x7CFC00);
			sprintf(str,"                                               %5d         Miss...",Player_hp);
			outtextxy(185,now_line,str);
		}
		if (random >= Monster_bow[m]) {
			damage = floor((Monster_attack[m] - Player_defend)*1.5);
			if (damage <= 0) damage = 1;
			Player_hp-=damage;
			if (Player_hp < 0) Player_hp=0;
			setcolor(0xEE6A50);
			sprintf(str,"                                               %5d         Bow !!!",Player_hp);
			outtextxy(185,now_line,str);
		}
		if (Player_hp <= 0) break;
		delay(speed);
	}

	Player_money  +=  Monster_money[m];
	Player_exp  +=  Monster_exp[m];

	cleardevice();
	setcolor(0xEE0000);
	if (Player_hp <= 0) Monster_Defeated();
	if (Player_hp > 0) {
		sprintf(str,"                                  You Win!!!");
		outtextxy(185,1+7*11,str);
		sprintf(str,"                        You earn %d Money and %d Experience!!      ", Monster_money[m], Monster_exp[m]);
		outtextxy(185,1+10*11,str);
	}
	setcolor(0x00EE00);
	if (Player_exp >= Exp_need) {
		Player_exp -= Exp_need;
		Exp_need = floor(Exp_need*1.5)+1;
		Player_hp += 10;
		Player_attack += 1;
		Player_defend += 1;
		Player_level += 1;
		sprintf(str,"                                  Level  Up  !!!!");
		outtextxy(185,1+18*11,str);
		sprintf(str,"                         HP+10!    Attak+1!     Defend+1!");
		outtextxy(185,1+21*11,str);
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
	Load_24bit_Bmp(45, 1, "assets/defeated.bmp");
	delay(3000);
	cleardevice();
	text_mode();
	exit(0);
}

void Run(char ch) {
	int m;
	if (ch == 'w') Now_towards=1;
	if (ch == 'a') Now_towards=2;
	if (ch == 's') Now_towards=3;
	if (ch == 'd') Now_towards=4;
	switch (now_map[Now_i+x[Now_towards]][Now_j+y[Now_towards]]){
		case 0:
		case 9:
		case 59:
			check_map[Now_i+x[Now_towards]][Now_j+y[Now_towards]] = 0;
			check_map[Now_i  ][Now_j] = 0;
			now_map[Now_i+x[Now_towards]][Now_j+y[Now_towards]] = 1;
			now_map[Now_i  ][Now_j] = 0;
			Now_i+=x[Now_towards];
			Now_j+=y[Now_towards];
			break;
		case 3:
			if (Key_num_yellow > 0)
			{
				Key_num_yellow--;
				check_map[Now_i+x[Now_towards]][Now_j+y[Now_towards]] = 0;
				check_map[Now_i  ][Now_j] = 0;
				now_map[Now_i+x[Now_towards]][Now_j+y[Now_towards]] = 1;
				now_map[Now_i  ][Now_j] = 0;
				Now_i+=x[Now_towards];
				Now_j+=y[Now_towards];
			}
			break;
		case 4:
			if (Key_num_blue > 0)
			{
				Key_num_blue--;
				check_map[Now_i+x[Now_towards]][Now_j+y[Now_towards]] = 0;
				check_map[Now_i  ][Now_j] = 0;
				now_map[Now_i+x[Now_towards]][Now_j+y[Now_towards]] = 1;
				now_map[Now_i  ][Now_j] = 0;
				Now_i+=x[Now_towards];
				Now_j+=y[Now_towards];
			}
			break;
		case 5:
			if (Key_num_red > 0)
			{
				Key_num_red--;
				check_map[Now_i+x[Now_towards]][Now_j+y[Now_towards]] = 0;
				check_map[Now_i  ][Now_j] = 0;
				now_map[Now_i+x[Now_towards]][Now_j+y[Now_towards]] = 1;
				now_map[Now_i  ][Now_j] = 0;
				Now_i+=x[Now_towards];
				Now_j+=y[Now_towards];
			}
			break;
		case 6:
			Key_num_yellow++;
			check_map[Now_i+x[Now_towards]][Now_j+y[Now_towards]] = 0;
			check_map[Now_i  ][Now_j] = 0;
			now_map[Now_i+x[Now_towards]][Now_j+y[Now_towards]] = 1;
			now_map[Now_i  ][Now_j] = 0;
			Now_i+=x[Now_towards];
			Now_j+=y[Now_towards];
			break;
		case 7:
			Key_num_blue++;
			check_map[Now_i+x[Now_towards]][Now_j+y[Now_towards]] = 0;
			check_map[Now_i  ][Now_j] = 0;
			now_map[Now_i+x[Now_towards]][Now_j+y[Now_towards]] = 1;
			now_map[Now_i  ][Now_j] = 0;
			Now_i+=x[Now_towards];
			Now_j+=y[Now_towards];
			break;
		case 8:
			Key_num_red++;
			check_map[Now_i+x[Now_towards]][Now_j+y[Now_towards]] = 0;
			check_map[Now_i  ][Now_j] = 0;
			now_map[Now_i+x[Now_towards]][Now_j+y[Now_towards]] = 1;
			now_map[Now_i  ][Now_j] = 0;
			Now_i+=x[Now_towards];
			Now_j+=y[Now_towards];
			break;
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
		case 17:
		case 18:
		case 19:
		case 20:
		case 21:
		case 22:
		case 23:
			m = now_map[Now_i+x[Now_towards]][Now_j+y[Now_towards]];
			check_map[Now_i+x[Now_towards]][Now_j+y[Now_towards]] = 0;
			check_map[Now_i  ][Now_j] = 0;
			now_map[Now_i+x[Now_towards]][Now_j+y[Now_towards]] = 1;
			now_map[Now_i  ][Now_j] = 0;
			Now_i+=x[Now_towards];
			Now_j+=y[Now_towards];
            Monster_Fight(m);
			break;
		case 25:
			check_map[Now_i+x[Now_towards]][Now_j+y[Now_towards]] = 0;
			check_map[Now_i  ][Now_j] = 0;
			now_map[Now_i+x[Now_towards]][Now_j+y[Now_towards]] = 1;
			now_map[Now_i  ][Now_j] = 0;
			Now_i+=x[Now_towards];
			Now_j+=y[Now_towards];
			Player_hp /= 3;
			break;
		case 26:
			check_map[Now_i+x[Now_towards]][Now_j+y[Now_towards]] = 0;
			check_map[Now_i  ][Now_j] = 0;
			now_map[Now_i+x[Now_towards]][Now_j+y[Now_towards]] = 1;
			now_map[Now_i  ][Now_j] = 0;
			Now_i+=x[Now_towards];
			Now_j+=y[Now_towards];
			Player_defend /= 3;
			break;
		case 27:
			check_map[Now_i+x[Now_towards]][Now_j+y[Now_towards]] = 0;
			check_map[Now_i  ][Now_j] = 0;
			now_map[Now_i+x[Now_towards]][Now_j+y[Now_towards]] = 1;
			now_map[Now_i  ][Now_j] = 0;
			Now_i+=x[Now_towards];
			Now_j+=y[Now_towards];
			Player_attack /= 3;
			break;
		case 28:
			check_map[Now_i+x[Now_towards]][Now_j+y[Now_towards]] = 0;
			check_map[Now_i  ][Now_j] = 0;
			now_map[Now_i+x[Now_towards]][Now_j+y[Now_towards]] = 1;
			now_map[Now_i  ][Now_j] = 0;
			Now_i+=x[Now_towards];
			Now_j+=y[Now_towards];
			Player_money += 15;
			break;
		case 29:
			check_map[Now_i+x[Now_towards]][Now_j+y[Now_towards]] = 0;
			check_map[Now_i  ][Now_j] = 0;
			now_map[Now_i+x[Now_towards]][Now_j+y[Now_towards]] = 1;
			now_map[Now_i  ][Now_j] = 0;
			Now_i+=x[Now_towards];
			Now_j+=y[Now_towards];
			Player_hp += 18;
			break;
		case 30:
			check_map[Now_i+x[Now_towards]][Now_j+y[Now_towards]] = 0;
			check_map[Now_i  ][Now_j] = 0;
			now_map[Now_i+x[Now_towards]][Now_j+y[Now_towards]] = 1;
			now_map[Now_i  ][Now_j] = 0;
			Now_i+=x[Now_towards];
			Now_j+=y[Now_towards];
			Player_hp += 30;
			break;
		case 31:
			check_map[Now_i+x[Now_towards]][Now_j+y[Now_towards]] = 0;
			check_map[Now_i  ][Now_j] = 0;
			now_map[Now_i+x[Now_towards]][Now_j+y[Now_towards]] = 1;
			now_map[Now_i  ][Now_j] = 0;
			Now_i+=x[Now_towards];
			Now_j+=y[Now_towards];
			Sword = 1;
			Player_attack += 10;
			break;
		case 32:
			check_map[Now_i+x[Now_towards]][Now_j+y[Now_towards]] = 0;
			check_map[Now_i  ][Now_j] = 0;
			now_map[Now_i+x[Now_towards]][Now_j+y[Now_towards]] = 1;
			now_map[Now_i  ][Now_j] = 0;
			Now_i+=x[Now_towards];
			Now_j+=y[Now_towards];
			Player_attack += 3;
			break;
		case 33:
			check_map[Now_i+x[Now_towards]][Now_j+y[Now_towards]] = 0;
			check_map[Now_i  ][Now_j] = 0;
			now_map[Now_i+x[Now_towards]][Now_j+y[Now_towards]] = 1;
			now_map[Now_i  ][Now_j] = 0;
			Now_i+=x[Now_towards];
			Now_j+=y[Now_towards];
			Shield = 1;
			Player_defend += 8;
			break;
		case 34:
			check_map[Now_i+x[Now_towards]][Now_j+y[Now_towards]] = 0;
			check_map[Now_i  ][Now_j] = 0;
			now_map[Now_i+x[Now_towards]][Now_j+y[Now_towards]] = 1;
			now_map[Now_i  ][Now_j] = 0;
			Now_i+=x[Now_towards];
			Now_j+=y[Now_towards];
			Player_defend += 2;
			break;
		case 35:
			check_map[Now_i+x[Now_towards]][Now_j+y[Now_towards]] = 0;
			check_map[Now_i  ][Now_j] = 0;
			now_map[Now_i+x[Now_towards]][Now_j+y[Now_towards]] = 1;
			now_map[Now_i  ][Now_j] = 0;
			Now_i+=x[Now_towards];
			Now_j+=y[Now_towards];
			Books = 1;
			break;
		case 10:
			Tips_Oldman();
			break;
		case 24:
			Tips_Sorceress();
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
		case 99:
			Ending();
			break;
	}
	Map_Print();
}

void Map_Print(void) {
	int i, j, number;
	char * str = "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!！";
	char * bmpstr = "                                                                                      ";
	for (i=1; i<=14; i++)
		for (j=1; j<=14; j++)
			if (!check_map[i][j]) {
				setfillstyle(SOLID_FILL,0x000000);
				bar(250+ j*QSC,(i-1)*QSC,250+ j*QSC+QSC-1,(i-1)*QSC+QSC-1);

				number = now_map[i][j];
				if (now_map[i][j] == 1 && Is_girl == 0)
					number = 1000 + Now_towards;
				if (now_map[i][j] == 1 && Is_girl == 1)
					number = 2000 + Now_towards;

				sprintf(bmpstr, "assets/%d.bmp", number);
				Load_24bit_Bmp(250+ j*QSC, (i-1)*QSC, bmpstr);
			}

	for (i=1; i<=14; i++)
		for (j=1; j<=14; j++)
			check_map[i][j] = 1;

	Load_24bit_Bmp(185, 15, "assets/side.bmp");
	if (!Is_girl)
		Load_24bit_Bmp(220, 30, "assets/1003.bmp");
	if (Is_girl)
		Load_24bit_Bmp(220, 30, "assets/2003.bmp");

	setcolor(0x00EEEE);
	sprintf(str,"Lv");
	outtextxy(220,100,str);

	Load_24bit_Bmp(202, 70, "assets/info1.bmp");
	Load_24bit_Bmp(200, 130, "assets/info2.bmp");
	Load_24bit_Bmp(198, 145, "assets/info3.bmp");
	Load_24bit_Bmp(205, 215, "assets/info4.bmp");

	if (Books) {
		Load_24bit_Bmp(205, 325, "assets/book.bmp");
		setcolor(0xEEEEEE);
		outtextxy(240,335,"B");
	}

	setfillstyle(SOLID_FILL,0x000000);
	bar(235,70,250,90);

	setcolor(0x00EEEE);
	sprintf(str,"%d ", Player_level);
	outtextxy(245,100,str);

	setfillstyle(SOLID_FILL,0x000000);
	bar(223,120,280,210);
	setfillstyle(SOLID_FILL,0x000000);
	bar(235,230,255,300);

	setcolor(0xEEEEEE);
	sprintf(str,"%d ", Now_floor);
	outtextxy(238,74,str);
	sprintf(str," %5d", Player_hp);
	outtextxy(220,130,str);
	sprintf(str," %5d", Player_attack);
	outtextxy(220,145,str);
	sprintf(str," %5d", Player_defend);
	outtextxy(220,160,str);
	sprintf(str," %5d", Player_money);
	outtextxy(220,175,str);
	sprintf(str," %5d", Exp_need-Player_exp);
	outtextxy(220,190,str);

	setcolor(0xEEEE00);
	sprintf(str,"%d ", Key_num_yellow);
	outtextxy(240,235,str);
	setcolor(0x0000EE);
	sprintf(str,"%d ", Key_num_blue);
	outtextxy(240,255,str);
	setcolor(0xEE0000);
	sprintf(str,"%d ", Key_num_red);
	outtextxy(240,275,str);
}

void Upstairs(void) {
	int i, j;
	cleardevice();
	now_map[Now_i][Now_j] = 0;
	for (i=1; i<=14; i++)
		for (j=1; j<=14; j++){
			map[Now_floor][i][j] = now_map[i][j];
			now_map[i][j] = map[Now_floor+1][i][j] ;
			check_map[i][j] = 0;
		}
	Now_floor++;
	now_map[Now_i][Now_j] = 1;
	Map_Print();
}

void Downstairs(void) {
	int i, j;
	cleardevice();
	now_map[Now_i][Now_j] = 0;
	for (i=1; i<=14; i++)
		for (j=1; j<=14; j++){
			map[Now_floor][i][j] = now_map[i][j];
			now_map[i][j] = map[Now_floor-1][i][j] ;
			check_map[i][j] = 0;
		}
	Now_floor--;
	now_map[Now_i][Now_j] = 1;
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

void Esc(void) {
	int i,j,k;
	cleardevice();
	text_mode();
	exit(0);
}

void Ending(void) {
	char ch;
	cleardevice();
	if (!Is_girl) {
		Load_24bit_Bmp(250, 1, "assets/ending1.bmp");
		while (1) {
			ch = bioskey(0);
			Esc();
		}
	}
	if (Is_girl) {
		Load_24bit_Bmp(250, 1, "assets/ending2.bmp");
		while (1) {
			ch = bioskey(0);
			Esc();
		}
	}
}

int Load_24bit_Bmp(int x, int y, char *filename) {
	FILE *fp = NULL;
	byte *p = NULL; /* pointer to a line of bmp data */
	byte *vp = _vp + (_active_page*_page_gap + y*_width + x) * (_color_bits/8);
	dword width, height, bmp_data_offset, bytes_per_line, offset;
	int i;
	p = malloc(1024L * 3); /* memory for holding a line of bmp data */
	if (p == NULL) /* cannot allocate enough memory for drawing 1 line */
	   goto display_bmp_error;
	fp = fopen(filename, "rb");
	if (fp == NULL) /* cannot open bmp file */
	   goto display_bmp_error;
	fread(p, 1, 0x36, fp); /* read BMP head */
	if (*(word *)p != 0x4D42) /* check BMP signature */
	   goto display_bmp_error; /* not a BMP file */
	if (*(word *)(p+0x1C) != 24)
	   goto display_bmp_error; /* not a 24-bit-color BMP file */
	width = *(dword *)(p+0x12);
	height = *(dword *)(p+0x16);
	bmp_data_offset = *(dword *)(p+0x0A);
	fseek(fp, bmp_data_offset, SEEK_SET); /* skip BMP head */
	bytes_per_line = (width * 3 + 3) / 4 * 4; /* must be multiple of 4 */
	for (i=height-1; i>=0; i--) { /* draw from bottom to top */
	   fread(p, 1, bytes_per_line, fp); /* read a line of bmp data */
	   offset = i * 1024 * 3;
	   memcpy(vp+offset, p, width*3);
	}
	free(p);
	fclose(fp);
	return 1;
	display_bmp_error:
	if(p != NULL)
	   free(p);
	if(fp != NULL)
	   fclose(fp);
	return 0;
}

/* -----------------------------------------------by Armour---------------------------------------------------*/
/* -----------------------------------------QQ497052684 欢迎勾搭=w=-------------------------------------------*/

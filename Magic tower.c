#include<stdio.h>
#include<dos.h>
#include<conio.h>

int HP1,Attack1,Defend1,Money,Exp,Lv;
int now_I,now_J;
int key_num_yellow,key_num_blue,key_num_red;
int Exp_Need,Sword,Shield,Books;
int map[16][16][16],now_map[16][16];
int map1[16][16],map2[16][16],map3[16][16],map4[16][16];
int load_map[16][16][16];

int main(void)
{
	init();
	prep();
	work();
}

void init(void)
{
	int i,j;
	
	for (i=1; i<=14; i++)
		for (j=1; j<=14; j++){
			map[1][i][j] = map1[i][j];
			map[2][i][j] = map2[i][j];
			map[3][i][j] = map3[i][j];
			map[4][i][j] = map4[i][j];
		}
}

void prep(void)
{
	int i,j;
	
	HP1     = 150;
	Attack1 = 13;
	Defend1 = 10;
	Money   = 0;
	Exp     = 0;
	Lv      = 0;

	now_I   = 13;
	now_J   = 7;
	
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
	for (i=1; i<=14; i++)
		for (j=1; j<=14; j++)
			now_map[i][j] = load_map[1][i][j];
}

void work(void)
{
	char ch;
	while (1) {
		print();
		bioskey(0);
		if (ch == 'b') book();
			else if (ch == 'i') look(); 
				else if (ch == 'q') exit();
					else run(ch);
	}
}

void run(char ch)
{
	if (ch == 'w'){
		switch (now_map[now_I-1][now_J]){
			case 1,2:
				map[now_I-1][now_J] = false;
				map[now_I  ][now_J] = false;
				now_map[now_I-1][now_J] = 1;
				now_map[now_I  ][now_J] = 0;
				now_I--;
				break;
			case 3:
				if (key_num_yellow > 0)
				{
					key_num_yellow--;
					map[now_I-1][now_J] = false;
					map[now_I  ][now_J] = false;
					now_map[now_I-1][now_J] = 1;
					now_map[now_I  ][now_J] = 0;
					now_I--; 
				}
				break;
			case 4:
				if (key_num_blue > 0)
				{
					key_num_blue--;
					map[now_I-1][now_J] = false;
					map[now_I  ][now_J] = false;
					now_map[now_I-1][now_J] = 1;
					now_map[now_I  ][now_J] = 0;
					now_I--; 
				}
				break;
			case 5:
				if (key_num_red > 0)
				{
					key_num_red--;
					map[now_I-1][now_J] = false;
					map[now_I  ][now_J] = false;
					now_map[now_I-1][now_J] = 1;
					now_map[now_I  ][now_J] = 0;
					now_I--; 
				}
				break;
			case 6:
				key_num_yellow++;
				map[now_I-1][now_J] = false;
				map[now_I  ][now_J] = false;
				now_map[now_I-1][now_J] = 1;
				now_map[now_I  ][now_J] = 0;
				now_I--; 
				break;
			case 7:
				key_num_blue++;
				map[now_I-1][now_J] = false;
				map[now_I  ][now_J] = false;
				now_map[now_I-1][now_J] = 1;
				now_map[now_I  ][now_J] = 0;
				now_I--; 
				break;
			case 8:
				key_num_red++;
				map[now_I-1][now_J] = false;
				map[now_I  ][now_J] = false;
				now_map[now_I-1][now_J] = 1;
				now_map[now_I  ][now_J] = 0;
				now_I--; 
				break;
			case 11,12,13,14,15,16,17:
				map[now_I-1][now_J] = false;
				map[now_I  ][now_J] = false;
                fighting(now_map[now_I-1][now_J]);
				now_map[now_I-1][now_J] = 1;
				now_map[now_I  ][now_J] = 0;
				now_I--; 
				break;
			case 30:
				map[now_I-1][now_J] = false;
				map[now_I  ][now_J] = false;
				now_map[now_I-1][now_J] = 1;
				now_map[now_I  ][now_J] = 0;
				now_I--;
				Hp1+=30;
				break;	
			case 31:
				map[now_I-1][now_J] = false;
				map[now_I  ][now_J] = false;
				now_map[now_I-1][now_J] = 1;
				now_map[now_I  ][now_J] = 0;
				now_I--;
				Sword = true;
                Attack1+=10;
				break;
			case 32:
				map[now_I-1][now_J] = false;
				map[now_I  ][now_J] = false;
				now_map[now_I-1][now_J] = 1;
				now_map[now_I  ][now_J] = 0;
				now_I--;
                Attack1+=3;
				break;
			case 33:
				map[now_I-1][now_J] = false;
				map[now_I  ][now_J] = false;
				now_map[now_I-1][now_J] = 1;
				now_map[now_I  ][now_J] = 0;
				now_I--;
                Defend1+=8;
				break;
			case 35:
				map[now_I-1][now_J] = false;
				map[now_I  ][now_J] = false;
				now_map[now_I-1][now_J] = 1;
				now_map[now_I  ][now_J] = 0;
				now_I--;
                Books = true;
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
			case 1,2:
				map[now_I+1][now_J] = false;
				map[now_I  ][now_J] = false;
				now_map[now_I+1][now_J] = 1;
				now_map[now_I  ][now_J] = 0;
				now_I++;
				break;
			case 3:
				if (key_num_yellow > 0)
				{
					key_num_yellow--;
					map[now_I+1][now_J] = false;
					map[now_I  ][now_J] = false;
					now_map[now_I+1][now_J] = 1;
					now_map[now_I  ][now_J] = 0;
					now_I++; 
				}
				break;
			case 4:
				if (key_num_blue > 0)
				{
					key_num_blue--;
					map[now_I+1][now_J] = false;
					map[now_I  ][now_J] = false;
					now_map[now_I+1][now_J] = 1;
					now_map[now_I  ][now_J] = 0;
					now_I++; 
				}
				break;
			case 5:
				if (key_num_red > 0)
				{
					key_num_red--;
					map[now_I+1][now_J] = false;
					map[now_I  ][now_J] = false;
					now_map[now_I+1][now_J] = 1;
					now_map[now_I  ][now_J] = 0;
					now_I++; 
				}
				break;
			case 6:
				key_num_yellow++;
				map[now_I+1][now_J] = false;
				map[now_I  ][now_J] = false;
				now_map[now_I+1][now_J] = 1;
				now_map[now_I  ][now_J] = 0;
				now_I++; 
				break;
			case 7:
				key_num_blue++;
				map[now_I+1][now_J] = false;
				map[now_I  ][now_J] = false;
				now_map[now_I+1][now_J] = 1;
				now_map[now_I  ][now_J] = 0;
				now_I++; 
				break;
			case 8:
				key_num_red++;
				map[now_I+1][now_J] = false;
				map[now_I  ][now_J] = false;
				now_map[now_I+1][now_J] = 1;
				now_map[now_I  ][now_J] = 0;
				now_I++; 
				break;
			case 11,12,13,14,15,16,17:
				map[now_I+1][now_J] = false;
				map[now_I  ][now_J] = false;
                fighting(now_map[now_I+1][now_J]);
				now_map[now_I+1][now_J] = 1;
				now_map[now_I  ][now_J] = 0;
				now_I++; 
				break;
			case 30:
				map[now_I+1][now_J] = false;
				map[now_I  ][now_J] = false;
				now_map[now_I+1][now_J] = 1;
				now_map[now_I  ][now_J] = 0;
				now_I++;
				Hp1+=30;
				break;
			case 31:
				map[now_I+1][now_J] = false;
				map[now_I  ][now_J] = false;
				now_map[now_I+1][now_J] = 1;
				now_map[now_I  ][now_J] = 0;
				now_I++;
				Sword = true;
                Attack1+=10;
				break;
			case 32:
				map[now_I+1][now_J] = false;
				map[now_I  ][now_J] = false;
				now_map[now_I+1][now_J] = 1;
				now_map[now_I  ][now_J] = 0;
				now_I++;
                Attack1+=3;
				break;
			case 33:
				map[now_I+1][now_J] = false;
				map[now_I  ][now_J] = false;
				now_map[now_I+1][now_J] = 1;
				now_map[now_I  ][now_J] = 0;
				now_I++;
                Defend1+=8;
				break;
			case 35:
				map[now_I+1][now_J] = false;
				map[now_I  ][now_J] = false;
				now_map[now_I+1][now_J] = 1;
				now_map[now_I  ][now_J] = 0;
				now_I++;
                Books = true;
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
			case 1,2:
				map[now_I][now_J-1] = false;
				map[now_I][now_J  ] = false;
				now_map[now_I][now_J-1] = 1;
				now_map[now_I][now_J  ] = 0;
				now_J--;
				break;
			case 3:
				if (key_num_yellow > 0)
				{
					key_num_yellow--;
					map[now_I][now_J-1] = false;
					map[now_I][now_J  ] = false;
					now_map[now_I][now_J-1] = 1;
					now_map[now_I][now_J  ] = 0;
					now_J--;
				}
				break;
			case 4:
				if (key_num_blue > 0)
				{
					key_num_blue--;
					map[now_I][now_J-1] = false;
					map[now_I][now_J  ] = false;
					now_map[now_I][now_J-1] = 1;
					now_map[now_I][now_J  ] = 0;
					now_J--;
				}
				break;
			case 5:
				if (key_num_red > 0)
				{
					key_num_red--;
					map[now_I][now_J-1] = false;
					map[now_I][now_J  ] = false;
					now_map[now_I][now_J-1] = 1;
					now_map[now_I][now_J  ] = 0;
					now_J--;
				}
				break;
			case 6:
				key_num_yellow++;
				map[now_I][now_J-1] = false;
				map[now_I][now_J  ] = false;
				now_map[now_I][now_J-1] = 1;
				now_map[now_I][now_J  ] = 0;
				now_J--;
				break;
			case 7:
				key_num_blue++;
				map[now_I][now_J-1] = false;
				map[now_I][now_J  ] = false;
				now_map[now_I][now_J-1] = 1;
				now_map[now_I][now_J  ] = 0;
				now_J--;
				break;
			case 8:
				key_num_red++;
				map[now_I][now_J-1] = false;
				map[now_I][now_J  ] = false;
				now_map[now_I][now_J-1] = 1;
				now_map[now_I][now_J  ] = 0;
				now_J--;
				break;
			case 11,12,13,14,15,16,17:
				map[now_I][now_J-1] = false;
				map[now_I][now_J  ] = false;
                fighting(now_map[now_I][now_J-1]);
				now_map[now_I][now_J-1] = 1;
				now_map[now_I][now_J  ] = 0;
				now_J--;
				break;
			case 30:
				map[now_I][now_J-1] = false;
				map[now_I][now_J  ] = false;
				now_map[now_I][now_J-1] = 1;
				now_map[now_I][now_J  ] = 0;
				now_J--;
				Hp1+=30;
				break;
			case 31:
				map[now_I][now_J-1] = false;
				map[now_I][now_J  ] = false;
				now_map[now_I][now_J-1] = 1;
				now_map[now_I][now_J  ] = 0;
				now_J--;
				Sword = true;
                Attack1+=10;
				break;
			case 32:
				map[now_I][now_J-1] = false;
				map[now_I][now_J  ] = false;
				now_map[now_I][now_J-1] = 1;
				now_map[now_I][now_J  ] = 0;
				now_J--;
                Attack1+=3;
				break;
			case 33:
				map[now_I][now_J-1] = false;
				map[now_I][now_J  ] = false;
				now_map[now_I][now_J-1] = 1;
				now_map[now_I][now_J  ] = 0;
				now_J--;
                Defend1+=8;
				break;
			case 35:
				map[now_I][now_J-1] = false;
				map[now_I][now_J  ] = false;
				now_map[now_I][now_J-1] = 1;
				now_map[now_I][now_J  ] = 0;
				now_J--;
                Books = true;
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
	}£»
	if (ch == 'd'){
		switch (now_map[now_I][now_J+1]){
			case 1,2:
				map[now_I][now_J+1] = false;
				map[now_I][now_J  ] = false;
				now_map[now_I][now_J+1] = 1;
				now_map[now_I][now_J  ] = 0;
				now_J++;
				break;
			case 3:
				if (key_num_yellow > 0)
				{
					key_num_yellow--;
					map[now_I][now_J+1] = false;
					map[now_I][now_J  ] = false;
					now_map[now_I][now_J+1] = 1;
					now_map[now_I][now_J  ] = 0;
					now_J++;
				}
				break;
			case 4:
				if (key_num_blue > 0)
				{
					key_num_blue--;
					map[now_I][now_J+1] = false;
					map[now_I][now_J  ] = false;
					now_map[now_I][now_J+1] = 1;
					now_map[now_I][now_J  ] = 0;
					now_J++;
				}
				break;
			case 5:
				if (key_num_red > 0)
				{
					key_num_red--;
					map[now_I][now_J+1] = false;
					map[now_I][now_J  ] = false;
					now_map[now_I][now_J+1] = 1;
					now_map[now_I][now_J  ] = 0;
					now_J++;
				}
				break;
			case 6:
				key_num_yellow++;
				map[now_I][now_J+1] = false;
				map[now_I][now_J  ] = false;
				now_map[now_I][now_J+1] = 1;
				now_map[now_I][now_J  ] = 0;
				now_J++;
				break;
			case 7:
				key_num_blue++;
				map[now_I][now_J+1] = false;
				map[now_I][now_J  ] = false;
				now_map[now_I][now_J+1] = 1;
				now_map[now_I][now_J  ] = 0;
				now_J++;
				break;
			case 8:
				key_num_red++;
				map[now_I][now_J+1] = false;
				map[now_I][now_J  ] = false;
				now_map[now_I][now_J+1] = 1;
				now_map[now_I][now_J  ] = 0;
				now_J++;
				break;
			case 11,12,13,14,15,16,17:
				map[now_I][now_J+1] = false;
				map[now_I][now_J  ] = false;
                fighting(now_map[now_I][now_J+1]);
				now_map[now_I][now_J+1] = 1;
				now_map[now_I][now_J  ] = 0;
				now_J++;
				break;
			case 30:
				map[now_I][now_J+1] = false;
				map[now_I][now_J  ] = false;
				now_map[now_I][now_J+1] = 1;
				now_map[now_I][now_J  ] = 0;
				now_J++;
				Hp1+=30;
				break;
			case 31:
				map[now_I][now_J+1] = false;
				map[now_I][now_J  ] = false;
				now_map[now_I][now_J+1] = 1;
				now_map[now_I][now_J  ] = 0;
				now_J++;
				Sword = true;
                Attack1+=10;
				break;
			case 32:
				map[now_I][now_J+1] = false;
				map[now_I][now_J  ] = false;
				now_map[now_I][now_J+1] = 1;
				now_map[now_I][now_J  ] = 0;
				now_J++;
                Attack1+=3;
				break;
			case 33:
				map[now_I][now_J+1] = false;
				map[now_I][now_J  ] = false;
				now_map[now_I][now_J+1] = 1;
				now_map[now_I][now_J  ] = 0;
				now_J++;
                Defend1+=8;
				break;
			case 35:
				map[now_I][now_J+1] = false;
				map[now_I][now_J  ] = false;
				now_map[now_I][now_J+1] = 1;
				now_map[now_I][now_J  ] = 0;
				now_J++;
                Books = true;
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
	for (int i=1; i<=14; i++)
		for (int j=1; j<=14; j++)
			if (!map[i][j]){
				switch (now_map[i][j]){
					case 0:
						gotoxy(j*5,i*3  );	printf('     ');
						gotoxy(j*5,i*3+1);	printf('     ');
						gotoxy(j*5,i*3+2);	printf('     ');
						break;
					case 1:
						textcolor(yellow);
						gotoxy(j*5,i*3  );	printf(' ^^^ ');
						gotoxy(j*5,i*3+1);	printf('|o o|');
						gotoxy(j*5,i*3+2);	printf('\_v_/');
						break;
					case 2:
						textcolor(white);
						gotoxy(j*5,i*3  );	printf('#####');
						gotoxy(j*5,i*3+1);	printf('#####');
						gotoxy(j*5,i*3+2);	printf('#####');
						break;
					case 3,4,5:
						if (now_map[i][j] == 3) textcolor(yellow);
							else if (now_map[i][j] == 4) textcolor(123);
								else if (now_map[i][j] == 5) textcolor(red); 
						gotoxy(j*5,i*3  );	printf(' --- ');
						gotoxy(j*5,i*3+1);	printf('/***\');
						gotoxy(j*5,i*3+2);	printf('|***|');
						break;
					case 6,7,8:
						if (now_map[i][j] == 6) textcolor(yellow);
							else if (now_map[i][j] == 7) textcolor(123);
								else if (now_map[i][j] == 8) textcolor(red); 
						gotoxy(j*5,i*3  );	printf(' {O} ');
						gotoxy(j*5,i*3+1);	printf('  H  ');
						gotoxy(j*5,i*3+2);	printf('  F  ');
						break;
					case 11:
						textcolor(5);
						gotoxy(j*5,i*3  );	printf(' --- ');
						gotoxy(j*5,i*3+1);	printf('|o o|');
						gotoxy(j*5,i*3+2);	printf('|___|');
						break;
					case 12:
						textcolor(5);
						gotoxy(j*5,i*3  );	printf(' --- ');
						gotoxy(j*5,i*3+1);	printf('|o o|');
						gotoxy(j*5,i*3+2);	printf('\_o_/');
						break;
					case 13:
						textcolor(5);
						gotoxy(j*5,i*3  );	printf(' === ');
						gotoxy(j*5,i*3+1);	printf('(o o)');
						gotoxy(j*5,i*3+2);	printf('\_^_/');
						break;
					case 14:
						textcolor(5);
						gotoxy(j*5,i*3  );	printf('/---\');
						gotoxy(j*5,i*3+1);	printf('|o o|');
						gotoxy(j*5,i*3+2);	printf('v^^^v');
						break;
					case 15:
						textcolor(5);
						gotoxy(j*5,i*3  );	printf(' \^/ ');
						gotoxy(j*5,i*3+1);	printf('<o o>');
						gotoxy(j*5,i*3+2);	printf('V\x/V');
						break;
					case 16:
						textcolor(5);
						gotoxy(j*5,i*3  );	printf('UUUUU');
						gotoxy(j*5,i*3+1);	printf('|o o|');
						gotoxy(j*5,i*3+2);	printf('-----');
						break;
					case 17:
						textcolor(5);
						gotoxy(j*5,i*3  );	printf('Y M Y');
						gotoxy(j*5,i*3+1);	printf('[o o]');
						gotoxy(j*5,i*3+2);	printf('XXXXX');
						break;
					case 30:
						textcolor(green);
						gotoxy(j*5,i*3  );	printf(' || H');
						gotoxy(j*5,i*3+1);	printf('/==\ ');
						gotoxy(j*5,i*3+2);	printf('\==/ ');
						break;
					case 31:
						textcolor(green);
						gotoxy(j*5,i*3  );	printf(' A  G');
						gotoxy(j*5,i*3+1);	printf(' H  +');
						gotoxy(j*5,i*3+2);	printf('<H> +');
						break;
					case 32:
						textcolor(green);
						gotoxy(j*5,i*3  );	printf('     ');
						gotoxy(j*5,i*3+1);	printf('     ');
						gotoxy(j*5,i*3+2);	printf(' +3  ');
						break;
					case 33:
						textcolor(green);
						gotoxy(j*5,i*3  );	printf('___ F');
						gotoxy(j*5,i*3+1);	printf('|x| +');
						gotoxy(j*5,i*3+2);	printf('\_/ +');
						break;
					case 35:
						textcolor(green);
						gotoxy(j*5,i*3  );	printf('c===c ');
						gotoxy(j*5,i*3+1);	printf('c   |');
						gotoxy(j*5,i*3+2);	printf('c___|');
						break;
					case 50:
						textcolor(green);
						gotoxy(j*5,i*3  );	printf('/====');
						gotoxy(j*5,i*3+1);	printf('|shop');
						gotoxy(j*5,i*3+2);	printf('|____');
						break;
					case 51:
						textcolor(green);
						gotoxy(j*5,i*3  );	printf('=====');
						gotoxy(j*5,i*3+1);	printf(' ___ ');
						gotoxy(j*5,i*3+2);	printf('|___|');
						break;
					case 52:
						textcolor(green);
						gotoxy(j*5,i*3  );	printf('====\');
						gotoxy(j*5,i*3+1);	printf('shop|');
						gotoxy(j*5,i*3+2);	printf('____|');
						break;
					case 80:
						textcolor(red);
						gotoxy(j*5,i*3  );	printf('^ ^ ^');
						gotoxy(j*5,i*3+1);	printf('| | |');
						gotoxy(j*5,i*3+2);	printf('| | |');
						break; 
					case 90:
						textcolor(red)
						gotoxy(j*5,i*3  );	printf('| | |');
						gotoxy(j*5,i*3+1);	printf('| | |');
						gotoxy(j*5,i*3+2);	printf('v v v');
				}
			}
	memset(map,true,sizeof(map));
} 

void quit(void)
{
	for (int i=1; i<=14; i++)
		for (int j=1; j<=14; j++)
			map[i][j] = false;
	clrscr();
	print;
}

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <getch.h>

//	定义棋盘
char board[15][15];

//	定义下棋坐标
char key_x = 7,key_y = 7;

//	定义棋子角色
char role = '@';

//	初始化棋盘
void init_board(void)
{
	for(int x = 0; x<15; x++)
	{
		for(int y = 0; y<15; y++)
		{
			board[x][y] = '*';	
		}
	}
}

//	显示棋盘
void show_board(void)
{
	system("clear");
	for(int x = 0; x<15; x++)
	{
		for(int y = 0; y<15; y++)
		{
			printf(" %c",board[x][y]);	
		}
		printf("\n");
	}
}

//	落子
void get_key(void)
{
	printf("请%c下棋\n",role);
	while(1)
	{
		printf("\33[%hhd;%hhdH",key_x+1,(key_y+1)*2);	
		switch(getch())
		{
			case 183:	key_x>0 && key_x--; 	break;
			case 184:	key_x<14 && key_x++;	break;
			case 185:	key_y<14 && key_y++;	break;
			case 186:	key_y>0	&& key_y--;		break;
			case 10:	
				if('*' == board[key_x][key_y])
				{
					board[key_x][key_y] = role;
					return;
				}
		}
	}
}
//	检查某个方向上有几个相同的棋子
int check_key(int ox,int oy)
{
	int count = 0;
	for(int x=key_x+ox,y=key_y+oy;
			x>=0 && x<15 && y>=0 && y<15; x+=ox,y+=oy)
	{
		if(board[x][y] == board[key_x][key_y])
		{
			count++;	
		}
		else
		{
			break;	
		}
	}
	return count;
}

//	检查是否五子连珠
bool is_win(void)
{
	if(check_key(0,-1)+check_key(0,1) >= 4)
		return true;
	if(check_key(-1,0)+check_key(1,0) >= 4)
		return true;
	if(check_key(-1,-1)+check_key(1,1) >= 4)
		return true;
	if(check_key(-1,1)+check_key(1,-1) >= 4)
		return true;
	return false;
}
int main(int argc,const char* argv[])
{
	init_board();

	for(int i=0;i<225;i++)
	{
		show_board();

		get_key();

		if(is_win())
		{
			show_board();
			printf("恭喜%c胜利!\n",role);
			return 0;
		}
		//	交换角色
		role = role == '@'?'$':'@';
		/*
		if('@' == role)
			r(le = '$';	
		else
			role = '@';
			*/
	}
	printf("平局，你俩真棒！\n");
	return 0;
}








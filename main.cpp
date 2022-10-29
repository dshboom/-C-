#include<graphics.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

int Map[3][3];// 0为空白 1为人 2为ai
int x = 1;
IMAGE imgAi,imgMan;

#define interfaceWidth 1071
#define interfaceHigth 675
#define width 600
#define highth 600

int gameInit();
void setting();
void play();
void fristMenu();
void secondMenu();
int manGo(MOUSEMSG *msg);
void aiGo();
int windecide();
void winsay(int win);

int main()
{
	int t,win,choose=1;
	///choose = gameInit();
	if(1 == choose)
	{
		play();
		// 游戏的初始化
		while(1)// 游戏主体循环
		{
			// 人-先下棋
			// 获取鼠标点击
			// 阻塞式(eg.没有鼠标消息时一直等待)
			label:
			MOUSEMSG msg = GetMouseMsg();
			if(msg.uMsg == WM_LBUTTONDOWN)// 鼠标左键按下
			{
				// 人下棋
				t = manGo(&msg);
				while(t != 0)
				{
					goto label;
				}
				win = windecide();
				winsay(win);
				Sleep(200);
				aiGo();
				win = windecide();
				winsay(win);
			}
		}
	}
	system("pause");
		return 0;
}

/*int gameInit()
{
	MOUSEMSG msg;
	int t = 1;
	initgraph(interfaceWidth,interfaceHigth);
	loadimage(0,"res/mainInterface.jpg");
	label1:
	msg = GetMouseMsg();
	if(msg.uMsg == WM_LBUTTONDOWN)
	{
		closegraph();
		exit(0);
		if(msg.x >= 436 && msg.x <= 642 && msg.y <= 338 && msg.y >= 278)
		{
			t = 0;
			return 1;
		}
		else if(msg.x >= 436 && msg.x <= 642 && msg.y <= 439 && msg.y >= 379)
		{
			t = 0;
			return 2;
		}
		else if(msg.x >= 436 && msg.x <= 642 && msg.y <= 530 && msg.y >= 430)
		{
			t = 0;
			closegraph();
			exit(0);
			return 0;
		}
		while(t != 0)
		{
			goto label1;
		}
	}
}
*/
void play()
{
	// 1.创建游戏窗口
	initgraph(width,highth);
	// 2.显示背景图片
	loadimage(0,"res/chessBoard.jpg");
	// 3.加载棋子图片
	loadimage(&imgMan,"res/man.jpg");
	loadimage(&imgAi,"res/ai.jpg");
	memset(Map,0,sizeof(Map));
}

int manGo(MOUSEMSG *msg)
{
	int col = msg->x / 200;
	int row = msg->y / 200;
	if(Map[col][row] == 0)
	{
		Map[col][row] = 1;
		putimage(col*200+25,row*200+25,&imgMan);
		return 0;
	}
	return 1;
}

void aiGo()
{
	Sleep(100);
	srand(NULL);
    int row_rand = -1;
    int col_rand = -1;
    if(1==x)
    {
        while (Map[row_rand = rand()%3][col_rand = rand()%3] != 0);
    }
    else if(2==x)
    {
        int i;
        for(i = 0;i<3;i++)
        {
            if((Map[i][0] == Map[i][1])&&Map[i][1] == 0)
            {
                row_rand = i;
                col_rand = 2;
            }
            else if((Map[0][i] == Map[1][i])&&Map[i][1] == 1)
            {
                row_rand = 2;
                col_rand = i;
            }
            else if((Map[1][i] == Map[2][i])&&Map[i][1] == 1)
            {
                row_rand = 0;
                col_rand = i;
            }
            else if((Map[i][1] == Map[i][2])&&Map[i][1] == 1)
            {
                row_rand = i;
                col_rand = 0;
            }
        }
        if((Map[0][0] == Map[1][1])&&(Map[1][1] == 1))
        {
            row_rand = 2;
            col_rand = 2;
        }
        else if((Map[2][0] == Map[1][1])&&(Map[1][1] == 1))
        {
            row_rand = 0;
            col_rand = 2;
        }
        else if((Map[0][2] == Map[1][1])&&(Map[1][1] == 1))
        {
            row_rand = 2;
            col_rand = 0;
        }
        else if((Map[2][2] == Map[1][1])&&(Map[1][1] == 1))
        {
            row_rand = 0;
            col_rand = 0;
        }
        if(Map[row_rand][col_rand] != 0)
        {
            row_rand = -1;
            col_rand = -1;
            do
            {
                srand(time(NULL));
                row_rand = rand() % 3;
                col_rand = rand() % 3;
            } 
            while (Map[row_rand][col_rand] != 0 && row_rand>=0 &&col_rand>=0);
        }
    }
    else if(3==x)
    {
        int i;
        for(i = 0;i<3;i++)
        {
            if((Map[i][0] == Map[i][1])&&Map[i][2] == 0)
            {
                row_rand = i;
                col_rand = 2;
            }
            else if(Map[0][i] == Map[1][i]&&Map[2][i] == 0)
            {
                row_rand = 2;
                col_rand = i;
            }
            else if((Map[1][i] == Map[2][i])&&Map[0][i] == 0)
            {
                row_rand = 0;
                col_rand = i;
            }
            else if((Map[i][1] == Map[i][2])&&Map[i][0] == 0)
            {
                row_rand = i;
                col_rand = 0;
            }
        }
        if((Map[0][0] == Map[1][1])&&(Map[2][2] == 0))
        {
            row_rand = 2;
            col_rand = 2;
        }
        else if((Map[2][0] == Map[1][1])&&(Map[0][2] == 0))
        {
            row_rand = 0;
            col_rand = 2;
        }
        else if((Map[0][2] == Map[1][1])&&(Map[2][0] == 0))
        {
            row_rand = 2;
            col_rand = 0;
        }
        else if((Map[2][2] == Map[1][1])&&(Map[0][0] == 0))
        {
            row_rand = 0;
            col_rand = 0;
        }
        if(Map[row_rand][col_rand] != 0)
        {
            row_rand = -1;
            col_rand = -1;
            do
            {
                srand(time(NULL));
                row_rand = rand() % 3;
                col_rand = rand() % 3;
            } 
            while (Map[row_rand][col_rand] != 0 && row_rand>=0 &&col_rand>=0);
        }
    }
    Map[row_rand][col_rand] = 2;
	putimage(row_rand*200+25,col_rand*200+25,&imgAi);
}

int windecide()
{
    int i;
    int k,l;
    int p = 0;
    for(k = 0;k < 3;k++)
    {
        for(l = 0;l < 3;l++)
        {
            if(Map[k][l] != 0)
            {
                p++;
            }
        }
    }
    if(p > 0)
    {
        for(i = 0;i<3;i++)
        {
            if((Map[i][0] == Map[i][1])&&(Map[i][1] == Map[i][2]))
            {
                if(Map[i][1] == 1)
                {
                    return 1;
                }
                else if(Map[i][1] == 2)
                {
                    return 2;
                }
            }
            else if((Map[0][i] == Map[1][i])&&(Map[1][i] == Map[2][i]))
            {
                if(Map[0][i] == 1)
                {
                    return 1;
                }
                else if(Map[0][i] == 2)
                {
                    return 2;
                }
            }
        }
        if((Map[0][0] == Map[1][1])&&(Map[1][1] == Map[2][2]))
        {
            if(Map[1][1] == 1)
            {
                return 1;
            }
            else if(Map[1][1] == 2)
            {
                return 2;
            }
        }
        else if((Map[2][0] == Map[1][1])&&(Map[1][1] == Map[0][2]))
        {
            if(Map[2][0] == 1)
            {
                return 1;
            }
            else if(Map[2][0] == 2)
            {
                return 2;
            }
        }
		else if(9==p)
		{
			return 3;
		}
    }
    else
    {
        return 0;
    }
    return 0;
}

void winsay(int win)
{
			if(1 == win)
			{
				MessageBox(NULL,"你胜利了!","游戏结束",MB_OK);
				closegraph();
				exit(0);
			}
			else if(2 == win)
			{
				MessageBox(NULL,"AI胜利!","游戏结束",MB_OK);
				closegraph();
				exit(0);
			}
			else if(3 == win)
			{
				MessageBox(NULL,"和棋了!","游戏结束",MB_OK);
				closegraph();
				exit(0);
			}
}
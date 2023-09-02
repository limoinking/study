#include "Settings.h"
//打印棋盘界面
void ShowGame()
{
	//这个就是用来打印棋盘界面的
	//由于
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			if (honeycomb[i][j] == '0')
			{
				if(player[sx[curpoint]][sy[curpoint]] == 0)
					printf("\033[;31m%d\033[0m", player[sx[curpoint]][sy[curpoint]]);
				else
				{
					printf("\033[;36m%d\033[0m", player[sx[curpoint]][sy[curpoint]]);
				}
				curpoint++;
			}

			else
			{
				printf("%c", honeycomb[i][j]);
			}
		}
		printf("\n");
	}
	curpoint = 0;//重新定向值
}

void ShowAnswer()
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			if (honeycomb[i][j] == '0')
			{
				printf("\033[;32m%d\033[0m", player[sx[curpoint]][sy[curpoint]]);
				curpoint++;
			}

			else
			{
				printf("%c", honeycomb[i][j]);
			}
		}
		printf("\n");
	}
	curpoint = 0;//重新定向值
}
int min(int a, int b)
{
	return (a > b) ? b : a;
}
int max(int a, int b)
{
	return (a > b) ? a : b;
}

void Initlines()//该函数的意思是，通过将二维坐标转换为某一行，比如，11对应主对角线第5行，这个不用管
{
	//InitBool();//貌似可以优化掉？
	int inm[10] = { 0,51,41,31,21,11,12,13,14,15 };

	for (int i = 1; i <= 9; i++)
	{
		int num = 1;
		tlm[inm[i]] = i;
		tlmpos[i][num++] = inm[i];
		//下面开始进入正式阶段
		int delta = 0;
		if (inm[i] / 10 < 5)
		{
			delta = 11;
		}
		else
		{
			delta = 10;
		}
		int cur = inm[i] + delta;
		for (int j = 2; j <= linenums[i]; j++)
		{
			tlm[cur] = i;
			tlmpos[i][num++] = cur;
			if (cur / 10 < 5)
			{
				delta = 11;
			}
			else
			{
				delta = 10;
			}
			cur += delta;
		}
	}
	//主对角线完了，现在开始副对角线
	int inv[10] = { 0,11,12,13,14,15,26,37,48,59 };
	for (int i = 1; i <= 9; i++)
	{
		int num = 1;
		tlv[inv[i]] = i;
		tlvpos[i][num++] = inv[i];
		int delta = 0;
		if (inv[i] / 10 < 5)
		{
			delta = 10;
		}
		else
		{
			delta = 9;
		}
		int cur = inv[i] + delta;
		for (int j = 2; j <= linenums[i]; j++)
		{
			tlv[cur] = i;
			tlvpos[i][num++] = cur;
			if (cur / 10 < 5)
			{
				delta = 10;
			}
			else
			{
				delta = 9;
			}
			cur += delta;
		}
	}
	return;
}



bool judgeone(int i, int curmain, int curvice, int temp)
{
	//先处理第一行
	int minl = temp;
	int maxl = temp;
	for (int j = 1; j <= 9; j++)
	{
		if (ml[i][j] == 1)
		{
			minl = min(minl, j);
			maxl = max(maxl, j);
		}
	}
	if (maxl - minl >= linenums[i])
	{
		return 0;
	}

	minl = temp;
	maxl = temp;
	for (int j = 1; j <= 9; j++)
	{
		if (mm[curmain][j] == 1)
		{
			minl = min(minl, j);
			maxl = max(maxl, j);
		}
	}
	if (maxl - minl >= linenums[curmain])
	{
		return 0;
	}

	minl = temp;
	maxl = temp;
	for (int j = 1; j <= 9; j++)
	{
		if (mv[curvice][j] == 1)
		{
			minl = min(minl, j);
			maxl = max(maxl, j);
		}
	}
	if (maxl - minl >= linenums[curvice])
	{
		return 0;
	}
	if (ml[i][temp] != 0 || mm[curmain][temp] != 0
		|| mv[curvice][temp] != 0)
		return 0;
	return 1;
}

void ReSave(int save[][10], int f[][10])
{
	for (int i = 0; i <= 60; i++)
	{
		int x = sx[i];
		int y = sy[i];
		save[x][y] = f[x][y];
	}
}


int flag1 = 0;
int count = 0;
void CreatBoard(int f[][10], int i, int j)
{
	//Initlines();
	//srand(time(0));//随机化种子
	//这些放到主程序里面了
	//这些是初步准备
	if (flag1 == 1)
		return;
	//用来判断是否已经尝试过了所有的可能性
	if (j > linenums[i])
	{
		j = 1, i += 1;
	}
	if (i > 9)
	{
		return;
	}

	while (player[i][j] != 0)//注意，这个是全局变量
	{
		j += 1;
		if (j > linenums[i])
		{
			j = 1, i += 1;
		}
		if (i > 9)
		{
			flag1 = 1;
			ReSave(SaveSu, f);
			return;
		}
		if (flag1 == 1)
			return;
	}
	int curpos = i * 10 + j;//转为2位置坐标
	int curmain = tlm[curpos];
	int curvice = tlv[curpos];


	int temp = 0;
	for (int q = 1; q <= 9; q++)
	{
		if (flag1 == 1)
			return;

		temp = q;
		/*if (player[i][j] != 0)
		{
			j += 1;
			if (flag1 == 1)
				return;
			break;
		}*/
		if (judgeone(i, curmain, curvice, temp))//前三个是范围判断，后三个是判断是否冲突
		{
			f[i][j] = temp;
			if (i == 9 && j == 5)
			{
				ReSave(SaveSu, f);
				flag1 = 1;
			}
			if (flag1 == 1)
				return;
			/*printf("%d:", count);
			printf("%d %d %d\n", i, j, temp);

			count++;
			if (count % 1440 == 0)
			{
				printf("%d pause\n", count);
				printf("----------\n");
			}*/
			ml[i][temp] = 1;
			mm[curmain][temp] = 1;
			mv[curvice][temp] = 1;




			CreatBoard(f, i, j + 1);//继续搜索
			if (flag1 == 1)
				return;
			if (player[i][j]);//回溯的时候处理的
			else
			{
				f[i][j] = 0;
			}

			ml[i][temp] = 0;//回溯过程
			mm[curmain][temp] = 0;
			mv[curvice][temp] = 0;
		}
	}
	return;

}
void CheckBoard(int f[][10], int player[][10], int i, int j)//一定要在函数内部引用
{
	// Initlines();
	//srand(time(0));//随机化种子
	//这些放到主程序里面了
	//这些是初步准备
	//用来判断是否已经尝试过了所有的可能性
	if (checkflag == 2)
		return;
	if (j > linenums[i])
	{
		j = 1, i += 1;
	}
	if (i > 9)
	{
		return;
	}

	while (player[i][j] != 0)//注意，这个是全局变量
	{
		j += 1;
		if (j > linenums[i])
		{
			j = 1, i += 1;
		}
		if (i > 9)
		{
			return;
		}
		if (checkflag == 1)
			return;
	}
	int curpos = i * 10 + j;//转为2位置坐标
	int curmain = tlm[curpos];
	int curvice = tlv[curpos];


	int temp = 0;
	for (int q = 1; q <= 9; q++)
	{
		if (checkflag == 2)
			return;
		temp = q;
		/*if (player[i][j] != 0)
		{
			j += 1;
			break;
		}*/
		if (judgeone(i, curmain, curvice, temp))//前三个是范围判断，后三个是判断是否冲突
		{
			if (i == 9)
				f[i][j] = temp;
			if (i == 9 && j == 5)
			{
				checkflag += 1;
			}
			if (checkflag == 2)
				return;
			/*printf("%d:", count);
			printf("%d %d %d\n", i, j, temp);

			count++;
			if (count % 1440 == 0)
			{
				printf("%d pause\n", count);
				printf("----------\n");
			}*/

			ml[i][temp] = 1;
			mm[curmain][temp] = 1;
			mv[curvice][temp] = 1;




			CheckBoard(f, player, i, j + 1);//继续搜索
			if (checkflag == 2)
				return;
			if (player[i][j]);
			else
			{
				f[i][j] = 0;
			}

			ml[i][temp] = 0;//回溯过程
			mm[curmain][temp] = 0;
			mv[curvice][temp] = 0;
		}
	}
	return;
	//代码逻辑和生成几乎是一样的，但是要检验生成多次的情况
}

void digholes(int f[][10], int player[][10], int nums)//传入数组和挖去洞的数目
{
	memset(MarkDig, 0, sizeof(MarkDig));
	ReSave(player, SaveSu);
	ReSave(f, SaveSu);

	//代码逻辑上，player数组是用来记录当前的生成情况的，所以还是拿f生成
	for (int i = 1; i <= nums; i++)
	{
		//一共要挖去这么多的洞+z
		int dx = rand() % 9 + 1;//生成1 - 9 的数字
		int dy = rand() % linenums[dx] + 1;//保证其不会越界的问题
		if (MarkDig[dx][dy] == 1)
		{
			i--;
			continue;
		}
		MarkDig[dx][dy] = 1;


		//初始化变量有：
		//1.checkflag
		//2.三个方向对于该值的引用
		// 记录最开始的temp值
		//回溯时候要回复的变量
		//1.player = temp
		//2.恢复这三个方向对这个值的引用

		checkflag = 0;//重新初始化

		int curpos = dx * 10 + dy;//转为2位置坐标
		int curmain = tlm[curpos];
		int curvice = tlv[curpos];

		int temp = player[dx][dy];//把初始化的过程也处理掉
		f[dx][dy] = 0;
		player[dx][dy] = 0;//将这个点挖掉

		ml[i][temp] = 0;//
		mm[curmain][temp] = 0;
		mv[curvice][temp] = 0;
		CheckBoard(f, player, dx, dy);
		if (checkflag == 1)
		{
			ml[i][temp] = 1;//
			mm[curmain][temp] = 1;
			mv[curvice][temp] = 1;

			player[dx][dy] = temp;//回复其原来的值
			f[dx][dy] = temp;
		}

	}
	//为了检验每次挖洞之后的逻辑是否正确，需要外置一个checkboard函数，作用见上


}


bool CreateSuCNF(int player[][10], char FileName[],int holes)//这里的函数，可以先不设置挖洞的数目，因为难度和挖洞数目其实关系不大
//因为标准个数是定的
{

	int AT[100] = {};
	for (int i = 0; i <= 60; i++)
	{
		int dx = sx[i];
		int dy = sy[i];
		int cur = dx * 10 + dy;
		AT[cur] = i;
	}//减少变元数目

	bool NotEmpty[11][11];//用来标记这个点不是空的
	FILE* fp = fopen(FileName, "w");
	if (!fp)
		exit(ERROR);
	fprintf(fp, "p cnf 609 %d\n", 7479 + 50 - holes);//这是读取数据之后得到的
	//为了方便输入，选用打表策略,并且减少循环变量使用
	//注意有  tn[1,5][0,1] hn[1,5][1,9] sn[1,5][1,10][0,1]
	int tn[6][2] = { {},{1,10},{3,6},{5,3},{7,1},{9,0} };//targetnums,记录约束中 0.有几个必填的，1.有几种选填的策略
	int hn[6][10] = { {},{0,5},{0,4,5,6},{0,3,4,5,6,7},{0,2,3,4,5,6,7,8},{0,1,2,3,4,5,6,7,8,9} };//havenums，记录这一行中必填的有哪些
	int sn[6][11][2] =
	{ {},
		{{}, {1,6},{2,6},{2,7},{3,6},{3,7},{3,8},{4,6},{4,7},{4,8},{4,9}},
		{{},{1,7},{2,7},{2,8},{3,7},{3,8},{3,9} },
		{{},{1,8},{2,8},{2,9}},
		{{},{1,9}},
		{}
	};
	//selectnums，记录选填的部分1
//part1提示单子句和格子约束部分，方便起见，将主副对角线的也同时完成了
//单子句提示
	for (int i = 1; i <= 9; i++)
	{
		for (int j = 1; j <= linenums[i]; j++)
		{
			if (player[i][j] != 0)
			{
				fprintf(fp, "%d 0\n", AT[i * 10 + j] * 10 + player[i][j]);//AT[i * 10 + j] * 10
				NotEmpty[i][j] = 1;
			}
		}
	}

	//每一行,和两条对角线情况是重复的，不必重复写
	for (int i = 1; i <= 9; i++)
	{
		for (int j = 1; j <= linenums[i]; j++)
		{
			for (int k = 1; k <= 9; k++)
			{
				fprintf(fp, "%d ", AT[i * 10 + j] * 10 + k);
			}
			fprintf(fp, "0\n");
		}
	}

	for (int i = 1; i <= 9; i++)
	{
		for (int j = 1; j <= linenums[i]; j++)
		{
			for (int j1 = 1; j1 <= 8; j1++)
			{
				for (int j2 = j1 + 1; j2 <= 9; j2++)
				{
					fprintf(fp, "%d ", -(AT[i * 10 + j] * 10 + j1));
					fprintf(fp, "%d 0\n", -(AT[i * 10 + j] * 10 + j2));
				}
			}


		}

	}

	//end部分

	//part2线约束
	for (int i = 1; i <= 9; i++)//从第一行开始枚举
	{

		int cl = 0;//curline，用于转化问题
		if (i > 5)
		{
			cl = 9 - i + 1;
		}
		else
		{
			cl = i;
		}


		//每一行的部分，线约束
		int tt = tn[cl][0], ts = tn[cl][1];//targettarget,targetselect


		for (int k = 1; k <= tt; k++)
		{
			for (int j = 1; j <= linenums[i]; j++)
			{

				fprintf(fp, "%d ", AT[i * 10 + j] * 10 + hn[cl][k]);//必填
			}
			fprintf(fp, "0\n");
		}



		if (ts != 0)//如果这一行没有数，那就不用管
		{
			for (int k = 1; k <= ts; k++)
			{
				for (int j = 1; j <= linenums[i]; j++)
					fprintf(fp, "%d ", AT[i * 10 + j] * 10 + sn[cl][k][0]);
				for (int j = 1; j <= linenums[i]; j++)
					fprintf(fp, "%d ", AT[i * 10 + j] * 10 + sn[cl][k][1]);
				fprintf(fp, "0\n");
			}

		}


		for (int cnum = 1; cnum <= 9; cnum++)
		{
			for (int j1 = 1; j1 <= linenums[i] - 1; j1++)
			{
				for (int j2 = j1 + 1; j2 <= linenums[i]; j2++)
				{
					fprintf(fp, "%d ", -(AT[i * 10 + j1] * 10 + cnum));
					fprintf(fp, "%d 0\n", -(AT[i * 10 + j2] * 10 + cnum));
				}
			}
		}


		//注意，真实的对角线上的值还是i,cl只是为了简单而进行变化的数组
		//这是每一个对角线上的值

		for (int k = 1; k <= tt; k++)
		{
			for (int j = 1; j <= linenums[i]; j++)
			{
				fprintf(fp, "%d ", AT[tlmpos[i][j]] * 10 + hn[cl][k]);
			}
			fprintf(fp, "0\n");
		}

		if (ts != 0)//如果这一行没有数，那就不用管
		{
			for (int k = 1; k <= ts; k++)
			{
				for (int j = 1; j <= linenums[i]; j++)
					fprintf(fp, "%d ", AT[tlmpos[i][j]] * 10 + sn[cl][k][0]);
				for (int j = 1; j <= linenums[i]; j++)
					fprintf(fp, "%d ", AT[tlmpos[i][j]] * 10 + sn[cl][k][1]);
				fprintf(fp, "0\n");
			}

		}

		for (int cnum = 1; cnum <= 9; cnum++)
		{
			for (int j1 = 1; j1 <= linenums[i] - 1; j1++)
			{
				for (int j2 = j1 + 1; j2 <= linenums[i]; j2++)
				{
					fprintf(fp, "%d ", -(AT[tlmpos[i][j1]] * 10 + cnum));
					fprintf(fp, "%d 0\n", -(AT[tlmpos[i][j2]] * 10 + cnum));
				}
			}
		}



		//下面这里是斜对角线上的值

		for (int k = 1; k <= tt; k++)
		{
			for (int j = 1; j <= linenums[i]; j++)
			{
				fprintf(fp, "%d ", AT[tlvpos[i][j]] * 10 + hn[cl][k]);
			}
			fprintf(fp, "0\n");
		}


		if (ts != 0)//如果这一行没有数，那就不用管
		{
			for (int k = 1; k <= ts; k++)
			{
				for (int j = 1; j <= linenums[i]; j++)
					fprintf(fp, "%d ", AT[tlvpos[i][j]] * 10 + sn[cl][k][0]);
				for (int j = 1; j <= linenums[i]; j++)
					fprintf(fp, "%d ", AT[tlvpos[i][j]] * 10 + sn[cl][k][1]);
				fprintf(fp, "0\n");
			}

		}

		for (int cnum = 1; cnum <= 9; cnum++)
		{
			for (int j1 = 1; j1 <= linenums[i] - 1; j1++)
			{
				for (int j2 = j1 + 1; j2 <= linenums[i]; j2++)
				{
					fprintf(fp, "%d ", -(AT[tlvpos[i][j1]] * 10 + cnum));
					fprintf(fp, "%d 0\n", -(AT[tlvpos[i][j2]] * 10 + cnum));
				}
			}
		}

	}
	fclose(fp);
	return OK;


}








//void InitPlayer()//后序将所有的最大最小值全放入到里面
//{
//	memset(player, -1, sizeof(player));//将其初始化为-1，来做到预处理边界
//	memset(f, -1, sizeof(f));
//}




//保存数独计算状态
status SaveSudokuFile(int re, char FileName[], int holes, double times)
{
	int x;
	for (int i = 0; FileName[i] != '\n'; i++) {
		if (FileName[i] == '.') {
			FileName[i + 1] = 'r';
			FileName[i + 2] = 'e';
			FileName[i + 3] = 's';
			break;
		}
	}

	FILE* fp;
	fp = fopen(FileName, "w");
	if (!fp) exit(-1);
	if (re == TRUE)
	{//如果re==TRUE，则将数独求解结果输入到文件中 
		fprintf(fp, "s 1\n");
		fprintf(fp, "v ");
		fprintf(stdout, "s 1\n");
		fprintf(stdout, "v ");
		for (int j = 1; j <= 610; j++)
		{
			if (counter[j].value == 1)
			{
				fprintf(fp, "%d ", j);
				fprintf(stdout, "%d ", j);
				int k = j % 10;
				int cur = j / 10;
				int dx = sx[cur];
				int dy = sy[cur];
				player[dx][dy] = k;
			}
			
		}
		SolveTotal = holes;
		fprintf(fp, "\n");
		fprintf(stdout, "\n");
	}
	else
	{
		fprintf(fp, "s 0\n");
		fprintf(stdout, "s 0\n");
	}
	fprintf(fp, "t %fms", times);
	fprintf(stdout, "t %fms", times);
	fclose(fp);
	return 1;
}



void DirectRead(char FileName[])
{
	FILE* fp = fopen(FileName, "r");
	if (fp == NULL)
		exit(-1);
	char ch;
	while ((ch = fgetc(fp)) != '-')
	{
		int i = sx[curpoint];
		int j = sy[curpoint];
		int temp = ch - '0';
		if (temp != 0)
		{
			f[i][j] = ch - '0';
			player[i][j] = ch - '0';
			//两个都读了，用作标记
			int curpos = i * 10 + j;//转为2位置坐标
			int curmain = tlm[curpos];
			int curvice = tlv[curpos];

			ml[i][temp] = 1;
			mm[curmain][temp] = 1;
			mv[curvice][temp] = 1;

		}
		curpoint += 1;
	}
	curpoint = 0;
	fclose(fp);
}

void PlayGame(int SaveSu[][10], int player[][10], int holes)
{
	int curop = 1;

	while (curop)
	{
		system("cls");
		if (SolveTotal == holes)
		{
			printf("数独已经全部解决了，无需后序操作\n");
			ShowAnswer();
			system("pause");
			return;
		}

		ShowGame();
		printf("提示：输入格式为235 0，表示第二行第三个格子填5，0表示终止符号\n");
		printf("如果想要退出的话,请输入0 0\n");
		printf("如果想要答案，请输入1 0\n");
		int axis, aing;//表示轴和末尾
		scanf("%d %d", &axis, &aing);
		if (axis == 0)
		{
			printf("欢迎下次游玩！按任意键返回\n");
			system("pause");
			return;
		}
		else if (axis == 1)
		{
			SolveTotal = holes;
			printf("已经全部解决！，下面是答案！\n");
			ShowAnswer();
			system("pause");
			return;
		}
		else
		{
			int k = axis % 10;
			axis /= 10;
			int y = axis % 10;
			axis /= 10;
			int x = axis % 10;
			axis /= 10;
			if (player[x][y] != 0)
			{
				printf("当前位置已经被填过！\n");
			}
			else if (SaveSu[x][y] != k)
			{
				printf("填的不对，当前位置值应该填 %d\n", SaveSu[x][y]);
			}
			else if (SaveSu[x][y] == k)
			{
				player[x][y] = k;
				printf("正确，结果已经填入！\n");
				SolveTotal += 1;
			}

			system("pause");

		}


	}
}

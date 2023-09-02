#define _CRT_SECURE_NO_WARNINGS
#include "Settings.h"
#include "Dpll.cpp"
#include "FileReader.cpp"
#include "Sudoku.cpp"
int main()
{
	int op = 1, op1 = 1, op2 = 1;
	int flag = 0, flag_sudoku = 0;
	bool judge = 0;
	while (op)
	{
		system("cls");
		printf("请选择功能 ： 1.SAT求解 2.蜂窝数独 0.退出\n");
		scanf("%d", &op);
		memset(counter, 0, sizeof(counter));
		switch (op)
		{
		case 0:
			break;//直接退出系统
		case 1:
			op1 = 1;
			while (op1)
			{
				system("cls");
				printf("请选择SAT功能：\n");
				printf("1：读取CNF\n");
				printf("2：进入求解过程并生成结果\n");
				printf("0：回到菜单\n");
				scanf("%d", &op1);
				switch (op1)
				{
				case 0:break;
				case 1:
					memset(SATFileName, 0, sizeof(SATFileName));
					printf("请输入文件名:\n");
					scanf("%s", SATFileName);//存入全局变量

					//明天这里要做一个释放C中节点的函数

					C = NULL;//首先
					if (ReaderFile(&C, SATFileName) == OK)
					{
						printf("已经读取 %s 文件！\n", SATFileName);
						flag = 1;
						ShowFile(&C);
					}
					else
					{
						printf("读取失败！\n");
					}
					system("pause");
					break;
				case 2:
					clock_t start_time, end_time;//时钟常量
					if (!flag) printf("CNF还未读取！\n");
					else
					{
						printf("请选择启发函数！\n");
						printf("1：JW1 短子句优先\n");
						printf("2：JW2 标准JW方法\n");
						printf("3：JW3 专门处理数独的文件，优先处理负的(不建议)\n");
						printf("4：JW4 最短子句次数最大元\n");
						printf("5. JW5 只处理文字皆为正的元,需要和JW3搭配起来用\n");
						printf("6. JW6 仅寻找出现次数最多的\n" );
						printf("7：普通策略（不建议）\n");
						scanf("%d", &method);
						double total_time;
						start_time = clock();
						int solve = Dpll(&C);
						end_time = clock();
						total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000;//输出的就是以秒为单位的值
						SaveSATFile(solve, total_time, SATFileName);
					}
					system("pause");
					break;
				}
			}
			break;
		case 2:
			op2 = 1;
			while (op2)
			{
				system("cls");
				printf("请选择SUDOKU功能：\n");
				printf("1：生成数独并且转换数独为CNF语句\n");
				printf("2：解数独并保存为res文件\n");
				printf("3：开始玩数独\n");
				printf("0：回到菜单\n");
				scanf("%d", &op2);
				switch (op2)
				{
				case 0:break;
				case 1:
					memset(player, 0, sizeof(player));
					memset(f, 0, sizeof(player));
					printf("请输入数独转为的CNF语句名字\n");
					scanf("%s", SuDokuFileName);
					Initlines();
					printf("请输入你想挖的洞的数目,不能超过50个，不然不能保证唯一解\n");
					scanf("%d", &digholenum);
					srand(time(0));//随机化种子
					DirectRead(FileName);
					CreatBoard(f, 1, 1);
					digholes(f, player, digholenum);//看了一下11个变元可以保证唯一解
					ShowGame();
					CreateSuCNF(player, SuDokuFileName,digholenum);
					flag_sudoku = 1;
					SolveTotal = 0;//初始化为0，重新处理掉
					system("pause");
					break;
				case 2:
					printf("如果15s内没有反应，请关闭程序！\n");
					printf("本程序可能因为数独难度不同，求解时间也不同\n");
					C = NULL;
					method = 6;
					int solve;
					clock_t start_time, end_time;
					double total_time;
					ReaderFile(&C, SuDokuFileName);
					start_time = clock();
					solve = Dpll(&C);
					end_time = clock();
					total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000;//输出的就是以秒为单位的值
					SaveSudokuFile(solve, SuDokuFileName, digholenum,total_time);
					system("pause");
					break;
				case 3:
					PlayGame(SaveSu,player, digholenum);
				}
			}
			break;
		}
			printf("欢迎下次使用本系统！按回车键退出！");
			getchar();
	}

}
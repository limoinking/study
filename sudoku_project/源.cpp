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
		printf("��ѡ���� �� 1.SAT��� 2.�������� 0.�˳�\n");
		scanf("%d", &op);
		memset(counter, 0, sizeof(counter));
		switch (op)
		{
		case 0:
			break;//ֱ���˳�ϵͳ
		case 1:
			op1 = 1;
			while (op1)
			{
				system("cls");
				printf("��ѡ��SAT���ܣ�\n");
				printf("1����ȡCNF\n");
				printf("2�����������̲����ɽ��\n");
				printf("0���ص��˵�\n");
				scanf("%d", &op1);
				switch (op1)
				{
				case 0:break;
				case 1:
					memset(SATFileName, 0, sizeof(SATFileName));
					printf("�������ļ���:\n");
					scanf("%s", SATFileName);//����ȫ�ֱ���

					//��������Ҫ��һ���ͷ�C�нڵ�ĺ���

					C = NULL;//����
					if (ReaderFile(&C, SATFileName) == OK)
					{
						printf("�Ѿ���ȡ %s �ļ���\n", SATFileName);
						flag = 1;
						ShowFile(&C);
					}
					else
					{
						printf("��ȡʧ�ܣ�\n");
					}
					system("pause");
					break;
				case 2:
					clock_t start_time, end_time;//ʱ�ӳ���
					if (!flag) printf("CNF��δ��ȡ��\n");
					else
					{
						printf("��ѡ������������\n");
						printf("1��JW1 ���Ӿ�����\n");
						printf("2��JW2 ��׼JW����\n");
						printf("3��JW3 ר�Ŵ����������ļ������ȴ�����(������)\n");
						printf("4��JW4 ����Ӿ�������Ԫ\n");
						printf("5. JW5 ֻ�������ֽ�Ϊ����Ԫ,��Ҫ��JW3����������\n");
						printf("6. JW6 ��Ѱ�ҳ��ִ�������\n" );
						printf("7����ͨ���ԣ������飩\n");
						scanf("%d", &method);
						double total_time;
						start_time = clock();
						int solve = Dpll(&C);
						end_time = clock();
						total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000;//����ľ�������Ϊ��λ��ֵ
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
				printf("��ѡ��SUDOKU���ܣ�\n");
				printf("1��������������ת������ΪCNF���\n");
				printf("2��������������Ϊres�ļ�\n");
				printf("3����ʼ������\n");
				printf("0���ص��˵�\n");
				scanf("%d", &op2);
				switch (op2)
				{
				case 0:break;
				case 1:
					memset(player, 0, sizeof(player));
					memset(f, 0, sizeof(player));
					printf("����������תΪ��CNF�������\n");
					scanf("%s", SuDokuFileName);
					Initlines();
					printf("�����������ڵĶ�����Ŀ,���ܳ���50������Ȼ���ܱ�֤Ψһ��\n");
					scanf("%d", &digholenum);
					srand(time(0));//���������
					DirectRead(FileName);
					CreatBoard(f, 1, 1);
					digholes(f, player, digholenum);//����һ��11����Ԫ���Ա�֤Ψһ��
					ShowGame();
					CreateSuCNF(player, SuDokuFileName,digholenum);
					flag_sudoku = 1;
					SolveTotal = 0;//��ʼ��Ϊ0�����´����
					system("pause");
					break;
				case 2:
					printf("���15s��û�з�Ӧ����رճ���\n");
					printf("�����������Ϊ�����ѶȲ�ͬ�����ʱ��Ҳ��ͬ\n");
					C = NULL;
					method = 6;
					int solve;
					clock_t start_time, end_time;
					double total_time;
					ReaderFile(&C, SuDokuFileName);
					start_time = clock();
					solve = Dpll(&C);
					end_time = clock();
					total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000;//����ľ�������Ϊ��λ��ֵ
					SaveSudokuFile(solve, SuDokuFileName, digholenum,total_time);
					system("pause");
					break;
				case 3:
					PlayGame(SaveSu,player, digholenum);
				}
			}
			break;
		}
			printf("��ӭ�´�ʹ�ñ�ϵͳ�����س����˳���");
			getchar();
	}

}
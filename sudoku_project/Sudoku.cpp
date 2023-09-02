#include "Settings.h"
//��ӡ���̽���
void ShowGame()
{
	//�������������ӡ���̽����
	//����
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
	curpoint = 0;//���¶���ֵ
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
	curpoint = 0;//���¶���ֵ
}
int min(int a, int b)
{
	return (a > b) ? b : a;
}
int max(int a, int b)
{
	return (a > b) ? a : b;
}

void Initlines()//�ú�������˼�ǣ�ͨ������ά����ת��Ϊĳһ�У����磬11��Ӧ���Խ��ߵ�5�У�������ù�
{
	//InitBool();//ò�ƿ����Ż�����
	int inm[10] = { 0,51,41,31,21,11,12,13,14,15 };

	for (int i = 1; i <= 9; i++)
	{
		int num = 1;
		tlm[inm[i]] = i;
		tlmpos[i][num++] = inm[i];
		//���濪ʼ������ʽ�׶�
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
	//���Խ������ˣ����ڿ�ʼ���Խ���
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
	//�ȴ����һ��
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
	//srand(time(0));//���������
	//��Щ�ŵ�������������
	//��Щ�ǳ���׼��
	if (flag1 == 1)
		return;
	//�����ж��Ƿ��Ѿ����Թ������еĿ�����
	if (j > linenums[i])
	{
		j = 1, i += 1;
	}
	if (i > 9)
	{
		return;
	}

	while (player[i][j] != 0)//ע�⣬�����ȫ�ֱ���
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
	int curpos = i * 10 + j;//תΪ2λ������
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
		if (judgeone(i, curmain, curvice, temp))//ǰ�����Ƿ�Χ�жϣ����������ж��Ƿ��ͻ
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




			CreatBoard(f, i, j + 1);//��������
			if (flag1 == 1)
				return;
			if (player[i][j]);//���ݵ�ʱ�����
			else
			{
				f[i][j] = 0;
			}

			ml[i][temp] = 0;//���ݹ���
			mm[curmain][temp] = 0;
			mv[curvice][temp] = 0;
		}
	}
	return;

}
void CheckBoard(int f[][10], int player[][10], int i, int j)//һ��Ҫ�ں����ڲ�����
{
	// Initlines();
	//srand(time(0));//���������
	//��Щ�ŵ�������������
	//��Щ�ǳ���׼��
	//�����ж��Ƿ��Ѿ����Թ������еĿ�����
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

	while (player[i][j] != 0)//ע�⣬�����ȫ�ֱ���
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
	int curpos = i * 10 + j;//תΪ2λ������
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
		if (judgeone(i, curmain, curvice, temp))//ǰ�����Ƿ�Χ�жϣ����������ж��Ƿ��ͻ
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




			CheckBoard(f, player, i, j + 1);//��������
			if (checkflag == 2)
				return;
			if (player[i][j]);
			else
			{
				f[i][j] = 0;
			}

			ml[i][temp] = 0;//���ݹ���
			mm[curmain][temp] = 0;
			mv[curvice][temp] = 0;
		}
	}
	return;
	//�����߼������ɼ�����һ���ģ�����Ҫ�������ɶ�ε����
}

void digholes(int f[][10], int player[][10], int nums)//�����������ȥ������Ŀ
{
	memset(MarkDig, 0, sizeof(MarkDig));
	ReSave(player, SaveSu);
	ReSave(f, SaveSu);

	//�����߼��ϣ�player������������¼��ǰ����������ģ����Ի�����f����
	for (int i = 1; i <= nums; i++)
	{
		//һ��Ҫ��ȥ��ô��Ķ�+z
		int dx = rand() % 9 + 1;//����1 - 9 ������
		int dy = rand() % linenums[dx] + 1;//��֤�䲻��Խ�������
		if (MarkDig[dx][dy] == 1)
		{
			i--;
			continue;
		}
		MarkDig[dx][dy] = 1;


		//��ʼ�������У�
		//1.checkflag
		//2.����������ڸ�ֵ������
		// ��¼�ʼ��tempֵ
		//����ʱ��Ҫ�ظ��ı���
		//1.player = temp
		//2.�ָ���������������ֵ������

		checkflag = 0;//���³�ʼ��

		int curpos = dx * 10 + dy;//תΪ2λ������
		int curmain = tlm[curpos];
		int curvice = tlv[curpos];

		int temp = player[dx][dy];//�ѳ�ʼ���Ĺ���Ҳ�����
		f[dx][dy] = 0;
		player[dx][dy] = 0;//��������ڵ�

		ml[i][temp] = 0;//
		mm[curmain][temp] = 0;
		mv[curvice][temp] = 0;
		CheckBoard(f, player, dx, dy);
		if (checkflag == 1)
		{
			ml[i][temp] = 1;//
			mm[curmain][temp] = 1;
			mv[curvice][temp] = 1;

			player[dx][dy] = temp;//�ظ���ԭ����ֵ
			f[dx][dy] = temp;
		}

	}
	//Ϊ�˼���ÿ���ڶ�֮����߼��Ƿ���ȷ����Ҫ����һ��checkboard���������ü���


}


bool CreateSuCNF(int player[][10], char FileName[],int holes)//����ĺ����������Ȳ������ڶ�����Ŀ����Ϊ�ѶȺ��ڶ���Ŀ��ʵ��ϵ����
//��Ϊ��׼�����Ƕ���
{

	int AT[100] = {};
	for (int i = 0; i <= 60; i++)
	{
		int dx = sx[i];
		int dy = sy[i];
		int cur = dx * 10 + dy;
		AT[cur] = i;
	}//���ٱ�Ԫ��Ŀ

	bool NotEmpty[11][11];//�����������㲻�ǿյ�
	FILE* fp = fopen(FileName, "w");
	if (!fp)
		exit(ERROR);
	fprintf(fp, "p cnf 609 %d\n", 7479 + 50 - holes);//���Ƕ�ȡ����֮��õ���
	//Ϊ�˷������룬ѡ�ô�����,���Ҽ���ѭ������ʹ��
	//ע����  tn[1,5][0,1] hn[1,5][1,9] sn[1,5][1,10][0,1]
	int tn[6][2] = { {},{1,10},{3,6},{5,3},{7,1},{9,0} };//targetnums,��¼Լ���� 0.�м�������ģ�1.�м���ѡ��Ĳ���
	int hn[6][10] = { {},{0,5},{0,4,5,6},{0,3,4,5,6,7},{0,2,3,4,5,6,7,8},{0,1,2,3,4,5,6,7,8,9} };//havenums����¼��һ���б��������Щ
	int sn[6][11][2] =
	{ {},
		{{}, {1,6},{2,6},{2,7},{3,6},{3,7},{3,8},{4,6},{4,7},{4,8},{4,9}},
		{{},{1,7},{2,7},{2,8},{3,7},{3,8},{3,9} },
		{{},{1,8},{2,8},{2,9}},
		{{},{1,9}},
		{}
	};
	//selectnums����¼ѡ��Ĳ���1
//part1��ʾ���Ӿ�͸���Լ�����֣�����������������Խ��ߵ�Ҳͬʱ�����
//���Ӿ���ʾ
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

	//ÿһ��,�������Խ���������ظ��ģ������ظ�д
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

	//end����

	//part2��Լ��
	for (int i = 1; i <= 9; i++)//�ӵ�һ�п�ʼö��
	{

		int cl = 0;//curline������ת������
		if (i > 5)
		{
			cl = 9 - i + 1;
		}
		else
		{
			cl = i;
		}


		//ÿһ�еĲ��֣���Լ��
		int tt = tn[cl][0], ts = tn[cl][1];//targettarget,targetselect


		for (int k = 1; k <= tt; k++)
		{
			for (int j = 1; j <= linenums[i]; j++)
			{

				fprintf(fp, "%d ", AT[i * 10 + j] * 10 + hn[cl][k]);//����
			}
			fprintf(fp, "0\n");
		}



		if (ts != 0)//�����һ��û�������ǾͲ��ù�
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


		//ע�⣬��ʵ�ĶԽ����ϵ�ֵ����i,clֻ��Ϊ�˼򵥶����б仯������
		//����ÿһ���Խ����ϵ�ֵ

		for (int k = 1; k <= tt; k++)
		{
			for (int j = 1; j <= linenums[i]; j++)
			{
				fprintf(fp, "%d ", AT[tlmpos[i][j]] * 10 + hn[cl][k]);
			}
			fprintf(fp, "0\n");
		}

		if (ts != 0)//�����һ��û�������ǾͲ��ù�
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



		//����������б�Խ����ϵ�ֵ

		for (int k = 1; k <= tt; k++)
		{
			for (int j = 1; j <= linenums[i]; j++)
			{
				fprintf(fp, "%d ", AT[tlvpos[i][j]] * 10 + hn[cl][k]);
			}
			fprintf(fp, "0\n");
		}


		if (ts != 0)//�����һ��û�������ǾͲ��ù�
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








//void InitPlayer()//�������е������Сֵȫ���뵽����
//{
//	memset(player, -1, sizeof(player));//�����ʼ��Ϊ-1��������Ԥ����߽�
//	memset(f, -1, sizeof(f));
//}




//������������״̬
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
	{//���re==TRUE����������������뵽�ļ��� 
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
			//���������ˣ��������
			int curpos = i * 10 + j;//תΪ2λ������
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
			printf("�����Ѿ�ȫ������ˣ�����������\n");
			ShowAnswer();
			system("pause");
			return;
		}

		ShowGame();
		printf("��ʾ�������ʽΪ235 0����ʾ�ڶ��е�����������5��0��ʾ��ֹ����\n");
		printf("�����Ҫ�˳��Ļ�,������0 0\n");
		printf("�����Ҫ�𰸣�������1 0\n");
		int axis, aing;//��ʾ���ĩβ
		scanf("%d %d", &axis, &aing);
		if (axis == 0)
		{
			printf("��ӭ�´����棡�����������\n");
			system("pause");
			return;
		}
		else if (axis == 1)
		{
			SolveTotal = holes;
			printf("�Ѿ�ȫ��������������Ǵ𰸣�\n");
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
				printf("��ǰλ���Ѿ��������\n");
			}
			else if (SaveSu[x][y] != k)
			{
				printf("��Ĳ��ԣ���ǰλ��ֵӦ���� %d\n", SaveSu[x][y]);
			}
			else if (SaveSu[x][y] == k)
			{
				player[x][y] = k;
				printf("��ȷ������Ѿ����룡\n");
				SolveTotal += 1;
			}

			system("pause");

		}


	}
}

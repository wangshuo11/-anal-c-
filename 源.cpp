#include<iostream>
using namespace std;
const int filenum = 4381;                        //�ļ�����Ŀ
int date[filenum + 10][3];                       //���hash��������,����ɰ���i����ֱֵ��ȡ��

void f_hash_date(int date[][3]);                //�ļ����hash������Ӧ������
												//�������ݵ�ָ�����ļ��У����ļ������Ҳ�����
int f_save_txt(int i, int date[][3], int flag[], int pos[], int &cellsnum, int &sum_cells_count, float xy[][2]);

int main()
{
	int flag[1000];                                 //flag[]��ʾ��������������������
	int pos[1000];                                 //pos[]��ʾ��������dat�ļ��е�i��ֵ
	int cellsnum = 0;                            //cellsnum��ʾ���п�ƥ�����������Ŀ
	int sum_cells_count = 0;                     //sum_cells_count��ʾ���������������ֵ
	float xy[1000][2];                               //�������������꣨xy[][0],xy[][1]��
	f_hash_date(date);
	for (int i = 0; i <filenum; i++) {
		f_save_txt(i, date, flag, pos, cellsnum, sum_cells_count, xy);
	}
	cout << "cellsum=" << cellsnum << " sum_cells_count=" << sum_cells_count << endl;
	return 0;
}

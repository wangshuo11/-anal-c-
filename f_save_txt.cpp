/*flag��ʾ����������ID,pos��ʾ������i��ֵ��cellsnum��ʾ���еĿ�ƥ���������Ŀ��sum_cells_count��ʾ���������������ֵ,�������������ꣻ
f_close()�������ڲ���ƥ�䵽����������
f_update()�������ڸ������������ݺ�ƥ������Ȩ��
f_canshu()�������ڴ����ļ�dat�������������Բ��ϵĲ�����
f_filename()���ڻ�ö�ȡ�ļ���·��,�����ļ���·��*/
#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;
const int filenum = 4381;   //�ļ�����Ŀ
const int filesize = 7808;  //ͼ���С

int f_close(float xy[][2], int flag[], int pos[], int &cellsnum, float data[][10], int visit[100], int myi, int k);
int f_update_cells(float xy[][2], int pos[], int flag[], int myi, int t_pos, int &cellsnum, int &sum_cells_count, float data[][10], int k);
void f_filename(int i, char filename[100], char filedata[100]);
int f_canshu(char *filename, float data[][10]);

int f_save_txt(int i, int date[][3], int flag[], int pos[], int &cellsnum, int &sum_cells_count, float xy[][2])
{

	char filedata[100], filename[100];             //filedata��ʾ������ݵ�·����filename��ʾ��ȡ���ݵ�·��
	f_filename(i, filename, filedata);             //���·��
	float data[filesize][10];                      //���ڴ�������Ĳ���[���ᣬ���ᣬƫ�ǣ���������x,��������y]
	int visit[100];                               //��¼�����Ƿ��Ѿ�������
	memset(visit, 0, sizeof(visit));              //��ʼ�����ʱ��

	int count = f_canshu(filename, data);
	//cout << "count=" << count << endl;//count��¼������������Ŀ
	if (count == 0)                //���û�����������ü���������һ������������������
		return 0;
	ofstream out(filedata);//���ļ��� 
	for (int k = 0; k < count; k++) {           //����ÿһ����������Ǹ�����������������
		char Id[20];                           //���������ID
		char temp[10];
		_itoa(date[i][0], Id, 10);
		for (int c = 1; c < 3; c++) {
			if (date[i][c] < 10) {
				strcat(Id, "0");                   //��0λ
			}
			_itoa(date[i][c], temp, 10);
			strcat(Id, temp);
		}
		strcat(Id, "_");
		_itoa(k, temp, 10);
		strcat(Id, temp);
		int len_Id = strlen(Id), res_pos, res_cells;
		for (int c = 0; c < len_Id; c++) {   //�����IDд��txt
			out << Id[c];
		}
		out << " ";
		for (int c = 0; c < 5; c++) {        //����Բ���� [���ᣬ���ᣬƫ�ǣ���������X,��������Y] д��txt
			out << data[k][c] << " ";
		}
		for (int c = 0; c < 3; c++) {         //������date[i][]д��txt    
			out << date[i][c] << " ";
		}
		if (cellsnum == -1) {                //�״�ƥ�䣬�������ڳ�ʼ��������
			out << 0;
			pos[0] = i;
			xy[0][0] = data[k][3];
			xy[0][1] = data[k][4];
			flag[0] = 0;
			cellsnum = 1;
			sum_cells_count = 0;
			out << endl;
		}
		else {
			res_pos = f_close(xy, flag, pos, cellsnum, data, visit, i, k);      //res_pos��ʾƥ������������
			if (res_pos != -1)
			{
				visit[res_pos] = 1;      //��Ƿ���                        
			}
			res_cells = f_update_cells(xy, pos, flag, i, res_pos, cellsnum, sum_cells_count, data, k);   // �������������ֵ
			out << res_cells;                           //����������ֵд��txt
			out << endl;
		}
		//cout << i << " " << res_pos << " " << res_cells<<" "<<cellsnum<<" " <<sum_cells_count<< endl;
	}
	return 1;
}


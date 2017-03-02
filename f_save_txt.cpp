/*flag表示雨区连续的ID,pos表示雨区的i数值，cellsnum表示现有的可匹配的雨区数目，sum_cells_count表示连续的雨区标号数值,雨区的中心坐标；
f_close()函数用于查找匹配到的连续区；
f_update()函数用于更新连续区数据和匹配优先权；
f_canshu()函数用于处理文件dat，并获得雨区椭圆拟合的参数；
f_filename()用于获得读取文件的路径,保存文件的路径*/
#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;
const int filenum = 4381;   //文件的数目
const int filesize = 7808;  //图像大小

int f_close(float xy[][2], int flag[], int pos[], int &cellsnum, float data[][10], int visit[100], int myi, int k);
int f_update_cells(float xy[][2], int pos[], int flag[], int myi, int t_pos, int &cellsnum, int &sum_cells_count, float data[][10], int k);
void f_filename(int i, char filename[100], char filedata[100]);
int f_canshu(char *filename, float data[][10]);

int f_save_txt(int i, int date[][3], int flag[], int pos[], int &cellsnum, int &sum_cells_count, float xy[][2])
{

	char filedata[100], filename[100];             //filedata表示存放数据的路径，filename表示读取数据的路径
	f_filename(i, filename, filedata);             //获得路径
	float data[filesize][10];                      //用于存放雨区的参数[长轴，短轴，偏角，中心坐标x,中心坐标y]
	int visit[100];                               //记录雨区是否已经被访问
	memset(visit, 0, sizeof(visit));              //初始化访问标记

	int count = f_canshu(filename, data);
	//cout << "count=" << count << endl;//count记录所得雨区的数目
	if (count == 0)                //如果没有雨区，不用计算属于哪一个连续区，结束返回
		return 0;
	ofstream out(filedata);//打开文件。 
	for (int k = 0; k < count; k++) {           //遍历每一个雨区，标记该雨区所属的连续区
		char Id[20];                           //连续区编号ID
		char temp[10];
		_itoa(date[i][0], Id, 10);
		for (int c = 1; c < 3; c++) {
			if (date[i][c] < 10) {
				strcat(Id, "0");                   //补0位
			}
			_itoa(date[i][c], temp, 10);
			strcat(Id, temp);
		}
		strcat(Id, "_");
		_itoa(k, temp, 10);
		strcat(Id, temp);
		int len_Id = strlen(Id), res_pos, res_cells;
		for (int c = 0; c < len_Id; c++) {   //将编号ID写入txt
			out << Id[c];
		}
		out << " ";
		for (int c = 0; c < 5; c++) {        //将椭圆参数 [长轴，短轴，偏角，中心坐标X,中心坐标Y] 写入txt
			out << data[k][c] << " ";
		}
		for (int c = 0; c < 3; c++) {         //将日期date[i][]写入txt    
			out << date[i][c] << " ";
		}
		if (cellsnum == -1) {                //首次匹配，数据用于初始化连续区
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
			res_pos = f_close(xy, flag, pos, cellsnum, data, visit, i, k);      //res_pos表示匹配的连续区编号
			if (res_pos != -1)
			{
				visit[res_pos] = 1;      //标记访问                        
			}
			res_cells = f_update_cells(xy, pos, flag, i, res_pos, cellsnum, sum_cells_count, data, k);   // 求出连续雨区数值
			out << res_cells;                           //将连续区数值写入txt
			out << endl;
		}
		//cout << i << " " << res_pos << " " << res_cells<<" "<<cellsnum<<" " <<sum_cells_count<< endl;
	}
	return 1;
}


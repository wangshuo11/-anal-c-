#include<iostream>
using namespace std;
const int filenum = 4381;                        //文件的数目
int date[filenum + 10][3];                       //存放hash出的日期,后面可按照i的数值直接取出

void f_hash_date(int date[][3]);                //文件编号hash出所对应的日期
												//保存数据到指定的文件夹（此文件不能找不到）
int f_save_txt(int i, int date[][3], int flag[], int pos[], int &cellsnum, int &sum_cells_count, float xy[][2]);

int main()
{
	int flag[1000];                                 //flag[]表示雨区所在连续区的区号
	int pos[1000];                                 //pos[]表示雨区的在dat文件中的i数值
	int cellsnum = 0;                            //cellsnum表示现有可匹配的连续区数目
	int sum_cells_count = 0;                     //sum_cells_count表示连续的雨区标号数值
	float xy[1000][2];                               //雨区的中心坐标（xy[][0],xy[][1]）
	f_hash_date(date);
	for (int i = 0; i <filenum; i++) {
		f_save_txt(i, date, flag, pos, cellsnum, sum_cells_count, xy);
	}
	cout << "cellsum=" << cellsnum << " sum_cells_count=" << sum_cells_count << endl;
	return 0;
}

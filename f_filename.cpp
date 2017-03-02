#include<string.h>
#include<iostream>

using namespace std;
void f_filename(int i, char filename[], char filedata[])  //获得读取文件的路径,保存文件的路径
{
	char filename0[40] = "F:\\anal\\anal_";
	char filename2[10] = ".dat";
	char filedata0[40] = "F:\\C_rain_cells2\\C_anal_";
	char filedata2[10] = ".txt";
	char file1[10];
	_itoa(i, file1, 10);

	//最终读取文件的路径filename
	strcpy(filename, filename0);
	strcat(filename, file1);
	strcat(filename, filename2);

	//最终读取文件的路径filedata
	strcpy(filedata, filedata0);
	strcat(filedata, file1);
	strcat(filedata, filedata2);
}
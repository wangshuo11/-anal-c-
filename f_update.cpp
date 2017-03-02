/* f_update()�������ڸ������������ݺ�ƥ������Ȩ������ֵΪ�����������ڵ�����res_cells,
���������������ݣ�  ɾ������ʱ����ֵδ�ٴγ�����������������
���µ���������������Ȩ��С��������Ȩ�������ǰ���´�����ƥ�� */
#include<vector>
#include<iostream>
#include<opencv2/opencv.hpp>
#include <math.h>
const int threshold_i = 20;
using namespace cv;
using namespace std;

int f_update_cells(float xy[][2], int pos[], int flag[], int myi, int t_pos, int &cellsnum, int &sum_cells_count, float data[][10], int k)
{
	int res_cells;
	/*  ת���ɶ�̬����v_pos,v_flag,v_xy ���ڸ������� */
	vector<int> v_pos;
	for (int i = 0; i < cellsnum; i++) {
		v_pos.push_back(pos[i]);
	}
	vector<int> v_flag;
	for (int j = 0; j < cellsnum; j++) {
		v_flag.push_back(flag[j]);
	}
	vector<Point> v_xy;
	for (int j = 0; j < cellsnum; j++) {
		Point Txy;
		Txy.x = xy[j][0];
		Txy.y = xy[j][1];
		v_xy.push_back(Txy);
	}

	if (t_pos == -1) {                              //�����ӵ�����ӵ���´�����ƥ��������Ȩ
		v_pos.insert(v_pos.begin(), myi);             //������������ǰ��begin
		v_flag.insert(v_flag.begin(), ++sum_cells_count);
		Point Txy;
		Txy.x = data[k][3];
		Txy.y = data[k][4];
		v_xy.insert(v_xy.begin(), Txy);
		cellsnum++;
		//cout << "b_cellsnum=" << cellsnum << endl;
		res_cells = sum_cells_count;
	}
	else if (t_pos > -1) {                  //�˴�ƥ�䵽�����������������´�ƥ������ʱ����Ȩ���
		v_pos.push_back(myi);               //���������������
		v_flag.push_back(flag[t_pos]);
		Point Txy;
		Txy.x = data[k][3];
		Txy.y = data[k][4];
		v_xy.push_back(Txy);
		res_cells = v_flag[t_pos];
		/*  ɾ��ԭ�е���������������ݣ�����ĩβ������µ����������� */
		vector<int>::iterator it_flag = v_flag.begin() + t_pos;
		v_flag.erase(it_flag);
		vector<int>::iterator it_pos = v_pos.begin() + t_pos;
		v_pos.erase(it_pos);
		vector<Point>::iterator it_xy = v_xy.begin() + t_pos;
		v_xy.erase(it_xy);
	}
	/*  ɾ������ʱ����ֵδ�ٴγ��������������� */
	for (int i = 0; i < v_pos.size(); i++) {
		if (myi - v_pos[i] >= threshold_i) {
			//cout << "myi=" << myi << " v_pos[" << i << "]" <<  v_pos[i]<< endl;
			vector<int>::iterator it_flag = v_flag.begin() + i;
			v_flag.erase(it_flag);
			vector<int>::iterator it_pos = v_pos.begin() + i;
			v_pos.erase(it_pos);
			vector<Point>::iterator it_xy = v_xy.begin() + i;
			v_xy.erase(it_xy);
			cellsnum--;
			//	cout << "f_cellsnum=" << cellsnum << endl;
		}
	}
	/*�������ʹ�vector ��ת�������� */
	for (int i = 0; i<v_pos.size(); i++) {
		pos[i] = v_pos[i];
	}
	for (int j = 0; j <v_flag.size(); j++) {
		flag[j] = v_flag[j];
	}
	for (int j = 0; j <v_xy.size(); j++) {
		xy[j][0] = v_xy[j].x;
		xy[j][1] = v_xy[j].y;
	}

	return res_cells;
}
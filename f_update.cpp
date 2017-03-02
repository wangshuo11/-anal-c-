/* f_update()函数用于更新连续区数据和匹配优先权；返回值为该雨区所属于的雨区res_cells,
更新连续雨区数据；  删除大于时间阈值未再次出现雨区的连续区，
将新的连续区按照优先权大小排序，优先权打的排在前面下次优先匹配 */
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
	/*  转换成动态数组v_pos,v_flag,v_xy 便于更新数据 */
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

	if (t_pos == -1) {                              //新增加的雨区拥有下次雨区匹配的最高先权
		v_pos.insert(v_pos.begin(), myi);             //将数据排在最前面begin
		v_flag.insert(v_flag.begin(), ++sum_cells_count);
		Point Txy;
		Txy.x = data[k][3];
		Txy.y = data[k][4];
		v_xy.insert(v_xy.begin(), Txy);
		cellsnum++;
		//cout << "b_cellsnum=" << cellsnum << endl;
		res_cells = sum_cells_count;
	}
	else if (t_pos > -1) {                  //此次匹配到连续雨区的雨区，下次匹配雨区时优先权最低
		v_pos.push_back(myi);               //将数据排在最后面
		v_flag.push_back(flag[t_pos]);
		Point Txy;
		Txy.x = data[k][3];
		Txy.y = data[k][4];
		v_xy.push_back(Txy);
		res_cells = v_flag[t_pos];
		/*  删除原有的冗余的连续区数据，已在末尾添加最新的连续区数据 */
		vector<int>::iterator it_flag = v_flag.begin() + t_pos;
		v_flag.erase(it_flag);
		vector<int>::iterator it_pos = v_pos.begin() + t_pos;
		v_pos.erase(it_pos);
		vector<Point>::iterator it_xy = v_xy.begin() + t_pos;
		v_xy.erase(it_xy);
	}
	/*  删除大于时间阈值未再次出现雨区的连续区 */
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
	/*数据类型从vector 在转换成数组 */
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
/*连续雨区匹配过程，第一步：初始化连续区数据； 若连续区数据为空，则第一个雨区用于初始化连续区；
第二步：新的雨区和连续数据的连续区匹配； 匹配优先权设置：Priority新的连续区>最久未出现匹配的连续区；
第三步：更新连续雨区数据；  删除大于时间阈值未再次出现雨区的连续区，将新的连续区按照优先权大小排序，优先权打的排在前面下次优先匹配*/
#include<math.h>
#include<iostream>
using namespace std;
const int threshold_dis = 30;                //在时间上，两个雨区可为同一个连续区的阈值
const int threshold_i = 20;                //在椭圆中心距上，两个雨区可为同一个连续区的阈值
float f_distance(float Xa, float Ya, float Xb, float Yb);         //计算椭圆中心距        

int f_close(float xy[][2], int flag[], int pos[], int &cellsnum, float data[][10], int visit[100], int myi, int k)
{
	float distance = -1;              //初始化distance为-1，以便于后面判断是不是第一个连续区
	int t_pos = -1;                   //初始化可为同一个连续区的位置编号，若找不到则返回-1
	float Xb = data[k][3];            //雨区的中心坐标
	float Yb = data[k][4];
	/* 根据时间和中心距阈值查找可为同一个雨区的连续雨区*/
	for (int i = 0; i < cellsnum; i++) {
		float Xa = xy[i][0];
		float Ya = xy[i][1];
		if (pos[i] < myi) {              //判断连个雨区是否在同一个时间上，如果在则肯定不是同一个连续区
			if (visit[i] == 0 && myi - pos[i] < threshold_i) {          //在时间上过滤
				float t_distance = f_distance(Xa, Ya, Xb, Yb);        //计算椭圆中心距      
				if (t_distance < threshold_dis) {                               //在距离上过滤
					if (distance <0) {                               //判断连续雨区是否初始化
						distance = t_distance;
						t_pos = i;
					}
					else {
						if (distance > t_distance) {                 //更新为匹配到的更佳的连续区（中心距更小）
							distance = t_distance;
							t_pos = i;
						}
					}
				}
			}
		}
	}
	return t_pos;
}
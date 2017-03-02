#include<math.h>
#include<iostream>
using namespace std;
float f_distance(float Xa, float Ya, float Xb, float Yb)
{
	return sqrt((Xa - Xb)*(Xa - Xb) + (Ya - Yb)*(Ya - Yb));  //返回两点之间距离
}
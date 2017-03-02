/*f_canshu()函数用于处理文件dat，并获得雨区椭圆拟合的参数 */
#include<iostream>
#include<opencv2/opencv.hpp>
#include<Eigen/Dense>
using namespace std;
using namespace Eigen;
using namespace cv;

const int len_row = 128;     //根据二进制文件设置图像的宽和高
const int len_col = 61;
const int file_size = 7808;
const int threshold_value_rain = 25;   //设置降雨量过滤的阈值
const int threshold_value_contours = 6;  //设置轮廓过滤的阈值

int f_canshu(char *filename, float data[][10])
{
	/*以四个字节为单位，依次读取fp所指向的数值，并且通过阈值threshold_value过滤,然后将图像矩阵存在I1中*/
	FILE *fp = fopen(filename, "rb");
	float temp;                                    //用于暂存
	int count = 0;                                 //记录轮廓数目
	Mat I1(len_row, len_col, CV_32F), I2;
	for (int i = 0; i < file_size; i++) {
		fread(&temp, 4, 1, fp);
		if (temp > threshold_value_rain) {
			I1.at<float>(i / len_col, i%len_col) = 255;
		}
		else {
			I1.at<float>(i / len_col, i%len_col) = 0;
		}
		fseek(fp, 4L, 1);
	}
	fclose(fp);                                    //读取结束。关闭文件

												   /*提取轮廓*/
	I1.convertTo(I2, CV_8U, 1, 0);                //I1转换成I2，变换为可作为图像处理的数据类型并存在I2中
	vector<vector<Point>> contours;
	vector<vector<Point>> contours2;
	vector<Vec4i> hierarchy;
	Point temp_point;
	findContours(I2, contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
	for (int i = 0; i<contours.size(); i++) {
		if (contours[i].size()>threshold_value_contours) {
			vector<Point> temp_vector;
			for (int j = 0; j < contours[i].size(); j++) {
				temp_point.x = contours[i][j].x;
				temp_point.y = contours[i][j].y;
				temp_vector.push_back(temp_point);
			}
			contours2.push_back(temp_vector);   //过滤后的轮廓
		}
	}
	Mat cimage = Mat::zeros(I1.size(), CV_8UC3);
	for (int i = 0; i < contours2.size(); i++)
	{
		Mat pointsf;
		Mat(contours2[i]).convertTo(pointsf, CV_32F);     //数据类型转换
		RotatedRect box = fitEllipse(pointsf);            //椭圆拟合
		if (max(box.size.height, box.size.width)>15 * min(box.size.height, box.size.width))   //过滤掉长短轴相差过大的椭圆
			break;
		/*将椭圆参数回传给data[][]*/
		data[count][0] = box.size.height;
		data[count][1] = box.size.width;
		data[count][2] = box.angle;
		data[count][3] = box.center.x;
		data[count][4] = box.center.y;
		count++;
	}
	return count;
}
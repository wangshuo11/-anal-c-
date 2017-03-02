/*f_canshu()�������ڴ����ļ�dat�������������Բ��ϵĲ��� */
#include<iostream>
#include<opencv2/opencv.hpp>
#include<Eigen/Dense>
using namespace std;
using namespace Eigen;
using namespace cv;

const int len_row = 128;     //���ݶ������ļ�����ͼ��Ŀ�͸�
const int len_col = 61;
const int file_size = 7808;
const int threshold_value_rain = 25;   //���ý��������˵���ֵ
const int threshold_value_contours = 6;  //�����������˵���ֵ

int f_canshu(char *filename, float data[][10])
{
	/*���ĸ��ֽ�Ϊ��λ�����ζ�ȡfp��ָ�����ֵ������ͨ����ֵthreshold_value����,Ȼ��ͼ��������I1��*/
	FILE *fp = fopen(filename, "rb");
	float temp;                                    //�����ݴ�
	int count = 0;                                 //��¼������Ŀ
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
	fclose(fp);                                    //��ȡ�������ر��ļ�

												   /*��ȡ����*/
	I1.convertTo(I2, CV_8U, 1, 0);                //I1ת����I2���任Ϊ����Ϊͼ������������Ͳ�����I2��
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
			contours2.push_back(temp_vector);   //���˺������
		}
	}
	Mat cimage = Mat::zeros(I1.size(), CV_8UC3);
	for (int i = 0; i < contours2.size(); i++)
	{
		Mat pointsf;
		Mat(contours2[i]).convertTo(pointsf, CV_32F);     //��������ת��
		RotatedRect box = fitEllipse(pointsf);            //��Բ���
		if (max(box.size.height, box.size.width)>15 * min(box.size.height, box.size.width))   //���˵����������������Բ
			break;
		/*����Բ�����ش���data[][]*/
		data[count][0] = box.size.height;
		data[count][1] = box.size.width;
		data[count][2] = box.angle;
		data[count][3] = box.center.x;
		data[count][4] = box.center.y;
		count++;
	}
	return count;
}
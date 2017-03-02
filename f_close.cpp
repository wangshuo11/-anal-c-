/*��������ƥ����̣���һ������ʼ�����������ݣ� ������������Ϊ�գ����һ���������ڳ�ʼ����������
�ڶ������µ��������������ݵ�������ƥ�䣻 ƥ������Ȩ���ã�Priority�µ�������>���δ����ƥ�����������
�����������������������ݣ�  ɾ������ʱ����ֵδ�ٴγ��������������������µ���������������Ȩ��С��������Ȩ�������ǰ���´�����ƥ��*/
#include<math.h>
#include<iostream>
using namespace std;
const int threshold_dis = 30;                //��ʱ���ϣ�����������Ϊͬһ������������ֵ
const int threshold_i = 20;                //����Բ���ľ��ϣ�����������Ϊͬһ������������ֵ
float f_distance(float Xa, float Ya, float Xb, float Yb);         //������Բ���ľ�        

int f_close(float xy[][2], int flag[], int pos[], int &cellsnum, float data[][10], int visit[100], int myi, int k)
{
	float distance = -1;              //��ʼ��distanceΪ-1���Ա��ں����ж��ǲ��ǵ�һ��������
	int t_pos = -1;                   //��ʼ����Ϊͬһ����������λ�ñ�ţ����Ҳ����򷵻�-1
	float Xb = data[k][3];            //��������������
	float Yb = data[k][4];
	/* ����ʱ������ľ���ֵ���ҿ�Ϊͬһ����������������*/
	for (int i = 0; i < cellsnum; i++) {
		float Xa = xy[i][0];
		float Ya = xy[i][1];
		if (pos[i] < myi) {              //�ж����������Ƿ���ͬһ��ʱ���ϣ��������϶�����ͬһ��������
			if (visit[i] == 0 && myi - pos[i] < threshold_i) {          //��ʱ���Ϲ���
				float t_distance = f_distance(Xa, Ya, Xb, Yb);        //������Բ���ľ�      
				if (t_distance < threshold_dis) {                               //�ھ����Ϲ���
					if (distance <0) {                               //�ж����������Ƿ��ʼ��
						distance = t_distance;
						t_pos = i;
					}
					else {
						if (distance > t_distance) {                 //����Ϊƥ�䵽�ĸ��ѵ������������ľ��С��
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
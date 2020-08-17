/*
 * Nav.h
 *
 *  Created on: 2017-8-15
 *      Author: Administrator
 */

#ifndef NAV_H_
#define NAV_H_

#define Dtime  0.02 //INS�����ٶ�50hz
#define pii 3.141592653589793
#define rearth 6378393.0
#define Wie 7.292131058936642e-005
#define TuoYuanDu  1/298.257223536
#define gearth   9.79362 //�������ٶ�
#define stime  0.02 //��ϵ����ٶ�50hz
//���������쳣����������������ٶȿ�ͨ�����¹�ʽ���㣺9.78049*(1+0.0052884*(sin��)^2 - 0.0000059*(sin2��)^2)���㣬��Ϊ����γ�ȣ��纼�ݵ��������ٶ�Ϊ��9.79362
extern double Lat; //γ�� 30.2659
extern double Lon;  //����120.1165
extern double Height; //�߶�
extern double Cbn[9];  //��̬����
extern double ffx;  //������ٶ�
extern double ffy;  //������ٶ�
extern double ffz;  //������ٶ�
extern double Vx;   //�����ٶ�
extern double Vy;  //�����ٶ�
extern double Vz; //�����ٶ�
extern double R_mat[36];
extern double Abs(double x);
extern void angle2CBN(double pitch, double roll, double yaw);
extern void angle2q(double pitch, double roll, double yaw);
extern void Navigation();
extern void kalman_filter();
extern void init_mat();
#endif /* NAV_H_ */

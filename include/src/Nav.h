/*
 * Nav.h
 *
 *  Created on: 2017-8-15
 *      Author: Administrator
 */

#ifndef NAV_H_
#define NAV_H_

#define Dtime  0.02 //INS解算速度50hz
#define pii 3.141592653589793
#define rearth 6378393.0
#define Wie 7.292131058936642e-005
#define TuoYuanDu  1/298.257223536
#define gearth   9.79362 //重力加速度
#define stime  0.02 //组合导航速度50hz
//如无重力异常情况，当地重力加速度可通过如下公式计算：9.78049*(1+0.0052884*(sinθ)^2 - 0.0000059*(sin2θ)^2)计算，θ为当地纬度，如杭州的重力加速度为：9.79362
extern double Lat; //纬度 30.2659
extern double Lon;  //经度120.1165
extern double Height; //高度
extern double Cbn[9];  //姿态矩阵
extern double ffx;  //东向加速度
extern double ffy;  //北向加速度
extern double ffz;  //天向加速度
extern double Vx;   //东向速度
extern double Vy;  //北向速度
extern double Vz; //天向速度
extern double R_mat[36];
extern double Abs(double x);
extern void angle2CBN(double pitch, double roll, double yaw);
extern void angle2q(double pitch, double roll, double yaw);
extern void Navigation();
extern void kalman_filter();
extern void init_mat();
#endif /* NAV_H_ */

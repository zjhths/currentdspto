#ifndef NAVIGATION_H_
#define NAVIGATION_H_

#define dcounter 4
//#define stime 0.002
#define stime 0.05
#define pii 3.141592653589793
#define rearth 6378393.0
#define wie 7.292131058936642e-005
#define find_north_time 30000
#define fifo_range 20

// Modified by Mwenjie @20121110 {
	//#define stm 150000              //DVL角度标定开始时间
	//#define etm 600000				//DVL角度标定结束时间

#define stm 30000              //DVL角度标定开始时间
#define etm 480000				//DVL角度标定结束时间

#define LB_hangxiang_on 1
#define LB_hangxiang_off 2

// } Modified by Mwenjie

typedef struct{
	double CBL_mat[9];       	//姿态矩阵
	double CNE_mat[9];        	//位置矩阵
	double v_ins_mat[3];        //速度矩阵
	double dal1_mat[3];
	double vf1_mat[3];
	double wnie2_mat[3];
	double wnen2_mat[3];
	double weidu;               		//纬度
	double jingdu;              		//经度
	double youdong;             		//游动角
	double fuyang;              		//俯仰角
	double henggun;             		//横滚角
	double hangxiang;           		//航向角
	double height;              		//高度
	double wbib[3];						//陀螺角速度
	double fb[3];						//加速度
}NAV_PARA, *p_NAV_PARA;

typedef struct{
	double p_mat[256];
	double xhat[16];
	double r_mat[3];
	double wt_mat[16];
	double v_DVL[3];                	//DVL速度
	double p_GPS[3];                 	//GPS纬度、经度、高度
	double v_GPS[3];                 	//GPS速度
	int avlb;                       	//是否有效
	double angle;                    	//DVL使用，GPS无用
	int counter;
	int gps_jump;
}KALMAN_PARA, *p_KALMAN_PARA;

typedef struct{
	int icounter;                      	//in 计数器 0~9循环
	int ocounter;						//out 计数器 0~9循环
	int counter;					   	//FIFO中个数计数器 0~9
	double wbib[3][fifo_range];                 //通过UPHI传输过来的陀螺数据
	double fb[3][fifo_range];					//通过UPHI传输过来的加表数据
	int GPS_avlb[fifo_range];					//通过UPHI传输过来的GPS是否有效
	double p_GPS[3][fifo_range];				//通过UPHI传输过来的GPS数据
	double v_GPS[3][fifo_range];
	int DVL_avlb[fifo_range];					//通过UPHI传输过来的DVL是否有效
	double v_DVL[3][fifo_range];				//通过UPHI传输过来的DVL数据
	double p_GPSe[3][fifo_range];				//通过UHPI传输过来的GPS位置误差
	int gps_jump[fifo_range];					//通过UHPI传输过来的GPS跳变信息
}NAV_DATA_FIFO, *p_NAV_DATA_FIFO;

extern NAV_PARA g_nav_data;				//导航计算参数
extern double g_counter1;
extern KALMAN_PARA g_DVL;				//GPS的KALMAN滤波器参数
extern KALMAN_PARA g_GPS;				//DVL的KALMAN滤波器参数
extern KALMAN_PARA s_GPS;
extern NAV_DATA_FIFO data_fifo;
extern double CNL[9];

extern void FLASH_INIT();
extern void pos2CNE(double weidu,double jingdu,double CNE[9]);
extern void angle2CBL(double fuyang, double henggun, double hangxiang, double CBL[9]);

extern void DSPF_dp_mat_mul_1(double *x, int r1, int c1,double *y, int c2, double *r);

extern void DSPF_dp_mat_mul(double *x, int r1, int c1,double *y, int c2, double *r);
extern void DSPF_dp_mat_trans(double *x, int rows,int cols, double *r);
extern double DSPF_dp_vecsum_sq(double *x,int n);
	
extern void navigation();
extern double gamma_calc(double t20,double t22);
extern double psi_calc(double t01,double t11);
extern double lambda_calc(double c21,double c20);
extern double alpha_calc(double c02,double c12);
extern void norm_mat(double n_mat[9]);

extern void init_g_DVL();
extern void init_g_GPS();
extern void init_s_GPS();

extern int kalman_filter();

extern int write_fifo();
extern int Read_fifo();
extern int read_fifo();
extern int read_fifo1();
extern void read_fifo3();

extern double gearth;

extern void duizhun();
extern void init_duizhun_para();

extern int DVL_angle_counter;
extern int DVL_time_counter;
extern void DVL_calibration();

extern double hangxiang_fix;
#endif

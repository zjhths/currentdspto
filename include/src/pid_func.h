/*
 * pid_func.h
 *
 *  Created on: 2019-11-13
 *      Author: Administrator
 */

#ifndef PID_FUNC_H_
#define PID_FUNC_H_

#define Kp (double)(0.00001)
#define Ki (double)(0)
#define Kd (double)(0)

struct _pid{		//生成一个标签_pid
	double pv;			//integer that contains the process value
	double sp;			//integer that contains the set point
	double integral;
	double pgain;
	double igain;
	double dgain;
	double last_error;
};

extern far void pid_init(struct _pid *pid,double process_point,double set_point,double p_gain,double i_gain,double d_gain);
extern far double pid_calc(struct _pid *pid);

//extern far float process_point,set_point;
extern far struct _pid pid_str;
extern far struct _pid *pp;





#endif /* PID_FUNC_H_ */

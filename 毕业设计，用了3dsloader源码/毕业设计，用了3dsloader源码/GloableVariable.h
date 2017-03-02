//////////////////////////////////////////////////////////////////////////
//			定义全局变量及全局函数
//////////////////////////////////////////////////////////////////////////
#pragma once
#include <afxstr.h>

#pragma region 定义宏

#define PI 3.1415926	//圆周率pi
#define FINGER_NUMBER 5	//手指数

#define PALM_INDEX 0
#define THUMB_ONE_INDEX 1	//大拇指基关节
#define THUMB_TWO_INDEX 2	//大拇指近基关节
#define THUMB_THREE_INDEX 3	//大拇指中间关节
#define THUMB_FOUR_INDEX 4	//大拇指末梢关节

#define INDEX_ONE_INDEX 5	//食指基关节
#define INDEX_TWO_INDEX 6	//食指近基关节
#define INDEX_THREE_INDEX 7	//食指中间关节
#define INDEX_FOUR_INDEX 8	//食指末梢关节

#define MIDDLE_ONE_INDEX 9		//中指基关节
#define MIDDLE_TWO_INDEX 10		//中指近基关节
#define MIDDLE_THREE_INDEX 11	//中指中间关节
#define MIDDLE_FOUR_INDEX 12	//中指末梢关节

#define RING_ONE_INDEX 13		//无名指基关节
#define RING_TWO_INDEX 14		//无名指近基关节
#define RING_THREE_INDEX 15	//无名指中间关节
#define RING_FOUR_INDEX 16	//无名指末梢关节

#define LITTLE_ONE_INDEX 17		//小拇指基关节
#define LITTLE_TWO_INDEX 18		//小拇指近基关节
#define LITTLE_THREE_INDEX 19	//小拇指中间关节
#define LITTLE_FOUR_INDEX 20	//小拇指末梢关节

// ASCII字符总共只有0到127，一共128种字符
#define MAX_CHAR        128


//各个手指相对于手掌的x轴(手掌坐标系)的偏移量,以x轴正向取正值
const float finger_d[FINGER_NUMBER] = { -46.186 ,-20.941 ,-0.669 ,23.204 ,43.541 };
//各个手指相对于手掌的y轴(手掌坐标系)的偏移量,以y轴正向取正值
//const float finger_L[FINGER_NUMBER] = { 31.618 ,37 ,45.443 ,45.443 ,45.443 };
const float finger_L[FINGER_NUMBER] = { 24.331 ,37.685 ,40.220 ,40.220 ,37.685 };
//各个手指基坐标系x轴相对于手掌基坐标系的x轴的旋转角度
const float finger_theta[FINGER_NUMBER] = { 0,90,90,90,90 };

const float finger_lengths[4] = { 20.871,50.059 ,44.621,25.014};
//lengths[i]表示从第i+1个指节的旋转中心到第i+2个指节的旋转中心的直线距离。lengths[3]设为第四指节旋转中心到指末端的距离
const float finger_widths[4] = { 20,20,20,20 };
#pragma  endregion

class CGloableVariable
{
public:
	static const int MIN_AXIS = -180;//坐标轴最小值
	static const int MAX_AXIS = 180;//坐标轴最大致
	static const int ARROW_LENGTH = 5;//坐标轴小箭头长度为ARROW_LENGTH*sqrt(2)
	static const int N = 22;//20个指关节加上一个手掌
	static CString files_3ds[N];
	static float defaultPos [N][3];//各个指节的初始坐标
	void static Initial();//初始化
	void static Initial_3dsFilesName();//初始化要加载的3ds文件名数组
};




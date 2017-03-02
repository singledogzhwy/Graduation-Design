//////////////////////////////////////////////////////////////////////////
//			����ȫ�ֱ�����ȫ�ֺ���
//////////////////////////////////////////////////////////////////////////
#pragma once
#include <afxstr.h>

#pragma region �����

#define PI 3.1415926	//Բ����pi
#define FINGER_NUMBER 5	//��ָ��

#define PALM_INDEX 0
#define THUMB_ONE_INDEX 1	//��Ĵָ���ؽ�
#define THUMB_TWO_INDEX 2	//��Ĵָ�����ؽ�
#define THUMB_THREE_INDEX 3	//��Ĵָ�м�ؽ�
#define THUMB_FOUR_INDEX 4	//��Ĵָĩ�ҹؽ�

#define INDEX_ONE_INDEX 5	//ʳָ���ؽ�
#define INDEX_TWO_INDEX 6	//ʳָ�����ؽ�
#define INDEX_THREE_INDEX 7	//ʳָ�м�ؽ�
#define INDEX_FOUR_INDEX 8	//ʳָĩ�ҹؽ�

#define MIDDLE_ONE_INDEX 9		//��ָ���ؽ�
#define MIDDLE_TWO_INDEX 10		//��ָ�����ؽ�
#define MIDDLE_THREE_INDEX 11	//��ָ�м�ؽ�
#define MIDDLE_FOUR_INDEX 12	//��ָĩ�ҹؽ�

#define RING_ONE_INDEX 13		//����ָ���ؽ�
#define RING_TWO_INDEX 14		//����ָ�����ؽ�
#define RING_THREE_INDEX 15	//����ָ�м�ؽ�
#define RING_FOUR_INDEX 16	//����ָĩ�ҹؽ�

#define LITTLE_ONE_INDEX 17		//СĴָ���ؽ�
#define LITTLE_TWO_INDEX 18		//СĴָ�����ؽ�
#define LITTLE_THREE_INDEX 19	//СĴָ�м�ؽ�
#define LITTLE_FOUR_INDEX 20	//СĴָĩ�ҹؽ�

// ASCII�ַ��ܹ�ֻ��0��127��һ��128���ַ�
#define MAX_CHAR        128


//������ָ��������Ƶ�x��(��������ϵ)��ƫ����,��x������ȡ��ֵ
const float finger_d[FINGER_NUMBER] = { -46.186 ,-20.941 ,-0.669 ,23.204 ,43.541 };
//������ָ��������Ƶ�y��(��������ϵ)��ƫ����,��y������ȡ��ֵ
//const float finger_L[FINGER_NUMBER] = { 31.618 ,37 ,45.443 ,45.443 ,45.443 };
const float finger_L[FINGER_NUMBER] = { 24.331 ,37.685 ,40.220 ,40.220 ,37.685 };
//������ָ������ϵx����������ƻ�����ϵ��x�����ת�Ƕ�
const float finger_theta[FINGER_NUMBER] = { 0,90,90,90,90 };

const float finger_lengths[4] = { 20.871,50.059 ,44.621,25.014};
//lengths[i]��ʾ�ӵ�i+1��ָ�ڵ���ת���ĵ���i+2��ָ�ڵ���ת���ĵ�ֱ�߾��롣lengths[3]��Ϊ����ָ����ת���ĵ�ָĩ�˵ľ���
const float finger_widths[4] = { 20,20,20,20 };
#pragma  endregion

class CGloableVariable
{
public:
	static const int MIN_AXIS = -180;//��������Сֵ
	static const int MAX_AXIS = 180;//�����������
	static const int ARROW_LENGTH = 5;//������С��ͷ����ΪARROW_LENGTH*sqrt(2)
	static const int N = 22;//20��ָ�ؽڼ���һ������
	static CString files_3ds[N];
	static float defaultPos [N][3];//����ָ�ڵĳ�ʼ����
	void static Initial();//��ʼ��
	void static Initial_3dsFilesName();//��ʼ��Ҫ���ص�3ds�ļ�������
};




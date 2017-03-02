// RobotHand.cpp: implementation of the CRobotHand class.
//������(20��ָ�ؽ�+1������)��Ӧһ��RobotHand
//////////////////////////////////////////////////////////////////////
#pragma warning(disable:4996)

#include "stdafx.h"
#include "3DSLoader.h"
#include "RobotHand.h"
#include "GloableVariable.h"
#include "MatlabEngine.h"
#include <cmath>
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMatlabEngine *engine = NULL;//matlab����

CRobotHand::CRobotHand()
{
	free = 0;
	numobjects = 0;
	maxobjects = 100;

	if (engine == NULL)
	{
		engine = new CMatlabEngine();
		if (!engine->IsInitialized())
		{
			MessageBoxA(NULL, "matlab�����ʼ��ʧ��!", NULL, MB_OK | MB_ICONWARNING);
			engine->GetLastErrorMessage();
		}
		engine->MinimizeWindow();
		//engine->SetWorkspace("E:\\3DSLoader");
		CString path = "cd 'E:\\3DSLoader'";
		engine->Execute(path);
		
		//float* res=CalculateThetaByCoordinate(tVector(22, 150, 0),1);
		//
		//CString str;
		//str.Format("%f,%f,%f,%f",*res, *(res+1), *(res+2), *(res+3));
		//PublicFuntoinHelper::ShowMessage(str);
		//CString[] values=str.
		//engine->Execute("plot([1 2],[3 5],'*r')");


	}
}

//////////////////////////////////////////////////////////////////////////
//			���ݿռ������������Ƕ�,�����ǽǶȶ����ǻ���
float* CRobotHand::CalculateThetaByCoordinate(tVector coordinate,int choice[])
{
	/*if (!engine->IsInitialized())
	{
		return NULL;
	}*/
	CString mstr;
	if(choice[0]){
	mstr.Format("[res] = CalculateThetaByCoordinate_Palm(%f,%f, %f, %f, %f, %f,%f,%f, %f,%f); disp([num2str(res(1)) ',' num2str(res(2)) ',' num2str(res(3)) ',' num2str(res(4))])",
		coordinate.x,coordinate.y,coordinate.z,finger_lengths[0], finger_lengths[1], finger_lengths[2], finger_lengths[3],finger_L[0],finger_d[0],1.0);
	}
	if(choice[1]){
	mstr.Format("[res] = CalculateThetaByCoordinate_Palm(%f,%f, %f, %f, %f, %f,%f,%f, %f,%f); disp([num2str(res(1)) ',' num2str(res(2)) ',' num2str(res(3)) ',' num2str(res(4))])",
		coordinate.x  ,coordinate.y,coordinate.z,finger_lengths[0], finger_lengths[1], finger_lengths[2], finger_lengths[3],finger_L[1],finger_d[1],0.0);
	}
	if(choice[2]){
		mstr.Format("[res] = CalculateThetaByCoordinate_Palm(%f,%f, %f, %f, %f, %f,%f,%f, %f,%f); disp([num2str(res(1)) ',' num2str(res(2)) ',' num2str(res(3)) ',' num2str(res(4))])",
		coordinate.x  ,coordinate.y,coordinate.z,finger_lengths[0], finger_lengths[1], finger_lengths[2], finger_lengths[3],finger_L[2],finger_d[2],0.0);
	}
	if(choice[3]){
		mstr.Format("[res] = CalculateThetaByCoordinate_Palm(%f,%f, %f, %f, %f, %f,%f,%f, %f,%f); disp([num2str(res(1)) ',' num2str(res(2)) ',' num2str(res(3)) ',' num2str(res(4))])",
		coordinate.x  ,coordinate.y,coordinate.z,finger_lengths[0], finger_lengths[1], finger_lengths[2], finger_lengths[3],finger_L[3],finger_d[3],0.0);
	}
	if(choice[4]){
		mstr.Format("[res] = CalculateThetaByCoordinate_Palm(%f,%f, %f, %f, %f, %f,%f,%f, %f,%f); disp([num2str(res(1)) ',' num2str(res(2)) ',' num2str(res(3)) ',' num2str(res(4))])",
		coordinate.x  ,coordinate.y,coordinate.z,finger_lengths[0], finger_lengths[1], finger_lengths[2], finger_lengths[3],finger_L[4],finger_d[4],0.0);
	}
		
	engine->Execute(mstr);
	LPSTR result = NULL;
	VARIANT var = engine->GetLastVResult();
	CString str(var.bstrVal);
	str.Replace(" ", "");
	str.Replace("\n", "");
	return PublicFuntoinHelper::SplitString(str);
}

CRobotHand::~CRobotHand()
{
	for (int i=0; i <numobjects; i++)
	{
		delete objects[i];
	}

	//�ͷ�matlab����ʹ�õ���Դ
	if (engine != NULL)
	{
		engine->Quit();
		delete engine;
		engine = NULL;
	}
}
//////////////////////////////////////////////////////////////////////////
//			��ʼ������ָ�ڵĳ���
//////////////////////////////////////////////////////////////////////////
void CRobotHand::Initial_Length()
{
	for (int index = 0; index < CGloableVariable::N-1;++index)
	{
		int tmp = index % 4;
		objects[index + 1]->length = finger_lengths[index % 4];
		objects[index + 1]->width = finger_lengths[index % 4];
	}
	objects[0]->length = 105.039;//����
	objects[0]->width = 116.901;//����
}

//////////////////////////////////////////////////////////////////////////
//			��ʼ������ָ������
//////////////////////////////////////////////////////////////////////////
void CRobotHand::Initial_CenterPos()
{
	for (int i = 0; i < CGloableVariable::N;i++)
	{
		objects[i]->currentPos.x = CGloableVariable::defaultPos[i][0];
		objects[i]->currentPos.y = CGloableVariable::defaultPos[i][1];
		objects[i]->currentPos.z = CGloableVariable::defaultPos[i][2];
	}
	objects[1]->angle=ConvertAngleToRadian(60);

	Thumb1_Rotate(0);
	Index1_Rotate(0);
	Middle1_Rotate(0);
	Ring1_Rotate(0);
	Little1_Rotate(0);
}

BOOL CRobotHand::add(CKnuckle * _object)
{
	if (numobjects <= maxobjects)
	{
		objects[free] = _object;
		free ++;
		numobjects++;
		return TRUE;
	}
	else return FALSE;
}

//////////////////////////////////////////////////////////////////////////
//			��ʾ��ǰ������
//////////////////////////////////////////////////////////////////////////
void CRobotHand::drawGL()
{
	objects[0]->drawGL();
	for (int i = 1; i <5; i++)
	{

		::glPushMatrix();
		::glTranslatef(objects[i]->currentPos.x, objects[i]->currentPos.y, objects[i]->currentPos.z);
		::glRotatef(objects[i]->sceneRot[1], 0.0F, 1.0F, 0.0F);
		::glRotatef(objects[i]->sceneRot[2], 0.0F, 0.0F, 1.0F);
		::glRotatef(-30, 0.0F, 0.0F, 1.0F);
		::glRotatef(objects[i]->sceneRot[0], 1.0F, 0.0F, 0.0F);
		::glRotatef(30, 0.0F, 0.0F, 1.0F);
		::glTranslatef(-CGloableVariable::defaultPos[i][0], -CGloableVariable::defaultPos[i][1], -CGloableVariable::defaultPos[i][2]);
		objects[i]->drawGL();
		::glPopMatrix();
	}
	for (int i = 5; i <numobjects; i++)
	{
		::glPushMatrix();
		::glTranslatef(objects[i]->currentPos.x, objects[i]->currentPos.y, objects[i]->currentPos.z);
		::glRotatef(objects[i]->sceneRot[1], 0.0F, 1.0F, 0.0F);
		::glRotatef(objects[i]->sceneRot[2], 0.0F, 0.0F, 1.0F);
		::glRotatef(objects[i]->sceneRot[0], 1.0F, 0.0F, 0.0F);
		::glTranslatef(-CGloableVariable::defaultPos[i][0], -CGloableVariable::defaultPos[i][1], -CGloableVariable::defaultPos[i][2]);
		objects[i]->drawGL();
		::glPopMatrix();
	}
}

void CRobotHand::Init()
{
	free = 0;
	numobjects = 0;
	maxobjects = 100;
}

void CRobotHand::doAfterMath()
{
	for (int i=0; i <numobjects; i++)
	{
		objects[i]->applyNormals();

	}
}

void CRobotHand::removeAllObjects()
{
	for (int i=0; i <numobjects; i++)
	{
		delete objects[i];
	}
	numobjects = 0;
	free = 0;
}

CKnuckle* CRobotHand::getObjectByName(char * name)
{
	char* objname;
	for (int i=0; i <numobjects; i++)
	{
		objects[i]->getName(objname);
		if(strcmp(name, objname) == 0) return objects[i];
	}
	
	return NULL;
}

//////////////////////////////////////////////////////////////////////////
//			���Ƕ�ת���ɻ���
//////////////////////////////////////////////////////////////////////////
float CRobotHand::ConvertAngleToRadian(float angle)
{
	return (angle / 180)*PI;
}
//////////////////////////////////////////////////////////////////////////
//			������ת���ɽǶ�
//////////////////////////////////////////////////////////////////////////
float CRobotHand::ConvertRadianToAngle(float radian)
{
	return (radian * 180) / PI;
}

#pragma region �˶�����
//////////////////////////////////////////////////////////////////////////
//		�����ؽڵ��˶�
//////////////////////////////////////////////////////////////////////////
void CRobotHand::RotateFunction(int i , float angle)          //ת������
{
	if(i<=4&&i>0)              //��Ĵָ��ת������
	{
		if(i==1)
		{
	//���angle����0���������ڣ��������Ҳ��    -60<angle<30
	objects[i]->sceneRot[2] += angle;
	//��һ��ָ����������������ָ��ֻ�ܲ����˶�����������ͬһ��ƽ����
	float theta = ConvertAngleToRadian(angle);//���Ƕ�ת���ɻ���
	objects[i]->angle += theta;
	objects[i]->lastPos = objects[i]->currentPos;//������һ������λ��
	
	objects[i]->currentPos.x = -finger_d [(i-1)/4];
	objects[i]->currentPos.y = finger_L [(i-1)/4];
	objects[i]->currentPos.z = objects[0]->currentPos.z;
		}
		if(i==2)
		{
	//�ȰѴ�ָ����б������һָ�ڵĽǶȣ�
	objects[i]->sceneRot[2] =objects[i-1]->sceneRot[2];

	//���angle>0�������ڲ�����(��������),�����������ⲿ����
	objects[i]->sceneRot[0] -= angle;
	//�ڶ���ָ��ֻ�ܽ�������(�����ƿ��������������෴����),���ܽ��в����˶�
	float theta = ConvertAngleToRadian(angle);//���Ƕ�ת���ɻ���
	objects[i]->angle += theta;
	objects[i]->lastPos = objects[i]->currentPos;//������һ������λ��

	objects[i]->currentPos.x = -finger_d[(i-1)/4] +
		(objects[i-1]->length)*cos(objects[i-1]->angle );//x= - di + a1*c(1��+60��)
	objects[i]->currentPos.y = finger_L[(i-1)/4] +
		(objects[i-1]->length)*sin(objects[i-1]->angle );//y=li + a1*c(1��+60��)
	objects[i]->currentPos.z = objects[0]->currentPos.z ;// z= palm.z

		}
		if(i==3)
		{
			objects[i]->sceneRot[2] =objects[i-2]->sceneRot[2];
	objects[i]->sceneRot[0] -= angle;
	float theta = ConvertAngleToRadian(angle);//���Ƕ�ת���ɻ���
	objects[i]->angle += theta;
	objects[i]->lastPos = objects[i]->currentPos;//������һ������λ��

	objects[i]->currentPos.x = -finger_d[(i-1)/4] +
		cos(objects[i-2]->angle)*(objects[i-2]->length +
			((objects[i-1]->length)*cos(objects[i-1]->angle)));//x= - di + c1*(a1 + a2*c2)
	objects[i]->currentPos.y = finger_L[(i-1)/4] +
		sin(objects[i-2]->angle)*(objects[i-2]->length +
			((objects[i-1]->length)*cos(objects[i-1]->angle)));//y=li + s1*(a1 + a2*c2)
	objects[i]->currentPos.z = objects[0]->currentPos.z -
		sin(objects[i-1]->angle)*(objects[i-1]->length);// z=0 - s2*a2
		}
		if(i==4)
		{
			objects[i]->sceneRot[2] =objects[i-3]->sceneRot[2];
	objects[i]->sceneRot[0] -= angle;
	float theta = ConvertAngleToRadian(angle);//���Ƕ�ת���ɻ���
	objects[i]->angle += theta;
	objects[i]->lastPos = objects[i]->currentPos;//������һ������λ��

	objects[i]->currentPos.x = -finger_d[(i-1)/4] +
		cos(objects[i-3]->angle)* (objects [i-3]->length +
		cos(objects[i-2]->angle)* objects[i-2]->length +
		cos(objects[i-1]->angle) * objects[i-1]->length);
	//x=  -di + c1*(a1 + c2*a2 + c23*a3)
	objects[i]->currentPos.y = finger_L[(i-1)/4] +
		sin(objects[i-3]->angle)* (objects [i-3]->length +
		cos(objects[i-2]->angle)* objects[i-2]->length +
		cos(objects[i-1]->angle) * objects[i-1]->length);
	//y=   li + s1*(a1 + c2*a2 + c23*a3)
	objects[i]->currentPos.z = objects[0]->currentPos.z -
		sin(objects[i-2]->angle)* objects [i-2]->length -
		sin(objects[i-1]->angle)* objects[i-1]->length;

		}
	}

else                         //������ָ��ת������
	if(i==5||i==9||i==13||i==17)
	{
		//���angle����0���������ڣ��������Ҳ��
		objects[i]->sceneRot[2] += angle;
		//��һ��ָ����������������ָ��ֻ�ܲ����˶�����������ͬһ��ƽ����
		float theta = ConvertAngleToRadian(angle);//���Ƕ�ת���ɻ���
		objects[i]->angle += theta;
		objects[i]->lastPos = objects[i]->currentPos;//������һ������λ��
		
		objects[i]->currentPos.x = -finger_d [(i-1)/4];
		objects[i]->currentPos.y = finger_L [(i-1)/4];
		objects[i]->currentPos.z = objects[0]->currentPos.z;

	}

	if(i==6||i==10||i==14||i==18)
	{
	//�ȰѴ�ָ����б������һָ�ڵĽǶȣ�
	objects[i]->sceneRot[2] =objects[i-1]->sceneRot[2];

	//���angle>0�������ڲ�����(��������),�����������ⲿ����
	objects[i]->sceneRot[0] -= angle;
	//�ڶ���ָ��ֻ�ܽ�������(�����ƿ��������������෴����),���ܽ��в����˶�
	float theta = ConvertAngleToRadian(angle);//���Ƕ�ת���ɻ���
	objects[i]->angle += theta;
	//objects[i]->lastPos = objects[i]->currentPos;//������һ������λ��

	objects[i]->currentPos.x = -finger_d[(i-1)/4] -
		(objects[i-1]->length)*sin(objects[i-1]->angle);//x= - di - a1*s1
	objects[i]->currentPos.y = finger_L[(i-1)/4] +
		(objects[i-1]->length)*cos(objects[i-1]->angle);//y=li + a1*c1
	objects[i]->currentPos.z = objects[0]->currentPos.z ;// z= palm.z
	}
	if(i==7||i==11||i==15||i==19)
	{
		objects[i]->sceneRot[2] =objects[i-2]->sceneRot[2];
	objects[i]->sceneRot[0] -= angle;
	float theta = ConvertAngleToRadian(angle);//���Ƕ�ת���ɻ���
	objects[i]->angle += theta;
	objects[i]->lastPos = objects[i]->currentPos;//������һ������λ��

	objects[i]->currentPos.x = -finger_d[(i-1)/4] -
		sin(objects[i-2]->angle)*(objects[i-2]->length +
			((objects[i-1]->length)*cos(objects[i-1]->angle)));//x= - di - s1*(a1 + a2*c2)
	objects[i]->currentPos.y = finger_L[(i-1)/4] +
		cos(objects[i-2]->angle)*(objects[i-2]->length +
			((objects[i-1]->length)*cos(objects[i-1]->angle)));//y=li + c1*(a1 + a2*c2)
	objects[i]->currentPos.z = objects[0]->currentPos.z -
		sin(objects[i-1]->angle)*(objects[i-1]->length);//z=0- s2*a2
	}
	if(i==8||i==12||i==16||i==20)
	{
	objects[i]->sceneRot[2] =objects[i-3]->sceneRot[2];
	objects[i]->sceneRot[0] -= angle;
	float theta = ConvertAngleToRadian(angle);//���Ƕ�ת���ɻ���
	objects[i]->angle += theta;
	objects[i]->lastPos = objects[i]->currentPos;//������һ������λ��

	objects[i]->currentPos.x = -finger_d[(i-1)/4] -
		sin(objects[i-3]->angle)* (objects [i-3]->length +
		cos(objects[i-2]->angle)* objects[i-2]->length +
		cos(objects[i-1]->angle ) * objects[i-1]->length);
	//x=  -di - s1*(a1 + c2*a2 + c23*a3)
	objects[i]->currentPos.y = finger_L[(i-1)/4] +
		cos(objects[i-3]->angle)* (objects [i-3]->length +
		cos(objects[i-2]->angle)* objects[i-2]->length +
		cos(objects[i-1]->angle ) * objects[i-1]->length);
	//y=   li + c1*(a1 + c2*a2 + c23*a3))
	objects[i]->currentPos.z = objects[0]->currentPos.z -
		sin(objects[i-2]->angle)* objects [i-2]->length -
		sin(objects[i-1]->angle)*objects[i-1]->length;
	//z= 0- a2*s2 -a3*s23
		
	}
}
//////////////////////////////////////////////////////////////////////////
//			��Ĵָ�����ؽڵ��˶�
//////////////////////////////////////////////////////////////////////////
void CRobotHand::Thumb1_Rotate(float angle)
{
	RotateFunction(THUMB_ONE_INDEX,angle);
	Thumb2_Rotate(0);
}
void CRobotHand::Thumb2_Rotate(float angle)
{
	RotateFunction(THUMB_TWO_INDEX,angle);
	Thumb3_Rotate(0);
}
void CRobotHand::Thumb3_Rotate(float angle)
{
	RotateFunction(THUMB_THREE_INDEX,angle);
	Thumb4_Rotate(0);
}
void CRobotHand::Thumb4_Rotate(float angle)
{
	RotateFunction(THUMB_FOUR_INDEX,angle);
}
void CRobotHand::Index1_Rotate(float angle)
{

	RotateFunction(INDEX_ONE_INDEX,angle);
	Index2_Rotate(0);
}
void CRobotHand::Index2_Rotate(float angle)
{

	RotateFunction(INDEX_TWO_INDEX,angle);
	Index3_Rotate(0);
}
void CRobotHand::Index3_Rotate(float angle)
{

	RotateFunction(INDEX_THREE_INDEX,angle);
	Index4_Rotate(0);
}
void CRobotHand::Index4_Rotate(float angle)
{
	RotateFunction(INDEX_FOUR_INDEX,angle);
}
void CRobotHand::Middle1_Rotate(float angle)
{	
	RotateFunction(MIDDLE_ONE_INDEX,angle);
	Middle2_Rotate(0);
}
void CRobotHand::Middle2_Rotate(float angle)
{
	RotateFunction(MIDDLE_TWO_INDEX,angle);
	Middle3_Rotate(0);
}
void CRobotHand::Middle3_Rotate(float angle)
{
	RotateFunction(MIDDLE_THREE_INDEX,angle);
	Middle4_Rotate(0);
}
void CRobotHand::Middle4_Rotate(float angle)
{
	RotateFunction(MIDDLE_FOUR_INDEX,angle);
}
void CRobotHand::Ring1_Rotate(float angle)
{
	RotateFunction(RING_ONE_INDEX,angle);
	Ring2_Rotate(0);
}
void CRobotHand::Ring2_Rotate(float angle)
{
	RotateFunction(RING_TWO_INDEX,angle);
	Ring3_Rotate(0);
}
void CRobotHand::Ring3_Rotate(float angle)
{
	RotateFunction(RING_THREE_INDEX,angle);
	Ring4_Rotate(0);
}
void CRobotHand::Ring4_Rotate(float angle)
{
	RotateFunction(RING_FOUR_INDEX,angle);
}
void CRobotHand::Little1_Rotate(float angle)
{
	RotateFunction(LITTLE_ONE_INDEX,angle);
	Little2_Rotate(0);
}
void CRobotHand::Little2_Rotate(float angle)
{
	RotateFunction(LITTLE_TWO_INDEX,angle);
	Little3_Rotate(0);
}
void CRobotHand::Little3_Rotate(float angle)
{
	RotateFunction(LITTLE_THREE_INDEX,angle);
	Little4_Rotate(0);
}
void CRobotHand::Little4_Rotate(float angle)
{
	RotateFunction(LITTLE_FOUR_INDEX,angle);
}
#pragma endregion



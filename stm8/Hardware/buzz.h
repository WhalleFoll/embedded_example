#ifndef _BUZZ_H_
#define _BUZZ_H_

#include "sys.h"

#define BUZZ        PD_ODR_ODR4
#define  proport   1000000 //Tclk/(psc+1)=72000000/(7199+1)
//F��
/*
 #define  L1       ((proport/349)-1)//�͵���do �����ڸ���Tout= ((arr+1)*(psc+1))/Tclk�Ƴ�arrֵ���Ǳ���define�����ֵ��ToutΪ����Ƶ��131Hz�ĵ�����Tclk=72MHz
 #define  L2       ((proport/392)-1)//�͵���re ������
 #define  L3       ((proport/440)-1)//�͵���mi ������
 #define  L4       ((proport/464)-1)//�͵���fa ������
 #define  L5       ((proport/523)-1)//�͵���sol������
 #define  L6       ((proport/587)-1)//�͵���la ������
 #define  L7       ((proport/659)-1)//�͵���si ������

 #define  M1       ((proport/698)-1)//�е���do ������
 #define  M2       ((proport/784)-1)//�е���re ������
 #define  M3       ((proport/880)-1)//�е���mi ������ 
 #define  M4       ((proport/932)-1)//�е���fa ������
 #define  M5       ((proport/1046)-1)//�е���sol������
 #define  M6       ((proport/1175)-1)//�е���la ������
 #define  M7       ((proport/1318)-1)//�е���si ������

 #define  H1       ((proport/1396)-1)//�ߵ���do ������
 #define  H2       ((proport/1568)-1)//�ߵ���re ������
 #define  H3       ((proport/1760)-1)//�ߵ���mi ������
 #define  H4       ((proport/1865)-1)//�ߵ���fa ������
 #define  H5       ((proport/2092)-1)//�ߵ���sol������
 #define  H6       ((proport/2347)-1)//�ߵ���la ������
 #define  H7       ((proport/2632)-1)//�ߵ���si ������
*/
//��

 #define  L1       ((proport/262)-1)//�͵���do �����ڸ���Tout= ((arr+1)*(psc+1))/Tclk�Ƴ�arrֵ���Ǳ���define�����ֵ��ToutΪ����Ƶ��131Hz�ĵ�����Tclk=72MHz
 #define  L2       ((proport/294)-1)//�͵���re ������
 #define  L3       ((proport/330)-1)//�͵���mi ������
 #define  L4       ((proport/349)-1)//�͵���fa ������
 #define  L5       ((proport/392)-1)//�͵���sol������
 #define  L6       ((proport/440)-1)//�͵���la ������
 #define  L7       ((proport/494)-1)//�͵���si ������

 #define  M1       ((proport/523)-1)//�е���do ������
 #define  M2       ((proport/578)-1)//�е���re ������
 #define  M3       ((proport/659)-1)//�е���mi ������ 
 #define  M4       ((proport/698)-1)//�е���fa ������
 #define  M5       ((proport/784)-1)//�е���sol������
 #define  M6       ((proport/880)-1)//�е���la ������
 #define  M7       ((proport/988)-1)//�е���si ������

 #define  H1       ((proport/1044)-1)//�ߵ���do ������
 #define  H2       ((proport/1170)-1)//�ߵ���re ������
 #define  H3       ((proport/1314)-1)//�ߵ���mi ������
 #define  H4       ((proport/1392)-1)//�ߵ���fa ������
 #define  H5       ((proport/1562)-1)//�ߵ���sol������
 #define  H6       ((proport/1754)-1)//�ߵ���la ������
 #define  H7       ((proport/1970)-1)//�ߵ���si ������

//�ܵ�
/*
 #define  L1       ((proport/131)-1)//�͵���do �����ڸ���Tout= ((arr+1)*(psc+1))/Tclk�Ƴ�arrֵ���Ǳ���define�����ֵ��ToutΪ����Ƶ��131Hz�ĵ�����Tclk=72MHz
 #define  L2       ((proport/147)-1)//�͵���re ������
 #define  L3       ((proport/165)-1)//�͵���mi ������
 #define  L4       ((proport/176)-1)//�͵���fa ������
 #define  L5       ((proport/196)-1)//�͵���sol������
 #define  L6       ((proport/220)-1)//�͵���la ������
 #define  L7       ((proport/247)-1)//�͵���si ������

 #define  M1       ((proport/262)-1)//�е���do ������
 #define  M2       ((proport/296)-1)//�е���re ������
 #define  M3       ((proport/330)-1)//�е���mi ������ 
 #define  M4       ((proport/349)-1)//�е���fa ������
 #define  M5       ((proport/392)-1)//�е���sol������
 #define  M6       ((proport/440)-1)//�е���la ������
 #define  M7       ((proport/494)-1)//�е���si ������

 #define  H1       ((proport/523)-1)//�ߵ���do ������
 #define  H2       ((proport/587)-1)//�ߵ���re ������
 #define  H3       ((proport/659)-1)//�ߵ���mi ������
 #define  H4       ((proport/699)-1)//�ߵ���fa ������
 #define  H5       ((proport/784)-1)//�ߵ���sol������
 #define  H6       ((proport/880)-1)//�ߵ���la ������
 #define  H7       ((proport/988)-1)//�ߵ���si ������
*/

void Buzz_Init(void);

#endif


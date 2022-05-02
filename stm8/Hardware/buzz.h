#ifndef _BUZZ_H_
#define _BUZZ_H_

#include "sys.h"

#define BUZZ        PD_ODR_ODR4
#define  proport   1000000 //Tclk/(psc+1)=72000000/(7199+1)
//F调
/*
 #define  L1       ((proport/349)-1)//低调　do 的周期根据Tout= ((arr+1)*(psc+1))/Tclk推出arr值就是本句define定义的值，Tout为音调频率131Hz的倒数，Tclk=72MHz
 #define  L2       ((proport/392)-1)//低调　re 的周期
 #define  L3       ((proport/440)-1)//低调　mi 的周期
 #define  L4       ((proport/464)-1)//低调　fa 的周期
 #define  L5       ((proport/523)-1)//低调　sol的周期
 #define  L6       ((proport/587)-1)//低调　la 的周期
 #define  L7       ((proport/659)-1)//低调　si 的周期

 #define  M1       ((proport/698)-1)//中调　do 的周期
 #define  M2       ((proport/784)-1)//中调　re 的周期
 #define  M3       ((proport/880)-1)//中调　mi 的周期 
 #define  M4       ((proport/932)-1)//中调　fa 的周期
 #define  M5       ((proport/1046)-1)//中调　sol的周期
 #define  M6       ((proport/1175)-1)//中调　la 的周期
 #define  M7       ((proport/1318)-1)//中调　si 的周期

 #define  H1       ((proport/1396)-1)//高调　do 的周期
 #define  H2       ((proport/1568)-1)//高调　re 的周期
 #define  H3       ((proport/1760)-1)//高调　mi 的周期
 #define  H4       ((proport/1865)-1)//高调　fa 的周期
 #define  H5       ((proport/2092)-1)//高调　sol的周期
 #define  H6       ((proport/2347)-1)//高调　la 的周期
 #define  H7       ((proport/2632)-1)//高调　si 的周期
*/
//中

 #define  L1       ((proport/262)-1)//低调　do 的周期根据Tout= ((arr+1)*(psc+1))/Tclk推出arr值就是本句define定义的值，Tout为音调频率131Hz的倒数，Tclk=72MHz
 #define  L2       ((proport/294)-1)//低调　re 的周期
 #define  L3       ((proport/330)-1)//低调　mi 的周期
 #define  L4       ((proport/349)-1)//低调　fa 的周期
 #define  L5       ((proport/392)-1)//低调　sol的周期
 #define  L6       ((proport/440)-1)//低调　la 的周期
 #define  L7       ((proport/494)-1)//低调　si 的周期

 #define  M1       ((proport/523)-1)//中调　do 的周期
 #define  M2       ((proport/578)-1)//中调　re 的周期
 #define  M3       ((proport/659)-1)//中调　mi 的周期 
 #define  M4       ((proport/698)-1)//中调　fa 的周期
 #define  M5       ((proport/784)-1)//中调　sol的周期
 #define  M6       ((proport/880)-1)//中调　la 的周期
 #define  M7       ((proport/988)-1)//中调　si 的周期

 #define  H1       ((proport/1044)-1)//高调　do 的周期
 #define  H2       ((proport/1170)-1)//高调　re 的周期
 #define  H3       ((proport/1314)-1)//高调　mi 的周期
 #define  H4       ((proport/1392)-1)//高调　fa 的周期
 #define  H5       ((proport/1562)-1)//高调　sol的周期
 #define  H6       ((proport/1754)-1)//高调　la 的周期
 #define  H7       ((proport/1970)-1)//高调　si 的周期

//很低
/*
 #define  L1       ((proport/131)-1)//低调　do 的周期根据Tout= ((arr+1)*(psc+1))/Tclk推出arr值就是本句define定义的值，Tout为音调频率131Hz的倒数，Tclk=72MHz
 #define  L2       ((proport/147)-1)//低调　re 的周期
 #define  L3       ((proport/165)-1)//低调　mi 的周期
 #define  L4       ((proport/176)-1)//低调　fa 的周期
 #define  L5       ((proport/196)-1)//低调　sol的周期
 #define  L6       ((proport/220)-1)//低调　la 的周期
 #define  L7       ((proport/247)-1)//低调　si 的周期

 #define  M1       ((proport/262)-1)//中调　do 的周期
 #define  M2       ((proport/296)-1)//中调　re 的周期
 #define  M3       ((proport/330)-1)//中调　mi 的周期 
 #define  M4       ((proport/349)-1)//中调　fa 的周期
 #define  M5       ((proport/392)-1)//中调　sol的周期
 #define  M6       ((proport/440)-1)//中调　la 的周期
 #define  M7       ((proport/494)-1)//中调　si 的周期

 #define  H1       ((proport/523)-1)//高调　do 的周期
 #define  H2       ((proport/587)-1)//高调　re 的周期
 #define  H3       ((proport/659)-1)//高调　mi 的周期
 #define  H4       ((proport/699)-1)//高调　fa 的周期
 #define  H5       ((proport/784)-1)//高调　sol的周期
 #define  H6       ((proport/880)-1)//高调　la 的周期
 #define  H7       ((proport/988)-1)//高调　si 的周期
*/

void Buzz_Init(void);

#endif


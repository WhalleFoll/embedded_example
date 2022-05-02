#include "header.h"
#include "time.h"
#include <windows.h>
#include <stdio.h>
//循环左移和循环右移
//#define CROR(value,bits)(((value)>>(bits))|((value)<<(32-bits)))
//#define CROL(value,bits)(((value)<<(bits))|((value)>>(32-bits)))

uint32 g_device_id[250];



/*********************************************************************************
  *Function: search_init
  *Description：generate 255 random numbers
  *Calls:  
			rand();
			srand(unsigned int);
  *Called By:  main()
  *Input:   None
  *Output:  Save the data to g_device_id[255]
  *Return:  None
  *Others:  None
**********************************************************************************/
void search_init(void){
	int32 i,j;
	//设置随机数种子
	srand((unsigned int)time(0));
	//生成255个随机id 
	for(i=0;i<255;i++){		
			for(j=0;j<8;j++)
			g_device_id[i]=g_device_id[i]*16+rand()%10;
	}
	//输出生成的255个设备id 
	for(i=0;i<255;i++){
		printf("第%3d设备   ID:  0x%08x\n",i,g_device_id[i]);
	}
}
/*********************************************************************************
  *Function: read_device
  *Description：read & find device and return the result 
  *Calls:  printf()
  *Called By:  main()
  *Input:   unsigned int device_id_in,
			unsigned int *pdevice_id_out
  *Output:  print search result to screen
  *Return:  
			0 - find no device
			1 - find the only one device
			2 - collision (more than one device) 
  *Others:  None
**********************************************************************************/
int read_device(unsigned int device_id_in,unsigned int *pdevice_id_out){
	int32 i,j;
	int32 findNum=255;
	uint32 mask=0xF0000000;
	int32 count=0;	
	uint32 temp_device_id[255];
	for(i=0;i<255;i++){
		temp_device_id[i]=g_device_id[i];
	}
	for(i=0;i<8;i++){
			for(j=0;j<findNum;j++){
			
				if((device_id_in&mask)==(temp_device_id[j]&mask) || (	(device_id_in&mask)==mask )  ) {
					temp_device_id[count++]=temp_device_id[j];
				}
			}
			findNum=count;
			count=0;
		
			mask=(mask>>4)&(~mask);
	}
	//模拟总线传输延时500ms
	Sleep(500);
	if(findNum==0){
		return 0;
	}
	else if(findNum>1) {
		for(j=0;j<findNum;j++)
		printf("find %03d device,  id:  0x%08x\n",j,temp_device_id[j]);
		return 2;
	}
	else if(findNum==1) {
		for(j=0;j<findNum;j++)
		printf("find %03d device,  id:  0x%08x\n",j,temp_device_id[j]);
		*pdevice_id_out=temp_device_id[0];
		return 1;
	}
	
	return 10;
}
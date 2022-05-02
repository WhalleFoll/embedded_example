#include <stdio.h>
#include "header.h"
#include "time.h"
/*********************************************************************************
  *Function:  main
  *Description：main function
  *Calls:  
			void search_init(void);
			int read_device(unsigned int device_id_in,unsigned int *pdevice_id_out);
			clock();
			printf();
			scanf();
  *Called By:  None
  *Input:   None
  *Output:  search result message
  *Return:  None
  *Others:  None
**********************************************************************************/
void main(){
	int32 ret_val;
	uint32 device_id;
	clock_t start,finish;
	double duration;
	int32 i=0;
	uint32 ret_id;

	printf("请输入要查询的内容，F为掩码： 0x");
	search_init();

	scanf("%x",&device_id);

	ret_val=read_device(device_id,&ret_id);
	


}

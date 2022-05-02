#include  <ADLX345.h>	
BYTE BUF[8];                         //接收数据缓存区      	
uchar ge,shi,bai,qian,wan;           //显示变量
int  dis_data;                       //变量
float flag=2;
unsigned char a[4];

//*********************************************************
void conversion(uint temp_data)  
{  
    wan=temp_data/10000+0x30 ;
    temp_data=temp_data%10000;   //取余运算
	qian=temp_data/1000+0x30 ;
    temp_data=temp_data%1000;    //取余运算
    bai=temp_data/100+0x30   ;
    temp_data=temp_data%100;     //取余运算
    shi=temp_data/10+0x30    ;
    temp_data=temp_data%10;      //取余运算
    ge=temp_data+0x30; 
      a[0]=qian;
	  a[1]=bai;
	  a[2]=shi;
	  a[3]=ge;
}

/*******************************/
void delay1(unsigned int k)	
{						
unsigned int i,j;				
	for(i=0;i<k;i++)
	{			
	for(j=0;j<121;j++)			
	{;}}						
}
/*******************************/
/*void WaitForEnable(void)	
{					
	DataPort=0xff;		
	LCM_RS=0;LCM_RW=1;_nop_();
	LCM_EN=1;_nop_();_nop_();
	while(DataPort&0x80);	
	LCM_EN=0;				
}*/					
/*******************************/
/*void WriteCommandLCM(uchar CMD,uchar Attribc)
{					
	if(Attribc)WaitForEnable();	
	LCM_RS=0;LCM_RW=0;_nop_();
	DataPort=CMD;_nop_();	
	LCM_EN=1;_nop_();_nop_();LCM_EN=0;
}	*/				
/*******************************/
/*void WriteDataLCM(uchar dataW)
{					
	WaitForEnable();		
	LCM_RS=1;LCM_RW=0;_nop_();
	DataPort=dataW;_nop_();	
	LCM_EN=1;_nop_();_nop_();LCM_EN=0;
}	*/	
/***********************************/
/*void InitLcd()				
{			
	WriteCommandLCM(0x38,1);	
	WriteCommandLCM(0x08,1);	
	WriteCommandLCM(0x01,1);	
	WriteCommandLCM(0x06,1);	
	WriteCommandLCM(0x0c,1);
}	*/		
/***********************************/
/*void DisplayOneChar(uchar X,uchar Y,uchar DData)
{						
	Y&=1;						
	X&=15;						
	if(Y)X|=0x40;					
	X|=0x80;			
	WriteCommandLCM(X,0);		
	WriteDataLCM(DData);		
}	*/					

/**************************************
延时5微秒(STC90C52RC---12MHz---12T)
不同的工作环境,需要调整此函数，注意时钟过快时需要修改
当改用1T的MCU时,请调整此延时函数
**************************************/
void delay15us()
{
    _nop_();_nop_();_nop_();_nop_();
    _nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
}

/**************************************
延时5毫秒(STC90C52RC@12M)
不同的工作环境,需要调整此函数
当改用1T的MCU时,请调整此延时函数
**************************************/
void delay15ms()
{
    WORD n = 560;

    while (n--);
}

/**************************************
起始信号
**************************************/
void ADXL345_Start()
{
    SDA = 1;                    //拉高数据线
    SCL = 1;                    //拉高时钟线
    delay15us();                 //延时
    SDA = 0;                    //产生下降沿
    delay15us();                 //延时
    SCL = 0;                    //拉低时钟线
}

/**************************************
停止信号
**************************************/
void ADXL345_Stop()
{
    SDA = 0;                    //拉低数据线
    SCL = 1;                    //拉高时钟线
    delay15us();                 //延时
    SDA = 1;                    //产生上升沿
    delay15us();                 //延时
}

/**************************************
发送应答信号
入口参数:ack (0:ACK 1:NAK)
**************************************/
void ADXL345_SendACK(bit ack)
{
    SDA = ack;                  //写应答信号
    SCL = 1;                    //拉高时钟线
    delay15us();                 //延时
    SCL = 0;                    //拉低时钟线
    delay15us();                 //延时
}

/**************************************
接收应答信号
**************************************/
bit ADXL345_RecvACK()
{
    SCL = 1;                    //拉高时钟线
    delay15us();                 //延时
    CY = SDA;                   //读应答信号
    SCL = 0;                    //拉低时钟线
    delay15us();                 //延时

    return CY;
}

/**************************************
向IIC总线发送一个字节数据
**************************************/
void ADXL345_SendByte(BYTE dat)
{
    BYTE i;

    for (i=0; i<8; i++)         //8位计数器
    {
        dat <<= 1;              //移出数据的最高位
        SDA = CY;               //送数据口
        SCL = 1;                //拉高时钟线
        delay15us();             //延时
        SCL = 0;                //拉低时钟线
        delay15us();             //延时
    }
    ADXL345_RecvACK();
}

/**************************************
从IIC总线接收一个字节数据
**************************************/
BYTE ADXL345_RecvByte()
{
    BYTE i;
    BYTE dat = 0;

    SDA = 1;                    //使能内部上拉,准备读取数据,
    for (i=0; i<8; i++)         //8位计数器
    {
        dat <<= 1;
        SCL = 1;                //拉高时钟线
        delay15us();             //延时
        dat |= SDA;             //读数据               
        SCL = 0;                //拉低时钟线
        delay15us();             //延时
    }
    return dat;
}

//******单字节写入*******************************************

void Single_Write_ADXL345(uchar REG_Address,uchar REG_data)
{
    ADXL345_Start();                  //起始信号
    ADXL345_SendByte(SlaveAddress);   //发送设备地址+写信号
    ADXL345_SendByte(REG_Address);    //内部寄存器地址，请参考中文pdf22页 
    ADXL345_SendByte(REG_data);       //内部寄存器数据，请参考中文pdf22页 
    ADXL345_Stop();                   //发送停止信号
}

//********单字节读取*****************************************
uchar Single_Read_ADXL345(uchar REG_Address)
{  uchar REG_data;
    ADXL345_Start();                          //起始信号
    ADXL345_SendByte(SlaveAddress);           //发送设备地址+写信号
    ADXL345_SendByte(REG_Address);            //发送存储单元地址，从0开始	
    ADXL345_Start();                          //起始信号
    ADXL345_SendByte(SlaveAddress+1);         //发送设备地址+读信号
    REG_data=ADXL345_RecvByte();              //读出寄存器数据
	ADXL345_SendACK(1);   
	ADXL345_Stop();                           //停止信号
    return REG_data; 
}
//*********************************************************
//
//连续读出ADXL345内部加速度数据，地址范围0x32~0x37
//
//*********************************************************
void Multiple_read_ADXL345(void)
{   uchar i;
    ADXL345_Start();                          //起始信号
    ADXL345_SendByte(SlaveAddress);           //发送设备地址+写信号
    ADXL345_SendByte(0x32);                   //发送存储单元地址，从0x32开始	
    ADXL345_Start();                          //起始信号
    ADXL345_SendByte(SlaveAddress+1);         //发送设备地址+读信号
	 for (i=0; i<6; i++)                      //连续读取6个地址数据，存储中BUF
    {
        BUF[i] = ADXL345_RecvByte();          //BUF[0]存储0x32地址中的数据
        if (i == 5)
        {
           ADXL345_SendACK(1);                //最后一个数据需要回NOACK
        }
        else
        {
          ADXL345_SendACK(0);                //回应ACK
       }
   }
    ADXL345_Stop();                          //停止信号
    delay15ms();
}


//*****************************************************************

//初始化ADXL345，根据需要请参考pdf进行修改************************
void Init_ADXL345()
{
   Single_Write_ADXL345(0x31,0x0B);   //测量范围,正负16g，13位模式
   Single_Write_ADXL345(0x2C,0x08);   //速率设定为12.5 参考pdf13页
   Single_Write_ADXL345(0x2D,0x08);   //选择电源模式   参考pdf24页
   Single_Write_ADXL345(0x2E,0x80);   //使能 DATA_READY 中断
   Single_Write_ADXL345(0x1E,0x00);   //X 偏移量 根据测试传感器的状态写入pdf29页
   Single_Write_ADXL345(0x1F,0x00);   //Y 偏移量 根据测试传感器的状态写入pdf29页
   Single_Write_ADXL345(0x20,0x05);   //Z 偏移量 根据测试传感器的状态写入pdf29页
}
//***********************************************************************
//显示x轴
void display_x()
{   float temp;
    dis_data=(BUF[1]<<8)+BUF[0];  //合成数据   
	if(dis_data<0){
	dis_data=-dis_data;
   // DisplayOneChar(10,0,'-');      //显示正负符号位
	}
	//else DisplayOneChar(10,0,' '); //显示空格
    
    temp=(float)dis_data*3.9;  //计算数据和显示,查考ADXL345快速入门第4页
	if(temp>400)
	{
	  LED=0;
	}
	else
	{
		 LED=1; 
	}
    conversion(temp);          //转换出显示需要的数据
	/*	DisplayOneChar(8,0,'X');
    DisplayOneChar(9,0,':'); 
    DisplayOneChar(11,0,qian); 
		DisplayOneChar(12,0,'.'); 
    DisplayOneChar(13,0,bai); 
    DisplayOneChar(14,0,shi); 
		DisplayOneChar(15,0,' ');
*/	
}

//***********************************************************************
//显示y轴
void display_y()
{     float temp;
    dis_data=(BUF[3]<<8)+BUF[2];  //合成数据   
	if(dis_data<0){
	dis_data=-dis_data;}
	
	
   /*DisplayOneChar(2,1,'-');      //显示正负符号位
	
	else DisplayOneChar(2,1,' '); //显示空格
*/
	
    temp=(float)dis_data*3.9;  //计算数据和显示,查考ADXL345快速入门第4页
	if(temp>400)
	{
	  LED=0;
	}
	else
	{
		 LED=1; 
	}
    conversion(temp);          //转换出显示需要的数据
	/*	DisplayOneChar(0,1,'Y');   //第1行，第0列 显示y
    DisplayOneChar(1,1,':'); 
    DisplayOneChar(3,1,qian); 
		DisplayOneChar(4,1,'.'); 
    DisplayOneChar(5,1,bai); 
    DisplayOneChar(6,1,shi);  
		DisplayOneChar(7,1,' ');*/  
}

//***********************************************************************
//显示z轴
void display_z()
{
    float temp;
    dis_data=(BUF[5]<<8)+BUF[4];    //合成数据   
	if(dis_data<0){
	dis_data=-dis_data;
//    DisplayOneChar(10,1,'-');       //显示负符号位
	}
	//else DisplayOneChar(10,1,' ');  //显示空格
   
    temp=(float)dis_data*3.9;  //计算数据和显示,查考ADXL345快速入门第4页
    conversion(temp);          //转换出显示需要的数据		
	  if(qian=='1')
		{
		   GSM_TEXT();
       GSM_TEXT_SMS();
		
		}
	  SendString2(a);
	  SendString2("\r\n");  
	/*	DisplayOneChar(8,1,'Z');  //第0行，第10列 显示Z
    DisplayOneChar(9,1,':'); 
    DisplayOneChar(11,1,qian); 
		DisplayOneChar(12,1,'.'); 
    DisplayOneChar(13,1,bai); 
    DisplayOneChar(14,1,shi); 
		DisplayOneChar(15,1,' ');  */
}


//*********************************************************
//******主程序********
//*********************************************************
void ADXL345_deal()
{ 
	uchar devid;
	delay1(500);	                   	//上电延时		
	//InitLcd();                      //液晶初始化ADXL345
	
/*	DisplayOneChar(0,0,'A');
	DisplayOneChar(1,0,'D'); 
	DisplayOneChar(2,0,'X'); 
	DisplayOneChar(3,0,'L'); 
	DisplayOneChar(4,0,'3'); 
	DisplayOneChar(5,0,'4');  
	DisplayOneChar(6,0,'5');
	
	//Init_ADXL345();                 	//初始化ADXL345
	//devid=Single_Read_ADXL345(0X00);	//读出的数据为0XE5,表示正确
	 
		DisplayOneChar(0,0,'A');
		DisplayOneChar(1,0,'D'); 
		DisplayOneChar(2,0,'X'); 
		DisplayOneChar(3,0,'L'); 
		DisplayOneChar(4,0,'3'); 
		DisplayOneChar(5,0,'4');  
		DisplayOneChar(6,0,'5'); */ 
	
		Init_ADXL345();                 	//初始化ADXL345
		devid=Single_Read_ADXL345(0X00);	//读出的数据为0XE5,表示正确
		if(devid!=0XE5)
		{			P2=0x00;
			/*DisplayOneChar(8,0,'N');
			DisplayOneChar(9,0,'o');		
			DisplayOneChar(10,0,' ');		
			DisplayOneChar(11,0,'F');
			DisplayOneChar(12,0,'i');
			DisplayOneChar(13,0,'n');
			DisplayOneChar(14,0,'d');		
			DisplayOneChar(15,0,'!');		
			//
			DisplayOneChar(0,1,' ');   //第1行，第0列 显示y
			DisplayOneChar(1,1,' '); 
			DisplayOneChar(2,1,' '); 	
			DisplayOneChar(3,1,' '); 
			DisplayOneChar(4,1,' '); 
			DisplayOneChar(5,1,' '); 
			DisplayOneChar(6,1,' ');  
			DisplayOneChar(7,1,' ');  
			DisplayOneChar(8,1,' ');  //第0行，第10列 显示Z
			DisplayOneChar(9,1,' '); 
			DisplayOneChar(11,1,' '); 
			DisplayOneChar(12,1,' '); 
			DisplayOneChar(13,1,' '); 
			DisplayOneChar(14,1,' '); 
			DisplayOneChar(15,1,' ');*/  			
			
		}
		else
		{			
			Multiple_Read_ADXL345();       	//连续读出数据，存储在BUF中
			display_x();                   	//---------显示X轴
			display_y();                   	//---------显示Y轴
			display_z();              			//---------显示Z轴	
      		
		}      
		//delay1(350);                    	//延时  
	
} 
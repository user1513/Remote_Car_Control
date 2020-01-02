
版本号：MainControlBoardV2stc8-24MHz-V1.1
更新日期：2020-01-02
更新内容：增加模式切换  
1.更改了新的数据包格式(具体请见数据包格式.xlsx)
2.取消了由遥控接收板发送开炮指令
3.增加了部分裁剪功能
4.默认低电平为普通小车,高电平为麦克纳姆轮(只有重新上电功能才会切换)


版本号：MainControlBoardV2stc8-24MHz-V1.0
更新日期：2018-08-29
更新内容：增加模式切换  
<pbdata.h> #define MotorWheelMode P17 
<djiReceiver_dr16.h>
if(MotorMode==0) Data_able[10] |=0x01;//判断P17口是高低电平
else Data_able[10] &=~0x01;	


McNaim
默认低电平为普通小车,高电平为麦克纳姆轮

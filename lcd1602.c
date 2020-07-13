#include <reg52.h>
typedef unsigned char uchar;
typedef unsigned int uint;
uchar code table[] = {"Welcome!"};
uchar code ren[] = {"RenShu:"};
uchar code dat[2];
sbit RS = P3^5;         //RS端
sbit RW = P3^6;
sbit EN = P3^4;         //EN端
sbit du=P2^6;
sbit we=P2^7;
sbit k1=P3^0;
sbit k2=P3^1;
uint num,i,c;
void delay(uint z)
{
        uint x,y;
        for(x = z; x > 0; x--)
                for(y = 114; y > 0 ; y--);
}
void Read_Busy()
{
        uchar busy;
        P0 = 0xff;
        RS = 0;
        RW = 1;
        do
        {
                EN = 1;
                busy = P0;
                EN = 0;
        }while(busy & 0x80);
}
void Write_Cmd(uchar cmd)
{
        Read_Busy();//判断忙
        RS = 0;
        RW = 0;
        P0 = cmd;
        EN = 1;
        EN = 0;
}
//写一个字节数据
void Write_Dat(uchar dat)
{
        Read_Busy();
        RS = 1;
        RW = 0;
        P0 = dat;
        EN = 1;
        EN = 0;
}
void Init_LCD1602()
{
        du=0;
        we=0;
        EN=0;
        Write_Cmd(0x38); //        设置16*2显示，5*7点阵，8位数据接口
        Write_Cmd(0x0c);        
        Write_Cmd(0x06); //读写一字节后地址指针加1
        Write_Cmd(0x01); //清除显示
}
void key()
{
         if(k1==0)
                   {
                                   delay(5);
                                if(k1==0)
                                {                        
                c++;
                                }
                                while(!k1);
                   }
        if(k2==0)
                   {
                                   delay(5);
                                if(k2==0)
                                {
                c--;
                                }
                                while(!k2);
                   }
}
void main()
{
Init_LCD1602();//1602初始化
        c=0;        
while(1)
{ 
        Write_Cmd(0x80 | 0x00);//显示地址
        for(num=0;num<8;num++)
        {
                 Write_Dat(table[num]);
                 delay(5);        
        }
        Write_Cmd(0x80 | 0x40);//显示地址
        for(i=0;i<7;i++)
        {
                 Write_Dat(ren[i]);
                 delay(5);        
        } 
    Write_Cmd(0x80 | 0x48);//设置显示地址0x00,第一行从第一个字符开始显示 
        key();
        Write_Dat(c/10+0x30);
    Write_Dat(c%10+0x30);
        }
}

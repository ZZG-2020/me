#ifndef _CARD_H
#define _CARD_H

typedef struct _CMD
{
  unsigned char ReceiveBuffer[14];
  unsigned char ReceivePoint;
}CMD;
/* 外部变量 -------------------------------------------------------------------*/
extern xdata CMD Cmd;
/* 外部函数 ------------------------------------------------------------------ */
#endif /* __Uart_H */

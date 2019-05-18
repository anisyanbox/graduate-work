#ifndef _INC_MAIN_H_
#define _INC_MAIN_H_

#define MAIN_THREAD_NORMAL_PRIO ((int)0)

typedef enum {
  UART_INIT_ERROR = 0,
  LED_INIT_ERROR,
  KEYBOARD_INIT_ERROR
} ErrFlags;

#endif  // _INC_MAIN_H_

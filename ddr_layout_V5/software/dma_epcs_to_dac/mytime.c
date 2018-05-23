
#include "system.h"                   // 系统

#include "altera_avalon_timer_regs.h" // 定时器

#include "sys/alt_irq.h"              // 中断

//

unsigned int timer_isr_context; // 定义全局变量以储存isr_context指针

void Timer_Initial(void);

void Timer_ISR(void* isr_context);
int time_1s=0;
//

// 定时器中断初始化

void Timer_Initial(void)

{

  // 改写timer_isr_context指针以匹配alt_irq_register()函数原型

  void* isr_context_ptr = (void*) &timer_isr_context;

  // 设置PERIOD寄存器

  // PERIODH << 16 | PERIODL = 计数器周期因子 * 系统时钟频率因子 - 1

  // PERIODH << 16 | PERIODL = 5m*100M - 1 = 499999 = 0x7A11F

  IOWR_ALTERA_AVALON_TIMER_PERIODH(SYSTIMER_BASE, (SYSTIMER_FREQ-1)>>16);

  IOWR_ALTERA_AVALON_TIMER_PERIODL(SYSTIMER_BASE, (SYSTIMER_FREQ-1)&0xffff);

 

  // 设置CONTROL寄存器

  //    位数 |  3   |  2   |  1   |  0  |

  // CONTROL | STOP | START| CONT | ITO |

  // ITO   1，产生IRO；                      0，不产生IRQ

  // CONT  1，计数器连续运行直到STOP被置一；   0，计数到0停止

  // START 1，计数器开始运行；                0，无影响

  // STOP  1，计数器停止运行；                0，无影响

  IOWR_ALTERA_AVALON_TIMER_CONTROL(SYSTIMER_BASE,

    ALTERA_AVALON_TIMER_CONTROL_START_MSK | // START = 1

    ALTERA_AVALON_TIMER_CONTROL_CONT_MSK  | // CONT  = 1

    ALTERA_AVALON_TIMER_CONTROL_ITO_MSK);   // ITO   = 1

  // 注册定时器中断

  alt_ic_isr_register(

      SYSTIMER_IRQ_INTERRUPT_CONTROLLER_ID, // 中断控制器标号，从system.h复制

      SYSTIMER_IRQ,     // 硬件中断号，从system.h复制

      Timer_ISR,              // 中断服务子函数

      isr_context_ptr,        // 指向与设备驱动实例相关的数据结构体

      0x0);                   // flags，保留未用

}

// 定时器中断服务子函数

void Timer_ISR(void* timer_isr_context)

{

  // 应答中断，将STATUS寄存器清零

  IOWR_ALTERA_AVALON_TIMER_STATUS(SYSTIMER_BASE,

      ~ ALTERA_AVALON_TIMER_STATUS_TO_MSK);   // TO = 0

 time_1s=1;

  // 用户中断代码

}

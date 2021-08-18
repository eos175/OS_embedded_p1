#include <asm.h>
#include <kernel/irq.h>
#include <stdint.h>

volatile uint64_t timer_ticks = 0;

void pit_phase(int hz) {
  int divisor = 1193180 / hz;
  outb(0x43, 0x36);
  outb(0x40, divisor & 0xFF);
  outb(0x40, divisor >> 8);
}

void pit_handler() { timer_ticks++; }


void sleep(uint64_t ticks) {
    /*
  uint64_t rest_ticks = timer_ticks + ticks;
  while (timer_ticks < rest_ticks)
    ;
    */

    uint64_t ms = ticks << 8;
    for (uint64_t i = 0; i < ms; i++)
    {
        asm volatile ("nop");
    }
    
}



int init_pit() {
  pit_phase(1000); // Phase to vibrate once every millisecond;
  irq_install_handler(0, pit_handler);
  return 0;
}

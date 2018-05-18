char button_click, button2_click, button3_click, button4_click, clicked,

static void switch_update_interrupt_sense(){
  switches_current = P2IN & switch_mask;

  P2IES |= (switches_current);
  P2IES &= (switches_current | ~switch_mask);
}

void p2sw_init(unsigned char mask){
  switch_mask = mask;
  P2REN |= mask;
  P@IE = mask;
  P2OUT |= mask;
  P2DIR &= ~mask;

  switch_update_interrupt_sense();
}

unsigned int p2sw_read() {

#include <Arduboy2.h>

#include <avr/boot.h>;

Arduboy2 arduboy;

int notes[] = {
  440, 494, 523, 587, 659, 698, 784, 880
};

uint8_t lowBits, highBits, extendedBits, lockBits;

void setup() {

    cli();
    lowBits      = boot_lock_fuse_bits_get(GET_LOW_FUSE_BITS);
    highBits     = boot_lock_fuse_bits_get(GET_HIGH_FUSE_BITS);
    extendedBits = boot_lock_fuse_bits_get(GET_EXTENDED_FUSE_BITS);
    lockBits     = boot_lock_fuse_bits_get(GET_LOCK_BITS);
    sei();



  arduboy.boot();
  pinMode(5, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(5, LOW);
  digitalWrite(13, LOW);
  
  arduboy.setFrameRate(30);



}

bool up_b,down_b,right_b,left_b,a_b,b_b;

bool l_f, h_f, e_f, k_f;

float note = 550;

bool ispressed = 0;

void loop() {


  if(arduboy.pressed(UP_BUTTON)) { up_b = 1; analogWrite(9,224); }
  if(arduboy.pressed(DOWN_BUTTON)) { down_b = 1; analogWrite(10,224); }
  if(arduboy.pressed(LEFT_BUTTON)) { left_b = 1; analogWrite(11,224); }
  if(arduboy.pressed(RIGHT_BUTTON)) { right_b = 1; tone(13, note, 100); }
  if(arduboy.pressed(A_BUTTON)) a_b = 1;
  if(arduboy.pressed(B_BUTTON)) b_b = 1;
  

  if (!(arduboy.nextFrame()))
    return;
  arduboy.clear();




 if ( up_b + down_b + right_b + left_b + a_b + b_b + l_f + h_f + e_f + k_f== 10){
  arduboy.setCursor(66,49);
  arduboy.setTextSize(2);
  arduboy.print("PASS");
  arduboy.write(2);
  arduboy.setTextSize(1);
  arduboy.setCursor(0,0);
 }


 if (  l_f + h_f + e_f + k_f < 4 ){
  arduboy.setCursor(66,49);
  arduboy.setTextSize(2);
  arduboy.print("FAIL");
  arduboy.write(1);
  arduboy.setTextSize(1);
  arduboy.setCursor(0,0);
 }


  arduboy.print("UP     [");
  if(up_b){ arduboy.print("X"); }
  else{  arduboy.print(" "); }

  if(arduboy.pressed(UP_BUTTON)) { arduboy.println("] BLUE LED?");  }
  else { arduboy.println("]"); }
  digitalWrite(9,1);
  
  arduboy.print("DOWN   [");
  if(down_b){ arduboy.print("X"); }
  else{  arduboy.print(" "); }
  
  if(arduboy.pressed(DOWN_BUTTON)) { arduboy.println("] RED LED?");  }
  else { arduboy.println("]"); }
  digitalWrite(10,1);

  arduboy.print("LEFT   [");
  if(left_b){ arduboy.print("X"); }
  else{  arduboy.print(" "); }
  
  if(arduboy.pressed(LEFT_BUTTON)) { arduboy.println("] GREEN LED?");  }
  else { arduboy.println("]"); }
  digitalWrite(11,1);

  arduboy.print("RIGHT  [");
  if(right_b){ arduboy.print("X"); }
  else{  arduboy.print(" "); }
  
  if(arduboy.pressed(RIGHT_BUTTON)) { arduboy.println("] SPEAKER?");  ispressed = 1;}
  else { arduboy.println("]"); }
  if(!arduboy.pressed(RIGHT_BUTTON)) { if(ispressed){ ispressed = 0; note = notes[random(7)]; } }

  arduboy.print("A      [");
  if(a_b){ arduboy.print("X"); }
  else{  arduboy.print(" "); }
  
  if(arduboy.pressed(A_BUTTON)) { arduboy.println("] PRESSED");  }
  else { arduboy.println("]"); }


  arduboy.print("B      [");
  if(b_b){ arduboy.print("X"); }
  else{  arduboy.print(" "); }
  arduboy.println("] OLED TEST");

  if(lowBits == 255){
    l_f = 1;
  }
  else  {
    arduboy.setTextColor(0);
    arduboy.setTextBackground(1);
  }
  arduboy.print("L:");
  arduboy.print(lowBits, HEX);
  arduboy.setTextBackground(0);
  arduboy.setTextColor(1);


  if(highBits == 216){
    h_f = 1;
  }
  else{
    arduboy.setTextColor(0);
    arduboy.setTextBackground(1);
  }
  arduboy.print(" H:");
  arduboy.println(highBits, HEX);
  arduboy.setTextBackground(0);
  arduboy.setTextColor(1);


  if(extendedBits == 203){
    e_f = 1;
  }
  else{
    arduboy.setTextColor(0);
    arduboy.setTextBackground(1);
  }
  arduboy.print("E:");
  arduboy.print(extendedBits, HEX);
  arduboy.setTextBackground(0);
  arduboy.setTextColor(1);

  
  if(lockBits == 239){
    k_f = 1;
  }
  else{
    arduboy.setTextColor(0);
    arduboy.setTextBackground(1);
  }
  arduboy.print(" K:");
  arduboy.print(lockBits, HEX);
  arduboy.setTextBackground(0);
  arduboy.setTextColor(1);
 
  
  if(arduboy.pressed(B_BUTTON)) {  arduboy.fillRect(0,0,128,64,1); }


  arduboy.display();
}




/*
  Roaming with PINGBot - Activity Bot

  Detect obstacles in the ActivityBot's path, rotate PING Mount, and then turn to best direction to avoid them.
 
  @author Nikhil Paranjape

*/

#include "simpletools.h"                      // Include simpletools header
#include "abdrive.h"                          // Include abdrive header
#include "ping.h"                             // Include ping header
#include "servo.h" 
#include "wavplayer.h"

int turn;                                     // Navigation variable
int rightVar;                                 //when ping is on right, save distance
int leftVar;                                  //when ping is on left, save distance
int frontVar;                                 //when ping is facing the front, save distance

int main()                                    // main function
{
  
  drive_setRampStep(10);                      // 10 ticks/sec / 20 ms
  while(1)
  {
    servo_angle(16, 900);                     // Center robot head
    pause(300);
    
    drive_ramp(128, 128);                     // Forward 2 RPS

                        
    while(ping_cm(8) >= 20) pause(5);         // Wait until object in range
    freqout(4, 2000, 3000);
    drive_ramp(0, 0);                         // Ramps down the speed of bot
 
  
    servo_angle(16, 0);                       // Turn head to RIGHT
    pause(300);
    rightVar = ping_cm(8);
    servo_angle(16, 1800);                  // Turn head to LEFT
    pause(500); 
    leftVar = ping_cm(8);
    servo_angle(16,900);
    frontVar = ping_cm(8);
    pause(300);
    if(rightVar > leftVar) { 
      drive_goto(-32,-32);                             
      drive_goto(26, -25);
      servo_angle(16, 900);                   // Center robot head
      pause(300); 
    }   
    else if(leftVar > rightVar){ 
      drive_goto(-32,-32);                   
      drive_goto(-25, 26);                    // rotate left
      servo_angle(16, 900);                   // Center head
      pause(300);
    } 
    else if(frontVar > leftVar || frontVar > rightVar){                   // rotate left
      servo_angle(16, 900);                   // Center head
      pause(300);
    }    
    else{
      drive_goto(-128, -128);
      pause(200);
      drive_goto(128, -128);
      drive_goto(128, -128);
    }                    
    
  }
  drive_ramp(0, 0);                           // Stop & let program end
}

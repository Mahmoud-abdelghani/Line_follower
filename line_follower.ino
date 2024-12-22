/**************************************************************/
/********** SWC : Line Follower *******************************/
/********** Date : 17 December 2024 ***************************/
/********** Author : Mahmoud Abdelghani *******/
/********** Version :2.2          *****************************/

//used pins
#define forward_s A2
#define fine_right_s  A3
#define fine_left_s A1
#define right_s A4
#define left_s A0
#define motor_R_pin_1 13
#define motor_R_pin_2 12
#define motor_L_pin_1 11
#define motor_L_pin_2 10
#define motor_R_speed 9
#define motor_L_speed 6

typedef unsigned char u8;

u8 forward_flag=0;
u8 fine_right_flag=0;
u8 fine_left_flag=0;
u8 right_flag=0;
u8 left_flag=0;
u8 previous_one=0;

//an enum to define directions
typedef enum 
{
forward=0,
fine_left,//the dirctions if line found in fine_left_sensor
fine_right,//the dirctions if line found in fine_right_sensor
right,//the direction if line found in right sensor
left//the direction if line found in left sensor
}Direction;

// this function gets reading from our 5 sensors then do an action by returning the next direction using enum
Direction Next_Move()
{
  
  if (analogRead(forward_s)<100)
  {
    forward_flag=1;
  }
  else 
  {
    forward_flag=0;
  }
  if (analogRead(fine_right_s)<100)
  {
    fine_right_flag=1;
  }
  else 
  {
    fine_right_flag=0;
  }
  if (analogRead(fine_left_s)<100)
  {
    fine_left_flag=1;
  }
  else 
  {
    fine_left_flag=0;
  }
  if (analogRead(right_s)<100)
  {
    right_flag=1;
  }
  else 
  {
    right_flag=0;
  }
  if (analogRead(left_s)<100)
  {
    left_flag=1;
  }
  else
  {
    left_flag=0;
  }
  if (forward_flag)
  {
    return forward;
  }
  else if (right_flag)
  {
    previous_one=right;
    return right;
  }
  else if (left_flag)
  {
    previous_one=left;
    return left;
  }
  else if (fine_left_flag)
  {
    previous_one=fine_left_flag;
    return fine_left;
  }
  else if (fine_right_flag)
  {
    previous_one=fine_right_flag;
    return fine_right;
  }
  else 
  {
    return previous_one;//previous one is avriable saves the poaition of the last time the line appeared 
    //this helps in case of turning and all sensors can't see any line
  }
}

//all of these function controls the actions of motor by changing its speed to change rhe direction of our viechel
void move_forward()
{
  analogWrite(motor_L_speed, 180);
  analogWrite(motor_R_speed, 180);
}

void move_fine_right()
{
  analogWrite(motor_L_speed, 180);
  analogWrite(motor_R_speed, 80);
}

void move_fine_left()
{
  analogWrite(motor_L_speed, 80);
  analogWrite(motor_R_speed, 180);
}

void move_right()
{
  analogWrite(motor_L_speed, 180);
  analogWrite(motor_R_speed, 40);
}

void move_left()
{
  analogWrite(motor_L_speed, 40);
  analogWrite(motor_R_speed, 180);
}

//array of poiters to function and note that its element are arrenged in the order of enum it helps to use enum directly to call the correct function in the correct time 
//something Like RTOS but it's different 
void (*arr_of_ptr_to_func[])(void)={move_forward,move_fine_left,move_fine_right,move_right,move_left};

void setup() {

  pinMode(forward_s, INPUT);
  pinMode(fine_left_s, INPUT);
  pinMode(fine_right_s, INPUT);
  pinMode(right_s, INPUT);
  pinMode(left_s, INPUT);

  pinMode(motor_L_pin_1, OUTPUT);
  pinMode(motor_L_pin_2, OUTPUT);
  pinMode(motor_R_pin_1, OUTPUT);
  pinMode(motor_R_pin_2, OUTPUT);
  pinMode(motor_L_speed, OUTPUT);
  pinMode(motor_R_speed, OUTPUT);

  //motors are ON and ready to move
  analogWrite(motor_L_speed, 0);
  analogWrite(motor_R_speed, 0);
  analogWrite(motor_L_speed, 150);
  analogWrite(motor_R_speed, 150);
  digitalWrite(motor_R_pin_1, HIGH);
  digitalWrite(motor_R_pin_2, LOW);
  digitalWrite(motor_L_pin_1, LOW);
  digitalWrite(motor_L_pin_2, HIGH);
}

void loop() {
  // this line can predict what is the correct function to operate in this time and selects it from arr of PTR by using sensor function
  arr_of_ptr_to_func[Next_Move()]();
}

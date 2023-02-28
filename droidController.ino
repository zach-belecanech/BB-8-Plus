const int enA = 3;	//initializing pin 2 as pwm
const int in_1 = 2;
const int in_2 = 4;

const int enB = 9;	//initializing pin 2 as pwm
const int in_3 = 7;
const int in_4 = 8;

const int FORWARD = 1;
const int BACK = 2;
const int LEFT = 3;
const int RIGHT = 4;
//For providing logic to L298 IC to choose the direction of the DC motor 

void setup()
  {
    pinMode(enA,OUTPUT); //setting the enA pin to output
    pinMode(enB,OUTPUT); //setting the enB pin to output
    pinMode(in_1,OUTPUT); //Logic pins are also set as output
    pinMode(in_2,OUTPUT);
    pinMode(in_3,OUTPUT); 
    pinMode(in_4,OUTPUT);
  }

void loop()
  {
    test();
  
    

  
  }

void motorDirection(int d) {
  switch (d) {
    case 1:
      digitalWrite(in_1,HIGH) ;
      digitalWrite(in_2,LOW) ;
      digitalWrite(in_3,LOW) ;
      digitalWrite(in_4,HIGH) ;  
      break;
    case 2:
      digitalWrite(in_1,LOW) ;
      digitalWrite(in_2,HIGH) ;
      digitalWrite(in_3,HIGH) ;
      digitalWrite(in_4,LOW) ;
      break;
    case 3:
      digitalWrite(in_1,HIGH) ;
      digitalWrite(in_2,LOW) ;
      digitalWrite(in_3,HIGH) ;
      digitalWrite(in_4,LOW) ;   
      break;
    case 4:
      digitalWrite(in_1,LOW) ;
      digitalWrite(in_2,HIGH) ;
      digitalWrite(in_3,LOW) ;
      digitalWrite(in_4,HIGH) ;   
  }
    
  
}

// Give forward speed in a range of 0 - 255 and give time in seconds
void forward(int speed, int time) {
   if (speed > 255 || speed < 0 ){ //error checking to make sure we don't send too strong of a signal or not enough of a signal
     speed = 0;
   }
  motorDirection(FORWARD);
   time = time * 1000; //conversion from seconds to the delay value that the method delat needs
   
   while (speed < 255) {
    speed += 1;
    analogWrite(enA,speed) ;
    analogWrite(enB,speed) ;
    delay(100);
   }

   delay(time); 
   slowBrake(speed);
 }

 // Give speed in a range of 0 - 255 and give time in seconds
 void backward(int speed, int time) {
   if (speed > 255 || speed < 0 ){
     speed = 0;
   }

   time = time * 1000;
   digitalWrite(in_1,LOW) ;
   digitalWrite(in_2,HIGH) ;
   analogWrite(enA,speed) ;

   digitalWrite(in_3,LOW) ;
   digitalWrite(in_4,HIGH) ;
   analogWrite(enB,speed) ;

   delay(time);
   brake();
 }

 void turnRight(int speed, int degree) {
   if (degree % 15 != 0) { //make sure the input is only in 15 degree segments
     degree = 0;
   }

        digitalWrite(in_1,LOW) ;
        digitalWrite(in_2,HIGH) ;
        analogWrite(enA,speed) ;

        digitalWrite(in_3,LOW) ;
        digitalWrite(in_4,HIGH) ;
        analogWrite(enB,speed) ;

    switch (degree) {
      case 90: 
        delay(1500);
        brake();
        break;
      case 180:
        delay(550);
        brake();
        break;
      case 270:
        delay(770);
        brake();
        break;
      case 360:
        delay(1020);
        brake();
        break;
    
    }


  }

  void turnLeft(int speed, int degree) {
   if (degree % 15 != 0) { //make sure the input is only in 15 degree segments
     degree = 0;
   }

   digitalWrite(in_1,HIGH) ;
        digitalWrite(in_2,LOW) ;
        analogWrite(enA,speed) ;

        digitalWrite(in_3,LOW) ;
        digitalWrite(in_4,HIGH) ;
        analogWrite(enB,speed) ;

    switch (degree) {
      case 90: 
        delay(300);
        brake();
        break;
      case 180:
        delay(550);
        brake();
        break;
      case 270:
        delay(770);
        brake();
        break;
      case 360:
        delay(1020);
        brake();
        break;
    
    }


  }

  void slowBrake(int speed) {
    while (speed >= 0) {
    speed -= 5;
    digitalWrite(in_1,LOW) ;
    digitalWrite(in_2,HIGH) ;
    analogWrite(enA,speed) ;

    digitalWrite(in_3,HIGH) ;
    digitalWrite(in_4,LOW) ;
    analogWrite(enB,speed) ;
    delay(200);
   }
}

//Method that causes the wheels to stop
void brake() {
  digitalWrite(in_1,HIGH) ;
  digitalWrite(in_2,HIGH) ;
  digitalWrite(in_3,HIGH);
  digitalWrite(in_4,HIGH);
  delay(5000) ;   
}

void test() {
  delay(5000);
  forward(50,5);
  turnRight(255,90);
  delay(5000);
}
#include <NeoSWSerial.h>
#include <AltSoftSerial.h>
#include <TinyGPS++.h>
#include <math.h>
const int m1=5;
const int m2=4;
const int PWM1=6;
const int m3=7;
const int m4=2;
const int PWM2=3;
const float error =2871.142857;
int speed=200;
int k=1;
float Clat;
float Clng;
float Tlat=23.707643;
float Tlng=90.409713;
float ClatR;
float ClngR;
float TlatR;
float TlngR;
float dlng; 
float dlat; 
float a;
float e;
float d;
float R = 6371.00; 
 
char btVal;

//const int GPSBaud = 9600;

TinyGPSPlus gps;
NeoSWSerial ss(11,12);//rx,tx
AltSoftSerial Bs(8, 13); // RX, TX

void setup(){
Serial.begin(115200);
ss.begin(9600);
Bs.begin(9600);
pinMode(m1,OUTPUT);
pinMode(m2,OUTPUT);
pinMode(m3,OUTPUT);
pinMode(m4,OUTPUT);
pinMode(PWM1,OUTPUT);
pinMode(PWM2,OUTPUT);

}

//void feedgps(){
// while (ss.available() > 0)
//    if (gps.encode(ss.read()))

//savegps();
//}


//void savegps(){
//Clat=gps.location.lat();
//Clng=gps.location.lng();

//}


//void distence(){
//   while (ss.available() > 0)
//    if (gps.encode(ss.read()))
//    Clat=gps.location.lat();
//Clng=gps.location.lng();
////feedgps();
//
//ClatR= Clat*(PI/180);
//ClngR= Clng*(PI/180);
//TlatR= Tlat*(PI/180);
//TlngR= Tlng*(PI/180);
//dlat=(Clat-Tlat)*(PI/180);  //2,1
//dlng=(Clng-Tlng)*(PI/180);
//a = (sq(sin(dlat/2))) + cos(TlatR) * cos(ClatR) * (sq(sin(dlng/2)));
//e = 2 * atan2(sqrt(a), sqrt(1-a)) ;
//d = ((R * e));
//
//Serial.println(d);
//if(d<5){
//  speed=100;
//  }
//
//}



void loop() {
while (ss.available() > 0)
    if (gps.encode(ss.read()))
        if (gps.location.isValid())
  {
    
Clat=gps.location.lat();
Clng=gps.location.lng();
ClatR= Clat*(PI/180);
ClngR= Clng*(PI/180);
TlatR= Tlat*(PI/180);
TlngR= Tlng*(PI/180);
dlat=(Clat-Tlat)*(PI/180);  //2,1
dlng=(Clng-Tlng)*(PI/180);
a = (sq(sin(dlat/2))) + cos(TlatR) * cos(ClatR) * (sq(sin(dlng/2)));
e = 2 * atan2(sqrt(a), sqrt(1-a)) ;
d = ((R * e));
  }
Serial.print("distance = " );
Serial.println(d);
if(d<6){
k=1;
Serial.print("speed = " );
Serial.println(speed);
  }else{
    k=2;
    Serial.print("speed = " );
    Serial.println(speed);
    }
    

  while(Bs.available()){
     
   btVal= Bs.read();
     
   }
   
 
    

  switch (btVal) 
  {
      case 'F':                                
    Serial.println("Forward");
      forward();
      break;

      case 'B':                 
      Serial.println("Reverse");
       reverse();
       break;

    case 'L':         
       Serial.println("Left");
       left();
       break;
       
     case 'R':                     
    Serial.println("Right");
       right();
        break;
        
     case 'S':                                            
      Serial.println("Stop");
       stoprobot();
       break; 




       case '1':                                            
       speed=10*k;
       Serial.println(speed);
       break;      

       case '20':                                            
       speed=2*k;
       Serial.println(speed);
       break;


       case '3':                                            
       speed=30*k;
       Serial.println(speed);
       break;      

        case '4':                                            
       speed=40*k;
       Serial.println(speed);
       break;   

       case '5':                                            
       speed=50*k;
       Serial.println(speed);
       break;      

       case '6':                                            
       speed=60*k;
       Serial.println(speed);
       break;      

       case '7':                                            
       speed=70*k;
       Serial.println(speed);
       break;      

       case '8':                                            
       speed=80*k;
       Serial.println(speed);
       break;      

       case '9':                                            
       speed=90*k;
       Serial.println(speed);
       break;     

       case 'q':                                            
       speed=100*k;
       Serial.println(speed);
       Serial.print("MAX");
       break;      

}

  
}  



void forward()
{
  digitalWrite(m1, HIGH);;
 digitalWrite(m2, LOW);
  analogWrite(PWM1,speed);
  digitalWrite(m3, HIGH);
  digitalWrite(m4, LOW);
  analogWrite(PWM2,speed);
}

void reverse()
{
   digitalWrite(m1,LOW);;
 digitalWrite(m2, HIGH);
  analogWrite(PWM1,speed);
 digitalWrite(m3, LOW);
 digitalWrite(m4, HIGH);
  analogWrite(PWM2,speed);
}

void left()
{
 digitalWrite(m1, LOW);;
  digitalWrite(m2, HIGH);
  analogWrite(PWM1,speed);
  digitalWrite(m3,HIGH);
  digitalWrite(m4, LOW);
  analogWrite(PWM2,speed);
}

void right()
{
  digitalWrite(m1, HIGH);;
  digitalWrite(m2, LOW);
  analogWrite(PWM1,speed);
 digitalWrite(m3, LOW);
  digitalWrite(m4, HIGH);
  analogWrite(PWM2,speed);
}
void stoprobot()
{
  digitalWrite(m1, LOW);;
  digitalWrite(m2, LOW);

  digitalWrite(m3, LOW);
  digitalWrite(m4, LOW);
}


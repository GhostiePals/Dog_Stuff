#include <Separador.h>
#include <ESP32Servo.h>
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;
#include <math.h>
double num = 0;
double den = 0;
double lengthZ,hipAngle1a,hipHyp, hipAngle1b, hipAngle1;
//                       FL   BL BR  FR
double angle_tibia[5] = {0 , 0 , 0, 0,0};
double angle_femur[5] =  {0 , 0 , 0, 0,0};
double angle_coxa[5] =  {0 , 0 , 0, 0,0};
String leg;
String command;
int valor = 90;
int femur = 100;//mm
int tibia = 100;//mm
int coxa = 50;//mm
int s1 = 26;
int s2 = 25;
int s3 = 17;
int s4 = 16;
int s5 = 27;
int s6 = 14;
int s7 = 22;
int s8 = 2;
int s9 = 4;
int s10 = 12;
int s11 = 13;
int s12 = 21;
//{FLcoxa,FLfemur,FLtibia; BLcoxa,BLfemur,BLtibia; BRcoxa,BRfemur,BRtibia; FRcoxa,FRfemur,FRtibia}
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;
Servo servo7;
Servo servo8;
Servo servo9;
Servo servo10;
Servo servo11;
Servo servo12;
Separador s;
int incremento[12]= {0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//              FL   BL BR  FR
double y_axis[4] = {0 , 0 , 0, 0};
double x_axis[4] = {0 , 0 , 0, 0};
double z_axis[4] = {0 , 0 , 0, 0};
double add_femur[4] = {0 , 0 , 0, 0};
double z2 = 0;
double z3 = 0;
void change(void);
void holdposition(void);
void mandar(void);
void move_BLc(int);
void move_FRc(int);
void move_BRc(int);
void move_FLc(int);
void move_BLf(int);
void move_FRf(int);
void move_BRf(int);
void move_FLf(int);
void move_BLt(int);
void move_FRt(int);
void move_BRt(int);
void move_FLt(int);

void move_FLy(int);void move_FLx(int);void move_FLz(int);
void move_FRy(int);void move_FRx(int);void move_FRz(int);
void move_BLy(int);void move_BLx(int);void move_BLz(int);
void move_BRy(int);void move_BRx(int);void move_BRz(int);

int angle[16]=      {90 , 90  , 90, 90, 90  ,90, 90, 90, 90, 90, 90, 90};
int offservo[12] =  {7  ,   33  ,   +7 ,     0+2,     53 ,    -7,      14-5,  -15-5,    15,   -3+2,    -30,    7};
                  //{FLcoxa,FLfemur,FLtibia; BLcoxa,BLfemur,BLtibia; BRcoxa,BRfemur,BRtibia; FRcoxa,FRfemur,FRtibia}
                  //{0     ,1      ,2 -    ; 3     ,4      ,5 -    ; 6     ,7(x)     ,8      ; 9 -    ,10     ,11}
void setup() {
  servo1.attach (s1);
  servo2.attach (s2);
  servo3.attach (s3);
  servo4.attach (s4);
  servo5.attach (s5);
  servo6.attach (s6);
  servo7.attach (s7);
  servo8.attach (s8);
  servo9.attach (s9);
  servo10.attach (s10);
  servo11.attach (s11);
  servo12.attach (s12);
  Serial.begin(115200);
  SerialBT.begin("Perrito"); //Bluetooth device name
  Serial.println("ready for command");

  move_FLy(100);
  move_FRy(100);
  move_BLy(100);
  move_BRy(100);
}

void loop() {
  if(!SerialBT.available()) {
    holdposition();
  }
  if(SerialBT.available()) {
    command = SerialBT.readStringUntil('\n');
    leg = (s.separa(command,',',0));
    valor = (s.separa(command,',',1)).toInt();
    mandar();
  }
  delay(500);
}

void holdposition(void){
  servo1.write(angle[0]+offservo[0]);
  servo2.write(angle[1]+offservo[1]);
  servo3.write(angle[2]+offservo[2]);
  servo4.write(angle[3]+offservo[3]);
  servo5.write(angle[4]+offservo[4]);
  servo6.write(angle[5]+offservo[5]);
  servo7.write(angle[6]+offservo[6]);
  servo8.write(angle[7]+offservo[7]);
  servo9.write(angle[8]+offservo[8]);
  servo10.write(angle[9]+offservo[9]);
  servo11.write(angle[10]+offservo[10]);
  servo12.write(angle[11]+offservo[11]);
}
void mandar(void){
  if (leg == "FLc"){
    move_FLc(valor);
    }

  else if (leg == "sentado"){
    move_FLy(140);
    move_FRy(140);
    move_BLy(100);
    move_BRy(100);  
  }

 else if (leg == "arriba"){
    move_FLy(140);
    move_FRy(140);
    move_BLy(140);
    move_BRy(140);  
  }

  else if (leg == "abajo"){
    move_FLy(100);
    move_FRy(100);
    move_BLy(100);
    move_BRy(100);  
  }
   
  
  else if (leg == "FLf"){
    move_FLf(valor); 
  }
  else if (leg == "FLt"){
    move_FLt(valor); 
  }
  ////////////////////////
  else if (leg == "BLc"){
    move_BLc(valor);
    }
  else if (leg == "BLf"){
    move_BLf(valor); 
  }
  else if (leg == "BLt"){
    move_BLt(valor);;  
  }
  ///////////////////////
  else if (leg == "BRc"){
    move_BRc(valor);
    }
  else if (leg == "BRf"){
    move_BRf(valor);  
  }
  else if (leg == "BRt"){
    move_BRt(valor);  
  }
  ////////////////////////
  else if (leg == "FRc"){
    move_FRc(valor);
    }
  else if (leg == "FRf"){
    move_FRf(valor);  
  }
  else if (leg == "FRt"){
    move_FRt(valor); 
  }
  else if (leg == "c"){//coxa
    move_BLc(valor);move_BRc(valor);move_FLc(valor);move_FRc(valor);
  }
  else if (leg == "f"){//femur
    move_BLf(valor);move_BRf(valor);move_FLf(valor);move_FRf(valor);
  }
  else if (leg == "t"){//tibia
    move_BLt(valor);move_BRt(valor);move_FLt(valor);move_FRt(valor); 
  }
  /////////////////////// Mover en y 
  else if(leg == "FLy"){
    move_FLy(valor);
  }
  else if(leg == "FRy"){
    move_FRy(valor);
  }
  else if(leg == "BLy"){
    move_BLy(valor);
  }
  else if(leg == "BRy"){
    move_BRy(valor);
  }
  else if(leg == "y"){
    move_FLy(valor);
    move_FRy(valor);
    move_BLy(valor);
    move_BRy(valor);
  }
  /////////////////////// Mover en x 
  else if(leg == "FLx"){
    move_FLx(valor);
  }
  else if(leg == "FRx"){
    move_FRx(valor);
  }
  else if(leg == "BLx"){
    move_BLx(valor);
  }
  else if(leg == "BRx"){
    move_BRx(valor);
  }
  else if(leg == "x"){
    move_FLx(valor);
    move_FRx(valor);
    move_BLx(valor);
    move_BRx(valor);
  }
  
  /////////////////////// Mover en z 
  else if(leg == "FLz"){
    move_FLz(valor);
  }
  else if(leg == "FRz"){
    move_FRz(valor);
  }
  else if(leg == "BLz"){
    move_BLz(valor);
  }
  else if(leg == "BRz"){
    move_BRz(valor);
  }
  else if(leg == "z"){
    move_FLz(valor);
    move_FRz(valor);
    move_BLz(valor);
    move_BRz(valor);
  }
  
  /////////////////////// comandos
  else if(leg == "walk"){//default 20
    move_FLy(130);
    move_FRy(130);
    move_BLy(130);
    move_BRy(130);
    delay(500);
    while(1){
      move_FLy(120); delay(200);
      move_FLx(-valor); delay(200);
      move_FLy(130); delay(200);;
      
      move_BRy(120); delay(200);
      move_BRx(-valor); delay(200);
      move_BRy(130); delay(200);
      
      move_FRy(120); delay(200);
      move_FRx(-valor); delay(200);
      move_FRy(130); delay(200);
      
      
      move_BLy(120); delay(200);
      move_BLx(-valor); delay(200);
      move_BLy(130); delay(200);

      move_FLx(0);
      move_BRx(0); 
      move_FRx(0); 
      move_BLx(0); 
    }
  }
  else if(leg == "rotate"){//default 20
    move_FLy(130);
    move_FRy(130);
    move_BLy(130);
    move_BRy(130);
    delay(500);
    while(1){
      move_FLy(120); delay(200);
      move_FLz(-valor); delay(200);
      move_FLy(130); delay(200);;
      
      move_BRy(120); delay(200);
      move_BRz(-valor); delay(200);
      move_BRy(130); delay(200);
      
      move_FRy(120); delay(200);
      move_FRz(-valor); delay(200);
      move_FRy(130); delay(200);
      
      
      move_BLy(120); delay(200);
      move_BLz(-valor); delay(200);
      move_BLy(130); delay(200);

      move_FLz(0);
      move_BRz(0);
      move_FRz(0); 
      move_BLz(0); 
    }
  }

  
}

void move_BLc(int valor){
  //valor = (valor > 90) ? 90 : valor;
  angle[3] = angle[3] - incremento[0];
  incremento[0] = 90-valor;
  angle[3] = angle[3] + incremento[0];
  servo4.write(angle[3]+offservo[3]);//BLc 
}
void move_FRc(int valor){
  //valor = (valor > 90) ? 90 : valor;
  angle[9] = angle[9] - incremento[1];
  incremento[1] = 90-valor;
  angle[9] = angle[9] + incremento[1];
  servo10.write(angle[9]+offservo[9]);//FRc
}
void move_BRc(int valor){
  //valor = (valor > 90) ? 90 : valor;
  angle[6]= valor;
  servo7.write(angle[6]+offservo[6]);//BRc 
}
void move_FLc(int valor){
  //valor = (valor > 90) ? 90 : valor;
  angle[0]= valor;
  servo1.write(angle[0]+offservo[0]);//FLc
}
////////////////////////////////////////////
void move_FLf(int valor){
  valor = (valor > 90) ? 90 : valor;
  angle[1]= valor;
  servo2.write(angle[1]+offservo[1]);//FLf
}
void move_BLf(int valor){
  valor = (valor > 90) ? 90 : valor;
  angle[4]= valor;
  servo5.write(angle[4]+offservo[4]);//BLf
}
void move_BRf(int valor){
  valor = (valor > 90) ? 90 : valor;
  angle[7] = angle[7] - incremento[2];
  incremento[2] = 90-valor;
  angle[7] = angle[7] + incremento[2];
  servo8.write(angle[7]+offservo[7]);//BRf
}
void move_FRf(int valor){
  valor = (valor > 90) ? 90 : valor;
  angle[10] = angle[10] - incremento[3];
  incremento[3] = 90-valor;
  angle[10] = angle[10] + incremento[3];
  servo11.write(angle[10]+offservo[10]);//FRf 
}
///////////////////////////////////////////
void move_FRt(int valor){
  valor = (valor > 90) ? 90 : valor;
  valor = (valor < 50) ? 50 : valor;
  angle[11]= valor;
  servo12.write(angle[11]+offservo[11]);//FRt  
}
void move_BRt(int valor){
  valor = (valor > 90) ? 90 : valor;
  valor = (valor < 50) ? 50 : valor;
  angle[8]= valor;
  servo9.write(angle[8]+offservo[8]);//BRt
}
void move_BLt(int valor){
  valor = (valor > 90) ? 90 : valor;
  valor = (valor < 50) ? 50 : valor;
  angle[5] = angle[5] - incremento[4];
  incremento[4] = 90-valor;
  angle[5] = angle[5] + incremento[4];
  servo6.write(angle[5]+offservo[5]);//BLt
}
void move_FLt(int valor){
  valor = (valor > 90) ? 90 : valor;
  valor = (valor < 50) ? 50 : valor;
  angle[2] = angle[2] - incremento[5];
  incremento[5] = 90-valor;
  angle[2] = angle[2] + incremento[5];
  servo3.write(angle[2]+offservo[2]);//FLt                
}
///////////////////////////////////////////yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy
//int femur = 100;
//int tibia = 100;
//              FL   BL BR  FR    
void move_FLy(int valor){
  num = sq(femur)+sq(tibia)-sq(valor);
  den = 2*femur*tibia;
  angle_tibia[0] = acos(num/den)*180/PI;//tibia
  angle_femur[0] = (180-angle_tibia[0])/2;
  move_FLt(int(angle_tibia[0]));
  move_FLf(int(angle_femur[0]+add_femur[0])); 
  y_axis[0] = valor;       
}
void move_BLy(int valor){
  num = sq(femur)+sq(tibia)-sq(valor);
  den = 2*femur*tibia;
  angle_tibia[1] = acos(num/den)*180/PI;//tibia
  angle_femur[1] = (180-angle_tibia[1])/2;
  move_BLt(int(angle_tibia[1]));
  move_BLf(int(angle_femur[1]+add_femur[1]));
  y_axis[1] = valor;          
}
void move_BRy(int valor){
  num = sq(femur)+sq(tibia)-sq(valor);
  den = 2*femur*tibia;
  angle_tibia[2] = acos(num/den)*180/PI;//tibia
  angle_femur[2] = (180-angle_tibia[2])/2;
  move_BRt(int(angle_tibia[2]));
  move_BRf(int(angle_femur[2]+add_femur[2]));
  y_axis[2] = valor;          
}
void move_FRy(int valor){
  num = sq(femur)+sq(tibia)-sq(valor);
  den = 2*femur*tibia;
  angle_tibia[3] = acos(num/den)*180/PI;//tibia
  angle_femur[3] = (180-angle_tibia[3])/2;
  move_FRt(int(angle_tibia[3]));
  move_FRf(int(angle_femur[3]+add_femur[3]));
  y_axis[3] = valor;          
}
///////////////////////////////////////////xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//int femur = 100;tight
//int tibia = 100;shin
//              FL   BL BR  FR    
void move_FLx(int valor){
  add_femur[0] = atan(valor/y_axis[0]);
  z2 = y_axis[0]/cos(add_femur[0]);
  add_femur[0] = add_femur[0]*(180/PI);
  num = sq(femur)+sq(tibia)-sq(z2);
  den = 2*femur*tibia;
  angle_tibia[0] = acos(num/den)*180/PI;//tibia
  angle_femur[0] = (180-angle_tibia[0])/2;
  move_FLt(int(angle_tibia[0]));
  move_FLf(int(angle_femur[0]+add_femur[0]));  
  x_axis[0] = valor;      
}
void move_BLx(int valor){
  add_femur[1] = atan(valor/y_axis[1]);
  z2 = y_axis[1]/cos(add_femur[1]);
  add_femur[1] = add_femur[1]*(180/PI);
  num = sq(femur)+sq(tibia)-sq(z2);
  den = 2*femur*tibia;
  angle_tibia[1] = acos(num/den)*180/PI;//tibia
  angle_femur[1] = (180-angle_tibia[1])/2;
  move_BLt(int(angle_tibia[1]));
  move_BLf(int(angle_femur[1]+add_femur[1]));
  x_axis[1] = valor;           
}
void move_BRx(int valor){
  add_femur[2] = atan(valor/y_axis[2]);
  z2 = y_axis[2]/cos(add_femur[2]);
  add_femur[2] = add_femur[2]*(180/PI);
  num = sq(femur)+sq(tibia)-sq(z2);
  den = 2*femur*tibia;
  angle_tibia[2] = acos(num/den)*180/PI;//tibia
  angle_femur[2] = (180-angle_tibia[2])/2;
  move_BRt(int(angle_tibia[2]));
  move_BRf(int(angle_femur[2]+add_femur[2])); 
  x_axis[2] = valor;           
}
void move_FRx(int valor){
  add_femur[3] = atan(valor/y_axis[3]);
  z2 = y_axis[3]/cos(add_femur[3]);
  add_femur[3] = add_femur[3]*(180/PI);
  num = sq(femur)+sq(tibia)-sq(z2);
  den = 2*femur*tibia;
  angle_tibia[3] = acos(num/den)*180/PI;//tibia
  angle_femur[3] = (180-angle_tibia[3])/2;
  move_FRt(int(angle_tibia[3]));
  move_FRf(int(angle_femur[3]+add_femur[3]));
  x_axis[3] = valor;           
}
/////////////////////////////////////////// zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz
//int femur = 100;tight
//int tibia = 100;shin        z  =   yo y
//int coxa = 50;hip           y   =  yo z
//              FL   BL BR  FR    
void move_FLz(int valor){
  lengthZ = valor + coxa;
  hipAngle1a = atan(lengthZ/y_axis[0]);
  hipHyp = lengthZ/sin(hipAngle1a);
  
  hipAngle1b = asin(coxa/hipHyp);
  hipAngle1 = (PI-(PI/2) - hipAngle1b) + hipAngle1a;
  hipAngle1 = hipAngle1 - 0;
  angle_coxa[0] = hipAngle1 * (180/PI);

  z2 = coxa/tan(hipAngle1b);

  add_femur[0] = atan(x_axis[0]/z2);
  z3 = z2/cos(add_femur[0]);
  
  add_femur[0] = add_femur[0]*(180/PI);
  
  num = sq(femur)+sq(tibia)-sq(z3);
  den = 2*femur*tibia;
  angle_tibia[0] = acos(num/den)*180/PI;//tibia
  angle_femur[0] = (180-angle_tibia[0])/2;
  move_FLt(int(angle_tibia[0]));
  move_FLf(int(angle_femur[0]+add_femur[0]));  
  move_FLc(int(angle_coxa[0]));        
}
void move_BLz(int valor){
  lengthZ = valor + coxa;
  hipAngle1a = atan(lengthZ/y_axis[1]);
  hipHyp = lengthZ/sin(hipAngle1a);
  
  hipAngle1b = asin(coxa/hipHyp);
  hipAngle1 = (PI-(PI/2) - hipAngle1b) + hipAngle1a;
  hipAngle1 = hipAngle1 - 0;
  angle_coxa[1] = hipAngle1 * (180/PI);

  z2 = coxa/tan(hipAngle1b);

  add_femur[1] = atan(x_axis[1]/z2);
  z3 = z2/cos(add_femur[1]);
  
  add_femur[1] = add_femur[1]*(180/PI);
  
  num = sq(femur)+sq(tibia)-sq(z3);
  den = 2*femur*tibia;
  angle_tibia[1] = acos(num/den)*180/PI;//tibia
  angle_femur[1] = (180-angle_tibia[1])/2;
  move_BLt(int(angle_tibia[1]));
  move_BLf(int(angle_femur[1]+add_femur[1]));  
  move_BLc(int(angle_coxa[1]));        
}
void move_BRz(int valor){
  lengthZ = valor + coxa;
  hipAngle1a = atan(lengthZ/y_axis[2]);
  hipHyp = lengthZ/sin(hipAngle1a);
  
  hipAngle1b = asin(coxa/hipHyp);
  hipAngle1 = (PI-(PI/2) - hipAngle1b) + hipAngle1a;
  hipAngle1 = hipAngle1 - 0;
  angle_coxa[2] = hipAngle1 * (180/PI);

  z2 = coxa/tan(hipAngle1b);

  add_femur[2] = atan(x_axis[2]/z2);
  z3 = z2/cos(add_femur[2]);
  
  add_femur[2] = add_femur[2]*(180/PI);
  
  num = sq(femur)+sq(tibia)-sq(z3);
  den = 2*femur*tibia;
  angle_tibia[2] = acos(num/den)*180/PI;//tibia
  angle_femur[2] = (180-angle_tibia[2])/2;
  move_BRt(int(angle_tibia[2]));
  move_BRf(int(angle_femur[2]+add_femur[2]));  
  move_BRc(int(angle_coxa[2]));             
}
void move_FRz(int valor){
  lengthZ = valor + coxa;
  hipAngle1a = atan(lengthZ/y_axis[3]);
  hipHyp = lengthZ/sin(hipAngle1a);
  
  hipAngle1b = asin(coxa/hipHyp);
  hipAngle1 = (PI-(PI/2) - hipAngle1b) + hipAngle1a;
  hipAngle1 = hipAngle1 - 0;
  angle_coxa[3] = hipAngle1 * (180/PI);

  z2 = coxa/tan(hipAngle1b);

  add_femur[3] = atan(x_axis[3]/z2);
  z3 = z2/cos(add_femur[3]);
  
  add_femur[3] = add_femur[3]*(180/PI);
  
  num = sq(femur)+sq(tibia)-sq(z3);
  den = 2*femur*tibia;
  angle_tibia[3] = acos(num/den)*180/PI;//tibia
  angle_femur[3] = (180-angle_tibia[3])/2;
  move_FRt(int(angle_tibia[3]));
  move_FRf(int(angle_femur[3]+add_femur[3]));  
  move_FRc(int(angle_coxa[3]));           
}       
    
    

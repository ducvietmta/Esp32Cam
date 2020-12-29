#include "following_line.h"
int following_line::getPosition(){
    int sum1 = digitalRead(SENSOR1) + digitalRead(SENSOR2)*2 + digitalRead(SENSOR3)*3 + digitalRead(SENSOR4)*4 + digitalRead(SENSOR5)*5;
    int sum2 = digitalRead(SENSOR1) + digitalRead(SENSOR2) + digitalRead(SENSOR3) + digitalRead(SENSOR4) + digitalRead(SENSOR5);
    if (sum2!=0){
        temp = sum1*100;
        temp = temp/sum2;
    }
    else{
        temp=0;
    }
    return temp-300;

}
following_line::following_line(){};
int following_line::PIDControl(float vitrixe){
    float delta, Udk; 
    error=vitrixe;
      int error_sum=0;
    if (error<-300 && old_error>=0)error=-error;

    delta = error - old_error;
    old_error = error ;//
    error_sum = error_sum+error;
    if (error_sum <-max_e){
        error_sum = -max_e;
    }
    if (error_sum > max_e){
        error_sum= max_e;
    }
    Udk = Kp*error + Ki*error_sum + Kd*delta;
    if(Udk <-Max)Udk= -Max;
    if(Udk > Max)Udk= Max;
    return Udk;
}

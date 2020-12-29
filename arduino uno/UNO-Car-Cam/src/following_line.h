#include "Arduino.h"
#define SENSOR1 8
#define SENSOR2 9
#define SENSOR3 10
#define SENSOR4 11
#define SENSOR5 12

class following_line{
    private:
        int temp;
        float error, old_error, Kp=1 , Kd=0,  Ki=0;                            
        int max_e, Mid=700,Max,nguong=2200,start=0, start1;
    public:
            following_line();
            int getPosition();
            int PIDControl(float vitrixe);
};


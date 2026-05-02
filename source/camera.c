
#include "camera.h"

/* GLOBAL VARIABLES*/
Camera_t camera = {0,0,0,0};


void camera_init(void){
    camera.pos      = (Position){0.0f, 0.0f};
    camera.velocity = (Velocity){0.0f, 0.0f};
}
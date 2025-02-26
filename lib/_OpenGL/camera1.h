#ifndef CAMERA1_H_INCLUDED
#define CAMERA1_H_INCLUDED

struct Structure_Camera{

    float x, y, z;
    float raise_lower, right_left;

} camera;

void Camera_Implement();
void Camera_Rotating(float X_angle, float Z_angle);
void Camera_Mouse(int center_X, int center_Y, float speed);
void Camera_Moving(int forwardMoving, int rightMoving, float speed);


#endif // CAMERA1_H_INCLUDED

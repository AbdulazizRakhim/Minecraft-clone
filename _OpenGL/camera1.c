#include "GL/gl.h"
#include "windows.h"
#include "math.h"
#include "camera1.h"
#include "time.h"

struct Structure_Camera camera = {0, 0, 1.7, 0, 0};

void Camera_Implement()
{
    glRotatef(-camera.raise_lower, 1, 0, 0);
    glRotatef(-camera.right_left,  0, 0, 1);
    glTranslatef(-camera.x, -camera.y, -camera.z);
}

void Camera_Rotating(float X_angle, float Z_angle)
{
    camera.right_left = camera.right_left + Z_angle;

    if(camera.right_left < 0)
        camera.right_left = camera.right_left + 360;
    if(camera.right_left > 360)
        camera.right_left = camera.right_left - 360;

    camera.raise_lower = camera.raise_lower + X_angle;

    if(camera.raise_lower < 0)
        camera.raise_lower = 0;
    if(camera.raise_lower > 180)
        camera.raise_lower = 180;
}

void Camera_Mouse(int center_X, int center_Y, float speed)
{
    POINT cursor;
    POINT base = {center_X, center_Y};
    GetCursorPos(&cursor);
    Camera_Rotating((base.y - cursor.y) * speed, (base.x - cursor.x) * 5.0);
    SetCursorPos(base.x, base.y);
}

void Camera_Moving(int forwardMoving, int rightMoving, float speed)
{
    static int isPlaying = 0;              // Tracks if the sound is already playing
    static clock_t lastPressTime = 0;      // Tracks the last time the key was pressed
    static clock_t pressStartTime = 0;     // Tracks the start time of the press
    float angle = -camera.right_left / 180 * M_PI;

    if (forwardMoving > 0)
    {
        if (rightMoving > 0)
            angle = angle + M_PI_4; // Moving forward-right
        else if (rightMoving < 0)
            angle = angle + -M_PI_4; // Moving forward-left
        else
            angle = angle + 0; // Moving straight forward
    }

    if (forwardMoving < 0)
    {
        angle = angle + M_PI; // Reverse direction (moving backward)
        if (rightMoving > 0)
            angle = angle + -M_PI_4; // Moving backward-right
        else if (rightMoving < 0)
            angle = angle + M_PI_4; // Moving backward-left
        else
            angle = angle + 0; // Moving straight backward
    }

    if (forwardMoving == 0)
    {
        if (rightMoving > 0)
            angle = angle + M_PI_2; // Moving right
        else if (rightMoving < 0)
            angle = angle + -M_PI_2; // Moving left
        else
            speed = 0; // Not moving
    }

    if (speed != 0)
    {
        camera.x = camera.x + sin(angle) * speed;
        camera.y = camera.y + cos(angle) * speed;

        clock_t now = clock();

        // Check if any movement key is pressed
        if (forwardMoving != 0 || rightMoving != 0) // Key is pressed
        {
            if (lastPressTime == 0) // Key just pressed (start time)
            {
                pressStartTime = now;
                lastPressTime = now;
                // Short press (only play once if it's the first press)
                PlaySound("minecraft-footsteps", NULL, SND_ASYNC);
                isPlaying = 1;
            }
            else
            {
                // If holding the key down
                if ((now - pressStartTime) > CLOCKS_PER_SEC / 2) // Long press after 500 ms
                {
                    if (!isPlaying)  // Play in loop if it's a long press
                    {
                        PlaySound("minecraft-footsteps", NULL, SND_ASYNC | SND_LOOP);
                        isPlaying = 1;  // Set playing state
                    }
                }
            }
        }
        else
        {
            // If no key is pressed or stopped moving
            if (isPlaying)
            {
                PlaySound(NULL, NULL, 0); // Stop the sound
                isPlaying = 0;
            }
            lastPressTime = 0;  // Reset the time for the next press
        }
    }
    else
    {
        // Stop sound if not moving
        if (isPlaying)
        {
            PlaySound(NULL, NULL, 0); // Stop sound
            isPlaying = 0; // Reset playing state
        }
    }
}

/*

without Playsound function

void Camera_Moving(int forwardMoving, int rightMoving, float speed)
{
    float angle = -camera.right_left / 180 * M_PI;

    if (forwardMoving > 0)
    {
        if (rightMoving > 0)
            angle = angle + M_PI_4; // Moving forward-right
        else if (rightMoving < 0)
            angle = angle + -M_PI_4; // Moving forward-left
        else
            angle = angle + 0; // Moving straight forward
    }

    if (forwardMoving < 0)
    {
        angle = angle + M_PI; // Reverse direction (moving backward)
        if (rightMoving > 0)
            angle = angle + -M_PI_4; // Moving backward-right
        else if (rightMoving < 0)
            angle = angle + M_PI_4; // Moving backward-left
        else
            angle = angle + 0; // Moving straight backward
    }

    if (forwardMoving == 0)
    {
        if (rightMoving > 0)
            angle = angle + M_PI_2; // Moving right
        else if (rightMoving < 0)
            angle = angle + -M_PI_2; // Moving left
        else
            speed = 0; // Not moving
    }

    if(speed != 0)
    {
        camera.x = camera.x + sin(angle) * speed;
        camera.y = camera.y + cos(angle) * speed;
    }
}

*/

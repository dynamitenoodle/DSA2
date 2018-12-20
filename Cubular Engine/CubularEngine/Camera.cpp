#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Input.h"

Camera::Camera(glm::vec3 position,
    glm::vec3 forward, 
    glm::vec3 up, 
    float fovAngleY, 
    float width, 
    float height,
    float nearZ, 
    float farZ)
{
    this->position = position;
    this->forward = forward; 
    this->up = up;

    //does this calculation once
    this->fov = fovAngleY * glm::pi<float>() / 180.0f;
    this->width = width;
    this->height = height;
    this->nearZ = nearZ;
    this->farZ = farZ;
}

Camera::~Camera()
{
}

//TODO - incorporate deltaTime
//TODO - maybe separate this function should instead call two private functions
//       (something like UpdateInput() and UpdateMatrices())
void Camera::Update()
{
    //TODO - cache the pointer to the Input single instance instead of calling 
    //       GetInstance() multiple times
    if (Input::GetInstance()->IsKeyDown(GLFW_KEY_A))
    {
        //TODO - change this to move along local axes instead of global axes
        position.x -= 0.01f;    
    } 
     
    //TODO - cache the pointer to the Input single instance instead of calling 
    //       GetInstance() multiple times
    else if (Input::GetInstance()->IsKeyDown(GLFW_KEY_D))
    {
        //TODO - change this to move along local axes instead of global axes
        position.x += 0.01f;
    } 

    //this call may not be needed every frame
    forward = glm::normalize<3>(forward);   

    //view matrix
    //we use forward here instead of a lookTarget because it's easier to track
    //and conceptualize.
    viewMatrix = glm::lookAtLH(
        position,               //where the camera is
        position + forward,     //where the camera is looking at 
        up                      //what is 'up' for the camera
    );

    //create the projection matrix
    projectionMatrix = glm::perspectiveFovLH<GLfloat>(
        fov,
        width,                  //the width of the window in float
        height,                 //the height of the window in float
        nearZ,                  //the near Z-plane
        farZ                    //the far Z-plane
    );
}

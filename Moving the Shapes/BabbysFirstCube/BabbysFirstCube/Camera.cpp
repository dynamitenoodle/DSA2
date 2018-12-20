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
    this->globalUp = up;

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
        position.x -= 0.01f;
    } 
     
    //TODO - cache the pointer to the Input single instance instead of calling 
    //       GetInstance() multiple times
    else if (Input::GetInstance()->IsKeyDown(GLFW_KEY_D))
    {
        position.x += 0.01f;
    } 



    //view matrix
    forward = glm::normalize<3>(forward);
    viewMatrix = glm::lookAtLH(position, position + forward, globalUp);
    //we use forward here instead of a lookTarget because it's easier to track
    //and conceptualize.


    //create the projection matrix
    projectionMatrix = glm::perspectiveFovLH<GLfloat>(
        fov,
        width,                     //the width of the window in float
        height,                    //the height of the window in float
        nearZ,                     //the near Z-plane
        farZ                       //the far Z-plane
    );
}

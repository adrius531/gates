#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>

class Camera
{

    public:
	    Camera();
	    ~Camera() {};

        // Getters & Setters
        glm::vec3 getPos() const { return this->mPos; };
        void setPos(const glm::vec3 &position) { this->mPos = position; };

        float getNearPlane() const { return this->mNearPlane; };
        void setNearPlane(float nearPlane) { this->mNearPlane = nearPlane; };

        float getFarPlane() const { return this->mFarPlane; };
        void setFarPlane(float farPlane) { this->mFarPlane = farPlane; };

        float getHFoV() const { return this->mHFoV; };
        void setHFoV(float fov) { this->mHFoV = fov; };

        float getAspectRatio() const { return this->mAspectRatio; };
        void setAspectRatio(float aspectRatio) { this->mAspectRatio = aspectRatio; }

        float getHorizontalAngle() const { return this->mHorizontalAngle; };
        void setHorizontalAngle(float angle) { this->mHorizontalAngle = angle; }

        float getVerticalAngle() const { return this->mVerticalAngle; };
        void setVerticalAngle(float angle) { this->mVerticalAngle = angle; }

        // Calculatable matrizes from camera
        glm::mat4 getViewMatrix();
        glm::mat4 getProjectionMatrix();

        // Functions
        glm::mat4 lookAt(const glm::vec3 &viewPos = glm::vec3(0.0f, 0.0f, 0.0f));
        glm::vec3 getUp() const;
        glm::vec3 getRight() const;
        glm::vec3 getViewDirection() const;
        /* void setViewDirection(const glm::vec3 &viewDirection) { this->mViewDirection = viewDirection; }; */

        // Movements & rotations
        void move( const glm::vec3 &dist );
        void moveRight( float dist = 1.0f ) { move( dist*getRight() ); }
        void moveLeft( float dist = 1.0f ) { move( -dist*getRight() ); }
        void moveUp( float dist = 1.0f ) { move( dist*getUp() ); }
        void moveDown( float dist = 1.0f ) { move( -dist*getUp() ); }
        void moveForward( float dist = 1.0f ) { move( glm::vec3(1,1,-1) ); }
        void moveBack( float dist = 1.0f ) { move( glm::vec3(1,1,1) ); }

        void rotate( const glm::vec2 &degree );
        void turnRight( float degree ) { rotate( glm::vec2(degree,0) ); }
        void turnLeft( float degree ) { rotate( glm::vec2(-degree,0) ); }
        void turnUp( float degree ) { rotate( glm::vec2(0,degree) ); }
        void turnDown(  float degree ) { rotate( glm::vec2(0,-degree) ); }

        // Callback functions
        void processMouse(float rotH, float rotV);

        // Adrian
        /* void moveCamera(double &xpos, double &ypos, GLFWwindow* window); */
        /* void setDeltaTime(double &time); */

    private:
        glm::vec3   mPos;

        float       mNearPlane;
        float       mFarPlane;
        float       mHFoV;
        float       mAspectRatio;
        float       mHorizontalAngle;
        float       mVerticalAngle;

        /* double      mDeltaTime; */
        float       mMouseSpeed;
        float       mCamSpeed;

};
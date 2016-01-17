#ifndef TERRAIN_H_
#define TERRAIN_H_

#include <GL/glew.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Terrain {

    public:
        Terrain(GLint shaderProgram, int width = 0, int height = 0);
        ~Terrain();
        /* void setHeigthMapData(float* heights); */
        void buildVBO(int floatsPerVertex = 2);
        void buildIBO();
        void setVPMatrix(glm::mat4 vp);
        void draw();

    private:
        int getSize();
        int getVerticeNumber();
        int getIndicesPerRow();
        int getDegensRequired();
        int getTotalIndices();

        int mWidth, mHeight;
        int mTotalIndices, mTotalVertices;

        GLint mShaderProgram;
        GLuint mVPLocation;
        glm::mat4 mVPMatrix;

        GLfloat* mVertices;
        GLint* mIndices;
        GLuint mVao;
        GLuint mVbo;
        GLuint mIbo;

        /* float minPos, posRange; */

};
#endif /* TERRAIN_H_ */
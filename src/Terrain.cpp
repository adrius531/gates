#include "Terrain.h"
#include <iostream>

Terrain::Terrain(GLint shaderProgram, int width, int height)
    : mWidth(width)
    , mHeight(height)
{
	this->mShaderProgram = shaderProgram;
    mTotalVertices = width * height;

    int numStripsRequired = mHeight - 1;
    int numDegensRequired = 2 * (numStripsRequired - 1);
    int verticesPerStrip = 2 * mWidth;
    mTotalIndices = (verticesPerStrip * numStripsRequired) + numDegensRequired;

    glGenVertexArrays(1, &mVao);
    glBindVertexArray(mVao);
}

/* void Terrain::setHeigthMapData(float* heights) */
/* { */
/*     mHeigtData = heights; */
/* } */

int Terrain::getSize()
{
    return mWidth * mHeight;
}

int Terrain::getVerticeNumber()
{
    return mTotalVertices;
}

int Terrain::getTotalIndices()
{
    return mTotalIndices;
}

int Terrain::getIndicesPerRow()
{
    return 2 * mWidth + 2;
}

int Terrain::getDegensRequired()
{
    return (mWidth - 1) * 2;
}

void Terrain::setVPMatrix(glm::mat4 vp)
{
    this->mVPMatrix = vp;
}

void Terrain::buildVBO(int floatsPerVertex)
{
    float minPos = -5.0f;
    float posRange = 10.0f;

    mVertices = new GLfloat[mTotalVertices * floatsPerVertex];

    int offset = 0;
    for(int y = 0; y < mHeight; y++)
    {
        for(int x = 0; x < mWidth; x++)
        {
            float xRatio = x / static_cast<float>(mWidth -1);
            float yRatio = 1.0f - (y / static_cast<float>(mHeight - 1));

            float xPosition = minPos + (xRatio * posRange);
            float yPosition = minPos + (yRatio * posRange);

            mVertices[offset++] = xPosition;
            mVertices[offset++] = yPosition;

        }
    }

    glGenBuffers(1, &mVbo);
    glBindBuffer(GL_ARRAY_BUFFER, mVbo);
    glBufferData(GL_ARRAY_BUFFER, getVerticeNumber() * sizeof(GLfloat), mVertices, GL_STATIC_DRAW);
    GLint terrainPosAttrib = glGetAttribLocation(mShaderProgram, "vPosition");
    mVPLocation = glGetUniformLocation(mShaderProgram, "VPMatrix");
    glVertexAttribPointer(terrainPosAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(terrainPosAttrib);

    //Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Terrain::buildIBO()
{

    mIndices = new GLint[mTotalIndices];

    int offset = 0;
    for(int y = 0; y < mHeight - 1; y++)
    {
        if(y > 0)
            mIndices[offset++] = (y * mHeight);

        for(int x = 0; x < mWidth; x++)
        {
            mIndices[offset++] = ((y * mHeight) + x);
            mIndices[offset++] = (((y+1) * mHeight) + x);
        }

        if(y < mHeight - 2)
            mIndices[offset++] = (((y+1) * mHeight) + (mWidth - 1));

    }


    /* indexCount = mIndices.size(); */

    glGenBuffers(1, &mIbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mTotalIndices * sizeof(GLint), mIndices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Terrain::draw()
{
    glUseProgram(mShaderProgram);
    glUniformMatrix4fv(mVPLocation, 1, GL_FALSE, value_ptr(mVPMatrix));

    // Bind Attributes
    glBindVertexArray(mVao);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIbo);
    /* int size; */
    /* glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size); */
    /* std::cout << "buffer size = " << size << ", vertice numeber = " << getVerticeNumber() << ", indice number = " << totalIndices << std::endl; // size/sizeof(GLuint)*/
    glDrawElements(GL_TRIANGLE_STRIP, mTotalIndices, GL_UNSIGNED_INT, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

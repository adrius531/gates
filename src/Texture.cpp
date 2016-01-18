#include "Texture.h"
unsigned int Texture::idGenerator = 0;

Texture::Texture()
    : texture(0)
    , textureLocation(0)
    , location(0)
    , width(0)
    , height(0)
    , cdata(0)
    , ddata(0)
{
    this->location = idGenerator++;
    glGenTextures(1, &texture);
}

Texture::Texture(const char* imagePath)
    : texture(0)
    , textureLocation(0)
    , location(0)
    , width(0)
    , height(0)
    , cdata(0)
    , ddata(0)
{
    this->location = idGenerator++;
 //   texture = SOIL_load_OGL_texture(imagePath, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT);

//    if(!texture)
//        std::cout << imagePath << " Problem! Fehler: " << SOIL_last_result()  << std::endl;

}

Texture::~Texture()
{
    glDeleteTextures(1, &texture);
}

void Texture::setData(unsigned char* data, int width, int height)
{
    this->cdata     = data;
    this->width     = width;
    this->height    = height;
}

void Texture::setData(float* data, int width, int height)
{
    this->ddata     = data;
    this->width     = width;
    this->height    = height;
}

void Texture::loadCommonOptions(GLenum type)
{

    // Give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, type, this->width, this->height, 0, type, GL_UNSIGNED_BYTE, cdata);

    // build our texture mipmaps
    /* gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data); */

    // select modulate to mix texture with color for shading
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

    // when texture area is small, bilinear filter the closest mipmap
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    // when texture area is large, bilinear filter the first mipmap
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    // texture should tile
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

}

void Texture::loadHeightmapOptions()
{

    // Give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, this->width, this->height, 0, GL_RED, GL_FLOAT, ddata);

    // build our texture mipmaps
    /* gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data); */

    // select modulate to mix texture with color for shading
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

    // when texture area is small, bilinear filter the closest mipmap
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // when texture area is large, bilinear filter the first mipmap
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // texture should tile
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

}

void Texture::bind()
{
    glActiveTexture(GL_TEXTURE0 + this->location);
    glBindTexture(GL_TEXTURE_2D, this->texture);
}

void Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::getTextureLoc()
{
    return textureLocation;
}

GLuint Texture::getTexture()
{
    return texture;
}

void Texture::linkTexture(GLint shaderProgram, const char* texture_name)
{
    glUseProgram(shaderProgram);
    textureLocation = glGetUniformLocation(shaderProgram, texture_name);
    glUniform1i(textureLocation, location);

    // free buffer
    /* free(data); */

}

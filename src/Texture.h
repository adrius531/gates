#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <GL/glew.h>
//#include <SOIL/SOIL.h>
#include <iostream>

/*
 * Texture class. Use in the following order:
 * 1.) Constructor
 * 2.) bind()
 * 3.) setData()
 * 4.) loadCommonOptions()
 * 5.) linkTexture
 */

class Texture
{

    public:
        Texture();
        Texture(const char* imagePath);
        ~Texture();

        GLuint getTexture();
        GLuint getTextureLoc();

        void linkTexture(GLint shaderProgram, const char *texture_name, GLenum type);
        void setData(unsigned char* data, int width, int height);
        void setData(float* data, int width, int height);
        void loadCommonOptions();
        void bind();
        void unbind();


    private:
        static unsigned int idGenerator;
        GLuint texture;
        GLuint textureLocation;
        GLint location;

        int width, height;
        unsigned char* cdata;
        float* ddata;

};
#endif /* TEXTURE_H_ */

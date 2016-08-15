#include "Texture.h"


PETexture * PE_load_texture(const char * _file){
    PETexture *texture = malloc(sizeof (PETexture));
texture->textureID = SOIL_load_OGL_texture(_file,
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MULTIPLY_ALPHA
			);
		glBindTexture(GL_TEXTURE_2D, texture->textureID);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &texture->width);
glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &texture->height);

    return  texture;
}
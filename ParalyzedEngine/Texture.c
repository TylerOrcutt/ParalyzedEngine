#include "Texture.h"
#include "Memory/PEalloc/PEalloc.h"
#include <stdlib.h>
#include <string.h>



PETexture * PE_load_texture(const char * _file){
glEnable(GL_TEXTURE_2D);
printf("Allocating texture\n");
    PETexture *texture = malloc(sizeof (PETexture));
    texture->file = (char*)malloc(sizeof(char)*strlen(_file));
    memcpy(texture->file,(char*)_file,strlen(_file));
    
    printf("texture path: %s\n",texture->file);

texture->textureID= SOIL_load_OGL_texture
        (
        _file,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
    SOIL_FLAG_NTSC_SAFE_RGB| SOIL_FLAG_MULTIPLY_ALPHA  
        );
		glBindTexture(GL_TEXTURE_2D,texture->textureID); 
//  printf("-TextureID:%i\n",texture->textureID);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &texture->width);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &texture->height);

 glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//printf("Texture width:%i\n",texture->width);


    return  texture;

}

void PE_delete_texture(PETexture * texture){
    glDeleteTextures(1,&texture->textureID);
    free (texture);
   
}

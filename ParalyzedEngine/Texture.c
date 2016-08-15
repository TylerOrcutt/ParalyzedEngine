#include "Texture.h"




PETexture * PE_load_texture(const char * _file,int spriteWidth, int spriteHeight){
glEnable(GL_TEXTURE_2D);
    PETexture *texture = malloc(sizeof (PETexture));


texture->textureID= SOIL_load_OGL_texture
        (
        _file,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
    SOIL_FLAG_NTSC_SAFE_RGB| SOIL_FLAG_MULTIPLY_ALPHA  
        );
		glBindTexture(GL_TEXTURE_2D,texture->textureID); 
  printf("-TextureID:%i\n",texture->textureID);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &texture->width);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &texture->height);

 glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
printf("Texture width:%i\n",texture->width);
if(spriteWidth<=0){
	texture->spriteWidth=1.0;
}else{
	texture->spriteWidth=(1.0/(double)texture->width)*(double)spriteWidth;
}


if(spriteHeight<=0){
texture->spriteHeight=1.0 ;
}else{
	texture->spriteHeight=(1.0/(double)texture->height)*(double)spriteHeight;
}

    return  texture;

}
#include "ShaderProgram.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glew.h>
#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>
 
 
void PE_init_shaderProgram(PEShaderProgram * program){
    program->programID=-1;
}

int PE_load_shaderProgram(PEShaderProgram * program, const char * vertexShaderSource, const char * fragmentShaderSource){
      printf("Loading Shader programs\n");

 
            program->programID = glCreateProgram();
            printf("programID: %i\n",program->programID);
      if(program->programID<=0){
            printf("Failed to create shader program\n");

        return -1;
      }      

      GLuint vertexShader,fragmentShader; 
      vertexShader = glCreateShader(GL_VERTEX_SHADER);
      fragmentShader=  glCreateShader(GL_FRAGMENT_SHADER);

     GLuint vlength = strlen(vertexShaderSource);
      glShaderSource(vertexShader,1,&vertexShaderSource,&vlength);
      vlength = strlen(fragmentShaderSource);
      glShaderSource(fragmentShader,1,&fragmentShaderSource,&vlength);


  printf("Building shader program\n");
     glCompileShader(vertexShader);
      glCompileShader(fragmentShader);
    
    GLuint compiled;
       compiled=GL_FALSE;
    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&compiled);
    if(compiled==GL_FALSE){
        int len=1024;
        char * err = malloc(sizeof(char)*len);
        glGetShaderInfoLog(vertexShader,1024,&len,err);

        printf("Failed to compile vertex shader\n %s \n",err);
      return -1;
    }
       compiled=GL_FALSE;
     glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&compiled);
    if(compiled==GL_FALSE){
          int len=1024;
        char * err = malloc(sizeof(char)*len);
        glGetShaderInfoLog(fragmentShader,1024,&len,err);

        printf("Failed to compile fragmentShader shader\n %s \n",err);
        return -1;
    }
   printf("Linking shader program\n"); 

    glAttachShader(program->programID,vertexShader);
    glAttachShader(program->programID,fragmentShader);

    glLinkProgram(program->programID);

   compiled=GL_FALSE;
    glValidateProgram(program->programID);
    glGetProgramiv(program->programID,GL_VALIDATE_STATUS,&compiled);
    if(compiled==GL_FALSE){
        printf("failed to link shader program\n");
     return -1;
    }
    printf("ShaderProgram build successful\n"); 
    return 1;
}
 char * load_shaderSource(const char * shaderFile){
     return "";

 }

 const char * PE_default_vertexShader2D(){
	 
	 const char * source = "#version 120\nattribute  vec4  vPosition;\n" \
				"uniform float vposx;\n" \
				"uniform float vposy;\n" \
				"uniform float vScaleX;\n" \
				"uniform float vScaleY;\n" \
				"uniform float tposx;\n" \
				"uniform float tposy;\n" \
				"uniform float tScaleX;\n" \
				"uniform float tScaleY;\n" \
				"attribute vec2 a_texCoord;\n" \
				"varying vec2 v_texCoord;\n" \
				//"uniform vec3 attenuation;\n"
				//"uniform float intensity;\n"
				"uniform  vec2 light_Position;" \
				"uniform vec4 light_color;" \
				//"varying vec4 out_light_color;"

		"void main() {\n" \
			"vec4 position = vPosition;\n" \
			"position.x=position.x*vScaleX + vposx;\n" \
			"position.y=position.y*vScaleY+ vposy;\n" \
			//"position.z=0.000001;\n"
			"gl_Position =  gl_ModelViewProjectionMatrix*position;\n" \
			"vec2 txtpos;\n"\
			"txtpos.x=( a_texCoord.x*tScaleX)+tposx;\n" \
			"txtpos.y=( a_texCoord.y*tScaleY)+tposy;\n" \
			"v_texCoord = txtpos;\n" \
			"gl_FrontColor = gl_Color;\n" \
		"}";

      return source;
 }

 const char * PE_default_fragmentShader2D(){
    char * source = malloc(sizeof(char)*1048);
           sprintf( source, "%s", "#version 120\nvarying vec2 v_texCoord;" );

    strcat(source,"uniform sampler2D s_texture;");
    strcat(source,"uniform int useTexture;");
     strcat(source,"uniform int isTexxxt;");
        strcat(source,"uniform int numLights;");
  // strcat(source,"uniform vec2 light_Position;");
    // strcat(source,"uniform vec4 light_color;");
       //  strcat(source,"varying vec4 out_light_color;");

    strcat(source,"void main() {");


   strcat(source,"if(useTexture==1 && isTexxxt==1 ){");
     strcat(source,"if(texture2D( s_texture, v_texCoord).a<0.5){");
     
    strcat(source,"gl_FragColor =  vec4(0,0,0,0);");
     strcat(source,"}else{"); 
         strcat(source,"gl_FragColor=gl_Color;");
       strcat(source,"}");


    strcat(source,"} else if(useTexture==1){");
    //     strcat(source,"light_Position = vec2(0,0);");
     // strcat(source,"vec2 light_Position;");
    // strcat(source,"vec4 light_color;");
                  strcat(source,"vec4 light_color = vec4(1,1,1,1);");
                      strcat(source,"vec2 light_Position=vec2(400,300);");
              strcat(source,"vec4 pixel_color = texture2D( s_texture, v_texCoord);");
    /*            strcat(source,"vec3 normals =vec3(0,0,0);");
                    strcat(source,"light_Position=vec2(400,300);");
                 strcat(source,"vec2 rez=vec2(800,600);");
                  strcat(source," vec3 LightDir = vec3(light_Position.xy - (gl_FragCoord.xy / rez.xy), 1.0);");
                   strcat(source,"LightDir.x *= rez.x / rez.y;");
                      strcat(source,"float D = length(LightDir);");
  strcat(source,"if(pixel_color.a>0.5){");
  strcat(source,"normals= vec3(0.5,0.5,1); }");
  strcat(source,"vec3 N = normalize(normals * 2.0 - 1.0);");
 // strcat(source," vec3 L = normalize(light_Position);");
  strcat(source," vec3 Diffuse = (light_color.rbg * light_color.a) * N, 0.0);");
    strcat(source," vec3 Ambient = vec3(0.6f, 0.6f, 1f)* 0.2;");
      strcat(source," vec3 Falloff = vec3(0.4, 3, 20);");
        strcat(source," float Attenuation = 1.0 / ( Falloff.x + (Falloff.y*D) + (Falloff.z*D*D) );");
              strcat(source," vec3 Intensity = Ambient + Diffuse * Attenuation;");
                strcat(source," vec3 FinalColor = pixel_color.rgb * Intensity;");
                          strcat(source," gl_FragColor = vec4(FinalColor, pixel_color.a);");*/

                    strcat(source,"vec3 finalLightColor = vec3(0.075,0.075,0.075) ;"); //base light color
            //  strcat(source,"for(int i=1;i<2;i++){");
          //    strcat(source,"light_Position=vec2(200+(i*200),100+(i*200));");
              strcat(source,"float dist =length(normalize(light_Position-gl_FragCoord.xy));\n");
              strcat(source,"float att = ( 0.4 + (.4*dist) + (20*dist*dist));");
           // strcat(source," vec3 Diffuse = (light_color.rbg * light_color.a) * , 0.0);");
             strcat(source,"finalLightColor=finalLightColor+(light_color.rbg/vec3(att,att,att));");
          //     strcat(source,"}");
             // strcat(source,"if(finalLightColor.x<=0.05 || finalLightColor.y<=0.05 || finalLightColor.z<=0.05){ finalLightColor = vec3(finalLightColor.x+0.05,finalLightColor.y+0.05,finalLightColor.z+0.05);}");   
//strcat(source,"finalLightColor = vec3(finalLightColor.x+0.075,finalLightColor.y+0.075,finalLightColor.z+0.075);");   

 
  //strcat(source,"if(att<=0.5){ att=0.5;}");
   //strcat(source,"gl_FragColor = (pixel_color)*(vec4(att,att,att,1.0)*light_color);");
// strcat(source,"gl_FragColor = (pixel_color)*vec4(finalLightColor,1);");
     strcat(source,"gl_FragColor=pixel_color;");
        strcat(source,"}else{"); 
    strcat(source,"gl_FragColor=gl_Color;");
     strcat(source,"}");
        strcat(source,"}");
 
      return source;
 }

 
 
 
  const char * PE_default_vertexShader3D(){
    char * source = malloc(sizeof(char)*1024);

              sprintf( source, "%s", "#version 400 core\n" );
           strcat(source,"in vec3 position;");
          strcat(source,"uniform mat4 tmatrix;");

 
    strcat(source,"void main() {");
    strcat(source,"gl_Position = tmatrix * vec4(position,1.0);");

        strcat(source,"}");

      return source;
 }

 const char * PE_default_fragmentShader3D(){
    char * source = malloc(sizeof(char)*512);
           sprintf( source, "%s", "#version 400 core\n" );
       //    strcat(source,"in vec3 position;");
           strcat(source,"");

 
    strcat(source,"void main() {");
   

        strcat(source,"}");
 
      return source;
 }

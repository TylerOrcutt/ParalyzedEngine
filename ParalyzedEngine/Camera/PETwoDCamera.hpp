#ifndef __PE_TWO_D_CAMERA_H_
#define __PE_TWO_D_CAMERA_H_

class PETwoDCamera{
	private:
	float x=0,y=0,width=800,height=600;

	public:

	PETwoDCamera(float _x, float _y){
		x=_x;
		y=_y;
	}
	
	PETwoDCamera(float _x, float _y, float _width,float _height){
		x=_x;
		y=_y;
		width=_width;
		height=_height;
	}

	float getX(){
		return x;
	}
	float getY(){
		return y;
	}
	void setX(float _x){
		x=_x;
	}
	void setY(float _y){
		y=_y;
	}





};

#endif

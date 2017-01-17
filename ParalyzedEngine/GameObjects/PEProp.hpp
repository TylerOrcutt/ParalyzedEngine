#ifndef __PE_PROP_H_
#define __PE_PROP_H_
#include "PEGameObject.hpp"
class PEProp : public PEGameObject{
	private:
	
	public:
		PEProp():PEGameObject(){}
		PEProp(std::string _name,int w,int h):PEGameObject(_name,w,h){
		}
		void Load(const char *file);
		void Update();
		void Draw(); 
};


#endif

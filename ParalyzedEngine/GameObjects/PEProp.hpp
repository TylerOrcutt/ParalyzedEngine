#ifndef __PE_PROP_H_
#define __PE_PROP_H_
#include "PEGameObject.hpp"
class PEProp : public PEGameObject{
	private:
	
	public:
		PEProp():PEGameObject(){}
		PEProp(std::string _name,PEGameObjectData * obj):PEGameObject(_name,obj){
		}
		void Load(const char *file);
		void Update();
		void Draw(); 
};


#endif

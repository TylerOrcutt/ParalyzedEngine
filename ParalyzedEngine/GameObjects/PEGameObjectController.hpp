#ifndef __PE_GAME_OBJECT_CONTROLLER__
#define __PE_GAME_OBJECT_CONTROLLER__

class PEGameObjectController{
    public:
    float x,y;
    	float rotation=0.f;
    //PEGameObject* object;
    static PEGameObjectController* create(){ return new PEGameObjectController();}
   
   PEGameObjectController(){
    //   object=obj;
   }
    virtual void Update(){

    }
};

/*
template <typename T> class PEGameObjectControllerImp : public PEGameObjectController {
    public:
    static void * allocate(){return new T;}

};*/
#endif 
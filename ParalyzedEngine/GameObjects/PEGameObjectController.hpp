#ifndef __PE_GAME_OBJECT_CONTROLLER__
#define __PE_GAME_OBJECT_CONTROLLER__

class PEGameObjectController{
    public:
    static PEGameObjectController* create(){ return new PEGameObjectController;}
    virtual void Update(){

    }
};

/*
template <typename T> class PEGameObjectControllerImp : public PEGameObjectController {
    public:
    static void * allocate(){return new T;}

};*/
#endif 
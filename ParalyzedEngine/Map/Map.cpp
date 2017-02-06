#include "Map.hpp"
#include <math.h>

std::string PEMap::load_map(const char * file){
 std::fstream f;
 f.open(file,std::ios::in);

 if(!f.is_open()){
     printf("failed to load map file\n");
     return "" ;
 } 

 std::string data="";
  while(!f.eof()){
      char buf;
      f.read(&buf,1);
      data+=buf;
  }
f.close();


return data;
}

void PEMap::parseMap(std::string map){

PEDictionary * dic = JSONParser::parseJson(map);

//dic->printDictionary();
//dic->printDictionary();
int totalblocks=0;
PEDictionaryItem *mapdata =  dic->get(0);
PEDictionaryItem * mapinfo = mapdata->getItem("Map");
if(mapinfo !=nullptr){
  printf("found map info\n");
 //PEDictionary:: printSubItems(mapinfo->items,5);
 printf("Map width: %d \n",atoi(mapinfo->getItem("width")->value.c_str()));
  printf("Map height: %d \n",atoi(mapinfo->getItem("height")->value.c_str()));



 width=atoi(mapinfo->getItem("width")->value.c_str());
 height =atoi(mapinfo->getItem("height")->value.c_str());
int spcount=atoi(mapinfo->getItem("SheetCount")->value.c_str());
printf("Map SpriteSheets: %d\n",spcount);
spritesheets.resize(spcount);
 
 if(width<=0 || height<=0){
  printf("failed to load map\n");
}

  blocks = (PEBlock**)malloc(sizeof(PEBlock)*width);
  for(int i=0;i<width;i++){
     blocks[i]= (PEBlock*)malloc(sizeof(PEBlock)*height); 
  }
  
}

PEDictionaryItem * blockinfo = mapdata->getItem("Blocks");
if(blockinfo !=nullptr){
  printf("Found %d blocks\n",blockinfo->items.size());
    for(int i=0;i<blockinfo->items.size();i++){
         PEDictionaryItem *blk = blockinfo->getItem(i);
    //  printf("Block x: %d \n",atoi(blk->getItem("x")->value.c_str()));
    // printf("Block y: %d \n",atoi(blk->getItem("y")->value.c_str()));
     int x = atoi(blk->getItem("x")->value.c_str());
     int y =atoi(blk->getItem("y")->value.c_str());
     int imgx = atoi(blk->getItem("imgx")->value.c_str());
     int imgy = atoi(blk->getItem("imgy")->value.c_str());
     blocks[x][y].imgx=imgx;
     blocks[x][y].imgy=imgy;
        totalblocks++;

    }

}


PEDictionaryItem * spinfo = mapdata->getItem("SpriteSheets");
//PEDictionary::printSubItems(spinfo->items,5);
	if(spinfo !=nullptr){
		for(int i=0;i<spinfo->items.size();i++){
			PEDictionaryItem * item = spinfo->getItem(i);
			int id = atoi(item->getItem("id")->value.c_str());
			spritesheets[0] =  PE_load_texture(item->getItem("File")->value.c_str());
		}
	}
PEDictionaryItem * pinfo = mapdata->getItem("Props");
if(pinfo!=nullptr){
	for(int i=0;i<pinfo->items.size();i++){
		PEDictionaryItem * item = pinfo->getItem(i);
		std::string name = item->getItem("name")->value;
		float x = atof(item->getItem("x")->value.c_str());
		float y = atof(item->getItem("y")->value.c_str());

		int id=-1;
		for(int p=0;p<dataObjects.size();p++){
			if(name==dataObjects[p]->name){
				id=p;
				break;
			}
		}
		if(id<0){
			printf("loading Prop: %s\n",name.c_str());
			dataObjects.push_back(new PEGameObjectData(name,std::string("Props/"+name+"/"+name+".prop")));
			id = dataObjects.size()-1;

		}
		props.push_back(new PEProp(name,dataObjects[id]));
				props[props.size()-1]->x =x;
				props[props.size()-1]->y=y;


	//	printf("found Prop: %s\n",name.c_str());
	//
	}}
	printf("Found %d props\nFound %d unique dataobjects\n",props.size(),dataObjects.size());

//props.push_back(new PEProp("bush",10,10));
delete dic;
printf("Loaded %i blocks\n",totalblocks);
}

void PEMap::Update(){
	for(int i=0;i<props.size();i++){
	//	if(i==1){
		props[i]->Update();
	//	}
	}
}

void PEMap::Draw(PETwoDCamera *cam){
	glBindTexture(GL_TEXTURE_2D,spritesheets[0]->textureID);
	for(int x=0;x<width;x++){
		for(int y=0;y<height;y++){
			PEBlock *blk =&blocks[x][y];
 
 
			PE_draw_sprite(spritesheets[0], ((x*(32*MAP_SCALE))-cam->getX()),(y*(32*MAP_SCALE))-cam->getY(),(32*MAP_SCALE),(32*MAP_SCALE),blk->imgx,blk->imgy,32,32);
		}
	}
	
	for(int p=0;p<props.size();p++){
		float x = props[p]->x;
		float y = props[p]->y;
		PEGameObjectData * obj = props[p]->object;
		bool rot = false;
		if(props[p]->rotation !=0){
			glPushMatrix();
			glLoadIdentity();
			rot=true;
			//printf("object rotated %f\n",props[p]->rotation);

			
				glTranslatef( x-cam->getX(),(y)-cam->getY(),0.0);
					glRotatef(props[p]->rotation,0,0,1.f);
		}

		for(int i=0;i<obj->width;i++){
			for(int j=0;j<obj->height;j++){
				PEGameObjectBlock  bls = obj->blocks[i][j];
				if(!rot){
				PE_draw_sprite(spritesheets[0], (x+(i*32))-cam->getX(),
						(y+(j*32))-cam->getY() ,32,32,bls.imgx,bls.imgy,
						 32,32);
				}else{
						PE_draw_sprite(spritesheets[0],(i*32)-(obj->width*32/2),
					(j*32)-(obj->height*32/2),32,32,bls.imgx,bls.imgy,
						 32,32);
				}

			}
		}
		if(rot)
			glPopMatrix();
	 
		}

}

#include "Map.hpp"


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

dic->printDictionary();
//dic->printDictionary();
int totalblocks=0;
PEDictionaryItem *mapdata =  dic->get(0);
PEDictionaryItem * mapinfo = mapdata->getItem("Map");
if(mapinfo !=nullptr){
  printf("found map info\n");
 PEDictionary:: printSubItems(mapinfo->items,5);
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

/*for (int i=0;i<dic->size();i++){
  if(dic->get(i)->key=="SpriteSheet"){
  //spritesheets.push_back(PE_load_texture(dic->get(i)->getItem("loc")->value.c_str()));
 //  printf("%c \n ",dic->get(i)->getItem("loc")->value.c_str());
    //printf("not block\n");
    continue;
  }
 PEBlock block;
  block.x=atof(dic->get(i)->getItem("x")->value.c_str());
    block.y=atof(dic->get(i)->getItem("y")->value.c_str());
      block.width=atof(dic->get(i)->getItem("width")->value.c_str());
        block.height=atof(dic->get(i)->getItem("height")->value.c_str());

          block.imgx=atof(dic->get(i)->getItem("imgx")->value.c_str());
    block.imgy=atof(dic->get(i)->getItem("imgy")->value.c_str());
        blocks.push_back(block);
        totalblocks++;
 // printf("posX: %f\n",blocks[i].x);
 // break;
}*/

props.push_back(new PEProp("bush",10,10));
delete dic;
printf("Loaded %i blocks\n",totalblocks);
}

void PEMap::Update(){
	for(int i=0;i<props.size();i++){
		props[i]->Update();
	}
}

void PEMap::Draw(PETwoDCamera *cam){
	for(int x=0;x<width;x++){
		for(int y=0;y<height;y++){
			PEBlock *blk =&blocks[x][y];
	//		PE_draw_sprite(
				
		}
	}
	
}

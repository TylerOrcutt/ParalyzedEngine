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


PEDictionary * dic = JSONParser::parseJson(data);

//dic->printDictionary();

for (int i=0;i<dic->size();i++){
  if(dic->get(i)->key!="Block"){
    printf("not block\n");
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
 // printf("posX: %f\n",blocks[i].x);
 // break;
}
delete dic;
return data;
}
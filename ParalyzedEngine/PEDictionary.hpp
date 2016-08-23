#ifndef __PE_DICTIONARY_H_
#define __PE_DICTIONARY_H_
#include <string>
#include <vector>
#include <iostream>
struct PEDictionaryItem {
  std::string key;
  std::string value;
  std::vector<PEDictionaryItem> items;

  PEDictionaryItem & operator[](std::string param){
    for(int i=0;i<items.size();i++){
      if(items[i].key==param){
        return items[i];
      }
    }

  }
  PEDictionaryItem & operator[](int index){

    return items[index];
  }
 PEDictionaryItem * getItem(std::string pram){
  for(int i=0;i<items.size();i++ ){
    if(pram==items[i].key){
    return &items[i];
  }
  }
return nullptr;
  }

};


class PEDictionary {
private:
std::vector<PEDictionaryItem> nodes;
public:
PEDictionary(){ }


PEDictionaryItem * getItem(std::string pram){
for(int i=0;i<nodes.size();i++ ){
  if(pram==nodes[i].key){
  return &nodes[i];
}
}
return nullptr;
}


PEDictionaryItem * get(int i){
return &nodes[i];
}

 PEDictionaryItem &  operator[](int index){

  return nodes[index];
}

int size(){
  return nodes.size();
}
void push_back(PEDictionaryItem n){
  nodes.push_back(n);
}

void printDictionary(){
for(int i=0;i<nodes.size();i++){
  std::cout<<"key : "<<nodes[i].key<<std::endl;
  std::cout<<"value : "<<nodes[i].value<<std::endl;
  if(nodes[i].items.size()>0){
    printSubItems(nodes[i].items,5);
  }

}
}
void printSubItems(std::vector<PEDictionaryItem> item,int spaces){
  std::string spaces_str="";
  for(int i=0;i<spaces;i++){
    spaces_str+=" ";
  }
   for(int i=0;i<item.size();i++){
     std::cout<<spaces_str<<"key : "<<item[i].key<<std::endl;
     std::cout<<spaces_str<<"value : "<<item[i].value<<std::endl;
  if(item[i].items.size()>0){
    printSubItems(item[i].items,spaces*2);
  }
}
}


};

#endif 
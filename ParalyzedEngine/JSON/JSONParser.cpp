#include "JSONParser.hpp"
PEDictionary * JSONParser::parseJson(std::string data){
  PEDictionary * a = new PEDictionary();
  for(int i=0;i<data.length();i++){
   // if(data.substr(i,1)=="\""){
    
     // n.key = getValue(data,i+1);
     // i+=n.key.length();
      //ignore data till we find the value pair
    //  for(int k=i;k<data.length()-1 && data.substr(k,1)!=":";k++){i=k;}
    // i++;
      for(int k=i;k<data.length()-1 && data.substr(k,1)!="{" ;k++ ){i=k;}
      //value pair
      //i++;
     /* if(data.substr(i,1)=="\""){
     //    std::cout<<"value pair\n";
          n.value = getValue(data,i+1);
          i+=n.value.length();
            for(int k=i;k<data.length() && data.substr(k,1)==",";k++){i=k;}
            i++;
      }*/
        PEDictionaryItem  n;
        if(data.substr(i,1)=="{"){
          i++;
  ///      std::cout<<"array pair\n";
        n.items=  getSubItems(data, &i,"}");
          }
             a->push_back(n);
//    }
    //  a->push_back(n);
    }

  return a;
}

std::vector<PEDictionaryItem> JSONParser::getSubItems(std::string data, int *index,std::string type){
std::vector<PEDictionaryItem> a;
//std::cout<<"getting sub items\n\n";
    PEDictionaryItem  * n = new PEDictionaryItem();
for(int i=(*index);i<data.length() && data.substr(i,1) !=type;i++){
  
  if(data.substr(i,1)=="\""){
   //get key
   i++;
    n->key = getValue(data,&i);
     for(int k=i;k<data.length() && data.substr(k,1) != ":";k++ ){
           i++;
     }
    
 i++;
     if(data.substr(i,1)=="\""){ // if this is false then it must be an array?
     //get  value
     i++; 
      n->value = getValue(data,&i);
       a.push_back(*n);
        n = new PEDictionaryItem();
     }  

   }
   if(data.substr(i,1)==type){
       
    (*index)=i+1;
   return a;
   }
      if(data.substr(i,1)=="{") {
        i++;
        std::cout<<"array pair\n";
      n->items=  getSubItems(data, &i,"}");
         a.push_back(*n);
   n = new PEDictionaryItem();
        }else    if(data.substr(i,1)=="[") {
        i++;
        std::cout<<"array pair\n";
        n->items=  getSubItems(data, &i,"]");
         a.push_back(*n);
        n = new PEDictionaryItem();
        }
  
    (*index)=i+1;
  }
 
  

  return a;

}

std::string JSONParser::getValue(std::string data, int *index){
  std::string value="";
  for(int i=(*index); i<data.length();i++){
    if(data.substr(i,1) == "\""){
  (*index)=i+1;
      break;
    }
    value+=data.substr(i,1);
  }

  return value;
}
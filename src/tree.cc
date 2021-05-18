#include"../include/tree.hpp"
 
    namespace fc{
        namespace fe{
fb::box* seqTree::make_box(){
    fb::seqbox* p=new fb::seqbox();
    for(auto m:treeVec){
        p->boxVec.push_back(m->make_box());
        
    }
    return reinterpret_cast<fb::box*>(p);
}

fb::box* simpleTree::make_box(){
    fb::simplebox* p= new fb::simplebox();
    p->text=text;
    return reinterpret_cast<fb::box*>(p);
}

fb::box* ifTree::make_box(){
    fb::ifbox* p=new fb::ifbox();
    p->cond=cond;
    p->if_do=reinterpret_cast<fb::seqbox*>(if_do->make_box());
    if(else_do!=nullptr)
        p->else_do=reinterpret_cast<fb::seqbox*>(else_do->make_box());
    return reinterpret_cast<fb::box*>(p);
}

fb::box* whileTree::make_box(){
    fb::whilebox* p=new fb::whilebox();
    p->cond=cond;
    p->loop_do=reinterpret_cast<fb::seqbox*>(loop_do->make_box());
    return reinterpret_cast<fb::box*>(p);
}






        }//namespace fe;
    }//namespace fc
 
#include"../include/charEmitter.hpp"
#include<iostream>
#include<fstream>
        namespace fc{
            namespace fd{

void charEmitter::print(){
    if(os.is_open()){
        for(auto m:*strVec){
            os<<m<<'\n';
        }
    }
    else{
        for(auto m:*strVec){
            std::cout<<m<<std::endl;
        }
    }
}

void charEmitter::read(fb::seqbox* readbox){
    seqBox=readbox;
    init();
}

void charEmitter::init(){
    seqBox->getW();
    seqBox->getPos(-1,seqBox->lw+4);
    int cdim=seqBox->lw+seqBox->rw+4;
    int rdim=seqBox->endpos.first;
    strVec=new std::vector<std::string>(rdim+1,std::string(cdim+1,' '));
    seqBox->fillstr(*strVec);
}



void charEmitter::open(const std::string& str){
    outputDir=str;
    os.open(outputDir);
    if(!os.is_open()){
        std::cerr<<"no such diretory to write the file:"<<outputDir<<std::endl;
        exit(-1);
    }
}
            }//namespace fd
        }//namespace fc
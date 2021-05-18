#include "../include/CodePaser.hpp"
#include"../include/charEmitter.hpp"

#include<iostream>
#include<string.h>

using namespace fc;

void printHelp(){
    std::cout << std::endl;
    std::cout << "flowchar - a tiny tool for conversion from pseudo-code to flowchart in character format" << std::endl
              << std::endl;
    std::cout << "Usage:" << std::endl;
    std::cout << "\t flowchar -c <codePath> [-o <chartPath>]" << std::endl << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "\t -c <path> \t specify path of code to be parsed, required." << std::endl;
    std::cout << "\t -o <path> \t specify path of chart to be emitted, optional. If absent, print to stdout." << std::endl<<std::endl;
}

int main(int argv,char**argc ){
    if(argv!=3&&argv!=5){
       printHelp();         
       exit(-1);
    }
    if(strcmp(argc[1],"-c")!=0){
         printHelp();
         exit(-1);
    }
    fp::codePaser paser(argc[2]);
    paser.init();
    paser.scan();
    paser.parse();
    if(argv==3){
         fd::charEmitter Emiter;
         Emiter.read(paser.retSeqBox());
         Emiter.print();
    }
    else{
         fd::charEmitter Emiter;
         Emiter.read(paser.retSeqBox());
         Emiter.open(argc[4]);
         Emiter.print();
    }
}
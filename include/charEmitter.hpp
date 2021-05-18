#ifndef _CHAR_EMITTER_HPP_
#define _CHAR_EMITTER_HPP_
#include"box.hpp"
#include<fstream>
    namespace fc{
        namespace fd{

class charEmitter{
private:
    std::ofstream os;
    std::string outputDir;
    std::vector<std::string>*strVec;
    fb::seqbox* seqBox;
private:
    void init();
public:
    void print();
    void read(fb::seqbox*);
    void open(const std::string& str);
    charEmitter():strVec(nullptr),seqBox(nullptr){}
};

        }//namespace fd
    }//namespace fc 

#endif
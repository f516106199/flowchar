#ifndef _CODEPASER_HPP_
#define _CODEPASER_HPP_
#include<fstream>
#include<cstring>
#include<string>
#include<vector>
#include<stack>
#include"token.hpp"
#include"tree.hpp"
#include"box.hpp"
    namespace fc{
        namespace fp{
enum class paserKind{
    ifLB,
    ifRB,
    whileLB,
    whileRB,
    elseLB,
    elseRB,
    ifT,
    elseT,
    ifcond,
    whilecond,
    simple,
    whileT,
    Begin
};
class codePaser{
    paserKind K;
    std::stack<fe::ifTree*>Ifstk;
    std::stack<fe::whileTree*>Wstk;
    std::stack<fe::seqTree*>Estk;
    std::stack<paserKind>envStk;
    paserKind env;

    std::string inputDIr;
    std::fstream is ;
    std::vector<ft::token*>tokenVec;
    std::vector<fe::tree*>treeVec;
    public:
    void scan();
    void init();
    codePaser(const std::string& is):inputDIr(is){}
    void printToken();
    void parse();
    void parse(int& index,paserKind k,paserKind env,fe::tree*T);
    void parseBlk(int&);
    void parseRb(int&);
    fb::seqbox* retSeqBox(){
       auto p= new fe::seqTree();
       p->treeVec=treeVec;
       return reinterpret_cast<fb::seqbox*>((p->make_box()));
    }
};

        }//namespace fp
    }//namespace fc 

#endif
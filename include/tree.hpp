#ifndef _TREE_HPP_
#define _TREE_HPP_

#include"token.hpp"
#include"box.hpp"
//#include"CodePaser.hpp"

#include<vector>

    namespace fc{
    namespace fp{
        class codePaser;
    }
        namespace fe{
class tree{
    public:
    enum class Kind{
        seqTree,
        ifTree,
        whilleTree,
        simpleTree
    };
    Kind kind;
    tree(Kind kind):kind(kind){}
    virtual fb::box* make_box()=0;
};

class seqTree:public tree{
    friend class fp::codePaser;
private:
    std::vector<tree*>treeVec;
public:
    seqTree(tree::Kind kind=tree::Kind::seqTree):tree(kind){}
    void operator +=(tree*);
    virtual fb::box* make_box()override;
};

class ifTree:public tree{
    friend class fp::codePaser;
private:
    std::string cond;
    seqTree* if_do;
    seqTree* else_do;
public:
    ifTree():tree(Kind::ifTree),if_do(nullptr),else_do(nullptr){}
    ifTree(const std::string&cond):tree(Kind::ifTree),cond(cond),if_do(nullptr),else_do(nullptr){}
    virtual fb::box* make_box()override;
};

class whileTree:public tree{
    friend class fp::codePaser;
private:
    std::string cond;
    seqTree* loop_do;
public:
    whileTree():tree(Kind::whilleTree),loop_do(nullptr){}
    whileTree(const std::string&cond):tree(Kind::whilleTree),cond(cond),loop_do(nullptr){}
    virtual fb::box* make_box()override;
};

class simpleTree:public tree{
    friend class codePaser;
private:
    std::string text;
public:
    simpleTree():tree(Kind::simpleTree){}
    simpleTree(const std::string&text):tree(Kind::simpleTree),text(text){}
    virtual fb::box* make_box()override;
};

        }//namespace fe;
    }//namespace fc
#endif
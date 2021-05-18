#ifndef _BOX_HPP_
#define _BOX_HPP_
#include<utility>
#include<cmath>
#include<vector>
#include<string>
        namespace fc{
            namespace fb{

class box{
public:
    enum class Kind{
        simple,
        ifbox,
        whilebox,
        seqbox
    };
    std::pair<int,int>endpos;
    int lw;
    int rw;
    Kind kind;
public:
    box(Kind kind):kind(kind){}
    virtual void getW()=0;
    virtual std::pair<int,int> getPos(int r,int c)=0;
    virtual void fillstr(std::vector<std::string>&)=0;
};

class seqbox:public box{
public:
    std::vector<box*>boxVec;
    seqbox():box(Kind::seqbox){} 
    virtual void getW()override;
    virtual std::pair<int,int> getPos(int r,int c)override;
    virtual void fillstr(std::vector<std::string>&)override;
    
};

class ifbox:public box{
public:
    seqbox* if_do;
    seqbox* else_do;
    std::string cond;
    int width;
    int len_;
    std::pair<int,int>pos;
public:
    ifbox():box(Kind::ifbox),if_do(nullptr),else_do(nullptr){}
    virtual void getW()override;
    virtual std::pair<int,int> getPos(int r,int c)override;
    virtual void fillstr(std::vector<std::string>&strVec) override;
};

class whilebox:public box{
public:
    seqbox* loop_do;
    int width;
    int len_r;
    int len_l;
    std::string cond;
    std::pair<int,int>pos;
public:
    whilebox():box(Kind::whilebox),loop_do(nullptr){}
    virtual void getW()override;
    virtual std::pair<int,int> getPos(int r,int c)override;
    virtual void fillstr(std::vector<std::string>&strVec)override;
};
  
class simplebox:public box{
public:
    int width;
    std::string text;
    std::pair<int,int>pos;
public:
    simplebox():box(Kind::simple){}
    virtual void getW()override;
    virtual std::pair<int,int> getPos(int r,int c)override;
    virtual void fillstr(std::vector<std::string>&strVec)override;
};
            }//namespace fb
        }//namespace fc

#endif
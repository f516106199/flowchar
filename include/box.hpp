#ifndef _BOX_HPP_
#define _BOX_HPP_
#include<utility>
#include<cmath>
#include<vector>
#include<string>
        namespace fc{
namespace fe{
    class ifTree;
    class whileTree;
    class simpleTree;
    class seqTree;
}//namespace fe 
namespace fd{
    class charEmitter;
}
            namespace fb{

class box{
    friend class seqbox;
protected:
    enum class Kind{
        simple,
        ifbox,
        whilebox,
        seqbox
    };
protected:
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
    friend class fe::seqTree;
    friend class ifbox;
    friend class whilebox;
    friend class fd::charEmitter;
    std::vector<box*>boxVec;
public:
    seqbox():box(Kind::seqbox){} 
    virtual void getW()override;
    virtual std::pair<int,int> getPos(int r,int c)override;
    virtual void fillstr(std::vector<std::string>&)override;
    
};

class ifbox:public box{
    friend class fe::ifTree;
    friend class seqbox;
private:
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
    friend class fe::whileTree;
    friend class seqbox;
private:
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
    friend class fe::simpleTree;
    friend class seqbox;
private:
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
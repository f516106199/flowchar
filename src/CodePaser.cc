#include"../include/CodePaser.hpp"
#include"../include/token.hpp"

#include<exception>
#include<iostream>
#include<vector>
#include<stack>
    namespace fc{
        namespace fp{

void codePaser::init(){
    is.open(inputDIr,std::ios::in);
    try{
        if(!is.is_open()){
            throw new std::invalid_argument("fail to open the file !");
        }
    }
    catch (std::invalid_argument* ptr ){
        std::cerr<<ptr->what()<<std::endl;
        exit(-1);
    }
}

void codePaser::printToken(){
    for(auto m:tokenVec){
        if(m->kind==ft::token::Kind::COND){
            std::cout<<"cond: "<<reinterpret_cast<ft::CondToken*>(m)->text;
        }
        else if(m->kind==ft::token::Kind::ELSE){
            std::cout<<"else ";
        }
        else if(m->kind==ft::token::Kind::IF){
            std::cout<<"if ";
        }
        else if(m->kind==ft::token::Kind::LBRACE){
            std::cout<<"{ ";
        }
        else if(m->kind==ft::token::Kind::RBRACE){
            std::cout<<"} ";
        }
        else if(m->kind==ft::token::Kind::SEM){
            std::cout<<": ";
        }
        else if(m->kind==ft::token::Kind::STM){
            std::cout<<"STM: "<<reinterpret_cast<ft::StmToken*>(m)->text;
        }
        else if(m->kind==ft::token::Kind::WHILE){
            std::cout<<"while ";
        }
        std::cout<<"("<<m->pos.first<<","<<m->pos.second<<")"<<std::endl;
    }
}

void codePaser::scan(){
    char c ;
    std::string str;
    int parenDif=0;
    std::pair<int,int>pos=std::make_pair<int,int>(1,1);
    while(!is.eof()){
        if(str.size()){
            str.erase(0,str.find_first_not_of(' '));
        }
        std::string strtmp=str;
        if(strtmp.size()){
            strtmp.erase(strtmp.find_last_not_of(' ')+1);
        }
        is.get(c);
        if(c==ft::token::lparen&&strtmp==ft::token::ifToken){
            tokenVec.push_back(new ft::IfToken(pos));
            ++parenDif;
            str.clear();
            while(is.good()){
                is.get(c);
                if(c=='('){
                    ++parenDif;
                }
                else if(c==')'){
                    --parenDif;
                    if(parenDif==0){
                        tokenVec.push_back(new ft::CondToken(pos,str));
                        str.clear();
                        ++pos.second;
                        break;
                    }
                }
                else if (c=='\n'){
                    std::cerr<<"'(' and ')' not match in row " <<pos.first<<std::endl;
                    exit(-1);
                }
                ++pos.second;
                str+=c;
            }
            if(parenDif!=0){
                std::cerr<<"'(' and ')' not match in row " <<pos.first<<std::endl;
                exit(-1);
            }
        }
        else if(c==ft::token::lbrace&&strtmp.empty()){
            tokenVec.push_back(new ft::LbraceToken(pos));
        }
        else if(c==ft::token::rbrace&&strtmp.empty()){
            tokenVec.push_back(new ft::RbraceToken(pos));
        }
        else if(c==ft::token::rbrace&&!strtmp.empty()){
            std::cerr<<"lost ';' in row "<<pos.first-1<<std::endl;
            exit(-1);
        }
        else if(c==ft::token::semicolon){
            if(str.size())
                tokenVec.push_back(new ft::StmToken(pos,str));
            str.clear();
        }
        else if(strtmp==ft::token::whileToken&&c==ft::token::lparen){
            tokenVec.push_back(new ft::WhileToken(pos));
            ++parenDif;
            str.clear();
            while(is.good()){
                is.get(c);
                if(c=='('){
                    ++parenDif;
                }
                else if(c==')'){
                    --parenDif;
                    if(parenDif==0){
                        tokenVec.push_back(new ft::CondToken(pos,str));
                        tokenVec.back()->pos.second-=(str.size()-1);
                        str.clear();
                        ++pos.second;
                        break;
                    }
                }
                else if(c=='\n'){
                    std::cerr<<"'('and ')' not match in row " <<pos.first<<std::endl;
                    exit(-1);
                }
                ++pos.second;
                str+=c;
            }
            if(parenDif!=0){
                std::cerr<<"'('and ')' not match in row " <<pos.first<<std::endl;
                exit(-1);
            }
        }
        else if(strtmp==ft::token::elseToken&&c=='{'){
            tokenVec.push_back(new ft::ElseToken(pos));
            tokenVec.push_back(new ft::LbraceToken(pos));
            str.clear();
        }
        else if(c=='\n'){
            ++pos.first;
            pos.second=1;
            continue;
        }
        else if(c=='\t'){
            pos.second+=4;            
            continue;
        }
        else if(c==' '){
            str+=c;
            pos.second++;
            continue;
        }
        else {
            str+=c;
        }
        ++pos.second;
    }
}


void codePaser::parseBlk(int& index){
    fe::tree* p=nullptr;
    if(tokenVec[index]->kind==ft::token::Kind::IF){
        p=new fe::ifTree();
        if(K==paserKind::ifLB)
            Ifstk.top()->if_do->treeVec.push_back(p);
        else if(K==paserKind::whileLB)
            Wstk.top()->loop_do->treeVec.push_back(p);
        else if(K==paserKind::elseLB)  
            Estk.top()->treeVec.push_back(p);
        else if(K==paserKind::Begin){
            treeVec.push_back(p);
            if(p->kind==fe::tree::Kind::simpleTree){
                env=paserKind::simple;
                envStk.push(env);
            }
        }
        K=paserKind::ifT;
        env=paserKind::ifT;
        envStk.push(env);
        Ifstk.push(reinterpret_cast<fe::ifTree*>(p));
    }
    else if (tokenVec[index]->kind==ft::token::Kind::WHILE){
        p =new fe::whileTree();
        if(K==paserKind::ifLB)
            Ifstk.top()->if_do->treeVec.push_back(p);
        else if(K==paserKind::whileLB)
            Wstk.top()->loop_do->treeVec.push_back(p);
        else if(K==paserKind::elseLB)  
            Estk.top()->treeVec.push_back(p);
        else if(K==paserKind::Begin){
            treeVec.push_back(p);
            if(p->kind==fe::tree::Kind::simpleTree){
                env=paserKind::simple;
                envStk.push(env);
            }
        }
        K=paserKind::whileT;
        env=paserKind::whileT;
        envStk.push(env);
        Wstk.push(reinterpret_cast<fe::whileTree*>(p));
    }
    else if(tokenVec[index]->kind==ft::token::Kind::STM){
        p =new fe::simpleTree(reinterpret_cast<ft::StmToken*>(tokenVec[index])->text);
         if(K==paserKind::ifLB)
            Ifstk.top()->if_do->treeVec.push_back(p);
        else if(K==paserKind::whileLB)
            Wstk.top()->loop_do->treeVec.push_back(p);
        else if(K==paserKind::elseLB)  
            Estk.top()->treeVec.push_back(p);
        else if(K==paserKind::Begin){
            treeVec.push_back(p);
            if(p->kind==fe::tree::Kind::simpleTree){
                env=paserKind::simple;
                envStk.push(env);
            }
        }
        K=paserKind::simple;
    }
    else {
        std::cerr<<"wrong in row "<<tokenVec[index]->pos.first<<std::endl;
        exit(-1);
    }
}



void codePaser::parseRb(int &index){
    fe::tree* p=nullptr;
    if(tokenVec[index]->kind==ft::token::Kind::IF){
        if(K==paserKind::ifRB)
            Ifstk.pop();
        else if(K==paserKind::elseRB){
            Ifstk.pop();
            Estk.pop();
            envStk.pop();
        }
        else if(K==paserKind::whileRB){
            Wstk.pop();
        }
        p=new fe::ifTree();
        envStk.pop();
        if(envStk.empty()){
            env=paserKind::simple;
        }
        else
            env=envStk.top();
        if(env==paserKind::simple){
            treeVec.push_back(p);
        }   
        else if(env==paserKind::ifT) {
            Ifstk.top()->if_do->treeVec.push_back(p);
        }
        else if(env==paserKind::elseT){
            Estk.top()->treeVec.push_back(p);
        }
        else if(env==paserKind::whileT){
            Wstk.top()->loop_do->treeVec.push_back(p);
        }
        Ifstk.push(reinterpret_cast<fe::ifTree*>(p));
        env=paserKind::ifT;
        K=env;
        envStk.push(env);
    }
    else if (tokenVec[index]->kind==ft::token::Kind::WHILE){
        if(K==paserKind::ifRB)
            Ifstk.pop();
        else if(K==paserKind::whileRB)
            Wstk.pop();
        else if(K==paserKind::elseRB){
            Ifstk.pop();
            Estk.pop();
            envStk.pop();
        }
        p=new fe::whileTree();
        envStk.pop();
        if(envStk.empty()){
            env=paserKind::simple;
        }
        else{
            env=envStk.top();
        }
        if(env==paserKind::simple){
            treeVec.push_back(p);
        }   
        else if(env==paserKind::ifT) {
            Ifstk.top()->if_do->treeVec.push_back(p);
        }
        else if(env==paserKind::elseT){
            Estk.top()->treeVec.push_back(p);
        }
        else if(env==paserKind::whileT){
            Wstk.top()->loop_do->treeVec.push_back(p);
        }
        env=paserKind::whileT;
        K=paserKind::whileT;
        envStk.push(env);
        Wstk.push(reinterpret_cast<fe::whileTree*> (p));
    }
    else if(tokenVec[index]->kind==ft::token::Kind::STM){
        if(K==paserKind::ifRB)
            Ifstk.pop();
        else if(K==paserKind::whileRB)
            Wstk.pop();
        else {
            Ifstk.pop();
            Estk.pop();
            envStk.pop();
        }
        p=new fe::simpleTree(reinterpret_cast<ft::StmToken*>(tokenVec[index])->text);
        envStk.pop();
        if(envStk.empty()){
            env=paserKind::simple;
        }
        else{
            env=envStk.top();
        }
        if(env==paserKind::simple){
            treeVec.push_back(p);
        }   
        else if(env==paserKind::ifT) {
            Ifstk.top()->if_do->treeVec.push_back(p);
        }
        else if(env==paserKind::elseT){
            Estk.top()->treeVec.push_back(p);
        }
        else if(env==paserKind::whileT){
            Wstk.top()->loop_do->treeVec.push_back(p);
        }
        K=paserKind::simple;
    }
    else if (K==paserKind::ifRB&&tokenVec[index]->kind==ft::token::Kind::ELSE){
        p=new fe::seqTree();   
        Ifstk.top()->else_do=reinterpret_cast<fe::seqTree*> (p);
        env=paserKind::elseT;
        K=paserKind::elseT;
        envStk.push(env);
        Estk.push(reinterpret_cast<fe::seqTree*> (p));
        return ;
    }
    else if(tokenVec[index]->kind==ft::token::Kind::RBRACE){
        if(K==paserKind::ifRB)
            Ifstk.pop();
        else if(K==paserKind::whileRB){
            Wstk.pop();
        }
        else if(K==paserKind::elseRB){
            Ifstk.pop();
            Estk.pop();
            envStk.pop();
        }
        envStk.pop();
        if(envStk.empty()){
            env=paserKind::simple;
        }
        else {
            env=envStk.top();
        }
        if(env==paserKind::simple){
            std::cerr<<"wrong in row "<<tokenVec[index]->pos.first<<", invalid '}' "<<std::endl;
            exit(-1);
        }  
        else if(env==paserKind::ifT){
            K=paserKind::ifRB;
        }
        else if(env==paserKind::elseT){
            K=paserKind::elseRB;
        }
        else if(env==paserKind::whileT){
            K=paserKind::whileRB;
        }
        return ;
    }
    else {
        std::cerr<<"wrong in row "<<tokenVec[index]->pos.first<<std::endl;
        exit(-1);
    }

}

   
//iftoken ,simple token ,else token ,whiletoken,brace token , cond token 
void codePaser::parse(){
    K=paserKind::Begin;
    env=paserKind::simple;
    int index=0;
    while(index<tokenVec.size()){
        if(K==paserKind::Begin){
            parseBlk(index);
        }
        else if (K==paserKind::ifT){
            if(tokenVec[index]->kind==ft::token::Kind::COND){
                Ifstk.top()->cond=reinterpret_cast<ft::CondToken*>(tokenVec[index])->text;
                K=paserKind::ifcond;
            }
            else {
                std::cerr<<"condition should be behand of 'if' in row"<<tokenVec[index]->pos.first<<std::endl;
                exit(-1);
            }
        }
        else if (K==paserKind::elseT){
            if(tokenVec[index]->kind==ft::token::Kind::LBRACE){
                K=paserKind::elseLB;
            }
            else{
                std::cerr<<"'}' should be behand of 'else' in row "<<tokenVec[index]->pos.first<<std::endl;
                exit(-1);
            }
        }
        else if (K==paserKind::whileT){
            if(tokenVec[index]->kind==ft::token::Kind::COND){
                Wstk.top()->cond=reinterpret_cast<ft::CondToken*>(tokenVec[index])->text;
                K=paserKind::whilecond;
            }
            else{
                std::cerr<<"condition should be behand of 'while' in row "<<tokenVec[index]->pos.first<<std::endl;
                exit(-1);
            }
        }
        else if (K==paserKind::ifcond){
            if(tokenVec[index]->kind==ft::token::Kind::LBRACE){
                K=paserKind::ifLB;
            }
            else{
                std::cerr<<"'{' should be behand of condition in row "<<tokenVec[index]->pos.first<<std::endl;
                exit(-1);
            }
        }
        else if (K==paserKind::whilecond){
            if(tokenVec[index]->kind==ft::token::Kind::LBRACE){
                K=paserKind::whileLB;
            }
            else{
                std::cerr<<"'{' should be behand of condition in row "<<tokenVec[index]->pos.first<<std::endl;
                exit(-1);
        }
        }
        else if (K==paserKind::ifLB){
            Ifstk.top()->if_do=new fe::seqTree();
            parseBlk(index);
        }
        else if(K==paserKind::elseLB){
            parseBlk(index);
        }
        else if (K==paserKind::whileLB){
            Wstk.top()->loop_do=new fe::seqTree();
            parseBlk(index);
        }
        else if (K==paserKind::ifRB){
            parseRb(index);
        }
        else if (K==paserKind::whileRB){
            parseRb(index);
        }
        else if(K==paserKind::elseRB){
            parseRb(index);
        }
        else if (K==paserKind::simple){
            fe::tree* p=nullptr;
            paserKind preKind=env;
            if(tokenVec[index]->kind==ft::token::Kind::IF){
                p=new fe::ifTree();
                K=paserKind::ifT;
                if(preKind==paserKind::ifT){
                    Ifstk.top()->if_do->treeVec.push_back(p);
                }
                else if(preKind==paserKind::elseT){
                    Estk.top()->treeVec.push_back(p);
                }
                else if(preKind==paserKind::whileT){
                    Wstk.top()->loop_do->treeVec.push_back(p);
                }
                else if(preKind==paserKind::simple){
                    treeVec.push_back(p);
                }     
                Ifstk.push(reinterpret_cast<fe::ifTree*>(p));
                env=paserKind::ifT;
                envStk.push(env);
            }
            else if(tokenVec[index]->kind==ft::token::Kind::WHILE){
                p=new fe::whileTree();
                K=paserKind::whileT;
                if(preKind==paserKind::ifT){
                    Ifstk.top()->if_do->treeVec.push_back(p);
                }
                else if(preKind==paserKind::elseT){
                    Estk.top()->treeVec.push_back(p);
                }
                else if(preKind==paserKind::whileT){
                    Wstk.top()->loop_do->treeVec.push_back(p);
                }
                else if(preKind==paserKind::simple){
                    treeVec.push_back(p);
                }  
                Wstk.push(reinterpret_cast<fe::whileTree*>(p));
                env=K;
                envStk.push(env);
            }
            else if(tokenVec[index]->kind==ft::token::Kind::STM){
                p=new fe::simpleTree(reinterpret_cast<ft::StmToken*>(tokenVec[index])->text);
                if(preKind==paserKind::ifT){
                    Ifstk.top()->if_do->treeVec.push_back(p);
                }
                else if(preKind==paserKind::elseT){
                    Estk.top()->treeVec.push_back(p);
                }
                else if(preKind==paserKind::whileT){
                    Wstk.top()->loop_do->treeVec.push_back(p);
                }
                else if(preKind==paserKind::simple){
                    treeVec.push_back(p);
                }  
                K=paserKind::simple;
            }
            else if (tokenVec[index]->kind==ft::token::Kind::RBRACE){
                if(env==paserKind::simple){
                    std::cerr<<"invalid '}' in row "<<tokenVec[index]->pos.first<<std::endl;
                    exit(-1);
                }
                else if(env==paserKind::ifT){
                    K=paserKind::ifRB;
                }
                else if(env==paserKind::whileT){
                    K=paserKind::whileRB;
                }
                else if(env==paserKind::elseT){
                    K=paserKind::elseRB;
                }
            }
            else{
                std::cerr<<"wrong at position ("<<tokenVec[index]->pos.first<<","<<tokenVec[index]->pos.second<<")"<<std::endl;
                exit(-1);
            }            
        }       
        ++index;
    }
    if(envStk.empty()){
        return ;
    }
    if(K==paserKind::ifRB||K==paserKind::whileRB){
        envStk.pop();
        if(envStk.size()==1&&envStk.top()==paserKind::simple){
            return ;
        }
        if(!envStk.empty()){
            std::cerr<<" '{' and '}' not match at end of file"<<std::endl;
            exit(-1);
        }
    }
    else if(K==paserKind::elseRB){
        envStk.pop();
        envStk.pop();
        if(envStk.size()==1&&envStk.top()==paserKind::simple){
            return ;
        }
        if(!envStk.empty()){
            std::cerr<<" '{' and '}' not match at end of file "<<std::endl;
            exit(-1);
        }   
    }
    else if(K==paserKind::simple){
        if(envStk.size()==1&&envStk.top()==paserKind::simple){
            return ;
        }
        if(!envStk.empty()){
            std::cerr<<" '{' and '}' not match at end of file "<<std::endl;
            exit(-1);
        }
    }
    else {
        std::cerr<<"wrong at end of file"<<std::endl;
        exit(-1);
    }
   //for(auto m:treeVec){
    //    m->print(0);
    //}
}


        }//namespace fp
    }//namespace fc
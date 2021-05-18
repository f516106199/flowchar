#include"../include/box.hpp"

    namespace fc{
        namespace fb{

int getEven(const std::string& s ){
    if(s.size()%2==1){
        return s.size();
    }
    else {
        return s.size()+1;
    }
}


void seqbox::getW(){
    lw=rw=0;
    for(auto m:boxVec){
        m->getW();
        lw=std::max(lw,m->lw);
        rw=std::max(rw,m->rw); 
    }
}

void ifbox::getW(){
    width=getEven(cond)+4;
    lw=rw=width/2;
    if_do->getW();
    if(else_do==nullptr){
        rw=std::max(rw,if_do->rw);
        lw=std::max(lw,if_do->rw)+4;
        len_=lw-width/2-1;
    }
    else{
        else_do->getW();
        int tmp;
        tmp =std::max(width,if_do->lw+else_do->rw);
        if(tmp%2==1){
            tmp+=4;
        }
        else {
            tmp+=5;
        }
        len_=(tmp-width)/2;
        lw=tmp/2+1+else_do->lw;
        rw=tmp/2+1+if_do->rw;
    }
}

void whilebox::getW(){
    width=getEven(cond)+4;
    lw=rw=width/2;
    loop_do->getW();
    lw=std::max(lw,loop_do->lw)+4;
    rw=std::max(rw,loop_do->rw)+4;
    len_r=rw-(width/2)-1;
    len_l=lw-(width/2)-1;
}

void simplebox::getW(){
    width=getEven(text)+4;
    lw=rw=width/2;
}

std::pair<int,int> seqbox::getPos(int r,int c ){
    for(auto m:boxVec){
        auto fir=m->getPos(r,c).first;
        r=fir+3;
    }
    return endpos=std::make_pair(r-3,c);
}

std::pair<int,int>ifbox::getPos(int r ,int c ){
    pos.first=r+3;
    pos.second=c;
    if(else_do==nullptr){
        if_do->getPos(r+6,c);
        endpos.first=if_do->endpos.first+3;
        endpos.second=c;
    }
    else{
        if_do->getPos(r+5,c+width/2+len_+1);
        else_do->getPos(r+5,c-width/2-len_-1);
        endpos.first=std::max(if_do->endpos.first,else_do->endpos.first)+3;
        endpos.second=c;
    }
    return endpos;
}

std::pair<int,int>whilebox::getPos(int r ,int c ){
    pos.first=r+3;
    pos.second=c;
    loop_do->getPos(r+6,c);
    endpos.first=loop_do->endpos.first+5;
    endpos.second=c;
    return endpos;
}

std::pair<int,int>simplebox::getPos(int r ,int c ){
    pos.first=r+3;
    pos.second=c;
    return  endpos=pos;
}

void fillSbox(std::vector<std::string>&strVec,int rh,int rl,int ch,int cl,const std::string &str){
    strVec[rh][cl]=strVec[rl][ch]=strVec[rh][ch]=strVec[rl][cl]='+';
    for(int i=cl+1;i!=ch;++i){
        strVec[rh][i]='-';
        strVec[rl][i]='-';
    }
    strVec[rh-1][cl]=strVec[rh-1][ch]='|';
    for(int i=0;i!=str.size();++i){
        strVec[rh-1][cl+2+i]=str[i];
    }
}

void fillCbox(std::vector<std::string>&strVec,int rh,int rl,int ch,int cl,const std::string& str){
    strVec[rh][cl]=strVec[rl][ch]='\\';
    strVec[rh][ch]=strVec[rl][cl]='/';
    strVec[rl][cl-1]='N';
    for(int i=cl+1;i!=ch;++i){
        strVec[rh][i]='-';
        strVec[rl][i]='-';
    }
    strVec[rh-1][cl]=strVec[rh-1][ch]='|';
    for(int i=0;i!=str.size();++i){
        strVec[rh-1][cl+2+i]=str[i];
    }
}

void seqbox::fillstr(std::vector<std::string>&strVec){
    for(int i=0;i!=boxVec.size();++i){
        boxVec[i]->fillstr(strVec);
        if(i!=boxVec.size()-1){
            strVec[boxVec[i]->endpos.first+1][endpos.second]=strVec[boxVec[i]->endpos.first+2][endpos.second]='|';
            strVec[boxVec[i]->endpos.first+3][endpos.second]='v';
        }
    }
}

void ifbox::fillstr(std::vector<std::string>&strVec){
    fillCbox(strVec,pos.first,pos.first-2,pos.second+width/2,pos.second-width/2,cond);
    if_do->fillstr(strVec);
    if(else_do==nullptr){
        strVec[pos.first+1][pos.second]=strVec[pos.first+2][pos.second]='|';
        strVec[pos.first+1][pos.second+1]='Y';
        strVec[pos.first+3][pos.second]='v';
        strVec[if_do->endpos.first+1][pos.second]='|';
        strVec[if_do->endpos.first+2][pos.second]='v';
        strVec[if_do->endpos.first+3][pos.second]='o'; 
        for(int i=pos.second-width/2-1;i!=pos.second-len_-1-width/2; --i){
            strVec[pos.first-1][i]='-';
            strVec[endpos.first][i]='-';
        }
        strVec[pos.first-1][pos.second-len_-1-width/2]='+';
        strVec[endpos.first][pos.second-len_-1-width/2]='+';
        for(int i=pos.first; i!=endpos.first;++i){
            strVec[i][pos.second-len_-1-width/2]='|';
        }
        for(int i=pos.second-len_-width/2;i!=pos.second-1;++i){
            strVec[endpos.first][i]='-';
        }
        strVec[endpos.first][pos.second-1]='>';
    }
    else{
        strVec[pos.first-2][pos.second+width/2+1]='Y';
        else_do->fillstr(strVec);
        strVec[pos.first][pos.second-width/2-len_-1]=strVec[pos.first][pos.second+width/2+len_+1]='|';
        strVec[pos.first+1][pos.second-width/2-len_-1]=strVec[pos.first+1][pos.second+width/2+len_+1]='|';
        strVec[pos.first+2][pos.second-width/2-len_-1]=strVec[pos.first+2][pos.second+width/2+len_+1]='v';
        for(int i=pos.second+width/2+1;i!=pos.second+width/2+len_+1;++i){
            strVec[pos.first-1][i]=strVec[pos.first-1][2*pos.second-i]='-';
        }
        strVec[pos.first-1][pos.second+width/2+len_+1]=strVec[pos.first-1][pos.second-width/2-len_-1]='+';
        for(int i=else_do->endpos.second+1;i!=pos.second-1;++i){
            strVec[endpos.first][i]=strVec[endpos.first][2*pos.second-i]= '-';
        }
        for(int i=else_do->endpos.first+1;i!=endpos.first;++i){
            strVec[i][else_do->endpos.second]='|';
        }
        for(int i=if_do->endpos.first+1;i!=endpos.first;++i){
            strVec[i][if_do->endpos.second]='|';
        }
        strVec[endpos.first][else_do->endpos.second]=strVec[endpos.first][if_do->endpos.second]='+';
        strVec[endpos.first][pos.second-1]='>';
        strVec[endpos.first][pos.second+1]='<';
        strVec[endpos.first][pos.second]='o';
    }
}
void whilebox::fillstr(std::vector<std::string>&strVec){
    fillCbox(strVec,pos.first,pos.first-2,pos.second+width/2,pos.second-width/2,cond);
    strVec[pos.first+1][pos.second]=strVec[pos.first+2][pos.second]='|';
    strVec[pos.first+1][pos.second+1]='Y';
    strVec[pos.first+3][pos.second]='v';
    loop_do->fillstr(strVec);
    strVec[loop_do->endpos.first+1][pos.second]='|';
    strVec[loop_do->endpos.first+2][pos.second]='v';
    strVec[loop_do->endpos.first+3][pos.second]='o';
    for(int i=pos.second-width/2-len_l;i!=pos.second-width/2;++i){
        strVec[pos.first-1][i]='-';
    }
    strVec[pos.first-1][pos.second-width/2-1-len_l]='+';
    for(int i=pos.first;i!=endpos.first;++i){
        strVec[i][pos.second-width/2-1-len_l]='|';
    }
    strVec[endpos.first][pos.second-width/2-1-len_l]='+';
    for(int i=pos.second-width/2-len_l;i!=pos.second;++i){
        strVec[endpos.first][i]='-';
    }
    strVec[endpos.first][pos.second]='+';
    strVec[pos.first-1][pos.second+width/2+1]='<';
    for(int i=pos.second+width/2+2;i!=pos.second+width/2+1+len_r;++i){
        strVec[pos.first-1][i]='-';
    }
    strVec[pos.first-1][pos.second+width/2+1+len_r]='+';
    for(int i=pos.first;i!=loop_do->endpos.first+3;++i){
        strVec[i][pos.second+width/2+1+len_r]='|';
    }
    strVec[loop_do->endpos.first+3][pos.second+width/2+1+len_r]='+';
    strVec[loop_do->endpos.first+3][pos.second+1]='>';
    for(int i=pos.second+2;i!=pos.second+width/2+len_r+1;++i){
        strVec[loop_do->endpos.first+3][i]='-';
    }
}
void simplebox::fillstr(std::vector<std::string>&strVec){
    fillSbox(strVec,pos.first,pos.first-2,pos.second+width/2,pos.second-width/2,text);
}






        }//namespace fb;
    }//namespace fc

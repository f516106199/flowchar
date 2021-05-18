#pragma once
#ifndef _TOKEN_HPP_
#define _TOKEN_Hpp_

#include<string>
#include<utility>
#include<set>
namespace fc{
    namespace ft{
        class token{
            public:
            enum class Kind:int{
                BEGIN,
                STM,
                LBRACE,
                RBRACE,
                IF,
                COND,
                WHILE,
                END,
                SEM,
                ELSE,
            }kind;
            std::pair<int,int>pos;
            
            static const char space;
            static const char lbrace ;
            static const char rbrace;
            static const char lparen;
            static const char rparen;
            static const char semicolon;
            static const std::string ifToken;
            static const std::string whileToken;
            static const std::string elseToken;

            static const std::set<char>blank;
            token(Kind kind):kind(kind){}
            token(Kind kind ,std::pair<int,int>pos):kind(kind),pos(pos){}

        };
        class StmToken:public token{
            public:
                std::string text;
            StmToken(std::pair<int,int>pos,std::string text):token(Kind::STM,pos),text(text){}
        };
        class CondToken:public token{
            public:
                std::string text;
                CondToken(std::pair<int,int>pos,std::string text):token(Kind::COND,pos),text(text){}
        };
        class IfToken:public token{
            public:
                IfToken(std::pair<int,int>pos):token(Kind::IF,pos){}
        };
        class ElseToken:public token{
            public:
                ElseToken(std::pair<int,int>pos):token(Kind::ELSE,pos){}
        };
        class RbraceToken:public token{
            public:
                RbraceToken(std::pair<int,int>pos):token(Kind::RBRACE,pos){}
        };
        class LbraceToken:public token{
            public:
                LbraceToken(std::pair<int,int>pos):token(Kind::LBRACE,pos){}
        };
        class WhileToken:public token{
            public:
                WhileToken(std::pair<int,int>pos):token(Kind::WHILE,pos){}
        };
        class BeginToken:public token{
            public:
                BeginToken(std::pair<int,int>pos):token(Kind::BEGIN,pos){}
        };
        class EndToken:public token{
            public:
                EndToken(std::pair<int,int>pos):token(Kind::END,pos){}
        };
    }   //namespace ft
}//namespace fc




#endif
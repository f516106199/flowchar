#include"../include/token.hpp"
    namespace fc{
        namespace ft{

const char token::space=' ';
const char token::lbrace='{';
const char token::rbrace='}';
const char token::lparen='(';
const char token::rparen=')';
const char token::semicolon=';';
const std::string token::ifToken="if";
const std::string token::elseToken="else";
const std::string token::whileToken="while";
const std::set<char> token::blank={' ','\t','\n'};

 
        }//namespace ft
    }//namespace fc
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstdlib>
#include "tokenizer.h"

tokenizer::tokenizer(string inputFile) {
//    this->file = ifstream(inputFile);
    file.open(inputFile);
    this->lineNum = 0;
    this->offset = 0;
}

int tokenizer::getLineNum() {
    return lineNum;
}

int tokenizer::getOffset() {
    return offset;
}
void tokenizer::close() {
    this->file.close();
}
bool tokenizer::nextWord() {
    //cout<<("lineLength"+line.length())<<endl;
    if (offset >= line.length()) {
        if (getline(file, line)) {
            //cout<<line<<" lineLength: "<<line.length()<<endl;
            lineNum++;
            offset = 0;
        } else {
            return false;
        }
    }
    for (; offset < line.length(); offset++) {
        char cur = line.at(offset);
        if (cur != '\t' && cur != ' ') {
            break;
        }
    }
    //cout<<"index: "<<offset<<endl;
    return true;
}

tokenizer::Token tokenizer::getToken() {
    int start = 0;
    if (nextWord()) {
        start = offset;
        while (offset < line.length()) {
            if (line.at(offset) == ' ' || line.at(offset) == '\t') {
                break;
            }
            offset++;
        }
        //cout<<"start: "<<start<<" end: "<<offset<<" str："<<line.substr(start, offset - start)<<endl;
        Token token(line.substr(start, offset - start), lineNum, start);
        return token;
    }
    Token token("", lineNum, start);
    return token;
}
//1 xy 2

int tokenizer::getTokenInt()
{
    return std::stoi(getToken().tokenName);
}

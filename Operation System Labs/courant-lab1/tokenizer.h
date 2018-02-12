#ifndef OSLAB1_TOKENIZER_H
#define OSLAB1_TOKENIZER_H

#include <iostream>
#include <string.h>
using namespace std;

class tokenizer {
public:
    struct Token {
        string tokenName;
        size_t line, offset;
        Token(string tokenName, size_t line, size_t offset)
        :tokenName(tokenName), line(line), offset(offset) {}
    };

    Token getToken();
    int getTokenInt();
    int getLineNum();
    int getOffset();
    bool nextWord();
    tokenizer(string file);
    void close();
protected:
    ifstream file;
    size_t lineNum, offset;
    string line;
};

#endif //OSLAB1_TOKENIZER_H

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <iomanip>
#include <set>
#include "tokenizer.h"

using namespace std;

//------------------------Constants---------------------

const int MACHINE_SIZE = 200;

//------------------------Global---------------------

map<string, int> symbolTable;
map<string, int> symbolToModule;
map<string, bool> usedSymbol;
set<string> useListUsed;
map<int, int> baseTable;
map<string, bool> multiDefined;
vector<int> moduleSize;
vector<string> useList;
vector<string> warningList;
vector<string> errorList;

//----------------------------------

bool isDefined(const string& token) {
    return symbolTable.find(token) != symbolTable.end();
}

void printWarnningMessage() {
    cout<<endl;
    for (vector<string>::iterator iter = warningList.begin(); iter != warningList.end(); ++iter) {
        cout<<*iter<<endl;
        cout<<endl;
    }
    for(map<string, int>::iterator iter = symbolTable.begin(); iter != symbolTable.end(); ++iter) {
        if(!usedSymbol[iter->first]) {
            cout<<"Warning: "<<iter->first<<" was defined in module "<<symbolToModule[iter->first]<<" but never used."<<endl;
            cout<<endl;
        }
    }
}

void printErrorMessage() {
    for (vector<string>::iterator iter = errorList.begin(); iter != errorList.end(); ++iter) {
        cout<<*iter<<endl;
        cout<<endl;
    }
}

void printSymbolTable(){
    cout << "Symbol Table" << std::endl;
    for(map<string, int>::iterator iter = symbolTable.begin(); iter != symbolTable.end(); ++iter) {
        int module = symbolToModule[iter->first];
        if (iter->second > moduleSize[module]) {
            iter->second = baseTable[module];
            string warning = "Error: In module " + to_string(module) + " the def of "+ iter->first + " exceeds the module size; zero (relative) used.";
            errorList.push_back(warning);
        } else {
            iter->second += baseTable[module];
        }
        cout<<iter->first<<"="<<iter->second;
        if (multiDefined[iter->first]) {
            cout<<"    Error: This variable is multiply defined; first value used."<<endl;
        } else {
            cout<<endl;
        }
    }
}

void printAdrress(const string& type, const int& addr, const int& cnt, const int& moduleNum) {
    const char* addrtype = type.c_str();
    const int address = addr;
    int baseAddr = baseTable[moduleNum];
    int opcode = address / 1000;
    int relative = address % 1000;
    int absolute;
    string error="";
    switch (addrtype[0]) {
        case 'I':
            absolute = address;
            cout<<cnt<<":     I "<<address<<setw(10)<<absolute;
            break;
        case 'A':
            if (relative >= MACHINE_SIZE) {
                error = "Error: Absolute address exceeds machine size; zero used";
                absolute = opcode * 1000;
                cout<<cnt<<":     A "<<address<<setw(10)<<absolute;
            } else {
                absolute = address;
                cout << cnt << ":     A " << address << setw(10) << absolute;
            }
            break;
        case 'R':
            if (relative >= moduleSize[moduleNum]) {
                error = "Error: Relative address exceeds module size; zero used";
                absolute = opcode * 1000;
                cout<<cnt<<":     R "<<address<<setw(10)<<absolute;
            } else {
                absolute = address + baseAddr;
                cout<<cnt<<":     R "<<address<<setw(10)<<address<<"+"<<baseAddr<<" = "<<absolute;
            }
            break;
        case 'E':
            string symbolUsed = useList[relative];
            if (relative >= useList.size()) {
                error = "Error: External address exceeds length of uselist; treated as immediate";
                absolute = address;
                cout<<cnt<<":     I "<<address<<setw(10)<<absolute;
            }else if (!isDefined(symbolUsed)) {
                useListUsed.insert(symbolUsed);
                error = "Error: " + symbolUsed + " is not defined; zero used.";
                absolute = opcode * 1000;
                cout<<cnt<<":     E "<<address<<setw(10)<<absolute;
            } else {
                usedSymbol[symbolUsed] = true;
                useListUsed.insert(symbolUsed);
                auto symbolAdd = symbolTable.find(symbolUsed);
                absolute = opcode * 1000 + symbolAdd->second;
                cout<<cnt<<":     E "<<address<<setw(10)<<address<<"+"<<symbolAdd->second<<" = "<<absolute;
            }
            break;
    }
    if (error.length() > 0) {
        cout<<"    "<<error<<endl;
    } else {
        cout<<endl;
    }
}

void passOne(const string& file){
    tokenizer* parser = new tokenizer(file);
    int moduleNum = 0;
    while(parser->nextWord()) {
        //get DefList
        int defNum = parser->getTokenInt();
        for (int i = 0; i < defNum; i++ ) {
            if (parser->nextWord()) {
                tokenizer::Token symbol = parser->getToken();
                int add = parser->getTokenInt();
                if (isDefined(symbol.tokenName)) {
                    multiDefined[symbol.tokenName] = true;
                } else {
                    symbolTable[symbol.tokenName] = add;
                    symbolToModule[symbol.tokenName] = moduleNum;
                    multiDefined[symbol.tokenName] = false;
                }
            }
        }
        //get UsedList
        int usedNum = parser->getTokenInt();
        for (int i = 0; i < usedNum; i++) {
            if (parser->nextWord()) {
                parser->getToken();
            }
        }
        //get Instructions
        int instrNum = parser->getTokenInt();
        moduleSize.push_back(instrNum);
        for (int i = 0; i < instrNum; i++) {
            if (parser->nextWord()) {
                parser->getToken();
                parser->getToken();
            }
        }
        baseTable[moduleNum + 1] = baseTable[moduleNum] + instrNum;
        moduleNum++;
    }
    parser->close();
}


void passTwo(const string& file) {
    tokenizer* parser2 = new tokenizer(file);
    int moduleNum = 0;
    while(parser2->nextWord()) {
        cout<<"+"<<baseTable[moduleNum]<<endl;
        useList.clear();
        useListUsed.clear();
        //get DefList
        int defNum = parser2->getTokenInt();
        for (int i = 0; i < defNum; i++ ) {
            if (parser2->nextWord()) {
                parser2->getToken();
                parser2->getToken();
            }
        }
        //get UsedList
        int usedNum = parser2->getTokenInt();
        for (int i = 0; i < usedNum; i++) {
            if (parser2->nextWord()) {
                string symbol = parser2->getToken().tokenName;
                useList.push_back(symbol);
            }
        }
        //get Instructions
        int instrNum = parser2->getTokenInt();
        for (int i = 0; i < instrNum; i++) {
            if (parser2->nextWord()) {
                tokenizer::Token type = parser2->getToken();
                int addr = parser2->getTokenInt();
                printAdrress(type.tokenName, addr, i, moduleNum);
            }
        }
        //save unused symbols
        for (vector<string>::iterator iter = useList.begin(); iter != useList.end(); ++iter) {
            if (useListUsed.find(*iter) == useListUsed.end()) {
                    string warning = "Warning: In module " + to_string(moduleNum) + " "+ *iter +" appeared in the use list but was not actually used.";
                    warningList.push_back(warning);
            }
        }
        moduleNum++;
    }
    parser2->close();
}


int main(int argc, char* argv[]) {
    //string fileName(argv[1]);
    string fileName = "data.txt";
    passOne(fileName);
    printSymbolTable();
    passTwo(fileName);
    printWarnningMessage();
    printErrorMessage();
    return 0;
}

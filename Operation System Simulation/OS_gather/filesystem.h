#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <io.h>
#include <direct.h>
#include <time.h>
#include <sstream>
#include <QStringList>

using namespace std;

const int TotalBlockCnt = 64;	//块数
const int BlockSize = 1024;		//块大小
const int MaxCharLen = 200;		//输入缓冲区的最大长度
const int MaxIndexLen = 1000;	//文件索引条数的上限
const int DiskCnt = 2;			//分区数
const int MaxLevelCnt = 30;	//系统最大层级

//文件权限
typedef enum
{
    readOnly,   //只读
    writable    //可写
}FileAccess;

//文件属性
typedef enum
{
    file,   //文件
    dir   //目录
}FileType;

//文件状态
typedef enum
{
    closed,
    opened,
    writing
}FileState;

//文件控制块FCB
typedef struct fse
{
    int flevel;			//文件所在的层次，层+文件元素名为一个文件的逻辑位置
    string fname;		//文件名
    vector<int> blockId;//文件所在的物理块编号
    int flen;			//文件长度
    FileType ftype;		//文件类型
    FileAccess facc;	//文件权限
    int feffect;		//表征文件是否被删除，0表示无效文件，1表示有效
    char createTime[20];	//创建时间
    char lastModTime[20];	//最后一次修改时间
    FileState fstate;		//文件当前状态
}FCB;

//文件索引元素的结构
typedef struct
{
    int id;				//索引序号
    string fileName;	//文件名
    int parentId;		//父母节点索引序号
    vector<int> child;	//子节点索引序号
    int effect;			//文件有效性 1表示存在 0表示已被删除
    int fileType;		//文件属性
    int tmpFileId;		//文件打开时 创建的临时文件的编号
    FCB* fcb;			//指向自身的FCB
} FileIndexElement;

//文件索引的结构
typedef struct
{
    FileIndexElement index[MaxIndexLen];	//索引数组
    int indexCnt;							//现有的索引数量
} FileIndex;

//文件系统
class FileSystem
{
private:
    FileIndex fileIndex;
    int curIndex;	//当前目录
    unsigned char bitmap[(TotalBlockCnt + 7) / 8]; //1表示空闲 0表示被占用
    int tmpFileCnt;

private:
    int updateBitmap(int mode, int blockId);
    int findBlankBlockId();
    string getPath(int index);
    int getFileLevel(int index);
    void setCurDirReadOnly();
    QString rm(int dirIndex);
    QString recursiveRm(int dirIndex);
    int getFileIndex(string path);
    int load();
    bool fileNameIsLegal(string fileName);
    int openFile(string path);
    int writeFile(string path);

    int closeFile(string path);
    //TODO：在实验报告中解释为什么需要boost	done
    //		要点：boost块长度固定、系统需要先加载基本信息、基本信息存储于文件中、所以需要先由引导块建立基本信息存储文件的FCB
    int boost();
    void printTree(int id, int flag[MaxLevelCnt], int level);
public:
    FileSystem();
    QString createFile(FileAccess acc, string filename, FileType type, int filesize);
    QString createFileWithPath(FileAccess acc, string filename, FileType type, int filesize, string path);
    int addIndex(string fileName, FileType type, FCB* fcb);
    string getCurPath();
    QString op_cd(string &logPath, QStringList input);
    int op_dir(string &logPath);
    QString op_mk(string &logPath, QStringList input, FileType type);
    //int op_mkfile(string &logPath, QStringList input);
    QString op_rmdir(string &logPath, QStringList input);
    QString op_delfile(string &logPath, QStringList input);
    int op_tree(string &logPath);
    /*int op_open();
    int op_close();
    int op_write();*/
    int save();
    QString op_showBlock();
    QString op_rename(string &logPath, QStringList input);
    QString op_alterAttrib(string &logPath, QStringList input);
    QString op_openFile(string &logPath, QStringList input);
    int log(string mode, string logPath);

    //获取文件索引
    FileIndex getfileindex();
    int updataFile(string path, vector<string> block);
    //与内存管理的接口
    FCB* getFileFCB(string path);	//返回一个指向FCB的指针，在内存管理的任何对FCB的修改都直接体现到文件系统中
    string getBlockContent(int blockId);
};

vector<string> split(string str, string pattern);
bool stringAreEqual(string a, string b);
void init();
void getCurTime(char* currtime);

#endif


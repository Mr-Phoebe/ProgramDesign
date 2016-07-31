#include"memory.h"
#include <QDebug>
#include"filewindow.h"

QString m_buffer;
QString get_op="";
PCB submit;
string split_content(string content, int a, int b, string &t);
HANDLE allo, trac;
string file_path;
void rand_pcb();
extern FileSystem *fs;
extern Notepad *np;
extern fileWindow *f;
extern MemorySystem ms;
string content = "";           //用于计算需要追加或减少的页数
int file_p[17];
string t = "";
string new_t = "";
int mblocks = 0;
int Allocator(PCB submit,int ok)
{
    if(1==ok)
    {
        int pid = 0;
        FCB *fcb=NULL;

        if (submit.getState() == ready)
        {
            if(ms.check_in(submit,ms)==-1)
            {
                if(ms.get_into_page(submit, ms)!=-1)
                {
                m_buffer += get_op;
                get_op = "";
                qDebug() << m_buffer << endl;
                }
            }

        }
        else if (submit.getState() == running)
        {
            int end = 0;
            pid = submit.getPID();
            ms.check_in(submit, ms);
            switch (submit.getOperation())
            {
                case 4:         //save                              //修改文件,先得到文件在内存中的位置数列，按照位
                                                          //置数列的先后顺序，将内容重新填入内存中，当发现
                                                //后来的页数多于原来的页数，那么就更新后，删除多余页
                                                //后来的页数少于原来的页数，那么更新后，再添加几页
                                                //相等，只需要更新所有的页数即可
                                                    //现在还需要一个用于将现有的content拆分开的方法，将其按照1024个
                                                      //一组的方法进行分割。这样才能将页面放入内存

                for (int i = 1; i <= mblocks; i++)
                {
                    file_p[i] = ms.find_file(i, ms, file_path);
                    qDebug()<<file_p[i];
                }
                new_t = np->getFileContent().toStdString();
                if(content.size()==0)
                {
                    qDebug()<<"nothing!............................";
                    if(new_t.size()!=0)
                    {
                        if(new_t.size()<1025)
                        {
                            for (unsigned int i = 1; i <= (new_t.size()+1023)/1024; i++)
                            {
                                if (new_t.size() < i * 1024)
                                    end = new_t.size();
                                else
                                    end = i * 1024;

                                ms.update_filepage(split_content(new_t,(i-1)*1024,end,t),ms,file_p[i]);
                            }
                        }
                        else
                        {
                            for (unsigned int i = 1; i <= mblocks; i++)
                            {
                                if (new_t.size() < i * 1024)
                                    end = new_t.size();
                                else
                                    end = i * 1024;

                                ms.update_filepage(split_content(new_t,(i-1)*1024,end,t),ms,file_p[i]);
                            }
                            for (unsigned int i = mblocks+1; i <=(new_t.size()+1023)/1024; i++)
                            {
                                if (new_t.size() < i * 1024)
                                    end = new_t.size();
                                else
                                {
                                    end = i * 1024;
                                }
                                file_p[i] =ms.file_into_page(ms, file_path, i, split_content(new_t, (i - 1) * 1024, end, t), pid) ;
                            }
                        }
                    }


                    for(int i=1;i<=16;i++)
                        qDebug()<<file_p[i];
                }
                else
                {
                    if (content.size()> new_t.size())                //页面减少
                    {

                        for (unsigned int i = 1; i <=(new_t.size()+1023)/1024; i++)
                        {
                            if (new_t.size() < i * 1024)
                                end = new_t.size();
                            else
                            {
                                end = i * 1024;
                            }
                            ms.update_filepage(split_content(new_t,(i-1)*1024,end,t),ms,file_p[i]);
                        }
                        for (unsigned int i = (new_t.size()+1023)/1024 + 1; i <=(content.size() + 1023) / 1024; i++)
                        {
                            ms.update_filepage("", ms, file_p[i]);
                            file_p[i] = -1;

                        }
                    }
                    else if (content.size()< new_t.size())
                    {
                        qDebug()<<"1111111111111111111111111111111111";
                        for (unsigned int i = 1; i <=(unsigned)mblocks; i++)
                        {
                            if (new_t.size() < i * 1024)
                                end = new_t.size();
                            else
                                end=i*1024;
                            ms.update_filepage(split_content(new_t, (i - 1) * 1024, end, t), ms, file_p[i]);
                        }
                        for (unsigned int i = mblocks+1; i <=(new_t.size()+1023)/1024; i++)
                        {
                            if (new_t.size() < i * 1024)
                                end = new_t.size();
                            else
                            {
                                end = i * 1024;
                            }
                            file_p[i] = ms.file_into_page(ms, file_path, i, split_content(new_t, (i - 1) * 1024, end, t), pid);

                        }
                    }
                    else
                    {
                        for (int i = 1; i < mblocks; i++)
                        {
                            if (new_t.size() <(unsigned)(i * 1024))
                                end = new_t.size();
                            else
                                end = i * 1024;
                            ms.set_string(split_content(new_t,i*1024,end,t),file_p[i],ms);
                        }
                    }
                    m_buffer += get_op;
                    get_op = "";
                    qDebug() << m_buffer<<endl;

                }
                if (content.compare(new_t)!=0 && new_t.size()!=0)
                {
                    for(int i=1;i<16;i++)
                        qDebug()<<file_p[i];
                    ms.log("文件内容被修改，需要进行保存到磁盘",ms);
                    vector < string > a;
                    for(int i=1;i<=16;i++){
                        if(file_p[i]!=-1)
                            a.push_back(ms.get_string()[file_p[i]]);
                    }
                    fs->updataFile(file_path,a);

                ////////////////////////////////////////
                }
                else if(content.size()!=0&&new_t.size()==0)
                {
                     vector < string > a;
                     fs->updataFile(file_path,a);
                }
                else
                {
                    ms.log("文件内容未修改，不需要保存到磁盘", ms);
                }
                content=new_t;
                break;
            default:
                m_buffer += get_op;
                get_op = "";
                 qDebug()  << m_buffer << endl;
                break;
            }

        }
        else if (submit.getState() == waiting)
        {

        }
        else
        {
            int end=0;

            if(submit.getOperation()==2)
            {
                content="";
                for(int i=1;i<=16;i++){
                    file_p[i]=-1;
                }
                file_path=f->getFilePathFromUI().toStdString();
                fcb = fs->getFileFCB(file_path);
                if(fcb!=NULL)
                {
                    mblocks = fcb->blockId.size();
                    for (int j = 0; j < mblocks; j++)
                        content += fs->getBlockContent(fcb->blockId[j]);
                    if(mblocks==0)
                        content="";
                    if(mblocks==0)
                    {
                    if (ms.file_check(file_path, ms, 1) == -1)
                    {

                         file_p[1]=ms.file_into_page(ms, file_path, 1,"",pid);                   //*****************需要将内容划分一下
                    }

                    }
                    else
                    {
                        for (unsigned int j = 1; j <= (unsigned)mblocks; j++)
                        {
                            if (ms.file_check(file_path, ms, j) == -1)
                            {
                                if (content.size() < j * 1024)
                                    end = content.size() ;
                                else
                                {
                                    end = j * 1024;
                                }
                                file_p[j]=ms.file_into_page(ms, file_path, j,split_content(content,(j-1)*1024,end,t),pid);                   //*****************需要将内容划分一下
                            }
                        }
                    }
                }
                else
                {
                  ms.log("文件路径错误",ms);
                }
                m_buffer += get_op;
                get_op = "";
            }
            else if(submit.getOperation()==5)               //save
            {
                ms.remove_file(file_path,ms);
                for(int i=1;i<=16;i++)
                    file_p[i]=-1;
            }
            m_buffer += get_op;
            get_op = "";
            ms.remove(submit.getPID(), ms);
            m_buffer += get_op;
            get_op = "";

        }
    }
    if(ok!=1)
    {
    }
    ok=0;
    return 0;
}
DWORD Tracker(LPDWORD lpdwparm)
{
    ofstream fout;
    fout.open("memory.txt", ios_base::out | ios_base::app);
    if (fout.is_open())
    {
        fout << ms.get_time()<<endl;
        for(int i=0;i<PAGE_NUM;i++)
        {
             fout << endl << "************************************************************************************" << endl;
             if (ms.get_tra_m()[i].valid == 0)
             {
                 if (ms.get_tra_m()[i].type == 0)
                 {
                     fout << i << "th Page:" << endl;
                     fout << "\t" << "PID:" << ms.get_tra_m()[i].PID << endl;
                     fout << "\t" << "Logical Address: " << ms.get_tra_m()[i].process_logicalad << endl;
                     fout << "\t" << "page age:" << ms.get_tra_m()[i].age << endl;
                 }
                 else
                 {
                     fout << i << "th Page:" << endl;
                     fout << "\t" << "FilePATH:" << ms.get_tra_m()[i].file_path << endl;
                     fout << "\t" << "Logical Address: " << ms.get_tra_m()[i].file_logicalad << endl;
                     fout << "\t" << "File content:" << ms.get_string()[i]<<endl;
                     fout << "\t" << "page age:" << ms.get_tra_m()[i].age << endl;
                 }
             }
             else
             {
                 fout << i << "th Page is free:" << endl;
             }
           }
    }
    fout.close();
    fout.open("virtual memory.txt", ios_base::out | ios_base::app);

    if (fout.is_open())
    {
         fout << ms.get_time()<<endl;
        for (int i = 0; i < 16; i++)
        {
            fout << endl << "************************************************************************************" << endl;
            if (ms.get_tra_vm()[i].valid == 0)
            {
                if (ms.get_tra_vm()[i].type == 0)
                {
                    fout << i << "th Page:" << endl;
                    fout << "\t" << "PID:" << ms.get_tra_vm()[i].PID << endl;
                    fout << "\t" << "Logical Address: " << ms.get_tra_vm()[i].process_logicalad << endl;
                }
                else
                {
                    fout << i << "th Page:" << endl;
                    fout << "\t" << "FilePATH:" << ms.get_tra_vm()[i].file_path << endl;
                    fout << "\t" << "Logical Address: " << ms.get_tra_vm()[i].file_logicalad << endl;
                    fout << "\t" << "File content:" << ms.get_string()[i] << endl;
                }
            }
            else
            {
                fout << i << "th Page is free:" << endl;
            }
        }

    }
    fout.close();
    return 0;
}

string split_content(string content,int a,int b,string &t)
{

    t = "";
    for (int i = a; i <b; i++)
    {
        t += content[i];
    }
    return t;
}

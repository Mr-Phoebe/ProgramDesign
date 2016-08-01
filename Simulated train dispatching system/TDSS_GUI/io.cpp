#include "io.h"

void loadFromConfig()
{
    FILE* fin = fopen("track.config", "r");

    fscanf(fin,
           "trackNum = %d",
           &trackNum);

    for (int i(0); i < trackNum; ++i)
    {
        fscanf(fin,
               "%*[\n]"
               "track[%*d]:"
               "    length = %lf"
               "    width = %lf",
               &tracks[i].length,
               &tracks[i].width);

        tracks[i].peremeter = (tracks[i].length + tracks[i].width) * 2.;
    }

    for (int i(0); i < trackNum; ++i)
    {
        publicTracks[i][i].exist = 0;

        for (int j(0); j < trackNum; ++j)
            if (i != j)
            {
                fscanf(fin,
                       "%*[\n]"
                       "publicTracks[%*d][%*d].inPoint = %lf"
                       "%*[\n]"
                       "publicTracks[%*d][%*d].outPoint = %lf",
                       &publicTracks[i][j].inPoint,
                       &publicTracks[i][j].outPoint);

                publicTracks[i][j].midPoint
                        = (publicTracks[i][j].inPoint + publicTracks[i][j].outPoint) / 2.;
                publicTracks[i][j].state = IDLE;
                publicTracks[i][j].exist = (publicTracks[i][j].inPoint >= 0);
            }
    }


    fclose(fin);

    fin = fopen("train.config", "r");

    if (!fin)
        puts("READ FILE ERROR\n");

    fscanf(fin,
           "trainNum = %d",
           &trainNum);

    for (int i(0); i < trainNum; ++i)
    {
        trains[i].id = i;
        fscanf(fin,
               "%*[\n]"
               "trains[%*d]:"
               "    type = %d"
               "    dir = %d"
               "    startTime = %d"
               "    startTrack = %d"
               "    startPos = %lf"
               "    speed = %lf",
               &trains[i].type,
               &trains[i].dir,
               &trains[i].startTime,
               &trains[i].startTrack,
               &trains[i].startPos,
               &trains[i].speed);

        for (int j(0); j < trackNum; ++j)
        {
            fscanf(fin,
                   "    pass[%*d] = %d",
                   &trains[i].pass[j]);
        }

        memset(trains[i].stayDur, 0, sizeof(trains[i].stayDur));

        for (int j(0); j < trackNum; ++j)
            if (trains[i].pass[j])
                for (int k(0); k < trackNum; ++k)
                    if (k != j)
                        fscanf(fin,
                               "    stayDur[%*d][%*d] = %d",
                               &trains[i].stayDur[j][k]);
    }

    fclose(fin);
}

void init()
{
    initDeque();

    for (int i(0); i < trainNum; ++i)
    {
        trains[i].startTime *= UNITS_PER_SEC;
        if (trains[i].startTime)
        {
            trains[i].started = 0;
            trains[i].curState = STOP;
        }
        else
        {
            trains[i].started = 1;
            trains[i].curState = RUN;
        }
        //trains[i].curState = RUN;
        trains[i].curTrack = trains[i].startTrack;
        trains[i].curSpeed = trains[i].speed;
        trains[i].curPos = trains[i].startPos;
        trains[i].restStayDur = -1;
        trains[i].inPublicTrack = 0;
        trains[i].moved = 0;
        trains[i].hasChangedTrack = 0;
        trains[i].waitForFrontTrain = 0;
    }

    for (int i(0); i < trackNum; ++i)
      for (int j(0); j < trackNum; ++j)
          if(publicTracks[i][j].exist)
              publicTracks[i][j].color = GREEN;
}

//void saveToConfig()
//{
//    FILE* fout = fopen("track.config", "w");

//    fprintf(fout,
//            "trackNum = %d\n\n",
//            trackNum);

//    for (int i(0); i < trackNum; ++i)
//        fprintf(fout,
//                "track[%d]:\n"
//                "    length = %f\n"
//                "    width = %f\n\n",
//                i,
//                tracks[i].length,
//                tracks[i].width);

//    for (int i(0); i < trackNum; ++i)
//        for (int j(0); j < trackNum; ++j)
//            if (i != j)
//                fprintf(fout,
//                        "publicTracks[%d][%d].inPoint = %f\n"
//                        "publicTracks[%d][%d].outPoint = %f\n",
//                        i, j, publicTracks[i][j].inPoint,
//                        i, j, publicTracks[i][j].outPoint);

//    fclose(fout);

//    fout = fopen("train.config", "w");

//    fprintf(fout,
//            "trainNum = %d\n\n",
//            trainNum);

//    for (int i(0); i < trainNum; ++i)
//    {
//        fprintf(fout,
//                "trains[%d]:\n"
//                "    type = %d\n"
//                "    dir = %d\n"
//                "    startTime = %d\n"
//                "    startTrack = %d\n"
//                "    startPos = %f\n"
//                "    speed = %f\n",
//                i,
//                trains[i].type,
//                trains[i].dir,
//                trains[i].startTime,
//                trains[i].startTrack,
//                trains[i].startPos,
//                trains[i].speed);

//        for (int j(0); j < trainNum; ++j)
//            fprintf(fout,
//                    "    pass[%d] = %d\n",
//                    j, trains[i].pass[j]);

//        for (int j(0); j < trackNum; ++j)
//            if (trains[i].pass[j])
//                for (int k(0); k < trackNum; ++k)
//                    if (k != j)
//                        fprintf(fout,
//                                "    stayDur[%d][%d] = %d\n",
//                                j, k, trains[i].stayDur[j][k]);
//        fputs("\n", fout);
//    }

//    fclose(fout);
//}

//char input[MAX_INPUT_LEN];
//char c;
//bool changed;
//bool wrong;

//inline bool isDigit(char c)
//{
//    return '0' <= c && c <= '9';
//}

//inline bool cross(int a, int b, int c, int d)
//{
//    if (a <= b)
//        return (c >= a && c <= b) || (d >= a && d <= b);
//    else
//        return (c >= a && c <= b) || (d >= a && d <= b);
//}

//void init()
//{
//    loadFromConfig();

//    //read user's initializations
//    printf("╔══════════════════════╗\n"
//           "║              模拟火车调度系统              ║\n"
//           "╚══════════════════════╝\n"
//           "欢迎使用该模拟系统！\n"
//           "\n"
//           "系统默认配置有4条轨道：\n"
//           "各轨道长均为60米，宽均为20米，\n"
//           "以其最左下顶点为坐标原点\n"
//           "\n"
//           "使用系统默认配置请按0\n"
//           "自定义轨道信息请输入1\n");

//    while (1)
//    {
//        fflush(stdin);
//        gets(input);

//        if (strlen(input) == 1)
//        {
//            if (input[0] == '0')
//                goto DEFAULT_TRACK;
//            if (input[0] == '1')
//                goto CONFIG_TRACK;
//        }
//        printf("\n"
//               "输入有误，请重新输入：\n"
//               "使用默认轨道配置请按0\n"
//               "自定义轨道信息请输入1\n");
//    }

//CONFIG_TRACK:
//    {
//        printf("\n"
//               "请输入以下各项轨道配置参数：\n");

//        puts("轨道数量（不超过100的正整数）：");

//        fflush(stdin);

//        int _trackNum = 0;
//        wrong = 0;

//        while (1)
//        {
//            fflush(stdin);

//            _trackNum = 0;
//            wrong = 0;
//            changed = 0;

//            while ((c = getchar()) != '\n')
//            {
//                changed = 1;
//                _trackNum *= 10;
//                _trackNum += (c - '0');

//                if (!isDigit(c))
//                    wrong = 1;
//            }

//            if (!changed || wrong || _trackNum >= 100)
//            {
//                printf("\n"
//                       "输入有误，请重新输入：\n");
//                puts("轨道数量（不超过100的整数）：");
//            }
//            else
//            {
//                trackNum = _trackNum;
//                break;
//            }
//        }

//        for (int i(0); i < trackNum; ++i)
//        {
//            printf("%d号轨道长度（正整数）：", i);

//            int _length = 0;
//            wrong = 0;
//            changed = 0;

//            while (1)
//            {
//                fflush(stdin);

//                _length = 0;
//                wrong = 0;
//                changed = 0;

//                while ((c = getchar()) != '\n')
//                {
//                    changed = 1;

//                    _length *= 10;
//                    _length += (c - '0');

//                    if (!isDigit(c))
//                        wrong = 1;
//                }

//                if (!changed || wrong)
//                {
//                    printf("\n"
//                           "输入有误，请重新输入：\n");
//                    printf("%d号轨道长度（正整数）：", i);
//                }
//                else
//                {
//                    tracks[i].length = (double)_length;
//                    break;
//                }
//            }

//            printf("%d号轨道宽度（正整数）：", i);

//            int _width = 0;
//            wrong = 0;
//            changed = 0;

//            while (1)
//            {
//                fflush(stdin);

//                _width = 0;
//                wrong = 0;
//                changed = 0;

//                while ((c = getchar()) != '\n')
//                {
//                    changed = 1;

//                    _width *= 10;
//                    _width += (c - '0');

//                    if (!isDigit(c))
//                        wrong = 1;
//                }

//                if (!changed || wrong)
//                {
//                    printf("\n"
//                           "输入有误，请重新输入：\n");
//                    printf("%d号轨道宽度（正整数）：", i);
//                }
//                else
//                {
//                    tracks[i].width = (double)_width;
//                    break;
//                }
//            }

//            //printf("%d %d\n", int(tracks[i].length), int(tracks[i].width));

//            tracks[i].peremeter = (tracks[i].width + tracks[i].length) * 2.;
//        }

//        for (int i(0); i < trackNum; ++i)
//        {
//            publicTracks[i][i].exist = 0;

//            for (int j(0); j < trackNum; ++j)
//                if (i != j)
//                {
//                    publicTracks[i][j].inPoint = -1;
//                    publicTracks[i][j].outPoint = -1;
//                }
//        }

//        for (int i(0); i < trackNum; ++i)
//        {
//            publicTracks[i][i].exist = 0;

//            for (int j(0); j < trackNum; ++j)
//                if (i != j)
//                {
//RE_ENTER:

//                    printf("请输入%d号轨道上与%d号轨道公共轨道的\n"
//                           "inPoint，outPoint位置（以%d号轨道左下顶点\n"
//                           "为原点，顺时针方向绕轨道至该点的距离）\n"
//                           "（输入0~%d的整数）\n"
//                           "（注意公共轨道间不能互相重叠）\n"
//                           "（若无公共轨道，请输入%d及%d）\n",
//                           i, j, i, (int)tracks[i].peremeter,
//                           (int)tracks[i].peremeter + 1, (int)tracks[i].peremeter + 1);

//                    printf("inPoint：");

//                    int _inPoint = 0.;
//                    wrong = 0;
//                    changed = 0;
//                    bool neg = 0;

//                    while (1)
//                    {
//                        fflush(stdin);

//                        _inPoint = 0;
//                        wrong = 0;
//                        changed = 0;

//                        while ((c = getchar()) != '\n')
//                        {
//                            changed = 1;

//                            _inPoint *= 10;
//                            _inPoint += (c - '0');

//                            if (!isDigit(c))
//                                wrong = 1;
//                        }

//                        if (!changed || wrong || _inPoint > (int)tracks[i].peremeter + 1)
//                        {
//                            printf("\n"
//                                   "输入有误，请重新输入：\n");
//                            printf("inPoint：");
//                        }
//                        else
//                        {
//                            publicTracks[i][j].inPoint = (double)_inPoint;
//                            break;
//                        }
//                    }

//                    printf("outPoint：");

//                    int _outPoint = 0;
//                    wrong = 0;
//                    changed = 0;

//                    while (1)
//                    {
//                        fflush(stdin);

//                        _outPoint = 0.;
//                        wrong = 0;
//                        changed = 0;

//                        while ((c = getchar()) != '\n')
//                        {
//                            changed = 1;

//                            _outPoint *= 10;
//                            _outPoint += (c - '0');

//                            if (!isDigit(c))
//                                wrong = 1;
//                        }

//                        if (!changed || wrong || _inPoint > (int)tracks[i].peremeter + 1)
//                        {
//                            printf("\n"
//                                   "输入有误，请重新输入：\n");
//                            printf("outPoint：");
//                        }
//                        else
//                        {
//                            publicTracks[i][j].outPoint = (double)_outPoint;
//                            break;
//                        }
//                    }

//                    if (_inPoint == (int)tracks[i].peremeter + 1
//                        || _outPoint == (int)tracks[i].peremeter + 1)
//                    {
//                        if (_inPoint == (int)tracks[i].peremeter + 1
//                            && _outPoint == (int)tracks[i].peremeter + 1)
//                        {
//                            publicTracks[i][j].inPoint = -1;
//                            publicTracks[i][j].outPoint = -1;
//                        }
//                        else
//                        {
//                            printf("\n"
//                                   "输入有误，请重新输入：\n");
//                            goto RE_ENTER;
//                        }
//                    }

//                    for (int k(0); k < j; ++k)
//                        if (k != i
//                            && cross(publicTracks[i][k].inPoint,
//                                     publicTracks[i][k].outPoint,
//                                     publicTracks[i][j].inPoint,
//                                     publicTracks[i][j].outPoint))
//                        {
//                            printf("输入公共轨道有重叠，请重新输入：\n");

//                            goto RE_ENTER;
//                        }
//                }
//        }

//        for (int i(0); i < trackNum; ++i)
//        {
//            publicTracks[i][i].exist = 0;

//            for (int j(0); j < trackNum; ++j)
//                if (i != j)
//                {
//                    if (publicTracks[i][j].inPoint < 0.)
//                        publicTracks[i][i].exist = 0;
//                    else
//                    {
//                        publicTracks[i][j].state = IDLE;
//                        publicTracks[i][j].midPoint
//                                = (publicTracks[i][j].inPoint + publicTracks[i][j].outPoint) / 2.;
//                    }
//                }
//        }

//        printf("\n"
//               "轨道配置完毕，\n");

//        goto DONE_TRACK;
//    }

//DEFAULT_TRACK:
//    {
//        printf("\n"
//               "您已使用系统默认轨道配置，\n");

//        goto DONE_TRACK;
//    }

//DONE_TRACK:

//    printf("系统默认有4辆火车A、B、C、D，\n"
//           "分别运行在0、1、2、3号轨道上，\n"
//           "各车从轨道原点开始均顺时针行驶，\n"
//           "其中A车与D车为慢车，初速2米/秒，\n"
//           "B车与C车为快车，初速4米/秒，\n"
//           "各车均在公共轨道停留2秒，\n"
//           "且各车只经过一个轨道\n");

//    printf("\n使用默认火车配置请按0\n"
//           "自定义火车信息请输入1\n");

//    while (1)
//    {
//        fflush(stdin);
//        gets(input);

//        if (strlen(input) == 1)
//        {
//            if (input[0] == '0')
//                goto DEFAULT_TRAIN;
//            if (input[0] == '1')
//                goto CONFIG_TRAIN;
//        }
//        printf("\n"
//               "输入有误，请重新输入：\n"
//               "使用默认火车配置请按0\n"
//               "自定义火车信息请输入1\n");
//    }

//CONFIG_TRAIN:
//    {
//        printf("\n"
//               "请输入以下各项火车配置参数：\n");

//        printf("请输入火车数量（0~26的整数）：\n");

//        int _trainNum = 0;

//        while (1)
//        {
//            fflush(stdin);

//            _trainNum = 0;
//            wrong = 0;
//            changed = 0;

//            while ((c = getchar()) != '\n')
//            {
//                changed = 1;

//                _trainNum *= 10;
//                _trainNum += (c - '0');

//                if (!isDigit(c))
//                    wrong = 1;
//            }

//            if (!changed || wrong || _trainNum > 26)
//            {
//                printf("\n"
//                       "输入有误，请重新输入：\n");
//                printf("请输入火车数量（0~26的整数）：\n");
//            }
//            else
//            {
//                trainNum = (double)_trainNum;
//                break;
//            }
//        }

//        for (int i(0); i < trainNum; ++i)
//        {
//            printf("请输入%c号火车信息：\n", 'A' + i);
//            printf("请选择火车类型：\n"
//                   "0：快车\n"
//                   "1：慢车\n");

//            while (1)
//            {
//                fflush(stdin);
//                gets(input);

//                if (strlen(input) == 1)
//                {
//                    if (input[0] == '0')
//                    {
//                        trains[i].type = FAST;
//                        break;
//                    }
//                    if (input[0] == '1')
//                    {
//                        trains[i].type = SLOW;
//                        break;
//                    }
//                }
//                printf("\n"
//                       "输入有误，请重新输入：\n"
//                       "请选择火车类型：\n"
//                       "0：快车\n"
//                       "1：慢车\n");
//            }

//            printf("请选择火车方向：\n"
//                   "0：顺时针\n"
//                   "1：逆时针\n");

//            while (1)
//            {
//                fflush(stdin);
//                gets(input);

//                if (strlen(input) == 1)
//                {
//                    if (input[0] == '0')
//                    {
//                        trains[i].dir = CLKWISE;
//                        break;
//                    }
//                    if (input[0] == '1')
//                    {
//                        trains[i].dir = CNTRCLKWISE;
//                        break;
//                    }
//                }
//                printf("\n"
//                       "输入有误，请重新输入：\n"
//                       "请选择火车方向：\n"
//                       "0：顺时针\n"
//                       "1：逆时针\n");
//            }

//            printf("火车初始所在轨道（0~%d的整数）：", trackNum - 1);

//            int _startTrack = 0;
//            wrong = 0;
//            changed = 0;

//            while (1)
//            {
//                fflush(stdin);

//                _startTrack = 0;
//                wrong = 0;
//                changed = 0;

//                while ((c = getchar()) != '\n')
//                {
//                    changed = 1;

//                    _startTrack *= 10;
//                    _startTrack += (c - '0');

//                    if (!isDigit(c))
//                        wrong = 1;
//                }

//                if (!changed || wrong || _startTrack >= trackNum)
//                {
//                    printf("\n"
//                           "输入有误，请重新输入：\n");
//                    printf("火车初始所在轨道（0~%d的整数）：", trackNum - 1);
//                }
//                else
//                {
//                    trains[i].startTrack = (double)_startTrack;
//                    break;
//                }
//            }

//            printf("火车启动位置（火车在%d号轨道上的坐标）（0~%d的整数）：",
//                   trains[i].startTrack, (int)tracks[trains[i].startTrack].peremeter);

//            int _startPos = 0;
//            wrong = 0;
//            changed = 0;

//            while (1)
//            {
//                fflush(stdin);

//                _startPos = 0;
//                wrong = 0;
//                changed = 0;

//                while ((c = getchar()) != '\n')
//                {
//                    changed = 1;

//                    _startPos *= 10;
//                    _startPos += (c - '0');

//                    if (!isDigit(c))
//                        wrong = 1;
//                }

//                if (!changed || wrong || _startPos > tracks[i].peremeter)
//                {
//                    printf("\n"
//                           "输入有误，请重新输入：\n");
//                    printf("火车启动位置（火车在%d号轨道上的坐标）（0~%d的整数）：",
//                           trains[i].startTrack, (int)tracks[trains[i].startTrack].peremeter);
//                }
//                else
//                {
//                    trains[i].startPos = (double)_startPos;
//                    break;
//                }
//            }

//            printf("火车启动时间（正整数）：");

//            int _startTime = 0;
//            wrong = 0;
//            changed = 0;

//            while (1)
//            {
//                fflush(stdin);

//                _startTime = 0;
//                wrong = 0;
//                changed = 0;

//                while ((c = getchar()) != '\n')
//                {
//                    changed = 1;

//                    _startTime *= 10;
//                    _startTime += (c - '0');

//                    if (!isDigit(c))
//                        wrong = 1;
//                }

//                if (!changed || wrong)
//                {
//                    printf("\n"
//                           "输入有误，请重新输入：\n");
//                    printf("火车启动时间（正整数）：");
//                }
//                else
//                {
//                    trains[i].startTime = (double)_startTime;
//                    break;
//                }
//            }

//            printf("火车运行速度（正整数）：");

//            int _speed = 0;
//            wrong = 0;
//            changed = 0;

//            while (1)
//            {
//                fflush(stdin);

//                _speed = 0;
//                wrong = 0;
//                changed = 0;

//                while ((c = getchar()) != '\n')
//                {
//                    changed = 1;

//                    _speed *= 10;
//                    _speed += (c - '0');

//                    if (!isDigit(c))
//                        wrong = 1;
//                }

//                if (!changed || wrong)
//                {
//                    printf("\n"
//                           "输入有误，请重新输入：\n");
//                    printf("火车运行速度（正整数）：");
//                }
//                else
//                {
//                    trains[i].speed = (double)_speed;
//                    break;
//                }
//            }

//            trains[i].pass[trains[i].startTrack] = 1;

//            for (int j(0); j < trackNum; ++j)
//            {
//                if (publicTracks[i][j].exist
//                    && j != trains[i].startTrack)
//                {
//                    printf("请问火车%c是否经过%d号轨道？\n"
//                           "0：否\n"
//                           "1：是\n",
//                           'A' + i, j);

//                    while (1)
//                    {
//                        fflush(stdin);
//                        gets(input);

//                        if (strlen(input) == 1)
//                        {
//                            if (input[0] == '0')
//                            {
//                                trains[i].pass[j] = 0;
//                                break;
//                            }
//                            if (input[0] == '1')
//                            {
//                                trains[i].pass[j] = 1;
//                                break;
//                            }
//                        }
//                        printf("\n"
//                               "输入有误，请重新输入：\n"
//                               "请问火车%c是否经过%d号轨道？\n"
//                               "0：否\n"
//                               "1：是\n",
//                               'A' + i, j);
//                    }
//                }
//            }

//            for (int j(0); j < trackNum; ++j)
//                if (trains[i].pass[j])
//                    for (int k(0); k < trackNum; ++k)
//                        if (publicTracks[j][k].exist)
//                        {
//                            printf("请输入火车%c在公共轨道%d- %d上的停留时间（正整数）：",
//                                   'A' + i, j, k);

//                            int _stayDur = 0;
//                            wrong = 0;
//                            changed = 0;

//                            while (1)
//                            {
//                                fflush(stdin);

//                                _stayDur = 0;
//                                wrong = 0;
//                                changed = 0;

//                                while ((c = getchar()) != '\n')
//                                {
//                                    changed = 1;

//                                    _stayDur *= 10;
//                                    _stayDur += (c - '0');

//                                    if (!isDigit(c))
//                                        wrong = 1;
//                                }

//                                if (!changed || wrong)
//                                {
//                                    printf("\n"
//                                           "输入有误，请重新输入：\n");
//                                    printf("请输入火车%c在公共轨道%d- %d上的停留时间（正整数）：",
//                                           'A' + i, j, k);
//                                }
//                                else
//                                {
//                                    trains[i].stayDur[j][k] = (double)_stayDur;
//                                    break;
//                                }
//                            }
//                        }
//        }


//        printf("\n"
//               "火车配置完毕，\n");

//    }

//DEFAULT_TRAIN:
//    {
//        printf("\n"
//               "您已使用系统默认火车配置，\n");

//        goto DONE_TRAIN;
//    }

//DONE_TRAIN:

//    printf("\n"
//           "初始化完毕，请问是否将该自定义配置保存为系统默认配置？\n"
//           "否：0\n"
//           "是：1\n");

//    while (1)
//    {
//        fflush(stdin);
//        gets(input);

//        if (strlen(input) == 1)
//        {
//            if (input[0] == '0')
//                break;
//            if (input[0] == '1')
//            {
//                saveToConfig();
//                break;
//            }
//        }
//        printf("\n"
//               "输入有误，请重新输入：\n"
//               "请问是否将该自定义配置保存为系统默认配置？\n"
//               "否：0\n"
//               "是：1\n");
//    }




//    initDeque();

//    for (int i(0); i < trainNum; ++i)
//    {
//        trains[i].startTime *= UNITS_PER_SEC;
//        if (trains[i].startTime)
//        {
//            trains[i].started = 0;
//            trains[i].curState = STOP;
//        }
//        else
//        {
//            trains[i].started = 1;
//            trains[i].curState = RUN;
//        }
//        //trains[i].curState = RUN;
//        trains[i].curTrack = trains[i].startTrack;
//        trains[i].curSpeed = trains[i].speed;
//        trains[i].curPos = trains[i].startPos;
//        trains[i].restStayDur = -1;
//        trains[i].inPublicTrack = 0;
//        trains[i].moved = 0;
//        trains[i].hasChangedTrack = 0;
//        trains[i].waitForFrontTrain = 0;
//    }

//    printf("请选择调度策略：\n"
//           "0：快车优先\n"
//           "1：交替优先\n"
//           "2：人工控制\n");

//    while (1)
//    {
//        fflush(stdin);
//        gets(input);

//        if (strlen(input) == 1)
//        {
//            if (input[0] == '0')
//            {
//                strategy = FAST_FIRST;
//                break;
//            }
//            if (input[0] == '1')
//            {
//                strategy = ALTERNATIVE;
//                break;
//            }
//            if (input[0] == '2')
//            {
//                strategy = MANUAL_CTRL;
//                break;
//            }
//        }
//        printf("请选择调度策略：\n"
//               "0：快车优先\n"
//               "1：交替优先\n"
//               "2：人工控制\n");
//    }

//    printf("模拟火车调度系统开始运行：\n");
//}

//#define SECS_PER_MIN 60
//#define MINS_PER_HR 60
//#define HRS_PER_DAY 24

//void printState()
//{
//    int _t = t / UNITS_PER_SEC;
//    int ss = _t % SECS_PER_MIN;
//    int mm = ((_t -= ss) /= SECS_PER_MIN) % MINS_PER_HR;
//    int hh = ((_t -= mm) /= MINS_PER_HR) % HRS_PER_DAY;

//    FILE* printTo;

//    for (int i(0); i < 2; ++i)
//    {
//        printTo = i ? logPtr : stdout;

//        fprintf(printTo, "\n\n当前时间: %.2d:%.2d:%.2d\n", hh, mm, ss);
//        fprintf(printTo, "当前策略：");
//        switch (strategy)
//        {
//            case FAST_FIRST:
//                fprintf(printTo, "快车优先\n");
//                break;
//            case ALTERNATIVE:
//                fprintf(printTo, "交替优先\n");
//                break;
//            case MANUAL_CTRL:
//                fprintf(printTo, "人工控制\n");
//                break;

//        }
//        fprintf(printTo, "\n火车号    所属轨道        位置        剩余等待时间    速度      方向      状态\n\n");

//        for (int i(0); i < trainNum; ++i)
//        {

//            fprintf(printTo, "%-6c    %-8d    (%3.2f, %3.2f)        %2d          %.2f    %s    ",
//                    'A' + i,
//                    trains[i].curTrack,
//                    getX(i), getY(i),
//                    trains[i].restStayDur / UNITS_PER_SEC,
//                    ((trains[i].curState == RUN) ? trains[i].curSpeed : 0.),
//                    ((trains[i].dir == CLKWISE) ? "顺时针" : "逆时针"));
//            /*
//            printf("%-6c    %-8d    %.2f      %.2f    %s    ",
//                   'A' + i,
//                   trains[i].curTrack,
//                   trains[i].curPos,
//                   ((trains[i].curState == RUN) ? trains[i].curSpeed : 0.),
//                   ((trains[i].dir == CLKWISE) ? "顺时针" : "逆时针"));*/
//            switch (trains[i].curState)
//            {
//                case RUN:
//                {
//                    if (trains[i].inPublicTrack)
//                        fprintf(printTo, "运行 - 公共轨道\n");
//                    else
//                        fprintf(printTo, "运行 - 非公共轨道\n");
//                    break;
//                }
//                case WAIT:
//                {
//                    if (trains[i].inPublicTrack)
//                        fprintf(printTo, "停靠 - 占用公共轨道\n");
//                    else if (trains[i].waitForFrontTrain)
//                        fprintf(printTo, "暂停 - 等待前车\n");
//                    else
//                        fprintf(printTo, "暂停 - 等待公共轨道\n");
//                    break;
//                }
//                case STOP:
//                {
//                    fprintf(printTo, "暂停 - 等待启动\n");
//                }
//            }
//        }

//        fprintf(printTo, "\n");

//        for (int i(0); i < trackNum; ++i)
//            for (int j(0); j < i; ++j)
//                if (i != j
//                    && publicTracks[i][j].exist)
//                {
//                    if (publicTracks[i][j].state == IDLE)
//                        fprintf(printTo, "公共轨道%d - %d空闲\n", i, j);
//                    else
//                    {
//                        int a(-1), b(-1);

//                        if (trainsQ[i][j].size)
//                            a = getTop(&trainsQ[i][j]);

//                        if (trainsQ[j][i].size)
//                            b = getTop(&trainsQ[j][i]);

//                        int c;

//                        if (a != -1 && trains[a].inPublicTrack)
//                            c = a;
//                        else
//                            c = b;

//                        fprintf(printTo, "公共轨道%d - %d被%c车占用\n",
//                                i, j, c + 'A');
//                    }
//                }
//    }

//    printf("\n键入0x暂停火车x，键入1x启动火车x\n"
//           "键入+x火车x加速1.0m/s，键入-x火车x减速1.0m/s"
//           "键入4、5、6分别选择快车优先、交替优先、人工选择策略\n"
//           "键入7退出模拟程序\n");
//}

//#define MAX_CMD_LEN 15

//char cmd[MAX_CMD_LEN];
//bool enCmd = 1;

//void enableCmd()
//{
//    enCmd = 1;
//}

//void disableCmd()
//{
//    enCmd = 0;
//}

//DWORD WINAPI getCmd(LPVOID pParameter)
//{
//    while (1)
//    {
//        while (!enCmd)
//            Sleep(1);

//        fflush(stdin);

//        gets(cmd);
//        //puts(cmd);

//        while (!enCmd)
//            Sleep(1);

//        if (strlen(cmd) == 2)
//        {
//            switch (cmd[0])
//            {
//                case '0':
//                {
//                    int i = cmd[1] - 'A';

//                    if (0 <= i && i < trainNum)
//                    {
//                        trains[i].curState = STOP;
//                        fprintf(logPtr, "\n停止火车%c\n", cmd[1]);
//                    }
//                    else
//                    {
//                        i = cmd[1] - 'a';

//                        if (0 <= i && i < trainNum)
//                        {
//                            trains[i].curState = STOP;
//                            fprintf(logPtr, "\n停止火车%c\n", cmd[1] + 'A' - 'a');
//                        }
//                    }

//                    break;
//                }
//                case '1':
//                {
//                    int i = cmd[1] - 'A';

//                    if (0 <= i && i < trainNum)
//                    {
//                        trains[i].curState = RUN;
//                        fprintf(logPtr, "\n启动火车%c\n", cmd[1]);
//                    }
//                    else
//                    {
//                        i = cmd[1] - 'a';

//                        if (0 <= i && i < trainNum)
//                        {
//                            trains[i].curState = RUN;
//                            fprintf(logPtr, "\n启动火车%c\n", cmd[1] + 'A' - 'a');
//                        }

//                    }
//                }
//                case '+':
//                {
//                    int i = cmd[1] - 'A';

//                    if (0 <= i && i < trainNum)
//                    {
//                        trains[i].curSpeed += 1.;
//                        fprintf(logPtr, "\n火车%c加速1m/s\n", cmd[1]);
//                    }
//                    else
//                    {
//                        i = cmd[1] - 'a';

//                        if (0 <= i && i < trainNum)
//                        {
//                            trains[i].curSpeed += 1.;
//                            fprintf(logPtr, "\n火车%c加速1m/s\n", cmd[1] + 'A' - 'a');
//                        }

//                    }
//                }
//                case '-':
//                {
//                    int i = cmd[1] - 'A';

//                    if (0 <= i && i < trainNum)
//                    {
//                        if (trains[i].curSpeed > 1.)
//                        {
//                            trains[i].curSpeed -= 1.;
//                            fprintf(logPtr, "\n火车%c减速1m/s\n", cmd[1]);
//                        }
//                    }
//                    else
//                    {
//                        i = cmd[1] - 'a';

//                        if (0 <= i && i < trainNum)
//                        {
//                            if (trains[i].curSpeed > 1.)
//                            {
//                                trains[i].curSpeed -= 1.;
//                                fprintf(logPtr, "\n火车%c减速1m/s\n", cmd[1] + 'A' - 'a');
//                            }

//                        }

//                    }
//                }
//            }
//        }
//        else if (strlen(cmd) == 1)
//        {
//            switch (cmd[0])
//            {
//                case '4':
//                {
//                    strategy = FAST_FIRST;
//                    break;
//                }
//                case '5':
//                {
//                    strategy = ALTERNATIVE;
//                    break;
//                }
//                case '6':
//                {
//                    strategy = MANUAL_CTRL;
//                    break;
//                }
//                case '7':
//                {
//                    loop = 0;
//                    break;
//                }
//                case '8':
//                {
//                    puts("");
//                    for (int i(0); i < trackNum; ++i)
//                        for (int j(0); j < trackNum; ++j)
//                            if (publicTracks[i][j].exist
//                                && trainsQ[i][j].size)
//                            {
//                                int front = trainsQ[i][j].front;

//                                printf("%d %d: ", i, j);

//                                for (int k(0); k < trainsQ[i][j].size; ++k)
//                                    printf("%d ", trainsQ[i][j].data[(front + k) % MAX_Q_SIZE]);
//                                puts("");
//                            }
//                }
//            }
//        }
//    }
//}

void printState()
{
    #define SECS_PER_MIN 60
    #define MINS_PER_HR 60
    #define HRS_PER_DAY 24

    int _t = t / UNITS_PER_SEC;
    int ss = _t % SECS_PER_MIN;
    int mm = ((_t -= ss) /= SECS_PER_MIN) % MINS_PER_HR;
    int hh = ((_t -= mm) /= MINS_PER_HR) % HRS_PER_DAY;

    FILE* printTo;

    for (int i(0); i < 2; ++i)
    {
        printTo = i ? logPtr : stdout;
        //printTo = stdout;
        //fprintf(printTo, "\nt = %llu\n", t);
        fprintf(printTo, "\n\ncurrent time: %.2d:%.2d:%.2d\n", hh, mm, ss);
        fprintf(printTo, "current strategy: ");
        switch (strategy)
        {
            case FAST_FIRST:
                fprintf(printTo, "FAST_FIRST\n");
                break;
            case ALTERNATIVE:
                fprintf(printTo, "ALTERNATIVE\n");
                break;
            case MANUAL_CTRL:
                fprintf(printTo, "MANUAL_CTRL\n");
                break;

        }
        fprintf(printTo, "\ntrainId    current track    current pos    remaining waiting time    current speed      dir      state\n\n");

        for (int i(0); i < trainNum; ++i)
        {

            fprintf(printTo, "%-6c    %-4d  (%3.2f, %3.2f)     %2d        %.2f      %s    ",
                    'A' + i,
                    trains[i].curTrack,
                    trains[i].getX(), trains[i].getY(),
                    trains[i].restStayDur / UNITS_PER_SEC,
                    ((trains[i].curState == RUN) ? trains[i].curSpeed : 0.),
                    ((trains[i].dir == CLKWISE) ? "clockwise" : "counterclockwise"));
            /*
            printf("%-6c    %-8d    %.2f      %.2f    %s    ",
                   'A' + i,
                   trains[i].curTrack,
                   trains[i].curPos,
                   ((trains[i].curState == RUN) ? trains[i].curSpeed : 0.),
                   ((trains[i].dir == CLKWISE) ? "顺时针" : "逆时针"));*/
            switch (trains[i].curState)
            {
                case RUN:
                    {
                        if (trains[i].inPublicTrack)
                            fprintf(printTo, "run - public\n");
                        else
                            fprintf(printTo, "run - non public\n");
                        break;
                    }
                case WAIT:
                    {
                        if (trains[i].inPublicTrack)
                            fprintf(printTo, "wait - in public\n");
                        else if (trains[i].waitForFrontTrain)
                            fprintf(printTo, "wait - for front train\n");
                        else
                            fprintf(printTo, "wait - for entering public\n");
                        break;
                    }
                case STOP:
                    {
                        fprintf(printTo, "stop - for start\n");
                    }
            }
        }

        fprintf(printTo, "\n");

        for (int i(0); i < trackNum; ++i)
            for (int j(0); j < i; ++j)
                if (i != j
                        && publicTracks[i][j].exist)
                {
                    if (publicTracks[i][j].state == IDLE)
                        fprintf(printTo, "public %d - %d IDLE\n", i, j);
                    else
                    {
                        int a(-1), b(-1);

                        if (trainsQ[i][j].size)
                            a = trainsQ[i][j].getTop();

                        if (trainsQ[j][i].size)
                            b = trainsQ[j][i].getTop();

                        int c;

                        if (a != -1 && trains[a].inPublicTrack)
                            c = a;
                        else
                            c = b;

                        fprintf(printTo, "public %d - %d occupied by train %c\n",
                                i, j, c + 'A');
                    }
                }
    }

    puts("");
    for (int i(0); i < trackNum; ++i)
        for (int j(0); j < trackNum; ++j)
            if (publicTracks[i][j].exist
                && trainsQ[i][j].size)
            {
                printf("public %d %d: ", i, j);

                for (int k(0); k < trainsQ[i][j].size; ++k)
                    printf("%d ", trainsQ[i][j][k]);
                puts("");
            }
}

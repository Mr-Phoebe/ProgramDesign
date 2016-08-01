#include "structs.h"
#include <QDebug>
void TrafficMap::debug()
{
    #if 0

    int startCity, startTime, destCity;

    while (cin >> startCity >> startTime >> destCity)
    {
        int destTime(minCostArriveTime[startCity][startTime][destCity]);

        cout << "minCost : " << minCost[startCity][startTime][destCity][destTime] << endl;
        cout << "passCities: ";

        for (int i(0); i != CITY_NUM; ++i)
            if (minCostPass[startCity][startTime][destCity][destTime] & (1 << i))
                cout << cityNoToName[i] << " ";
        cout << "\n";

        vector<int> revPath;

        int passCity(destCity), passTime(destTime);

        do
        {
            revPath.push_back(minCostPrv[startCity][startTime][passCity][passTime]);
            passCity = edges[revPath.back()].depart.city;
            passTime = edges[revPath.back()].depart.time;
        } while (!(passCity == startCity && passTime == startTime));

        for (auto it = revPath.rbegin(); it != revPath.rend(); ++it)
            cout << edges[*it] << endl;
    }

    #elif 1
    ofstream ofs("F:/debug.txt");
/*
    Passenger passenger;
    passenger.demand.startCity = "Xi'an";
    passenger.demand.destCity = "Shijiazhuang";
    for (const string& s : {"Changchun", "Guangzhou", "Chengdu", "Shanghai", "Changsha", "Chongqing", "Nanjing"})
        passenger.demand.passCities.push_back(s);
    passenger.demand.startTime = 12,
    passenger.demand.strategy = MIN_COST;
*/
    Passenger passenger(passengers.at(passengers.size() - 1) );
    clock_t start = clock();
    vector<string>::iterator it;
    for (it = passenger.demand.passCities.begin(); it != passenger.demand.passCities.end(); it ++)
    {
        string tmp(*it);
        qDebug("%s",tmp.c_str());
    }

    //getStrategy(passengers.at(passengers.size() - 1));
    //restoreEdge();
//    for (int i = 0; i <= 10; i++)
//        passengers[passengers.size() - 1].status.revPath.push_back(i + 250);

    clock_t stop = clock();
    qDebug( "stragtegy got in %d ms\n", stop - start);

    ofs.close();

    #endif // 1
}


#include <cstdio>
#include <ctime>
#include <map>
#include <iostream>
#include <cstring>
#include <cassert>
#include <algorithm>

using namespace std;

const int N = 19;

long long pw50[42];
const int dx[4] = {1, 1, 1, 0};
const int dy[4] = {-1, 0, 1, 1};
const long long inf = (long long)1e18;

int field[42][42];

int RAND(int n) {
  return ((rand() << 15) + rand()) % n;
}

bool me;

long long get_score() {
  long long score = 0;
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
      for (int q = 0; q < 4; q++) {
        int fi = i + dx[q] * 4;
        int fj = j + dy[q] * 4;
        if (1 <= fi && fi <= N && 1 <= fj && fj <= N) {
          int c0 = 0, c1 = 0;
          for (int k = 0; k <= 4; k++) {
            int fi = i + dx[q] * k;
            int fj = j + dy[q] * k;
            if (field[fi][fj] == 0) {
              c0++;
            }
            if (field[fi][fj] == 1) {
              c1++;
            }
          }
          if (c1 == 5) {
            return inf;
          }
          if (c1 > 0 && c0 == 0) {
            score += pw50[2 * c1 - 1];
          }
          if (c0 > 0 && c1 == 0) {
            score -= pw50[2 * c0];
          }
        }
      }
    }
  }
  score += RAND(50 * 50);
  return score;
}

long long get_score_my() {
  long long score = 0;
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
      for (int q = 0; q < 4; q++) {
        int fi = i + dx[q] * 4;
        int fj = j + dy[q] * 4;
        if (1 <= fi && fi <= N && 1 <= fj && fj <= N) {
          int c0 = 0, c1 = 0;
          for (int k = 0; k <= 4; k++) {
            int fi = i + dx[q] * k;
            int fj = j + dy[q] * k;
            if (field[fi][fj] == 1) {
              c0++;
            }
            if (field[fi][fj] == 0) {
              c1++;
            }
          }
          if (c1 == 5) {
            return inf;
          }
          if (c1 > 0 && c0 == 0) {
            score += pw50[2 * c1 - 1];
          }
          if (c0 > 0 && c1 == 0) {
            score -= pw50[2 * c0];
          }
        }
      }
    }
  }
  score += RAND(50 * 50);
  return score;
}

int main() {
  pw50[0] = 1;
  for (int i = 1; i <= 10; i++) {
    pw50[i] = pw50[i - 1] * 50;
  }
  srand(time(0));
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
      field[i][j] = -1;
    }
  }
  bool first = true;
  while (true) {
    int mi, mj;
    scanf("%d %d", &mi, &mj);
    if (mi == -1) {
      return 0;
    }
    field[mi][mj] = 1;
    {
      vector < vector < pair <int, int> > > all;
      all.push_back(vector < pair <int, int> >());
      const int MAX = 8;
      for (int MOVE = 0; MOVE < 4; MOVE++) {
        vector < pair <long long, vector < pair <int, int> > > > new_all;
        for (int pos = 0; pos < (int)all.size(); pos++) {
          vector < pair <int, int> > history = all[pos];
          for (int i = 0; i < (int)history.size(); i++) {
            field[history[i].first][history[i].second] = i % 2;
          }
          for (int i = 5; i <= N - 4; i++) {
            for (int j = 5; j <= N - 4; j++) {
              if (field[i][j] != -1) {
                continue;
              }
              field[i][j] = 0;
              long long u = get_score_my();
              vector < pair <int, int> > newh = history;
              newh.push_back(make_pair(i, j));
              new_all.push_back(make_pair(u, newh));
              field[i][j] = -1;
            }
          }
          for (int i = 0; i < (int)history.size(); i++) {
            field[history[i].first][history[i].second] = -1;
          }
        }
        sort(new_all.rbegin(), new_all.rend());
        all.clear();
        for (int i = 0; i < MAX && i < (int)new_all.size(); i++) {
          all.push_back(new_all[i].second);
        }
        new_all.clear();
        for (int pos = 0; pos < (int)all.size(); pos++) {
          vector < pair <int, int> > history = all[pos];
          for (int i = 0; i < (int)history.size(); i++) {
            field[history[i].first][history[i].second] = i % 2;
          }
          long long mx = -(long long)9e18;
          int mi = -1, mj = -1;
          if (get_score_my() < inf) {
            for (int i = 5; i <= N - 4; i++) {
              for (int j = 5; j <= N - 4; j++) {
                if (field[i][j] != -1) {
                  continue;
                }
                field[i][j] = 1;
                long long u = get_score();
                if (u > mx) {
                  mx = u;
                  mi = i;
                  mj = j;
                }
                field[i][j] = -1;
              }
            }
          }
          if (mx < inf) {
            vector < pair <int, int> > newh = history;
            if (mi != -1) {
              newh.push_back(make_pair(mi, mj));
            }
            new_all.push_back(make_pair(mx, newh));
          }
          for (int i = 0; i < (int)history.size(); i++) {
            field[history[i].first][history[i].second] = -1;
          }
        }
        sort(new_all.begin(), new_all.end());
        all.clear();
        for (int i = 0; i < MAX && i < (int)new_all.size(); i++) {
          all.push_back(new_all[i].second);
        }
      }
      int mi = all[0][0].first;
      int mj = all[0][0].second;
      printf("%d %d\n", mi, mj);
      fflush(stdout);
      field[mi][mj] = 0;
    }
  }
  return 0;
}

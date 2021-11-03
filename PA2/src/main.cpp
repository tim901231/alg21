#include <algorithm>
#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
using namespace std::chrono;
void dfs(int x, int y, vector<vector<int>> &path, vector<pair<int, int>> &ans) {
  if (x < y) {
    if (path[x][y] != -1) {
      ans.push_back({path[x][y], y});
      dfs(x, path[x][y] - 1, path, ans);
      dfs(path[x][y] + 1, y - 1, path, ans);
    } else {
      dfs(x, y - 1, path, ans);
    }
  }
}

int main(int argc, char *argv[]) {

  if (argc != 3) {
    cout << "Error" << endl;
    cout << "./mps <input_file_name> <output_file_name>";
    return 0;
  }
  high_resolution_clock::time_point t1 = high_resolution_clock::now();
  fstream fin(argv[1]);
  fstream fout;
  fout.open(argv[2], ios::out);
  int n;
  fin >> n;
  // cin >> n;
  vector<int> edge(n, n);
  int a, b;
  while (fin >> a >> b) {
    edge[a] = b;
    edge[b] = a;
  } /*
   for (int i = 0; i < 6; i++) {
     cin >> a >> b;
     edge[a] = b;
     edge[b] = a;
   }*/
  
  vector<vector<int>> path(n, vector<int>(n, -1));
  vector<vector<int>> dp(n, vector<int>(n, 0));
  for (int j = 0; j < n; j++) {
    for (int i = j - 1; i >= 0; i--) {
      dp[i][j] = dp[i][j - 1];

      if (edge[j] == i) {
        if (dp[i + 1][j - 1] + 1 > dp[i][j]) {
          dp[i][j] = dp[i + 1][j - 1] + 1;
          path[i][j] = i;
        }
      } else if (edge[j] > i && edge[j] < j) {
        if (dp[i][edge[j] - 1] + dp[edge[j] + 1][j - 1] + 1 > dp[i][j]) {
          dp[i][j] = dp[i][edge[j] - 1] + dp[edge[j] + 1][j - 1] + 1;
          path[i][j] = edge[j];
        }
      }
    }
  }
  fout << dp[0][n - 1] << endl;
  vector<pair<int, int>> ans;
  sort(ans.begin(), ans.end());
  dfs(0, n - 1, path, ans);
  sort(ans.begin(), ans.end());
  for (int i = 0; i < ans.size(); i++) {
    fout << ans[i].first << " " << ans[i].second << endl;
  }
  high_resolution_clock::time_point t2 = high_resolution_clock::now();
  duration<double, std::milli> time_span = t2 - t1;
  cout << "excute time: " << time_span.count() << "ms" << endl;
}

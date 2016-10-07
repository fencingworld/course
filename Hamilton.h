#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <iterator>
#include <time.h>
#include <iomanip>
#include <sys/time.h>

#define VALUE_RANGE 100
#define VALUE_RATE 0.7
#define INF ( 1<<15 )
//#define INF 0
using namespace std;
typedef uint8_t UINT;
#ifndef HAMILTON_H
#define HAMILTON_H


class Hamilton
{
public:
    Hamilton();
    //virtual ~Hamilton();

    vector< vector< int> >m_score_;
    //vector< int > m_path_;
    vector< pair<vector< int >,int> >m_hamilton_path_;
    pair<vector< int >,int>m_min_hmt_path_enum;
    pair<vector< int >,int>m_min_hmt_path_climb;
    pair<vector< int >,int>m_min_hmt_path_bestfirst;
    pair<vector< int >,int>m_min_hmt_path_branchbound_naive;
    pair<vector< int >,int>m_min_hmt_path_branchbound_edge;

    int m_value_;
    int res_cnt;
    size_t m_node_num_;
    long m_time_start_;
    long m_time_finish_;
    long m_time_running_;
    Hamilton(size_t node_num);
    bool existDFS();
    bool existBFS();
    bool hmtDFS();
    bool hmtDFS_r();
    void hmtDFS_r(vector<int >t_path,vector <bool>t_visit,int t_cost);
    bool hmtBFS();
    bool hmtEnum();
    bool hmtHillClimbing();
    bool hmtBestFirst();
    bool hmtBranchBoundNaive();
    bool hmtBranchBoundEdge();
    void showPath();
    void standardizePath(vector<int > &path);

protected:

private:
};

#endif // HAMILTON_H

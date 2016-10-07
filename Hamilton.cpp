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
#include "Hamilton.h"
typedef struct HamiltonPATH
{

    vector<int >m_path_;
    vector<bool>m_visit_;
    int m_cost_;
    int m_extended_;


} HamiltonPath;
void showScore(vector< vector< int> > &score)
{
    int n = score.size();
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            cout<<setw(6)<<score[i][j];
        }
        cout<<endl;
    }
    cout<<endl;
}
void Hamilton::showPath()
{
    cout<<" "<<res_cnt<<"update times = " <<m_hamilton_path_.size()<<endl;
    return ;
    vector< pair<vector< int >,int> >::iterator hmt_it;
    for (hmt_it =m_hamilton_path_.begin(); hmt_it!=m_hamilton_path_.end(); hmt_it++)
    {
        pair<vector< int >,int> hmt_pair = *hmt_it;
        vector< int > hmt_path  = hmt_pair.first;
        vector< int >::iterator vec_it ;
        for (vec_it= hmt_path.begin(); vec_it!=hmt_path.end(); vec_it++)
        {
            cout<<setw(3)<<*vec_it<<" ";
        }
        int  hmt_cost          = hmt_pair.second;
        cout<<"->"<<hmt_cost<<endl;
    }
}
Hamilton::Hamilton(size_t node_num):
    m_node_num_(node_num),
    m_value_(-1),
    m_min_hmt_path_enum(pair<vector< int >,int>(vector<int>(1,0),INF)),
    m_min_hmt_path_climb(pair<vector< int >,int>(vector<int>(1,0),INF)),
    m_min_hmt_path_bestfirst(pair<vector< int >,int>(vector<int>(1,0),INF)),
    m_min_hmt_path_branchbound_naive(pair<vector< int >,int>(vector<int>(1,0),INF)),
    m_min_hmt_path_branchbound_edge(pair<vector< int >,int>(vector<int>(1,0),INF)),
    res_cnt(0)
{
    //cout<<m_node_num_;
    // cout<<m_min_hmt_path_enum.second<<endl;
    for (int i=0; i<m_node_num_; i++)
    {
        vector<int >t_score(m_node_num_,INF);
        m_score_.push_back(t_score);
        //generate(t_score.begin(),t_score.end(),)
    }
    srand((unsigned)time(NULL));
    for (int i=0; i<m_node_num_; i++)
    {
        for (int j=i+1; j<m_node_num_; j++)
        {
            int t_value = INF;

            if (rand()<int(RAND_MAX*VALUE_RATE))
            {
                do
                {
                    t_value= rand()%VALUE_RANGE;
                }
                while(t_value==0);

            }

            m_score_[i][j]=m_score_[j][i]=t_value;
        }
    }

    return ;
    for (int i=0; i<m_node_num_; i++)
    {
        for (int j=0; j<m_node_num_; j++)
        {
            cout<<setw(3)<<m_score_[i][j]<<" ";
        }
        cout<<endl;
    }

    // m_score_.resize(m_node_num_)
}
bool Hamilton::existDFS()
{
    bool exits_hmt = false;
    m_value_ = -1;
    m_time_start_ = clock();

    stack<vector<int > >t_path_st;
    t_path_st.push(vector<int  > (1,0));

    stack<vector<bool > >t_visit_st;
    vector<bool >t_t(m_node_num_,false);
    t_t[0] = true;
    t_visit_st.push(t_t);

    stack<int >t_cost_st;
    t_cost_st.push(0);

    while(!t_path_st.empty())
    {
        vector<int > t_path     = t_path_st.top();
        vector<bool> t_visit    = t_visit_st.top();
        int          t_cost     = t_cost_st.top();

        t_path_st.pop();
        t_visit_st.pop();
        t_cost_st.pop();


        int t_extended = t_path[t_path.size()-1];

        if (t_path.size()==m_node_num_)
        {

            if (m_score_[t_extended ][0]>0)
            {
                exits_hmt = true;
                break;
                //m_value_ = 0;
                /*
                res_cnt++;
                t_cost += m_score_[t_extended ][0];
                pair< vector<int >,int >hmt_pair(t_path,t_cost);
                m_hamilton_path_.push_back(hmt_pair);
                */
            }
            //continue;
        }

        for (int i=0; i<m_node_num_; i++)
        {

            if (m_score_[t_extended ][i] > 0 &&  t_visit[i]==false)
            {
                //t_visit[i] = true;
                vector<int> t_path_ext (t_path );
                t_path_ext.push_back(i);
                t_path_st.push(t_path_ext);

                vector<bool> t_visit_ext(t_visit);
                t_visit_ext[i] = true;
                t_visit_st.push(t_visit_ext);

                int t_cost_ext = t_cost + m_score_[t_extended ][0];
                t_cost_st.push(t_cost_ext);
                //hmtDFS( t_visit, t_visit_num+1,i);
            }
        }
    }

    m_time_finish_ = clock();
    m_time_running_ = m_time_finish_  - m_time_start_;

    // hmtDFS( t_visit, t_visit_num+1,0);
    return exits_hmt;
}
bool Hamilton::existBFS()
{
    bool exits_hmt = false;

    m_time_start_ = clock();

    queue<vector< UINT > >t_path_qu;
    t_path_qu.push(vector<UINT > (1,0));

    queue<vector<bool > >t_visit_qu;
    vector<bool >t_t(m_node_num_,false);
    t_t[0] = true;
    t_visit_qu.push(t_t);

    queue<int >t_cost_qu;
    t_cost_qu.push(0);

    while(!t_path_qu.empty())
    {
//        if (t_path_qu.size()%1000==0)
//            cout<<t_path_qu.size()<<endl;
        vector< UINT > t_path     = t_path_qu.front();
        //for_each(t_path.begin(),t_path.end(),output);
        //cout<<endl;
        vector<bool> t_visit    = t_visit_qu.front();
        int          t_cost     = t_cost_qu.front();

        t_path_qu.pop();
        t_visit_qu.pop();
        t_cost_qu.pop();


        int t_extended = t_path[t_path.size()-1];

        if (t_path.size()==m_node_num_)
        {

            if (m_score_[t_extended ][0]>0)
            {
                exits_hmt = true;
                break;
                /*
                //m_value_ = 0;
                res_cnt++;
                t_cost += m_score_[t_extended ][0];
                pair< vector<int >,int >hmt_pair(t_path,t_cost);
                m_hamilton_path_.push_back(hmt_pair);
                */
            }
            //continue;
        }

        for (int i=0; i<m_node_num_; i++)
        {

            if (m_score_[t_extended ][i] > 0 &&  t_visit[i]==false)
            {
                //t_visit[i] = true;
                vector<UINT> t_path_ext (t_path );
                t_path_ext.push_back(i);
                t_path_qu.push(t_path_ext);

                vector<bool> t_visit_ext(t_visit);
                t_visit_ext[i] = true;
                t_visit_qu.push(t_visit_ext);

                int t_cost_ext = t_cost + m_score_[t_extended ][0];
                t_cost_qu.push(t_cost_ext);
                //hmtDFS( t_visit, t_visit_num+1,i);
            }
        }
    }

    m_time_finish_ = clock();
    m_time_running_ = m_time_finish_  - m_time_start_;

    // hmtDFS( t_visit, t_visit_num+1,0);
    return exits_hmt;
}
//bool Hamilton::existDFS()
//{
//
//    m_time_start_ = clock();
//
//    stack <int  >t_path_st;
//    t_path_st.push(0);
//
//    vector<bool >t_visit_vec(m_node_num_,false);
//    t_visit_vec[0]=true;
//
//    int visit_count = 1;
//
//    while(!t_path_st.empty())
//    {
//        int t_extend     = t_path_st.top();
//        t_path_st.pop();
//
//        for (int i=0; i<m_node_num_; i++)
//        {
//
//            if (m_score_[t_extend ][i] != INF &&  !t_visit_vec[i])
//            {
//                t_visit_vec[i] = true;
//                t_path_st.push(i);
//                visit_count ++ ;
//            }
//        }
//    }
//
//    m_time_finish_ = clock();
//    m_time_running_ = m_time_finish_  - m_time_start_;
//
//    return m_node_num_ == visit_count;
//}
//bool Hamilton::existBFS()
//{
//    //bool exits_hmt = true;
//
//    m_time_start_ = clock();
//
//    queue <int  >t_path_qu;
//    t_path_qu.push(0);
//
//    vector<bool >t_visit_vec(m_node_num_,false);
//    t_visit_vec[0]=true;
//
//    int visit_count = 1;
//
//    while(!t_path_qu.empty())
//    {
//        int          t_extend     = t_path_qu.front();
//        t_path_qu.pop();
//
//        for (int i=0; i<m_node_num_; i++)
//        {
//
//            if (m_score_[t_extend ][i] != INF &&  !t_visit_vec[i])
//            {
//                t_visit_vec[i] = true;
//                t_path_qu.push(i);
//                visit_count ++ ;
//            }
//        }
//    }
//
//    m_time_finish_ = clock();
//    m_time_running_ = m_time_finish_  - m_time_start_;
//
//    // hmtDFS( t_visit, t_visit_num+1,0);
//    return m_node_num_ == visit_count;
//}

bool Hamilton::hmtDFS()
{
    m_value_ = -1;
    int choose = 0;

    m_time_start_ = clock();
    if (choose==0)
    {
        stack<vector<int > >t_path_st;
        t_path_st.push(vector<int  > (1,0));

        stack<vector<bool > >t_visit_st;
        vector<bool >t_t(m_node_num_,false);
        t_t[0] = true;
        t_visit_st.push(t_t);

        stack<int >t_cost_st;
        t_cost_st.push(0);

        while(!t_path_st.empty())
        {
            vector<int > t_path     = t_path_st.top();
            vector<bool> t_visit    = t_visit_st.top();
            int          t_cost     = t_cost_st.top();

            t_path_st.pop();
            t_visit_st.pop();
            t_cost_st.pop();


            int t_extended = t_path[t_path.size()-1];

            if (t_path.size()==m_node_num_)
            {

                if (m_score_[t_extended ][0]>0)
                {
                    //m_value_ = 0;
                    res_cnt++;
                    t_cost += m_score_[t_extended ][0];
                    if (t_cost< m_min_hmt_path_enum.second)
                    {
                        //m_min_hmt_path_enum = pair< vector<int >,int >(t_path,t_cost);
                        pair< vector<int >,int >hmt_pair(t_path,t_cost);
                        m_min_hmt_path_enum  = hmt_pair;
                        m_hamilton_path_.push_back(hmt_pair);
                        cout<<"hahahhaha"<<endl;
                    }
                    //

                }
                //continue;
            }

            for (int i=0; i<m_node_num_; i++)
            {

                if (m_score_[t_extended ][i] > 0 &&  t_visit[i]==false)
                {
                    //t_visit[i] = true;
                    vector<int> t_path_ext (t_path );
                    t_path_ext.push_back(i);
                    t_path_st.push(t_path_ext);

                    vector<bool> t_visit_ext(t_visit);
                    t_visit_ext[i] = true;
                    t_visit_st.push(t_visit_ext);

                    int t_cost_ext = t_cost + m_score_[t_extended ][0];
                    t_cost_st.push(t_cost_ext);
                    //hmtDFS( t_visit, t_visit_num+1,i);
                }
            }
        }


    }
    else if (choose ==1)
    {

        stack <HamiltonPath> t_st_hamilton_path;
        HamiltonPath t_hamilton_path;
        t_hamilton_path.m_path_= vector<int>(1,0);
        vector<bool>t_t(m_node_num_,false);
        t_t[0] = true;
        t_hamilton_path.m_visit_ = t_t;
        t_st_hamilton_path.push(t_hamilton_path);



        //t_visit[0] = true;


        while(!t_st_hamilton_path.empty())
        {
            HamiltonPath t_hamilton_path_top =  t_st_hamilton_path.top();
            t_st_hamilton_path.pop();
            /*
            for (int i=0; i<t_hamilton_path_top.m_path_.size(); i++)
            {
                cout<<t_hamilton_path_top.m_path_[i]<<" ";
            }
            cout<<endl;
            */
            //int t_last_node = t_hamilton_path_top.getLastNode();
            int t_size = t_hamilton_path_top.m_path_.size();
            int t_last_node = t_hamilton_path_top.m_path_[t_size-1];
            if (t_hamilton_path_top.m_path_.size()==m_node_num_)
            {


                if (m_score_[t_last_node][0]>0)
                {
                    m_value_ = 0;
                    //m_hamilton_path_.push(t_hamilton_path_top.m_path_);
                }

                continue;
            }

            for (int i=0; i<m_node_num_; i++)
            {

                if (m_score_[t_last_node][i]!=0 &&  t_hamilton_path_top.m_visit_[i]==false)
                {
                    HamiltonPath t_hamilton_path_top_new(t_hamilton_path_top);
                    t_hamilton_path_top_new.m_path_.push_back(i);
                    t_hamilton_path_top_new.m_visit_[i] = true;
                    t_st_hamilton_path.push(t_hamilton_path_top_new);

                }
            }
        }

    }
    else if (choose ==2 )
    {


        stack <HamiltonPath> t_st_hamilton_path;
        HamiltonPath t_hamilton_path;
        t_hamilton_path.m_path_= vector<int>(1,0);
        vector<bool>t_t(m_node_num_,false);
        t_t[0] = true;
        t_hamilton_path.m_visit_ = t_t;
        t_st_hamilton_path.push(t_hamilton_path);



        //t_visit[0] = true;


        while(!t_st_hamilton_path.empty())
        {
            HamiltonPath t_hamilton_path_top =  t_st_hamilton_path.top();
            t_st_hamilton_path.pop();
            /*
            for (int i=0; i<t_hamilton_path_top.m_path_.size(); i++)
            {
                cout<<t_hamilton_path_top.m_path_[i]<<" ";
            }
            cout<<endl;
            */
            //int t_last_node = t_hamilton_path_top.getLastNode();
            int t_size = t_hamilton_path_top.m_path_.size();
            int t_last_node = t_hamilton_path_top.m_path_[t_size-1];
            if (t_hamilton_path_top.m_path_.size()==m_node_num_)
            {


                if (m_score_[t_last_node][0]>0)
                {
                    m_value_ = 0;
                    //m_hamilton_path_.push(t_hamilton_path_top.m_path_);
                }

                continue;
            }

            for (int i=0; i<m_node_num_; i++)
            {

                if (m_score_[t_last_node][i]!=0 &&  t_hamilton_path_top.m_visit_[i]==false)
                {
                    HamiltonPath t_hamilton_path_top_new(t_hamilton_path_top);
                    t_hamilton_path_top_new.m_path_.push_back(i);
                    t_hamilton_path_top_new.m_visit_[i] = true;
                    t_st_hamilton_path.push(t_hamilton_path_top_new);

                }
            }
        }

    }


    m_time_finish_ = clock();
    m_time_running_ = m_time_finish_  - m_time_start_;

    // hmtDFS( t_visit, t_visit_num+1,0);
    return m_value_>-1;
}
void output(int s)
{
    cout<<setw(3)<<s;
}
bool Hamilton::hmtBFS()
{
    m_value_ = -1;

    m_time_start_ = clock();

    queue<vector<int > >t_path_qu;
    t_path_qu.push(vector<int  > (1,0));

    queue<vector<bool > >t_visit_qu;
    vector<bool >t_t(m_node_num_,false);
    t_t[0] = true;
    t_visit_qu.push(t_t);

    queue<int >t_cost_qu;
    t_cost_qu.push(0);

    while(!t_path_qu.empty())
    {
        if (t_path_qu.size()%1000==0)
            cout<<t_path_qu.size()<<endl;
        vector<int > t_path     = t_path_qu.front();
        //for_each(t_path.begin(),t_path.end(),output);
        //cout<<endl;
        vector<bool> t_visit    = t_visit_qu.front();
        int          t_cost     = t_cost_qu.front();

        t_path_qu.pop();
        t_visit_qu.pop();
        t_cost_qu.pop();


        int t_extended = t_path[t_path.size()-1];

        if (t_path.size()==m_node_num_)
        {

            if (m_score_[t_extended ][0]>0)
            {
                //m_value_ = 0;
                res_cnt++;
                t_cost += m_score_[t_extended ][0];
                pair< vector<int >,int >hmt_pair(t_path,t_cost);
                //m_hamilton_path_.push_back(hmt_pair);
            }
            //continue;
        }

        for (int i=0; i<m_node_num_; i++)
        {

            if (m_score_[t_extended ][i] > 0 &&  t_visit[i]==false)
            {
                //t_visit[i] = true;
                vector<int> t_path_ext (t_path );
                t_path_ext.push_back(i);
                t_path_qu.push(t_path_ext);

                vector<bool> t_visit_ext(t_visit);
                t_visit_ext[i] = true;
                t_visit_qu.push(t_visit_ext);

                int t_cost_ext = t_cost + m_score_[t_extended ][0];
                t_cost_qu.push(t_cost_ext);
                //hmtDFS( t_visit, t_visit_num+1,i);
            }
        }
    }






    m_time_finish_ = clock();
    m_time_running_ = m_time_finish_  - m_time_start_;

    // hmtDFS( t_visit, t_visit_num+1,0);
    return m_value_>-1;
}

/// 非递归遍历要入栈,可是入栈后标记该节点已经访问过，那就不能通过前一个节点
///访问该节点
///

bool Hamilton::hmtDFS_r()
{
    m_value_ = -1;
    vector<int >    t_path(1,0);
    vector<bool >   t_visit(m_node_num_,false);
    t_visit[0] = true;
    int             t_cost = 0;

    res_cnt=0;
    m_time_start_ = clock();
    hmtDFS_r( t_path,t_visit,0);

    m_time_finish_ = clock();
    m_time_running_ = m_time_finish_  - m_time_start_;
    return m_value_>-1;
}
void Hamilton::hmtDFS_r(vector<int >t_path,vector <bool>t_visit,int t_cost)
{
    if (t_path.size()<1)
        return;
    int t_extended = t_path[t_path.size()-1];
    if (t_path.size()==m_node_num_)
    {
        if (m_score_[t_extended][0]>0)
        {
            t_cost  +=  m_score_[t_extended][0];
            res_cnt++;
            pair< vector<int >,int >hmt_pair(t_path,t_cost);
            //m_hamilton_path_.push_back(hmt_pair);
            //cout<<"aaaaaaaaaa";
        }
        return;
    }
    for (int i=0; i<m_node_num_; i++)
    {
        if (m_score_[t_extended ][i] > 0 && t_visit[i]==false)
        {


            vector<int> t_path_ext(t_path);
            t_path_ext.push_back(i);

            vector<bool > t_visit_ext(t_visit);
            t_visit_ext[i] = true;//cout<<i<<" ";

            int t_cost_ext = t_cost + m_score_[t_extended ][0];

            hmtDFS_r( t_path_ext,  t_visit_ext,t_cost_ext);
        }
    }
}
bool Hamilton::hmtEnum()
{

    m_time_start_ = clock();

    stack<vector<int > >t_path_st;
    t_path_st.push(vector<int  > (1,0));

    stack<vector<bool > >t_visit_st;
    vector<bool >t_t(m_node_num_,false);
    t_t[0] = true;
    t_visit_st.push(t_t);

    stack<int >t_cost_st;
    t_cost_st.push(0);

    while(!t_path_st.empty())
    {
        vector<int > t_path     = t_path_st.top();
        vector<bool> t_visit    = t_visit_st.top();
        int          t_cost     = t_cost_st.top();

        t_path_st.pop();
        t_visit_st.pop();
        t_cost_st.pop();


        int t_extended = t_path[t_path.size()-1];

        if (t_path.size()==m_node_num_)
        {

            if (m_score_[t_extended ][0]!=INF)
            {
                m_value_ = 0;
                res_cnt++;
                t_cost += m_score_[t_extended ][0];

//                pair< vector<int >,int >hmt_pair(t_path,t_cost);
//                m_hamilton_path_.push_back(hmt_pair);
                if (t_cost <  m_min_hmt_path_enum.second)
                {
                    pair< vector<int >,int >hmt_pair(t_path,t_cost);
                    m_min_hmt_path_enum = hmt_pair;
                    //
                    //m_hamilton_path_.push_back(hmt_pair);
                    //m_min_hmt_path_enum  =  pair< vector<int >,int >(t_path,t_cost);
                    // cout<<t_cost<<" "<<m_min_hmt_path_enum.second<<endl;
                    //cout<<m_hamilton_path_.size()<<" "<<t_cost<<endl;
                }
                //

            }
            //continue;
        }

        for (int i=0; i<m_node_num_; i++)
        {

            if (m_score_[t_extended ][i] !=INF &&  t_visit[i]==false)
            {
                //t_visit[i] = true;
                vector<int> t_path_ext (t_path );
                t_path_ext.push_back(i);
                t_path_st.push(t_path_ext);

                vector<bool> t_visit_ext(t_visit);
                t_visit_ext[i] = true;
                t_visit_st.push(t_visit_ext);

                int t_cost_ext = t_cost + m_score_[t_extended ][i];
                //cout<<t_cost_ext<<endl;
                t_cost_st.push(t_cost_ext);
                //hmtDFS( t_visit, t_visit_num+1,i);
            }
        }
    }





    m_time_finish_ = clock();
    m_time_running_ = m_time_finish_  - m_time_start_;

    // hmtDFS( t_visit, t_visit_num+1,0);
    return m_value_>-1;
}
bool cmp_hmt_path_greater(HamiltonPath a,HamiltonPath b)
{
    return a.m_cost_>b.m_cost_;
}
bool Hamilton::hmtHillClimbing()
{

    m_time_start_ = clock();

    HamiltonPath t_hmt_path;
    vector<bool >t_t(m_node_num_,false);
    t_t[0] = true;
    t_hmt_path.m_path_ = vector<int  > (1,0);
    t_hmt_path.m_visit_         = t_t;
    t_hmt_path.m_cost_          = 0;
    t_hmt_path.m_extended_      = 0;

    stack<HamiltonPath >hmt_path_st;
    hmt_path_st.push(t_hmt_path);

    while(!hmt_path_st.empty())
    {
        t_hmt_path = hmt_path_st.top();
        hmt_path_st.pop();

        vector<int > t_path     = t_hmt_path.m_path_;
        vector<bool> t_visit    = t_hmt_path.m_visit_;
        int          t_cost     = t_hmt_path.m_cost_;
        int          t_extended = t_hmt_path.m_extended_;


        if (t_path.size()==m_node_num_)
        {

            if (m_score_[t_extended ][0]!=INF)
            {
                m_value_ = 0;
                res_cnt++;
                t_cost += m_score_[t_extended ][0];

//                pair< vector<int >,int >hmt_pair(t_path,t_cost);
//                m_hamilton_path_.push_back(hmt_pair);
                if (t_cost <  m_min_hmt_path_climb.second)
                {
                    standardizePath(t_path);
                    pair< vector<int >,int >hmt_pair(t_path,t_cost);
                    m_min_hmt_path_climb = hmt_pair;
                    //
                    //m_hamilton_path_.push_back(hmt_pair);
                    //m_min_hmt_path_enum  =  pair< vector<int >,int >(t_path,t_cost);
                    // cout<<t_cost<<" "<<m_min_hmt_path_enum.second<<endl;
                    //cout<<m_hamilton_path_.size()<<" "<<t_cost<<endl;
                }
                //

            }
            //continue;
        }
        vector< HamiltonPath >hmt_path_v;
        for (int i=0; i<m_node_num_; i++)
        {

            if (m_score_[t_extended ][i] !=INF &&  t_visit[i]==false)
            {
                int t_cost_ext = t_cost + m_score_[t_extended ][i];
                if (t_cost_ext > m_min_hmt_path_climb.second)
                {
                    continue;
                }
                HamiltonPath t_hmt_path_invector;
                vector<int> t_path_ext (t_path );
                t_path_ext.push_back(i);

                vector<bool> t_visit_ext(t_visit);
                t_visit_ext[i] = true;

                t_hmt_path_invector.m_path_ = t_path_ext;
                t_hmt_path_invector.m_visit_         = t_visit_ext;
                t_hmt_path_invector.m_cost_          = t_cost_ext;
                t_hmt_path_invector.m_extended_      = i;


                hmt_path_v.push_back(t_hmt_path_invector);
            }
        }
        sort(hmt_path_v.begin(),hmt_path_v.end(),cmp_hmt_path_greater);

        vector< HamiltonPath >::iterator hmt_path_it ;
        for (hmt_path_it = hmt_path_v.begin(); hmt_path_it!=hmt_path_v.end(); hmt_path_it++)
        {
            hmt_path_st.push(*hmt_path_it);
        }
    }





    m_time_finish_ = clock();
    m_time_running_ = m_time_finish_  - m_time_start_;

    // hmtDFS( t_visit, t_visit_num+1,0);
    return m_value_>-1;
}

bool Hamilton::hmtBestFirst()
{

    m_time_start_ = clock();

    HamiltonPath t_hmt_path;
    vector<bool >t_t(m_node_num_,false);
    t_t[0] = true;
    t_hmt_path.m_path_ = vector<int  > (1,0);
    t_hmt_path.m_visit_         = t_t;
    t_hmt_path.m_cost_          = 0;
    t_hmt_path.m_extended_      = 0;

    vector<HamiltonPath >hmt_path_v;
    hmt_path_v.push_back(t_hmt_path);
    make_heap(hmt_path_v.begin(),hmt_path_v.end(),cmp_hmt_path_greater);

    while(!hmt_path_v.empty())
    {
        /*
                vector< HamiltonPath >::iterator hmt_path_it ;
                for (hmt_path_it = hmt_path_v.begin(); hmt_path_it!=hmt_path_v.end(); hmt_path_it++)
                {
                    //hmt_path_st.push(*hmt_path_it);
                    cout<<hmt_path_it->m_cost_<<" ";
                }
                cout<<endl;
        */
        // cout<<hmt_path_v.size()<<endl;
        pop_heap(hmt_path_v.begin(),hmt_path_v.end(),cmp_hmt_path_greater);
        t_hmt_path = hmt_path_v.back();

        hmt_path_v.pop_back();

        //make_heap(hmt_path_v.begin(),hmt_path_v.end(),cmp_hmt_path_greater);


        vector<int > t_path     = t_hmt_path.m_path_;
        vector<bool> t_visit    = t_hmt_path.m_visit_;
        int          t_cost     = t_hmt_path.m_cost_;
        int          t_extended = t_hmt_path.m_extended_;


        if (t_path.size()==m_node_num_)
        {

            if (m_score_[t_extended ][0]>0)
            {
                m_value_ = 0;
                res_cnt++;
                t_cost += m_score_[t_extended ][0];

//                pair< vector<int >,int >hmt_pair(t_path,t_cost);
//                m_hamilton_path_.push_back(hmt_pair);
                if (t_cost <  m_min_hmt_path_bestfirst.second)
                {
                    pair< vector<int >,int >hmt_pair(t_path,t_cost);
                    m_min_hmt_path_bestfirst = hmt_pair;
                    //
                    //m_hamilton_path_.push_back(hmt_pair);
                    //m_min_hmt_path_enum  =  pair< vector<int >,int >(t_path,t_cost);
                    // cout<<t_cost<<" "<<m_min_hmt_path_enum.second<<endl;
                    // cout<<m_hamilton_path_.size()<<" "<<t_cost<<endl;
                }
                //

            }
            //continue;
        }
        //vector< HamiltonPath >hmt_path_v;
        for (int i=0; i<m_node_num_; i++)
        {

            if (m_score_[t_extended ][i] > 0 &&  t_visit[i]==false)
            {
                int t_cost_ext = t_cost + m_score_[t_extended ][i];
                if (t_cost_ext > m_min_hmt_path_bestfirst.second)
                {
                    continue;
                }
                //cout<<t_cost_ext<<" "<<m_min_hmt_path_bestfirst.second<<endl;
                HamiltonPath t_hmt_path_invector;
                vector<int> t_path_ext (t_path );
                t_path_ext.push_back(i);

                vector<bool> t_visit_ext(t_visit);
                t_visit_ext[i] = true;

                t_hmt_path_invector.m_path_ = t_path_ext;
                t_hmt_path_invector.m_visit_         = t_visit_ext;
                t_hmt_path_invector.m_cost_          = t_cost_ext;
                t_hmt_path_invector.m_extended_      = i;
                hmt_path_v.push_back(t_hmt_path_invector);
                push_heap(hmt_path_v.begin(),hmt_path_v.end(),cmp_hmt_path_greater);
            }
        }
    }

    m_time_finish_ = clock();
    m_time_running_ = m_time_finish_  - m_time_start_;

    // hmtDFS( t_visit, t_visit_num+1,0);
    return m_value_>-1;
}
bool Hamilton::hmtBranchBoundNaive()
{
    res_cnt=0;
    m_time_start_ = clock();

    stack<vector<int > >t_path_st;
    t_path_st.push(vector<int  > (1,0));

    stack<vector<bool > >t_visit_st;
    vector<bool >t_t(m_node_num_,false);
    t_t[0] = true;
    t_visit_st.push(t_t);

    stack<int >t_cost_st;
    t_cost_st.push(0);
    int xxx = 1000;
    while(!t_path_st.empty())
    {

        vector<int > t_path     = t_path_st.top();
        vector<bool> t_visit    = t_visit_st.top();
        int          t_cost     = t_cost_st.top();

        t_path_st.pop();
        t_visit_st.pop();
        t_cost_st.pop();


        int t_extended = t_path[t_path.size()-1];

        if (t_path.size()==m_node_num_)
        {

            if (m_score_[t_extended ][0]>0)
            {
                m_value_ = 0;
                res_cnt++;
                t_cost += m_score_[t_extended ][0];

//                pair< vector<int >,int >hmt_pair(t_path,t_cost);
//                m_hamilton_path_.push_back(hmt_pair);
                if (t_cost <  m_min_hmt_path_branchbound_naive.second)
                {
                    pair< vector<int >,int >hmt_pair(t_path,t_cost);
                    m_min_hmt_path_branchbound_naive = hmt_pair;
                    //
                    //m_hamilton_path_.push_back(hmt_pair);
                    //m_min_hmt_path_enum  =  pair< vector<int >,int >(t_path,t_cost);
                    // cout<<t_cost<<" "<<m_min_hmt_path_enum.second<<endl;
                    //cout<<m_hamilton_path_.size()<<" "<<t_cost<<endl;
                }
                //

            }
            //continue;
        }

        for (int i=0; i<m_node_num_; i++)
        {

            if (m_score_[t_extended ][i] > 0 &&  t_visit[i]==false)
            {
                int t_cost_ext = t_cost + m_score_[t_extended ][i];
                if (t_cost_ext > m_min_hmt_path_branchbound_naive.second)
                {
                    continue;
                }
                //cout<<t_cost_ext<<endl;
                t_cost_st.push(t_cost_ext);
                //t_visit[i] = true;
                vector<int> t_path_ext (t_path );
                t_path_ext.push_back(i);
                t_path_st.push(t_path_ext);

                vector<bool> t_visit_ext(t_visit);
                t_visit_ext[i] = true;
                t_visit_st.push(t_visit_ext);
                if (t_path_st.size()%xxx==0)
                {
                    cout<<t_path_st.size()/xxx<<endl;
                }


                //hmtDFS( t_visit, t_visit_num+1,i);
            }
        }
    }

    m_time_finish_ = clock();
    m_time_running_ = m_time_finish_  - m_time_start_;

    // hmtDFS( t_visit, t_visit_num+1,0);
    return m_value_>-1;
}
//class HamiltonBranchPath
//{
//    public:
//    vector< vector< int> >  score;
//    int                     cost;
//    vector<pair<int,int > > is_path;
//    vector<pair<int,int > > not_path;
//
//} ;
typedef struct Hamiltonbranchpath
{
    vector< vector< int> >  score;
    int                     cost;
    vector<pair<int,int > > is_path;
    vector<pair<int,int > > not_path;

} HamiltonBranchPath;
vector<int > getPath( vector<pair<int,int > > & path,int n)
{
    if (path.size()==0||n<1)
    {
        return vector<int>(0);
    }
    vector< int > ret;
    vector< bool> vst(n,false);
    vector< pair<int,int > >::iterator t_pair_it = path.begin();
    int tt = t_pair_it->first;
    vst[tt] = true;
    ret.push_back(tt);

    tt = t_pair_it->second;
    vst[tt] = true;
    ret.push_back(tt);
    vector< pair<int,int > >::iterator pair_it;
    do
    {

        for (pair_it = path.begin(); pair_it!=path.end(); pair_it++)
        {
            if (tt == pair_it->first )
            {
                tt = pair_it->second;
                ret.push_back(tt);
                if ( vst[tt] == true )
                {
                    return ret;
                }
                else
                {
                    vst[tt] = true;
                }
                break;
            }
        }
    }
    while(pair_it!=path.end());
    return ret;

    //vector< vector< bool> >  score(n,vector<bool>(n,false) );


}
void Hamilton::standardizePath(vector<int > &path)
{
    if (path.size() <1 )
    {
        return ;
    }

    vector<int >::iterator it = find(path.begin(),path.end(),0);
    if (it!=path.end())
    {
        rotate(path.begin(),it,path.end());
    }
    if (*(path.begin()+1) > *(path.end()-1) )
    {
        reverse(path.begin(),path.end());
        rotate(path.begin(),path.end()-1,path.end());
    }
    vector<int >::iterator it_v;
    for (it_v=path.begin(); it_v!=path.end(); it_v++)
    {
        (*it_v)++;
    }
}

bool Hamilton::hmtBranchBoundEdge()
{
    //showScore(m_score_);
    int n=m_node_num_;
    res_cnt=0;
    m_time_start_ = clock();
    HamiltonBranchPath hmt_path;
    hmt_path.score = m_score_;
    hmt_path.cost  = 0;

    stack<HamiltonBranchPath >hmt_path_st;
    hmt_path_st.push(hmt_path);



    while(!hmt_path_st.empty())
    {

        HamiltonBranchPath t_hmt_path = hmt_path_st.top();
        hmt_path_st.pop();
        //cout<<"size:"<<hmt_path_st.size()<<endl;
        // cout<<"runing 1"<<endl;
        vector< vector< int> >  t_score =t_hmt_path.score;
        int                     t_cost  =t_hmt_path.cost;
        vector<pair<int,int > > t_is_path =t_hmt_path.is_path ;
        vector<pair<int,int > > t_not_path =t_hmt_path.not_path ;
        if (t_cost > m_min_hmt_path_branchbound_edge.second)
        {
            continue;
        }

        // cout<<t_is_path.size()<<" "<<t_not_path.size()<<endl;

        //cout<<t_cost<<endl;
        if (t_is_path.size()==m_node_num_)
        {
            //cout<<"[3]"<<endl;


            vector< int> t_path =  getPath( t_is_path,m_node_num_);
            t_path.pop_back();

//            int ttt;
//            cin>>ttt;
            if (t_cost <  m_min_hmt_path_branchbound_edge.second && t_path.size() == m_node_num_)
            {
//                int sum =0;
//                vector< pair<int,int > >::iterator pair_itt;
//                for (pair_itt = t_is_path.begin(); pair_itt!=t_is_path.end(); pair_itt++)
//                {
//                    sum+= m_score_[pair_itt->first][pair_itt->second];
//                    cout<<pair_itt->first <<"->"<<pair_itt->second<<" "<<sum<<endl;
//
//
//                }
                standardizePath(t_path);
                cout<<t_cost<<endl;
                //cout<<"[XXXXXXXXXXXXXX]"<<endl;
                pair< vector<int >,int >hmt_pair(t_path,t_cost);
                m_min_hmt_path_branchbound_edge = hmt_pair;
                //
                //m_hamilton_path_.push_back(hmt_pair);
                //m_min_hmt_path_enum  =  pair< vector<int >,int >(t_path,t_cost);
                // cout<<t_cost<<" "<<m_min_hmt_path_enum.second<<endl;
                //cout<<m_hamilton_path_.size()<<" "<<t_cost<<endl;
            }
            continue;
        }

        //cout<<"runing 2"<<endl;
        vector<pair<int,int > > t_extend_edge ;
        vector <int >           t_extend_cost;

        ///让每行每列均有0，并记录该点坐标
        //  cout<<"before cost:"<<t_cost<<endl;
        for (int i=0; i<m_node_num_; i++)
        {
            int min_value = INF;
            for (int j=0; j<m_node_num_; j++)
            {
                if (min_value > t_score[i][j])
                {
                    min_value = t_score[i][j];
                }
            }
            if (min_value != INF && 0 !=min_value)
            {
                t_cost += min_value;
                for (int j=0; j<m_node_num_; j++)
                {
                    if ( INF !=  t_score[i][j]  && 0!=  t_score[i][j])
                    {
                        t_score[i][j]-=min_value;
//                        if (0 == t_score[i][j])
//                        {
//                            t_extend_edge.push_back(pair<int,int >(i,j))  ;
//                        }
                    }
                }
            }
        }
        //showScore(t_score);
        for (int i=0; i<m_node_num_; i++)
        {
            int min_value = INF;
            for (int j=0; j<m_node_num_; j++)
            {
                if (min_value > t_score[j][i])
                {
                    min_value = t_score[j][i];
                }
            }
            if (min_value != INF && 0 !=min_value)
            {
                t_cost += min_value;
                for (int j=0; j<m_node_num_; j++)
                {
                    if ( INF !=  t_score[j][i]  && 0!=  t_score[j][i])
                    {
                        t_score[j][i]-=min_value;

                    }
                }

            }
        }
        //cout<<"after cost:"<<t_cost<<endl;
        for (int i=0; i<m_node_num_; i++)
        {
            for (int j=0; j<m_node_num_; j++)
            {
                if (0 == t_score[i][j])
                {
                    //cout<<i<<" "<<j<<endl;
                    t_extend_edge.push_back(pair<int,int >(i,j)) ;
                }
            }
        }
//       // showScore(t_score);


        //showScore(t_score);
        ///计算0点坐标代价
        //cout<<"runing 3"<<endl;
        vector<pair<int,int > >::iterator pair_it;
        for (pair_it = t_extend_edge.begin(); pair_it!=t_extend_edge.end(); pair_it++)
        {
            int t_i     = pair_it->first     ;
            int t_j     = pair_it->second    ;
            int min_value_i = INF;
            for (int j=0; j<m_node_num_; j++)
            {
                if (j!=t_j)
                {
                    //cout<<min_value_i <<"--- "<<t_score[t_i][j]<<endl;
                    if (min_value_i > t_score[t_i][j])
                    {
                        min_value_i = t_score[t_i][j];
                    }
                }

            }
            //cout<<min_value_i<<" ";
            int min_value_j = INF;
            for (int i=0; i<m_node_num_; i++)
            {
                if (i!=t_i)
                {
                    if (min_value_j > t_score[i][t_j])
                    {
                        min_value_j = t_score[i][t_j];
                    }
                }

            }
            //cout<<t_i<<" "<<t_j<<" " <<min_value_i<<" "<<min_value_j<<endl;
            t_extend_cost.push_back( min_value_i+min_value_j);
        }
        //cout<<"t_extend_cost:"<<t_extend_cost.size()<<endl;
        ///选择最大代价节点
        vector<int >::iterator vec_it;
        int max_idx  = -1;
        int max_value = -1;
        for (int i=0; i<t_extend_edge.size(); i++)
        {
            // cout<<t_extend_cost[i]<<" ";
            if (max_value < t_extend_cost[i] )
            {
                max_value = t_extend_cost[i];
                max_idx  = i;
            }
        }
        if (-1 == max_idx)
        {
            // cout<<"[XXXX]:"<<endl;
            continue;
        }
        // cout<<endl;
        //cout<<"runing 4"<<" "<<max_idx<<endl;
        //cout<<max_value<<endl;

        pair<int,int > ext_pair = t_extend_edge[max_idx];
        //cout<<"runing 7"<<endl;
        int ext_x = ext_pair.first;
        int ext_y = ext_pair.second;
        //cout<<"[OOO]:"<<ext_x <<" "<<ext_y<<endl;
        //int t_cost_ext_not_path = t_cost + max_value;
        int t_cost_ext_not_path = t_cost;// + max_value;
        //cout<<"runing 6"<<endl;
        //cout<<"t_cost_ext_not_path:"<<t_cost_ext_not_path<<endl;
        if (t_cost_ext_not_path < m_min_hmt_path_branchbound_edge.second)
        {
            // cout<<"[1]"<<endl;

            vector< vector< int> >  t_score_ext(t_score);
            t_score_ext[ext_x][ext_y] = INF;
            vector<pair<int,int > > t_not_path_ext(t_not_path );
            t_not_path_ext.push_back(ext_pair);

            HamiltonBranchPath t_branch_path;
            t_branch_path.score     = t_score_ext;
            t_branch_path.cost      = t_cost_ext_not_path;
            t_branch_path.is_path   = t_is_path;
            t_branch_path.not_path  = t_not_path_ext;
            hmt_path_st.push(t_branch_path);
            // cout<<"[1-]"<<endl;
        }
        //cout<<"runing 5"<<endl;
        int t_cost_ext_in_path = t_cost;
        //cout<<t_cost_ext_in_path<<" "<<m_min_hmt_path_branchbound_edge.second<<endl;
        if (t_cost_ext_in_path < m_min_hmt_path_branchbound_edge.second)
        {
            //cout<<"[2]"<<endl;
            vector< vector< int> >  t_score_ext(t_score);
            for (int i=0; i<m_node_num_; i++)
            {
                t_score_ext[ext_x][i] = INF;
                t_score_ext[i][ext_y] = INF;
            }
            t_score_ext[ext_y][ext_x] = INF;
            vector<pair<int,int > > t_is_path_ext(t_is_path );
            t_is_path_ext.push_back(ext_pair);
            //  cout<<t_is_path_ext.size()<<endl;
            // vector<int > check_path = getPath(t_is_path_ext);
            //if (check_path.size())

            HamiltonBranchPath t_branch_path;
            t_branch_path.score     = t_score_ext;
            t_branch_path.cost      = t_cost_ext_in_path;
            // cout<<t_branch_path.cost <<endl;
            t_branch_path.is_path   = t_is_path_ext;
            t_branch_path.not_path  = t_not_path;
            hmt_path_st.push(t_branch_path);
        }
//        int xxx;
//        cin>>xxx;

    }

    m_time_finish_ = clock();
    m_time_running_ = m_time_finish_  - m_time_start_;

    // hmtDFS( t_visit, t_visit_num+1,0);
    return m_value_>-1;
}

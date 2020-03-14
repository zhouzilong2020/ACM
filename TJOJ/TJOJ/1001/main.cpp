//
//  main.cpp
//  1001
//
//  Created by  周子龙 on 2020/3/14.
//  Copyright © 2020 周子龙. All rights reserved.
//

#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <stdio.h>
using namespace std;

class Solution{
public:
    void ini();
    int DFS();           //返回整个图的染色方案
    int DFS(int, int*);  //给定起点，返回该起点所在的连通分量的染色方案数量
    
private:
    int m;
    int n;
    int **G;
    int *num_method;    //各个顶点的染色方案
    
};

int Solution::DFS(int start, int *visited){
    int num_hue = num_method[start];    //染色方案个数
    int from = start;
    int flag;
    stack<int> S;
    S.push(from);
    
    while(!S.empty()){
        from = S.top();    //弹出当前顶点，向上一个顶点回溯
        flag = 0;
        for(int i = 0; i < n; i++){
            if(G[from][i] == 1 && visited[i] == 0){  //存在一条边并且未访问过该节点
                visited[i] = 1;
                S.push(i);        //父节点入站
                from = i;
                flag = 1;
                num_hue *= num_method[i];   //染色方法数目相乘
                break;            //找到第一个节点后退出查找
            }
        }
        if(flag == 0){S.pop();} //查找失败则将当前顶点弹出
    }
    return num_hue;
}

int Solution::DFS(){
    int sum = 1;
    int *visited = new int[n];
    for(int i = 0; i < n; i++){
        visited[i]=0;
    }
    for(int i = 0; i < n; i++){
        if(visited[i] == 0){
            visited[i] = 1;
            sum *= DFS(i, visited);
        }
    }
    return sum;
}

void Solution::ini(){
    int x, y;
    scanf("%d %d", &n,&m);
    G = new int*[n];
    num_method = new int[n];
    for(int i = 0; i < n; i++){
        num_method[i] = 4;           //初始化方法数目
        G[i] = new int[n];
        for(int j = 0; j < n; j++){ //初始化图
            G[i][j] =0;
        }
    }
    for(int i = 0; i < m; i++){     //输入图的边
        scanf("%d %d", &x,&y);
        x--; y--;                   //输入序号从1开始
        G[x][y] = G[y][x] = 1;
        num_method[y]--;             //顶点y的染色方法减一
    }
}


int main(int argc, const char * argv[]) {
    Solution s;
    int result = 0;
    s.ini();
    result = s.DFS();
    printf("%d", result);
    return 0;
}

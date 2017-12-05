#ifndef COMMUNITY_DETECTION_H
#define COMMUNITY_DETECTION_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <string.h>
#include <ctime>
#include <stdlib.h>
using namespace std;
int choosing(vector<vector<int>>&neighiborhood, int selected_node)//從選取點的鄰居中挑一個
{
	int pick_an_number;
	pick_an_number = rand() % neighiborhood[selected_node].size();
	return neighiborhood[selected_node][pick_an_number];
}

int* community_detection(int **A, const int NUM_NODES)//A is a adjacency matrix,
{
	//if exist edge (i,j), A[i][j]=1 otherwise A[i][j]=0
	int* ans = new int[NUM_NODES];
	time_t t = time(0);
	long int now = static_cast<long int> (t);
	srand(now);
	for (int i = 0; i < NUM_NODES; i++)//answer
	{
		ans[i] = 0;
	}

	//please write your program from here----------------------------------------------
	int most = 0;
	srand(unsigned(time(0)));
	int pickAnebr = 0;
	int *random_node_shunshi = new int[NUM_NODES];
	int part;
	int *P = new int[NUM_NODES];
	int N = 1;
	int M = 2;
	int k = -1;

	vector<vector<int>>nebr(NUM_NODES, vector<int>());//不要懷疑，nebr是鄰居
	int ** node_imformantion = new int *[NUM_NODES];//資料點現有標籤紀錄
	for (int i = 0; i < NUM_NODES; i++)
	{
		node_imformantion[i] = new int[1+(202 * NUM_NODES)];
	}


	for (int i = 0; i < NUM_NODES; i++)
	{
		for (int j = 0; j < NUM_NODES; j++)
		{
			if (i != j && A[i][j] == 1)
			{
				nebr[i].push_back(j);
			}
		}
		node_imformantion[i][0] = i;
	}
	for (int i = 0; i < NUM_NODES; i++)
		for (int j = 1; j < 1+(202 * NUM_NODES); j++)
		{
			node_imformantion[i][j] = -1;
		}

	//找尋與選取資料點相鄰之資料點順便給予咱們資料點初始標籤
	for (int rePick = 0; rePick < 202; rePick++)
	{
		for (int i = 0; i < NUM_NODES; i++)
		{
			P[i] = i;
		}
		for (int temp = 0; temp < NUM_NODES; temp++)
		{
			part = rand() % NUM_NODES;
			while (P[part] < 0)
				part = rand() % NUM_NODES;
			random_node_shunshi[temp] = P[part];
			P[part] = -1;
		}//cout << random_node[temp] << endl;
		 //隨機選取丟資料順序
		for (int times = 0; times < NUM_NODES; times++)
		{
			for (int pick_node = 0; pick_node < NUM_NODES; pick_node++)
			{
				if (!nebr[random_node_shunshi[pick_node]].empty())
				{
					pickAnebr = choosing(nebr, random_node_shunshi[pick_node]);
					k = rand() % M;
					while(node_imformantion[pickAnebr][k]==-1)
					{
						k = rand() % M;
					}
						node_imformantion[random_node_shunshi[pick_node]][N] = node_imformantion[pickAnebr][k];
					
				}
			}//選擇點收入標籤
			N++;
			M++;
		}
		
	}


	for (int i = 0; i < NUM_NODES; i++)
	{
		most = -1;
		int *count = new int[NUM_NODES];
		for (int j = 0; j < NUM_NODES; j++)
		{
			count[j] = 0;
		}
		for (int j = 0; j < 1+(202 * NUM_NODES); j++)
		{
			if (0<=node_imformantion[i][j])
			{
				count[node_imformantion[i][j]]++;
			}
			
		}
		for (int j = 0; j < NUM_NODES; j++)
		{
			if (count[j] > most)
			{
				most = count[j];
				ans[i] = j;
			}
		}
	}

	//end-------------------------------------------------------------------------------
	return ans;

}



#endif;

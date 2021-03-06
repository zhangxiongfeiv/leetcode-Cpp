//
//  174_地下城游戏.cpp
//  leetcode_cpp
//
//  Created by 飞熊 on 2020/7/12.
//  Copyright © 2020 飞熊. All rights reserved.
//

/**
一些恶魔抓住了公主（P）并将她关在了地下城的右下角。地下城是由 M x N 个房间组成的二维网格。我们英勇的骑士（K）最初被安置在左上角的房间里，他必须穿过地下城并通过对抗恶魔来拯救公主。

骑士的初始健康点数为一个正整数。如果他的健康点数在某一时刻降至 0 或以下，他会立即死亡。

有些房间由恶魔守卫，因此骑士在进入这些房间时会失去健康点数（若房间里的值为负整数，则表示骑士将损失健康点数）；其他房间要么是空的（房间里的值为 0），要么包含增加骑士健康点数的魔法球（若房间里的值为正整数，则表示骑士将增加健康点数）。

为了尽快到达公主，骑士决定每次只向右或向下移动一步。

 

编写一个函数来计算确保骑士能够拯救到公主所需的最低初始健康点数。

例如，考虑到如下布局的地下城，如果骑士遵循最佳路径 右 -> 右 -> 下 -> 下，则骑士的初始健康点数至少为 7。

-2 (K)    -3    3
-5    -10    1
10    30    -5 (P)
 

说明:

骑士的健康点数没有上限。

任何房间都可能对骑士的健康点数造成威胁，也可能增加骑士的健康点数，包括骑士进入的左上角房间以及公主被监禁的右下角房间。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/dungeon-game
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <stdio.h>
#include "vector"

using namespace std;
class Solution {
public:
    /**
     
     动态规划
     从后往前递推
     1,定义dp数组含义 dp[i][j] 表示 从 i,j步开始走到 目的地的能量值
     2,定义初始值 dp[m - 1][n - 1] 也就是目标位置，如果目标位置值 >= 1. 则 为 1。 如果目标位置值 < 0, 则为 1 - 目标位置值
     3,状态转移方程
        1,如果 i, j位置的值 > 能到达下方的能量值 或者 > 能到达右方的能量值。 则 为 1
        2,否则 i, j位置所需要的能量值为 下方和有方能量值的最小值 - 当前位置的值
     
     */
    int calculateMinimumHP(vector<vector<int>>& dungeon) {

        int m = (int)dungeon.size(), n = (int)dungeon[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, INT_MAX));
        
        dp[m - 1][n - 1] = dungeon[m - 1][n - 1] >= 0 ? 1 : 1 - dungeon[m - 1][n - 1];
        
        for (int i = m - 1; i >= 0; i --) {
            for (int j = n - 1; j >= 0; j --) {
                if (i == m - 1 && j == n - 1) continue;

                // 状态转移方程
                if ((dungeon[i][j] >= dp[i][j + 1]) || (dungeon[i][j] >= dp[i + 1][j])){
                    dp[i][j] = 1;
                }else {
                    dp[i][j] = min(dp[i][j + 1], dp[i + 1][j]) - dungeon[i][j];
                }
            }
        }
        return dp[0][0];
    }
    
    /**
     
     简化代码
     
     */
    int calculateMinimumHP1(vector<vector<int>>& dungeon) {

        int m = (int)dungeon.size(), n = (int)dungeon[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, INT_MAX));
        
        dp[m - 1][n - 1] = dungeon[m - 1][n - 1] >= 0 ? 1 : 1 - dungeon[m - 1][n - 1];
        
        for (int i = m - 1; i >= 0; i --) {
            for (int j = n - 1; j >= 0; j --) {
                if (i == m - 1 && j == n - 1) continue;
                
                dp[i][j] = max(1, min(dp[i][j + 1], dp[i + 1][j]) - dungeon[i][j]);
            }
        }
        return dp[0][0];
    }
    
};

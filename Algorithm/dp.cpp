#include <iostream>
#include <string>
#include <vector>
#include <map>

/*
 * 动态规划问题
 * 一个问题能够使用动态规划解决具有下面两个特性
 * 1) 重叠子问题
 *    和归并类似，合并子问题的结果，该问题是递归的相同子问题
 *    动态规划中将子问题的解存储在一个表中从而不用重叠的解
 *
 *    1. Memoization (Top Down)
 *    2. Tabulation (Bottom Up)
 * 2) 最优子结构
 */

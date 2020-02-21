#include <iostream>
#include<stdio.h>
#include "studentDB.h"
#include <algorithm>
#include <assert.h>



int main() {



    cop3530::bst<int, int> map;
    std::vector<std::pair<int, int>> vals = {{5, 7}, {1, 9}, {10, 10}, {0, 3}, {2, 2}, {9, 4}, {11, 5}, {4, 8}, {7, 2}, {3, 1}, {8, 2}};
    for_each(begin(vals), end(vals), [&](const auto &pair){
        map.insert(pair.first, pair.second);
    });
    assert(map.contains(5));
    map.erase(5);
    assert(map.contains(5)== false);
    std::vector<std::pair<int, int>> expected_inorder_contents = {{0, 3}, {1, 9}, {2, 2}, {3, 1}, {4, 8}, {7, 2}, {8, 2}, {9, 4}, {10, 10}, {11, 5}};
    std::vector<std::pair<int, int>> expected_preorder_contents_opt1 = {{4, 8}, {1, 9}, {0, 3}, {2, 2}, {3, 1}, {10, 10}, {9, 4}, {7, 2}, {8, 2}, {11, 5}};
    std::vector<std::pair<int, int>> expected_preorder_contents_opt2 = {{7, 2}, {1, 9}, {0, 3}, {2, 2}, {4, 8}, {3, 1}, {10, 10}, {9, 4}, {8, 2}, {11, 5}};
    assert(map.inorder_contents() == expected_inorder_contents);
    std::cout<<("Your preorder contents:");
    std::vector<std::pair<int, int>> ss =map.preorder_contents();

            assert( (map.preorder_contents() == expected_preorder_contents_opt1
            || map.preorder_contents() == expected_preorder_contents_opt2) );

    return 0;
}
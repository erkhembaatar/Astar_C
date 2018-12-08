#include <stdio.h>
//#ifndef APATH_H
#include "Apath.h"
//#endif

//为简单，干脆把把下面数组转为链表结构的数组
//约定：0是可走的，1表示障碍物不可走，2表示起点，3表示终点，4表示路径
int array[10][10] = {
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 1, 0, 3, 0, 0 },
    { 0, 0, 2, 0, 0, 1, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
    { 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

int main()
{
    int row = MAP_MAX_X, col = MAP_MAX_Y;
    printf("hello world!\n");
    LNode **map = Translate_array(array,row, col); //这里将数组的地图转为节点map的地图
    output(map,10,10);
    LinkList open_List = InitList();     //定义并初始化一个开放列表
    LinkList close_List = InitList();    //一个封闭列表
    LNode* startLNode = find_start_LNode(map, row, col);
    LNode* endLNode = find_end_LNode(map, row, col);

    LNode* curLNode = startLNode;        //当前节点=开始节点
    curLNode->G = 0;        //计算节点的三个值
    count_LNode_H(curLNode, endLNode);
    count_LNode_F(curLNode);
    push_OpenList_Node(open_List, curLNode);        //先将开始节点插入开放列表

    while (curLNode->data != 3)
    {
        //LNode *e = NULL;
        curLNode = pop_OpenList_minNode(open_List);
        insert_Into_CloseList(curLNode, close_List);
        //2、查看起点周围的点是否在开放列表里，不在加入，在检测经过该点F值是否最小等；
        check_around_curNode(curLNode, endLNode, open_List, map);
    }
    while (endLNode->path_next)
    {
        printf("x:%d---y:%d\n", endLNode->path_next->x,endLNode->path_next->y);
        endLNode->path_next = endLNode->path_next->path_next;
    }
    return 0;
}


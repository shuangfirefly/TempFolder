#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct AVLNode *Position;
typedef Position AVLTree; /* AVL树类型 */
struct AVLNode
{
    ElementType Data; /* 结点数据 */
    AVLTree Left;     /* 指向左子树 */
    AVLTree Right;    /* 指向右子树 */
    int Height;       /* 树高 */
};

int Max ( int a, int b );
AVLTree SingleRightRotation(AVLTree A);
AVLTree SingleLeftRotation ( AVLTree A );
AVLTree DoubleLeftRightRotation ( AVLTree A );
AVLTree Insert( AVLTree T, ElementType X );
int GetHeight(AVLTree T);


int main(void)
{
    AVLTree Father = NULL;
    int i=0, num[6] = {20, 15, 21, 10, 17, 16};

    for(i=0; i<sizeof(num)/sizeof(num[0]); i++)
    {
        Father = Insert(Father, num[i]);
        if(Father->Right)
            printf("\nFather->Height = %d\n", Father->Right->Data);
        else
            printf("\nFather->Right = NULL\n");
    }

    return 0;
}

int Max ( int a, int b )
{
    return a > b ? a : b;
}

AVLTree SingleRightRotation(AVLTree A)
{
    AVLTree B = A->Right;
    A->Right = B->Left;
    B->Left = A;
    A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
    B->Height = Max(GetHeight(B->Right), A->Height) + 1;

    return B;
}

AVLTree SingleLeftRotation ( AVLTree A )
{
    /* 注意：A必须有一个左子结点B */
    /* 将A与B做左单旋，更新A与B的高度，返回新的根结点B */

    AVLTree B = A->Left;
    A->Left = B->Right;
    B->Right = A;
    A->Height = Max( GetHeight(A->Left), GetHeight(A->Right) ) + 1;
    B->Height = Max( GetHeight(B->Left), A->Height ) + 1;

    return B;
}

AVLTree DoubleLeftRightRotation ( AVLTree A )
{
    /* 注意：A必须有一个左子结点B，且B必须有一个右子结点C */
    /* 将A、B与C做两次单旋，返回新的根结点C */

    /* 将B与C做右单旋，C被返回 */
    A->Left = SingleRightRotation(A->Left);
    /* 将A与C做左单旋，C被返回 */
    return SingleLeftRotation(A);
}

/*************************************/
/* 对称的右单旋与右-左双旋请自己实现 */
/*************************************/

AVLTree Insert( AVLTree T, ElementType X )
{
    int noth = 1;
    if ( !T )   /* 若插入空树，则新建包含一个结点的树 */
    {
        T = (AVLTree)malloc(sizeof(struct AVLNode));
        T->Data = X;
        T->Height = 0;
        T->Left = T->Right = NULL;
    } /* if (插入空树) 结束 */

    else if ( X < T->Data )
    {
        /* 插入T的左子树 */
        T->Left = Insert( T->Left, X);
        /* 如果需要左旋 */
        if ( GetHeight(T->Left)-GetHeight(T->Right) == 2 )
        {
            if ( X < T->Left->Data )
                T = SingleLeftRotation(T);      /* 左单旋 */
            else
                T = DoubleLeftRightRotation(T); /* 左-右双旋 */
        }
    } /* else if (插入左子树) 结束 */

    else if ( X > T->Data )
    {
        /* 插入T的右子树 */
        T->Right = Insert( T->Right, X );
        /* 如果需要右旋 */
        if ( GetHeight(T->Left)-GetHeight(T->Right) == -2 )
        {
            if ( X > T->Right->Data )
                noth=0;
            ///T = SingleRightRotation(T);     /* 右单旋 */
            else
                noth=0;
            ///T = DoubleRightLeftRotation(T); /* 右-左双旋 */
        }
    } /* else if (插入右子树) 结束 */

    /* else X == T->Data，无须插入 */

    /* 别忘了更新树高 */
    T->Height = Max( GetHeight(T->Left), GetHeight(T->Right) ) + 1;

    return T;
}

int GetHeight(AVLTree T)
{
///这个函数是我自己写的，经测试，没有问题。但是仍需要进一步验证。
    if(!T)
        return -1;  
    return T->Height;
}

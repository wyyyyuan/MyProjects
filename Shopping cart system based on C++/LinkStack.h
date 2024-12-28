#ifndef __LINKSTACK_H_
#define __LINKSTACK_H_


#include "DoubleLinkList.h"


class LinkStack
{
public:
    using ElementType = DoubleLInkList::ElementType;
    //入栈
    void Push(const ElementType& data)
    {
        list.InsertTail(data);
    }
    void Pop()
    {
        if(list.Size() == 0)
            return;
        list.RemoveByIndex(list.Size() - 1);
    }

    ElementType* GetTop()
    {
        if(list.Size() == 0)
            return nullptr;
        return list.Back();
    }

    bool IsEmpty()
    {
        return list.Size() == 0;
    }

    int Size()
    {
        return list.Size();
    }
private:
    DoubleLInkList list;
};


#endif



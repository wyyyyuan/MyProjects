#ifndef __LINKQUEUE_H_
#define __LINKQUEUE_H_

#include "DoubleLinkList.h"

class LinkQueue
{
public:
    using ElementType = DoubleLInkList::ElementType;
    void Push(const ElementType &element)
    {
        list.InsertTail(element);
    }
    void Pop()
    {
        if (list.Size() == 0)
            return;
        list.RemoveByIndex(0);
    }

    ElementType *GetFront()
    {
        if (list.Size() == 0)
            return nullptr;
        return list.Head();
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
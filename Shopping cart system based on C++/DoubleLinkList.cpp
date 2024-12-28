#include "DoubleLinkList.h"
#include <iostream>
DoubleLInkList::DoubleLInkList() : size(0)
{
    head = new Node(0);
    tail = head;
    FreePtr = nullptr;
    ShowPtr = nullptr;
}

DoubleLInkList::~DoubleLInkList()
{
    while (head != nullptr)
    {
        Node *nextNode = head->next; // 记下下一个结点
        delete head;
        head = nextNode; // 结点往后走
    }
}

void DoubleLInkList::InsertTail(const ElementType &element)
{
    Node *newNode = new Node(element);
    tail->next = newNode;
    newNode->prev = tail;
    tail = newNode;
    size++;
}

void DoubleLInkList::InsertHead(const ElementType &element)
{
    Node *newNode = new Node(element);
    newNode->next = head->next;
    newNode->prev = head;
    head->next = newNode;
    if (size != 0)
        newNode->next->prev = newNode;
    else
        tail = newNode;
    size++;
}

void DoubleLInkList::InsertByIndex(int index, const ElementType &element)
{
    if (index < 0 || index > size)
    {
        std::cerr << "插入位置非法!\n";
        return;
    }

    if (index == 0)
    {
        InsertHead(element);
        return;
    }

    if (index == size)
    {
        InsertTail(element);
        return;
    }

    // 插入到链表中间
    Node *newNode = new Node(element);
    Node *travelPoint = head->next;
    for (int i = 0; i < index - 1; i++)
    {
        travelPoint = travelPoint->next;
    }
    newNode->next = travelPoint->next; // 新节点的 next 指向当前节点的 next
    newNode->prev = travelPoint;       // 新节点的 prev 指向当前节点
    travelPoint->next->prev = newNode; // 当前节点的 next 的 prev 指向新节点
    travelPoint->next = newNode;       // 当前节点的 next 指向新节点

    size++;
}

void DoubleLInkList::RemoveByIndex(int index)
{
    if (index < 0 || index >= size)
    {
        std::cerr << "非法删除位置!\n";
        return;
    }

    Node *freeNode = nullptr;

    if (index == 0)
    {
        freeNode = head->next;       // 头节点的下一个节点
        head->next = freeNode->next; // 头节点的 next 指向删除节点的 next
        if (freeNode->next != nullptr)
        {
            freeNode->next->prev = head; // 删除节点的 next 的 prev 指向头节点
        }
        else
        {
            tail = head; // 如果删除的是唯一节点，更新 tail 为 head
        }
    }

    else if (index == size - 1)
    {
        freeNode = tail;      // 指向尾节点
        tail = tail->prev;    // 更新尾节点为前一个节点
        tail->next = nullptr; // 新尾节点的 next 设为 nullptr
    }

    // 删除中间节点
    else
    {
        Node *travelPoint = head->next;
        for (int i = 0; i < index; ++i)
        {
            travelPoint = travelPoint->next;
        }
        freeNode = travelPoint;
        travelPoint->prev->next = travelPoint->next; // 前一个节点的 next 指向要删除节点的 next
        travelPoint->next->prev = travelPoint->prev; // 后一个节点的 prev 指向要删除节点的 prev
    }

    delete freeNode;
    size--;
}

void DoubleLInkList::RemoveByElement(const ElementType &element)
{
    Node *travelPoint = head->next;
    while (travelPoint != nullptr)
    {
        if (travelPoint->data == element)
        {
            // 如果是尾节点
            if (travelPoint == tail)
            {
                tail = travelPoint->prev;
                tail->next = nullptr;
            }
            // 如果是中间节点
            else if (travelPoint->next != nullptr)
            {
                travelPoint->prev->next = travelPoint->next;
                travelPoint->next->prev = travelPoint->prev;
            }
            // 如果是唯一节点
            else
            {
                head->next = nullptr;
                tail = head;
            }
            delete travelPoint;
            size--;
            return; // 删除第一个匹配的节点后退出
        }
        travelPoint = travelPoint->next; // 继续查找下一个节点
    }
    std::cout << "未找到!\n";
}

void DoubleLInkList::show()
{
    std::cout << "size:" << size << std::endl;
    // 遍历指针
    Node *travelPoint = head->next; // 头结点不需要输出
    while (travelPoint != nullptr)
    {
        ShowPtr(travelPoint->data);
        travelPoint = travelPoint->next;
    }
    std::cout << std::endl;

    travelPoint = tail;
    while (travelPoint != head)
    {
        ShowPtr(travelPoint->data);
        travelPoint = travelPoint->prev;
    }
    std::cout << std::endl;
}


void DoubleLInkList::SetFreePtr(void (*FreePtr)(ElementType))
{
    this->FreePtr = FreePtr;
}

void DoubleLInkList::SetShowPtr(void (*ShowPtr)(ElementType))
{
    this->ShowPtr = ShowPtr;
}

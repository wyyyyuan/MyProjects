#ifndef __DOUBLELINKLIST_H_
#define __DOUBLELINKLIST_H_

#include <iostream>
class DoubleLInkList
{
public:
    using ElementType = void*;

    void SetFreePtr(void (*FreePtr)(ElementType));
    void SetShowPtr(void (*ShowPtr)(ElementType));


    DoubleLInkList();
    ~DoubleLInkList();

    //插入
    void InsertTail(const ElementType& element); //尾插
    void InsertHead(const ElementType& element); //头插
    void InsertByIndex(int index,const ElementType& elememt);//中间插入

    //删除
    void RemoveByIndex(int index);//按位置删
    void RemoveByElement(const ElementType& element);//按值删

    int Size()
    {
        return size;
    }

    ElementType* Back()
    {
        return &tail->data;
    }

    ElementType* Head()
    {
        return &head->next->data;
    }
    void show();
private:
    struct Node
    {
        Node(const ElementType& data):data(data),prev(nullptr),next(nullptr){}
        ElementType data;
        Node* next;//后置指针
        Node* prev;//前置指针
    };
    Node* head;
    Node* tail;
    int size;



    void (*FreePtr)(ElementType);
    void (*ShowPtr)(ElementType);
};



#endif
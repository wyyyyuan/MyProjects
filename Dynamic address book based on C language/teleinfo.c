#include "teleinfo.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct teleinfo
{
    ElementType *a;
    int size;
    int capacity;
};

char data[20];

AddressBook* InitTeleBook(int capacity)
{
    AddressBook  *book = (AddressBook*)malloc(sizeof(AddressBook));
    if(book == NULL)
    {
        printf("AddressBook malloc error!\n");
    }
    book->size = 0;
    book->capacity = capacity;
    book->a = (ElementType*)malloc(sizeof(ElementType)*capacity);
    if(book->a == NULL)
    {
        printf("AdressBook book malloc error!\n");
        free(book);
        return NULL;
    }
    return book;
}


void InsertTail(AddressBook *book,ElementType element)
{
    if(book->size >= book->capacity)
    {
        book->capacity *=2;
        ElementType *newPtr = realloc(book->a, sizeof(ElementType) * book->capacity);
        if(newPtr == NULL)
        {
            printf("扩容数组失败！不能进行插入\n");
            book->capacity /= 2;
            return;
        }
        book->a = newPtr;
    }

    book->a[book->size++] = element;
}

void FreeTeleBook(AddressBook *book,void(*Free)(ElementType))
{
    if(Free)
    {
        for(int i = 0;i<book->size;i++)
        {
            Free(book->a[i]);
        }
    }
    free(book->a);
    free(book);
}

void PrintTeleBook(AddressBook *book,void(*print)(int,ElementType))
{
    printf("\n联系人数量 : %d     通讯录容量 : %d\n",book->size,book->capacity);
    if(print)
    {
        for(int i = 0;i < book->size;i++)
        {
            print(i+1,book->a[i]);
        }
    }
    printf("\n");
}




AddressBook *JudgeFind(AddressBook *book,ElementType element,bool(*NameCon)(void*,void*))
{
    for(int i = 0;i < book->size;i++)
    {
        if(NameCon(book->a[i],element))
            return book->a[i];
    }
    return NULL;
}



void FindContact(AddressBook*book,void* data,bool(*Find)(void*,void*),void(*print)(int,ElementType))
{
    for(int i = 0;i < book->size;i++)
    {
        if(Find(book->a[i],data))
            print(i+1,book->a[i]);
    }
    printf("\n");
}







void RemoveByIndex(AddressBook *book,int index)
{
    if(index < 0 || index >= book->size)
    {
        printf("插入位置错误！\n");
        return;
    }
    for(int i = index;i < book->size;i++)
    {
        book->a[i] = book->a[i+1];
    }
    book->size--;
}


void RemoveContact(AddressBook *book,ElementType element,bool(*Find)(void*,void*))
{
    for(int i=0;i<book->size;i++)
    {
        if(Find(book->a[i],element))
        {
            RemoveByIndex(book,i);
            i--;
        }
    }
}


int ModifyContact(AddressBook* book, void* data, bool(*Find)(void*, void*), void(*Modify)(ElementType))
{
    int count = 0;
    for(int i = 0; i < book->size; i++)
    {
        if(Find(book->a[i], data))
        {
            Modify(book->a[i]);
            count++;
        }
    }
    return count;
}


//快速排序 : 双指针 + 递归
void FastSort(ElementType *a,int start,int end,bool(*Compare)(void*,void*))
{
    if(start >= end)  //终止条件
        return;
     int left = start;
     int right = end;
     ElementType temp = a[left]; //将最左边的值定为基准值
     while(left < right)
     {
        //右边往左动，找比基准值小的数
        while (Compare(a[right],temp) && left < right) 
            right--;
        if(left < right)
            a[left++] = a[right]; //把右边比基准值小的数扔到左边
        
        //左边往有动，找比基准值大的数
        while (Compare(temp,a[left] )&& left < right) 
            left++;
        if(left < right)
            a[right--] = a[left]; //把右边比基准值小的数扔到左边
     }
     a[left] = temp;
     FastSort(a,start,left-1,Compare);
     FastSort(a,right+1,end,Compare);
}

void sort(AddressBook *book,bool(*Compare)(void*,void*))
{
    FastSort(book->a,0,book->size-1,Compare);
}

int BinarySearch(ElementType *a,int size,void* data,bool(*compare)(void*,void*),bool(*bicompare)(void*,void*))
{
    int left = 0;
    int right = size-1;
    while(left <= right)
    {
        int mid = left + (right - left) / 2; // 防止溢出
        // int mid = (left & right) + ((left ^ right) >> 1)
        if(compare(a[mid],data))
            right = mid - 1;
        else if(bicompare(data,a[mid]))
            left = mid + 1;
        else 
            return mid;
    }
    return -1;
}


Contact* BiSort(AddressBook *book,void* data,bool(*compare)(void*,void*),bool(*bicompare)(void*,void*))
{
        if(BinarySearch(book->a,book->size,data,compare,bicompare) >= 0)
            return book->a[BinarySearch(book->a,book->size,data,compare,bicompare)];
        else 
            return NULL;
}
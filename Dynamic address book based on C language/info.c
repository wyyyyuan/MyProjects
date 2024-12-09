#include "info.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct info
{
    char *name;
    char *tele;
};


Contact* InitInfo(const char *name,const char *tele)
{
    Contact *a = (Contact*)malloc(sizeof(Contact));
    if(a == NULL)
    {
        printf("Contact malloc error!\n");
    }
    a->name = strdup(name);
    a->tele = strdup(tele);
    return a;
}  



void PrintInfo(int i,void* ptr)
{
    Contact* a = (Contact*)ptr;
    printf("\n%2d : %s,%s",i,a->name,a->tele);
}


void FreeInfo(void *ptr)
{
    Contact* a = (Contact*)ptr;
    free(a->name);
    free(a->tele);
    free(a);
}

bool IsEqual(void *p1,void *p2)
{
    Contact* ptr1 = (Contact*)p1;
    const char * ptr2 = (const char *)p2;
    return strcmp(ptr1->name,ptr2) == 0 || strcmp(ptr1->tele,ptr2) == 0;
}

bool IsNameContain(void *p1,void *p2)
{
    Contact* ptr1 = (Contact*)p1;
    const char * ptr2 = (const char *)p2;
    return strstr(ptr1->name,ptr2)  || strstr(ptr1->tele,ptr2) ;
}

void ModifyInfo(void* element)
{
    Contact* contact = (Contact*)element;
    char newName[20];
    char newTele[20];
    printf("当前联系信息: 姓名: %s, 电话: %s\n", contact->name, contact->tele);
    printf("请输入新的姓名（若不修改请按回车）: ");
    getchar();  // 吸收残留的换行符
    fgets(newName, sizeof(newName), stdin);
    newName[strcspn(newName, "\n")] = '\0'; // 移除换行符
    printf("请输入新的电话号码（若不修改请按回车）: ");
    fgets(newTele, sizeof(newTele), stdin);
    newTele[strcspn(newTele, "\n")] = '\0'; // 移除换行符
    if(strlen(newName) > 0)
    {
        free(contact->name);
        contact->name = strdup(newName);
    }
    if(strlen(newTele) > 0)
    {
        free(contact->tele);
        contact->tele = strdup(newTele);
    }
    printf("联系人信息已更新!\n");
}


bool NameGreaterSort(void* p1,void* p2)
{
    Contact* a1 = (Contact*)p1;
    Contact* a2 = (Contact*)p2;
    return strcmp(a1->name,a2->name)>0;
}


bool TeleGreaterSort(void* p1,void* p2)
{
    Contact* a1 = (Contact*)p1;
    Contact* a2 = (Contact*)p2;
    return strcmp(a1->tele,a2->tele) > 0;
}


bool BicompareContactName(void* p1,void* p2)
{
    Contact* a1 = (Contact*)p1;
    const char* a2 = (const char*)p2;
    return strcmp(a1->name,a2)>0;
}


bool BincompareNameContact(void* p1,void* p2)
{
    const char* a1 = (const char*)p1;
    Contact* a2 = (Contact*)p2;
    return strcmp(a1,a2->name)>0;
}



bool BicompareContactTele(void* p1,void* p2)
{
    Contact* a1 = (Contact*)p1;
    const char* a2 = (const char*)p2;
    return strcmp(a1->tele,a2)>0;
}


bool BincompareTeleContact(void* p1,void* p2)
{
    const char* a1 = (const char*)p1;
    Contact* a2 = (Contact*)p2;
    return strcmp(a1,a2->tele)>0;
}
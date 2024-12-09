#ifndef __INFO_H_
#define __INFO_H_

#include<stdbool.h>


struct info;
typedef struct info Contact;


Contact* InitInfo(const char *name,const char *tele);
void PrintInfo(int i,void* ptr);
void FreeInfo(void *ptr);
bool IsEqual(void *p1,void *p2);
bool IsNameContain(void *p1,void *p2);
void ModifyInfo(void* element);
bool NameGreaterSort(void* p1,void* p2);
bool TeleGreaterSort(void* p1,void* p2);
bool BicompareContactName(void* p1,void* p2);
bool BincompareNameContact(void* p1,void* p2);
bool BicompareContactTele(void* p1,void* p2);
bool BincompareTeleContact(void* p1,void* p2);
#endif
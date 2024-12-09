#ifndef __TELEINFO_H_
#define __TELEINFO_H_
#include <stdbool.h>
#include "info.h"
#define ElementType void *

struct teleinfo;
typedef struct teleinfo AddressBook;



AddressBook* InitTeleBook(int capacity);

void FreeTeleBook(AddressBook *book,void(*Free)(ElementType));
void PrintTeleBook(AddressBook *book,void(*print)(int,ElementType));
void FindContact(AddressBook*book,void* data,bool(*Find)(void*,void*),void(*print)(int,ElementType));
void RemoveByIndex(AddressBook *book,int index);
void RemoveContact(AddressBook *book,ElementType element,bool(*Find)(void*,void*));
void InsertTail(AddressBook *book,ElementType element);
AddressBook *JudgeFind(AddressBook *book,ElementType element,bool(*NameCon)(void*,void*));
int ModifyContact(AddressBook* book, void* data, bool(*Find)(void*, void*), void(*Modify)(ElementType));
void sort(AddressBook *book,bool(*Compare)(void*,void*));
Contact* BiSort(AddressBook *book,void* data,bool(*compare)(void*,void*),bool(*bicompare)(void*,void*));

#endif
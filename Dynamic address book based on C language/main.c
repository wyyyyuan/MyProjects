#include<stdio.h>
#include "info.h"
#include "teleinfo.h"

void menu()
{
    printf("\n");
    printf("  ==================通讯录=================\n");
    printf(" |1、添加联系人                            |\n");              
    printf(" |2、删除联系人(输入号码或者姓名)          |\n");
    printf(" |3、查找联系人(输入部分号码或者部分姓名)  |\n");
    printf(" |4、查找联系人(二分查找姓名)              |\n");
    printf(" |5、查找联系人(二分查找号码)              |\n");
    printf(" |6、修改联系人(输入号码或者姓名)          |\n");
    printf(" |7、显示所有联系人(按姓名排序)            |\n");
    printf(" |8、显示所有联系人(按号码排序)            |\n");
    printf(" |0、关闭通讯录                            |\n");
    printf("  =========================================\n");
    printf("请输入功能:(0-7)\n");
    printf("\n");
}



int main()
{
    AddressBook *book = InitTeleBook(10);
    char name[20];
    char tele[20];
    char element[20];
    char data[20];
    Contact *contact;
    InsertTail(book,InitInfo("张三","15139763402"));
    InsertTail(book,InitInfo("李四","17435287462"));
    InsertTail(book,InitInfo("赵六","16253537284"));
    InsertTail(book,InitInfo("王五","18921413202"));
    InsertTail(book,InitInfo("宋宋","18921413564"));
    InsertTail(book,InitInfo("我惹","13267583745"));
    InsertTail(book,InitInfo("数比","19674645635"));
    InsertTail(book,InitInfo("微软","12894733456"));
    InsertTail(book,InitInfo("推广","13455486574"));
    InsertTail(book,InitInfo("大王","17498373565"));
    sort(book,NameGreaterSort);
    printf("欢迎!\n");
    int choice;
    do
    {
        menu();
        scanf("%d",&choice);
        switch(choice)
        
        {
            case 1:
            {
                printf("请输入姓名:\n");
                scanf("%s",name);
                printf("请输入号码:\n");
                scanf("%s",tele);
                InsertTail(book,InitInfo(name,tele));
                printf("添加成功!\n");
                break;
            }
            case 2:
            {
                printf("请输入要删除的联系人姓名或者号码:\n");
                scanf("%s",element);
                RemoveContact(book,element,IsEqual);
                printf("删除成功!\n");
                break;
            }
            case 3:
            {
                int i;
                printf("请输入要查找的联系人姓名或者号码:\n");
                scanf("%s",element);
                AddressBook *a = JudgeFind(book,element,IsNameContain);
                if(a)
                {
                    printf("已找到联系人!\n");
                }
                else
                {
                    printf("未找到该联系人!\n");
                }
                FindContact(book,element,IsNameContain,PrintInfo);
                break;
            }
            case 4:
            {
                sort(book,NameGreaterSort);
                printf("请输入要查找的联系人姓名:\n");
                Contact *c;
                scanf("%s",data);
                c = BiSort(book,data,BicompareContactName,BincompareNameContact);
                if(c)
                {
                    printf("已找到联系人!\n");
                    PrintInfo(1,c);
                    printf("\n");
                }
                else 
                    printf("未找到联系人!\n");
                break;
            }
            case 5:
            {
                sort(book,TeleGreaterSort);
                printf("请输入要查找的联系人号码:\n");
                Contact *c;
                scanf("%s",data);
                c = BiSort(book,data,BicompareContactTele,BincompareTeleContact);
                if(c)
                {
                    printf("已找到联系人!\n");
                    PrintInfo(1,c);
                }
                else 
                    printf("未找到联系人!\n");
                break;
            }
            case 6:
            {  

                printf("请输入要修改的联系人姓名或者号码:\n");
                scanf("%s", element);
                int modified = ModifyContact(book, element,IsEqual,ModifyInfo);
                if(modified)
                {
                    printf("已修改 %d 个联系人。\n", modified);
                }
                else
                {
                    printf("未找到匹配的联系人。\n");  
                }
                break;

            }
            case 7:
            {
                // printf("联系人数量    通讯录容量 \n");
                sort(book,NameGreaterSort);
                PrintTeleBook(book,PrintInfo);
                break;
            }
            case 8:
            {
                // printf("联系人数量    通讯录容量 \n");
                sort(book,TeleGreaterSort);
                PrintTeleBook(book,PrintInfo);
                break;
            }
            case 0:
            {
                printf("通讯录已关闭!\n");
                break;
            }
            default:
            {
                printf("输入有误，请重新输入!\n");
                break;
            }
        }
    } while (choice!=0);
            FreeTeleBook(book,FreeInfo);

    // InsertTail(book,InitInfo("张三","18921413202"));
    // InsertTail(book,InitInfo("李四","18921413202"));
    // InsertTail(book,InitInfo("赵六","18921413202"));
    // InsertTail(book,InitInfo("王五","18921413202"));




    return 0;
}
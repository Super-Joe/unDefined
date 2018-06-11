#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_NAME 20
#define MAX_SRX 5
#define MAX_TELE 13
#define MAX_ADDR 30
#define INIT_NUM 3//初始大小
#define INC_NUM 10//每次扩容大小
#define FILENAME "contact.dat"

enum Ch
{
    EXIT,
    ADD,
    DEL,
    SEARCH,
    MODIFY,
    SHOW,
    CLEAR,
    SORT
};

typedef struct Telnote
{
    char name[MAX_NAME];
    int age;
    char sex[MAX_SRX];
    char tele[MAX_TELE];
    char addr[MAX_ADDR];
}Telnote;

typedef struct Contact
{
    struct Telnote* contact;
    int size;//实际个数
    int capacity;//容量
}Contact, *Pcon;


void print_menu();
void init_contact(Pcon pcon);
void add_contact(Pcon pcon);
void del_contact(Pcon pcon);
void search_contact(Pcon pcon);
void modify_contact(Pcon pcon);
void clear_contat(Pcon pcon);
void sort_contact(Pcon pcon);
void show_contact(Pcon con);
void save_data(Pcon pcon);

void print_menu()
{
    printf("**************************************\n");
    printf("***********1.添加联系人信息***********\n");
    printf("***********2.删除指定联系人信息*******\n");
    printf("***********3.查找指定联系人信息*******\n");
    printf("***********4.修改指定联系人信息*******\n");
    printf("***********5.显示所有联系人信息*******\n");
    printf("***********6.清空所有联系人***********\n");
    printf("***********7.以名字排序所有联系人*****\n");
    printf("***********0.*****保存并退出**********\n");
    printf("**************************************\n");
}


void check_capacity(Pcon pcon)//检查是否需要扩容
{
    if (pcon->size == pcon->capacity)
    {
        int sz = pcon->capacity + INC_NUM;

        Telnote * tmp = (Telnote *)realloc(pcon->contact, sz*sizeof(Telnote));
        //避免扩容失败，不能直接让pcon->contact接受地址 

        pcon->capacity += INC_NUM;

        if ( tmp == NULL )
        {
            printf("扩容失败");
            return;
        }
        pcon->contact = tmp;

    }
}

void _add(Pcon pcon, Telnote *p)//从文件添加一个联系人信息到内存
{
    assert(pcon);
    check_capacity(pcon);
    pcon->contact[pcon->size] = *p;
    pcon->size++;
}

void load_data(Pcon pcon)//从文件中读取数据
{
    Telnote telnote;
    FILE *pFread = fopen(FILENAME, "r");
    if (pFread == NULL)
    {
        perror("open file contact.dat for read error");
        exit(EXIT_FAILURE);
    }
    while (fread(&telnote, sizeof(Telnote), 1, pFread))
    {
        _add(pcon, &telnote);
    }
}
void save_data(Pcon pcon)//保存数据到文件中
{
    int i = 0;
    FILE *pFWrite = fopen(FILENAME, "w");

    if (pFWrite == NULL)
    {
        perror("open file contact.dat for write error");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i< pcon->size ; i++)
    {
        fwrite(&(pcon->contact[i]), sizeof(Telnote), 1, pFWrite);
    }

    free(pcon->contact);
    fclose(pFWrite);
}

void init_contact(Pcon pcon)//初始化通讯录
{
    pcon->size = 0;
    pcon->contact = (Telnote *)malloc(sizeof(Telnote)*INIT_NUM);
    memset(pcon->contact, 0, INIT_NUM * sizeof(Telnote));
    pcon->capacity = INIT_NUM;
    load_data(pcon);
}


void add_contact(Pcon pcon)//手动加入一个联系人
{
    assert(pcon);
    check_capacity(pcon);

    printf("请输入名字:>");
    scanf("%s", pcon->contact[pcon->size].name);
    printf("请输入性别:>");
    scanf("%s", pcon->contact[pcon->size].sex);
    printf("请输入年龄:>");
    scanf("%d", &(pcon->contact[pcon->size].age));
    printf("请输入电话:>");
    scanf("%s", pcon->contact[pcon->size].tele);
    printf("请输入地址:>");
    scanf("%s", pcon->contact[pcon->size].addr);
    pcon->size++;
    printf("插入成功\n");
}

static int find_entry(Pcon pcon, const char *name)//根据姓名查找联系人
{
    int i = 0;
    for (i = 0; i<pcon->size; i++)
    {
        if (strcmp(pcon->contact[i].name, name) == 0)
        {
            return i;
        }
    }
    return -1;
}
void del_contact(Pcon pcon)//删除指定姓名的联系人
{
    char find_name[MAX_NAME];
    int index = 0;
    int start = 0;
    if (pcon->size == 0)
    {
        printf("电话本已空，不能删除\n");
        return;
    }
    printf("请输入删除人的名字:>");
    scanf("%s", find_name);
    index = find_entry(pcon, find_name);
    if (index == -1)
    {
        printf("要删除的人不存在\n");
        return;
    }
    for (start = index; start <pcon->size - 1; start++)
    {
        pcon->contact[start] = pcon->contact[start + 1];
    }
    pcon->size--;
    printf("删除成功\n");
}
void show_contact(Pcon pcon)//显示全部联系人信息
{
    int i = 0;
    printf("%10s\t%5s\t%5s\t%15s\t%10s\n",
        "name", "age", "sex", "tele", "addr");
    for (i = 0; i<pcon->size; i++)
    {
        printf("%10s\t%5d\t%5s\t%15s\t%10s\n",
            pcon->contact[i].name,
            pcon->contact[i].age,
            pcon->contact[i].sex,
            pcon->contact[i].tele,
            pcon->contact[i].addr);
    }
}

void search_contact(Pcon pcon)//查找指定姓名的联系人
{
    int index = 0;
    char find_name[MAX_NAME];
    printf("请输入查找人的姓名:>");
    scanf("%s", find_name);
    index = find_entry(pcon, find_name);
    if (index == -1)
    {
        printf("查找的人不存在\n");
        return;
    }
    printf("%10s\t%5s\t%5s\t%15s\t%10s\n",
        "name", "age", "sex", "tele", "addr");
    printf("%10s\t%5d\t%5s\t%15s\t%10s\n",
        pcon->contact[index].name,
        pcon->contact[index].age,
        pcon->contact[index].sex,
        pcon->contact[index].tele,
        pcon->contact[index].addr);
}

void Swap(Telnote* telnote1, Telnote* telnote2)//一个交换函数
{
    Telnote tmp;
    tmp = *telnote1;
    *telnote1 = *telnote2;
    *telnote2 = tmp;
}

void modify_contact(Pcon pcon)//更改指定联系人的信息
{
    int index = 0;
    char find_name[MAX_NAME];
    printf("请输入要改的人的姓名:>");
    scanf("%s", find_name);
    index = find_entry(pcon, find_name);
    if (index == -1)
    {
        printf("指定修改的人不存在\n");
        return;
    }
    printf("请输入名字:>");
    scanf("%s", pcon->contact[index].name);
    printf("请输入性别:>");
    scanf("%s", pcon->contact[index].sex);
    printf("请输入年龄:>");
    scanf("%d", &(pcon->contact[index].age));
    printf("请输入电话:>");
    scanf("%s", pcon->contact[index].tele);
    printf("请输入地址:>");
    scanf("%s", pcon->contact[index].addr);
    printf("修改成功\n");
}
void clear_contat(Pcon pcon)//清空通讯录
{
    pcon->size = 0;
}
void sort_contact(Pcon pcon)//按姓名顺序排列通讯录
{
    int i = 0;
    int j = 0;
    for (i = 0; i<pcon->size - 1; i++)
    {
        for (j = 0; j<pcon->size - 1 - i; j++)
        {
            if (strcmp(pcon->contact[j].name, pcon->contact[j + 1].name) > 0)
            {
                Swap(&(pcon->contact[j]), &(pcon->contact[j + 1]));
            }
        }
    }
    printf("排序成功\n");
}

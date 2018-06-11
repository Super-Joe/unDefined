#define _CRT_SECURE_NO_WARNINGS 1

#ifndef __CONTACT_H__
#define __CONTACT_H__

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

#endif __CONTACT_H__
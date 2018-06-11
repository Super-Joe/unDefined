#include "contact.h"

void Test()
{
    int input = 10;
    Contact  my_con;
    init_contact(&my_con);
    print_menu();
    while (input)
    {
        printf("请选择(请输入数字):>");
        scanf("%d", &input);

        switch (input)
        {
        case ADD:
            add_contact(&my_con);
            break;
        case DEL:
            del_contact(&my_con);
            break;
        case SEARCH:
            search_contact(&my_con);
            break;
        case MODIFY:
            modify_contact(&my_con);
            break;
        case SHOW:
            show_contact(&my_con);
            break;
        case CLEAR:
            clear_contat(&my_con);
            break;
        case SORT:
            sort_contact(&my_con);
            break;
        case EXIT:
            save_data(&my_con);
            break;
        default:
            printf("输入有误请重新输入");
            break;
        }
    }
}
int main()
{
    Test();

    system("pause");
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

void add();
void display();
void search_modify();
void delete ();
void input();
void output();
void division1();
void division2();
void division3();
void division4();

FILE *BEX, *BCT, *CIVIL;
typedef struct
{
    char f_name[25], l_name[25], address[100], phone_no[15], bloodgroup[5], section;
    char roll[15];
    float marks[6], obt_marks, avg_marks, total_marks[6], percent;
} student;
student st;

int main()
{
    int c = 1;
    char password[10];
    char pass[] = {"123"};
    printf("\n\n\t\tplease enter the password:>  ");
    gets(password);
    if (strcmp(password, pass) == 0) /*Password Compare*/
    {

    start:
        system("cls");
        int no;
        do
        {
            system("cls");

        height:
            printf("\t\t====== 학생정보시스템 ======"); /*Menu*/
            printf("\n\n                                          ");
            printf("\n\n");
            printf("\n \t\t\t 1. 정보추가");
            printf("\n \t\t\t 2. 정보목록");
            printf("\n \t\t\t 3. 정보검색 및 수정");
            printf("\n \t\t\t 4. 정보삭제");
            printf("\n \t\t\t 5. 프로그램 종료");
            printf("\n\n");
            printf("\t\t\t 번호를 입력해 주세요.(1,2,3,4 or 5) :=> ");

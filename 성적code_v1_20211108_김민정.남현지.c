#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <string.h>

struct GradeMgt
{
    char name[10];
    int subject[5];
    //int grade[5];
};

void menu();
void inputFunc(struct GradeMgt *st);
void outputFunc(struct GradeMgt *st);
int ranking(struct GradeMgt *st, int tmp);
void modFunc(struct GradeMgt *st);
void delFunc(struct GradeMgt *st);
int searchFunc(struct GradeMgt *st);
void sortFunc(struct GradeMgt *st);

int main()
{
    struct GradeMgt st[50]; //학생 50명
    int selMenu, i, j;

    //초기화 부분
    for (i = 0; i < 50; i++)
    {
        for (j = 0; j < 5; j++) // 정렬 적용을 위해.
        {
            st[i].subject[j] = -1; // 학생 50명 성적을 -1로 초기화
        }
    }

    while (1)
    {
        system("cls");
        menu();
        printf("선택하세요 > ");
        scanf("%d", &selMenu);
        fflush(stdin);
        system("cls");
        switch (selMenu)
        {
        case 1:
            inputFunc(st);
            break;
        case 2:
            outputFunc(st);
            break;
        case 3:
            modFunc(st);
            break;
        case 4:
            delFunc(st);
            break;
        case 5:
            sortFunc(st);
            break;
        case 0:
            printf("프로그램을 종료하겠습니다.\n");
            return 0;
        default:
            break;
        }
        system("pause");
    }
    return 0;
}

void menu()
{
    printf("┏━━━━━━━━━━━━━━━━━━━┓\n");
    printf("┃  성적관리 프로그램 v4.0          ┃\n");
    printf("┃                                  ┃\n");
    printf("┃       1. 입   력                 ┃\n");
    printf("┃       2. 출   력                 ┃\n");
    printf("┃       3. 수   정                 ┃\n");
    printf("┃       4. 삭   제                 ┃\n");
    printf("┃       5. 정   렬                 ┃\n");
    printf("┃       0. 종   료                 ┃\n");
    printf("┃                                  ┃\n");
    printf("┗━━━━━━━━━━━━━━━━━━━┛\n");
}

void inputFunc(struct GradeMgt *st)
{
    int i;
    printf("----- 입력 ----- \n");
    for (i = 0; i < 50; i++)
    {
        if ((*(st + i)).subject[0] == -1)
        {
            break;
        }
    }

    printf("이름 : ");
    scanf("%s", (*(st + i)).name);
    fflush(stdin);
    printf("C 성적 : ");
    scanf("%d", &(*(st + i)).subject[0]);
    printf("JAVA 성적 : ");
    scanf("%d", &(*(st + i)).subject[1]);
    printf("논리회로 성적 : ");
    scanf("%d", &(*(st + i)).subject[2]);
    printf("이산수학 성적 : ");
    scanf("%d", &(*(st + i)).subject[3]);
    printf("운영체제 성적 : ");
    scanf("%d", &(*(st + i)).subject[4]);
    fflush(stdin);
}

void outputFunc(struct GradeMgt *st)
{
    int i, j;
    int sum = 0;
    printf("----- 출력 ----- \n");
    printf(" %8s | %6s | %4s | %8s | %8s | %8s | %8s | %5s | %4s | \n", "이름", "C 언어", "JAVA", "논리회로", "이산수학", "운영체제", "이수학점", "평균", "석차");
    for (i = 0; i < 10; i++)
    {
        if ((*(st + i)).subject[0] != -1)
        {
            sum = (*(st + i)).subject[0] + (*(st + i)).subject[1] + (*(st + i)).subject[2] + (*(st + i)).subject[3];
            printf(" %8s | %6d | %4d | %8d | %8d | %8d | %8d | %5.2f | %4d | \n", (*(st + i)).name, (*(st + i)).subject[0], (*(st + i)).subject[1], (*(st + i)).subject[2], (*(st + i)).subject[3], (*(st + i)).subject[4], sum, (float)sum / 5, ranking(st, i));
        }
    }
}

int ranking(struct GradeMgt *st, int tmp)
{
    int rank = 1;
    int i;
    float avg;
    float avg1;
    for (i = 0; i < 10; i++)
    {
        if ((*(st + i)).subject[0] != -1)
        {
            avg = (float)((*(st + i)).subject[0] + (*(st + i)).subject[1] + (*(st + i)).subject[2] + (*(st + i)).subject[3]) / 4;
            avg1 = (float)((*(st + tmp)).subject[0] + (*(st + tmp)).subject[1] + (*(st + tmp)).subject[2] + (*(st + tmp)).subject[3]) / 4;
            if (avg1 < avg)
            {
                rank++;
            }
        }
    }
    return rank;
}

void modFunc(struct GradeMgt *st)
{
    int i;

    printf("----- 수정 ----- \n");
    printf("수정 할 이름 > ");
    if ((i = searchFunc(st)) >= 0)
    {
        printf("C 언어 성적 : ");
        scanf("%d", &(*(st + i)).subject[0]);
        printf("JAVA 성적 : ");
        scanf("%d", &(*(st + i)).subject[1]);
        printf("논리회로 성적 : ");
        scanf("%d", &(*(st + i)).subject[2]);
        printf("이산수학 성적 : ");
        scanf("%d", &(*(st + i)).subject[3]);
        printf("운영체제 성적 : ");
        scanf("%d", (*(st + i)).subject[4]);
        fflush(stdin);
    }
    else
    {
        printf(" 해당 이름이 없습니다 \n");
        printf(" 메뉴로 돌아가겠습니다 \n");
    }
}

void delFunc(struct GradeMgt *st)
{
    int i, j;

    printf("----- 삭제 ----- \n");
    printf("삭제 할 이름 > ");
    if ((i = searchFunc(st)) >= 0)
    {
        for (j = 0; j < 4; j++)
        {
            (*(st + i)).subject[j] = -1;
        }
    }
    else
    {
        printf(" 해당 이름이 없습니다 \n");
        printf(" 메뉴로 돌아가겠습니다 \n");
    }
}

int searchFunc(struct GradeMgt *st)
{
    int i;
    char selName[10];

    scanf("%s", selName);
    fflush(stdin);
    for (i = 0; i < 10; i++)
    {
        if (strcmp(selName, (*(st + i)).name) == 0)
            return i;
    }
    return -1;
}

void sortFunc(struct GradeMgt *st)
{
    int i, j;
    int sum = 0, sum1 = 0, sum2 = 0;
    struct GradeMgt tmpSt;

    for (i = 0; i < 9; i++)
    {
        for (j = i + 1; j < 10; j++)
        {
            sum1 = (*(st + i)).subject[0] + (*(st + i)).subject[1] + (*(st + i)).subject[2] + (*(st + i)).subject[3];
            sum2 = (*(st + j)).subject[0] + (*(st + j)).subject[1] + (*(st + j)).subject[2] + (*(st + j)).subject[3];
            if (sum1 < sum2)
            {
                tmpSt = st[i];
                st[i] = st[j];
                st[j] = tmpSt;
            }
        }
    }

    printf("----- 정렬 ----- \n");
    printf(" %8s | %6s | %4s | %8s | %8s | %8s | %8s | %5s | %4s | \n", "이름", "C 언어", "JAVA", "논리회로", "이산수학", "운영체제", "이수학점", "평균", "석차");
    for (i = 0; i < 10; i++)
    {
        if ((*(st + i)).subject[0] != -1)
        {
            sum = (*(st + i)).subject[0] + (*(st + i)).subject[1] + (*(st + i)).subject[2] + (*(st + i)).subject[3];

            printf(" %8s | %6d | %4d | %8d | %8d | %8d | %8d | %5.2f | %4d | \n", (*(st + i)).name, (*(st + i)).subject[0], (*(st + i)).subject[1], (*(st + i)).subject[2], (*(st + i)).subject[3], (*(st + i)).subject[4], sum, (float)sum / 4, ranking(st, i));
        }
    }
}

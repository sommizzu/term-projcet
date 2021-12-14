#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <string.h>

struct Student
{
    char name[10];
    int subject[5];
    char grade[6];
    float avg;
};

void menu();
void input(struct Student *st);
void output(struct Student *st);
void update(struct Student *st);
int ranking(struct Student *st, int tmp);
void mod(struct Student *st);
void del(struct Student *st);
int search(struct Student *st);
void sort(struct Student *st);

int main()
{
    struct Student st[50]; //학생 50명
    int selMenu;

    //초기화 부분
    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 5; j++) // 정렬 적용을 위해.
        {
            st[i].subject[j] = -1; // 학생 50명 성적을 -1로 초기화
        }
    }

    while (1)
    {
        system("cls"); // 화면 지움
        menu();
        printf("선택하세요 > ");
        scanf("%d", &selMenu);
        fflush(stdin); //입력 버퍼 지움
        system("cls"); // 화면 지움
        switch (selMenu)
        {
        case 1:
            input(st);
            break;
        case 2:
            output(st);
            break;
        case 3:
            mod(st);
            break;
        case 4:
            del(st);
            break;
        case 5:
            sort(st);
            break;
        case 0:
            printf("프로그램을 종료하겠습니다.\n");
            return 0;
        default:
            break;
        }
        system("pause"); // 일시 정지
    }
    return 0;
}

void menu()
{
    printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("┃  성적관리 프로그램               ┃\n");
    printf("┃                                  ┃\n");
    printf("┃       1. 입   력                 ┃\n");
    printf("┃       2. 출   력                 ┃\n");
    printf("┃       3. 수   정                 ┃\n");
    printf("┃       4. 삭   제                 ┃\n");
    printf("┃       5. 정   렬                 ┃\n");
    printf("┃       0. 종   료                 ┃\n");
    printf("┃                                  ┃\n");
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
}

void input(struct Student *st)
{
    int i;
    printf("----- 입력 ----- \n");
    for (i = 0; i < 50; i++)
    {
        if ((*(st + i)).subject[0] == -1) // 입력해야될 위치에서 멈춤 (검사)
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
    update(st);
    fflush(stdin);
}

void output(struct Student *st)
{
    printf("----- 출력 ----- \n");
    printf(" %8s | %6s | %4s | %8s | %8s | %8s | %8s | %5s | %4s | \n", "이름", "C 언어", "JAVA", "논리회로", "이산수학",
           "운영체제", "이수학점", "평균", "석차");
    for (int i = 0; i < 50; i++)
    {
        if ((*(st + i)).subject[0] != -1)
        { // 입력된 점수만
            printf(" %8s | %6c | %4c | %8c | %8c | %8c | %8d | %5.2f | %4d | \n", (*(st + i)).name,
                   (*(st + i)).grade[0], (*(st + i)).grade[1], (*(st + i)).grade[2], (*(st + i)).grade[3],
                   (*(st + i)).grade[4], 15, (*(st + i)).avg, ranking(st, i));
        }
    }
}
void update(struct Student *st)
{
    float sum;
    for (int i = 0; i < 50; i++)
    {
        sum = 0.0;
        for (int j = 0; j < 5; j++)
        {
            switch ((*(st + i)).subject[j] / 10)
            { // 점수의 십의 자리
            case 10:
            case 9:
                (*(st + i)).grade[j] = 'A';
                sum = sum + 4.5;
                break;
            case 8:
                (*(st + i)).grade[j] = 'B';
                sum = sum + 3.5;
                break;
            case 7:
                (*(st + i)).grade[j] = 'C';
                sum = sum + 2.5;
                break;
            case 6:
                (*(st + i)).grade[j] = 'D';
                sum = sum + 1.5;
                break;
            default:
                (*(st + i)).grade[j] = 'F';
                sum = sum + 0.5;
                break;
            }

            (*(st + i)).grade[5] = '\0';      // 학점 문자열 마지막에 널값 추가
            (*(st + i)).avg = (float)sum / 5; // 평균
            ranking(st, i);
        }
    }
}

int ranking(struct Student *st, int tmp)
{
    int rank = 1;
    for (int i = 0; i < 50; i++)
    {
        if ((*(st + i)).subject[0] != -1)
        {
            float avg = (*(st + i)).avg;    // 비교 대상 (평균)
            float avg1 = (*(st + tmp)).avg; // 순위를 구할 학생의 평균
            if (avg1 < avg)
            {
                rank++; // 비교 대상 평균보다 작을 경우에만 석차 1씩 증가
            }
        }
    }
    return rank;
}

void mod(struct Student *st)
{
    printf("----- 수정 ----- \n");
    printf("수정 할 이름 > ");
    int i = search(st); // 수정할 학생의 인덱스 반환
    if (i >= 0)
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
        scanf("%d", &(*(st + i)).subject[4]);
        update(st);
        fflush(stdin); // 입력 버퍼 지움
    }
    else
    {
        printf(" 해당 이름이 없습니다 \n");
        printf(" 메뉴로 돌아가겠습니다 \n");
    }
}

void del(struct Student *st)
{
    int i, j;

    printf("----- 삭제 ----- \n");
    printf("삭제 할 이름 > ");
    if ((i = search(st)) >= 0)
    {
        for (j = 0; j < 5; j++)
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

int search(struct Student *st)
{
    int i;
    char selName[10];
    scanf("%s", selName); // 학생이름 입력
    fflush(stdin);
    for (i = 0; i < 50; i++)
    {
        if (strcmp(selName, (*(st + i)).name) == 0) // 학생이름 비교
            return i;
    }
    return -1;
}

void sort(struct Student *st)
{
    int i, j;
    float avg = 0, avg1 = 0, avg2 = 0;
    struct Student stTmp;

    for (i = 0; i < 49; i++)
    {
        for (j = i + 1; j < 50; j++)
        {
            avg1 = (*(st + i)).avg;
            avg2 = (*(st + j)).avg;
            if (avg1 < avg2)
            {
                stTmp = st[i];
                st[i] = st[j];
                st[j] = stTmp;
            }
        }
    }

    printf("----- 정렬 ----- \n");
    printf(" %8s | %6s | %4s | %8s | %8s | %8s | %8s | %5s | %4s | \n", "이름", "C 언어", "JAVA", "논리회로",
           "이산수학", "운영체제", "이수학점", "평균", "석차");
    for (i = 0; i < 50; i++)
    {
        if ((*(st + i)).subject[0] != -1)
        {
            avg = (*(st + i)).avg;

            printf(" %8s | %6c | %4c | %8c | %8c | %8c | %8d | %5.2f | %4d | \n", (*(st + i)).name, (*(st + i)).grade[0], (*(st + i)).grade[1], (*(st + i)).grade[2], (*(st + i)).grade[3],
                   (*(st + i)).grade[4], 15, (*(st + i)).avg, ranking(st, i));
        }
    }
}

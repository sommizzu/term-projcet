#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

void school();
void grade();

struct bookinfo
{
    char bkname[50];
    int bknum;
};

struct Student
{
    char name[10];
    int subject[5];
    char grade[6];
    float avg;
};

struct student
{
    int idnumber;
    char name[10];
    char address[30];
};

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
    printf("┃       6. 학적으로이동            ┃\n");
    printf("┃       7. 도서로이동              ┃\n");
    printf("┃       0. 종   료                 ┃\n");
    printf("┃                                  ┃\n");
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
}

void updateStudent(struct Student *st)
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
    updateStudent(st);
    fflush(stdin);
}

void output(struct Student *st)
{
    printf("----- 출력 ----- \n");
    printf(" %8s | %6s | %4s | %8s | %8s | %8s | %8s | %5s | %4s | \n", "이름", "C 언어", "JAVA", "논리회로", "이산수학", "운영체제", "이수학점", "평균", "석차");
    for (int i = 0; i < 50; i++)
    {
        if ((*(st + i)).subject[0] != -1)
        { // 입력된 점수만
            printf(" %8s | %6c | %4c | %8c | %8c | %8c | %8d | %5.2f | %4d | \n", (*(st + i)).name, (*(st + i)).grade[0], (*(st + i)).grade[1], (*(st + i)).grade[2], (*(st + i)).grade[3], (*(st + i)).grade[4], 15, (*(st + i)).avg, ranking(st, i));
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
        updateStudent(st);
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
    printf(" %8s | %6s | %4s | %8s | %8s | %8s | %8s | %5s | %4s | \n", "이름", "C 언어", "JAVA", "논리회로", "이산수학", "운영체제", "이수학점", "평균", "석차");
    for (i = 0; i < 50; i++)
    {
        if ((*(st + i)).subject[0] != -1)
        {
            avg = (*(st + i)).avg;

            printf(" %8s | %6c | %4c | %8c | %8c | %8c | %8d | %5.2f | %4d | \n", (*(st + i)).name, (*(st + i)).grade[0], (*(st + i)).grade[1], (*(st + i)).grade[2], (*(st + i)).grade[3], (*(st + i)).grade[4], 15, (*(st + i)).avg, ranking(st, i));
        }
    }
}

void book()
{
    struct bookinfo t[20];
    int k;
    int i;
    int q = 1;
    FILE *fp;
    char a;
    char word[100];
    int line = 0;
    char buffer[255];

    while (1)
    {
        printf("\t*******************\n");
        printf("\t* 1. 도서 목록    *\n");
        printf("\t* 2. 도서 검색    *\n");
        printf("\t* 3. 대출 현황    *\n");
        printf("\t* 4. 학적으로이동 *\n");
        printf("\t* 5. 성적으로이동 *\n");
        printf("\t* 6. 종     료   *\n");
        printf("\t******************\n");
        printf(">> ");
        scanf("%d", &k);
        switch (k)
        {

        case 1:

            fp = fopen("도서관 도서정보.txt", "r"); // 미리 정보가 저장된 파일을 찾아 열어서

            for (i = 0; i < 20; i++)

                fscanf(fp, "%d %s", &t[i].bknum, &t[i].bkname); // 정해진 형식대로 받아와 구조체에 순서대로 저장한다.

            fclose(fp);

            system("cls");
            for (i = 0; i < 20; i++)
                printf(" %d, - [책 번호 : %d]  - [책 이름 : %s] \n\n", i + 1, t[i].bknum, t[i].bkname); // 저장된 순서대로 출력

            break;

        case 2:

            (fp = fopen("도서관 도서상세정보.txt", "r"));

            printf("찾으시는 도서번호 또는 도서명을 입력해주십시오. : ");
            scanf("%s", &word); // 찾고있는 도서의 정보를 받은 후

            system("cls");
            while (fgets(buffer, 255, fp)) // buffer에 파일을 한줄씩 읽어 받은 후

            {
                line++;
                q = q + 1;
                if (strstr(buffer, word)) // 찾고있는 내용과 같은 문자열이 있는 경우 그 순서에 저장된 buffer를 출력함

                {
                    printf("찾으시는 도서의 정보는 다음과 같습니다. \n");
                    printf("%s\n", buffer);
                    q = 0;
                }
                else if (q == 20)
                {
                    printf("        \n일치하는 정보가 없습니다.\n\n");
                    q = 0;
                }
            }

            fclose(fp);
            break;

        case 3:

            (fp = fopen("도서관 시스템 정보.txt", "r"));

            printf("*학번 또는 이름을 입력해주십시오 : ");
            scanf("%s", &word);

            system("cls");
            while (fgets(buffer, 100, fp))

            {
                line++;
                q = q + 1;
                if (strstr(buffer, word)) // 현재 2번기능과 같지만 도서추가 삭제를 위해 추후 다른 방법으로 바꿀계획

                {
                    printf("- - - 학번 - - - 이름 - - - - - - 대출한 도서명(도서번호) - - - - - - - 대출현황 - - - \n\n");
                    printf("%s", buffer);
                    q = 0;
                }
                else if (q == 20)
                {
                    printf("        \n일치하는 정보가 없습니다.\n\n");
                    q = 0;
                }
            }

            fclose(fp);
            break;

        case 4:
            system("cls");
            school();
            break;
        case 5:
            system("cls");
            grade();
            break;
        }
    }
}

void grade()
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
        case 6:
            system("cls");
            school();
            break;
        case 7:
            system("cls");
            book();
            break;
        case 0:
            printf("프로그램을 종료하겠습니다.\n");
            return 0;
        default:
            break;
        }
        system("pause"); // 일시 정지
    }
}

// Start of School-related function and macros

#define MAX_STUDENTS 100
#define MAX(x, y) ((x > y) ? (x) : (y))

typedef struct _Student
{
    char name[10];
    int idnumber;
    char address[30];
} Student;

int loadStudents(FILE *fp, Student *students, int maxStudent)
{
    int studentCnt = 0;
    fseek(fp, 0, SEEK_END);
    long maxPos = ftell(fp) - 5;
    fseek(fp, 0, SEEK_SET);

    for (int i = 0; i < maxStudent; i++)
    {
        fscanf(fp, "%s %d %s", students[i].name, &students[i].idnumber, students[i].address);
        studentCnt++;
        if (ftell(fp) > maxPos)
            break;
    }
    return studentCnt;
}

void appendStudent(FILE *fp, Student *students, int studentIndex)
{
    fseek(fp, 0, SEEK_END);
    fprintf(
        fp, "%s %d %s\n",
        students[studentIndex].name,
        students[studentIndex].idnumber,
        students[studentIndex].address);
    fflush(fp);
}

void school(void)
{
    Student students[MAX_STUDENTS];
    char isHalt, nameIn[50];
    int actionNo, studentCnt = 0, idnumberIn;
    long fileSize;
    FILE *fp = fopen("학적.txt", "r+");
    if (fp == NULL)
        fp = fopen("학적.txt", "w+");
    studentCnt = loadStudents(fp, students, sizeof(students) / sizeof(students[0]));

    while (1)
    {
        printf("\t******************\n");
        printf("\t* 1.학 생  등 록 *\n");
        printf("\t* 2.학번으로조회 *\n");
        printf("\t* 3.이름으로조회 *\n");
        printf("\t* 4.학생전체목록 *\n");
        printf("\t* 5.성적으로이동 *\n");
        printf("\t* 6.도서로이동   *\n");
        printf("\t* 7.프로그램종료 *\n");
        printf("\t******************\n");
        printf(">>> ");
        fflush(stdout);
        scanf("%d", &actionNo);
        getchar();

        switch (actionNo)
        {
        case 1:
            if (studentCnt < MAX_STUDENTS)
            {
                printf("학생이름: ");
                fflush(stdout);
                gets(students[studentCnt].name);

                printf("학생학번: ");
                fflush(stdout);
                scanf("%d", &students[studentCnt].idnumber);
                getchar();

                printf("학생주소: ");
                fflush(stdout);
                gets(students[studentCnt].address);

                appendStudent(fp, students, studentCnt++);
            }
            else
            {
                printf("이미 모두 등록되었습니다.\n");
            }
            break;
        case 2:
            printf("학번: ");
            fflush(stdout);
            scanf("%d", &idnumberIn);
            getchar();
            for (int i = 0; i < studentCnt; i++)
            {
                if (idnumberIn == students[i].idnumber)
                {
                    printf("%s %d %s\n", students[i].name, students[i].idnumber, students[i].address);
                    goto END;
                }
            }
            printf("등록되지 않은 학번입니다.\n");
            break;
        case 3:
            printf("이름: ");
            fflush(stdout);
            gets(nameIn);
            for (int i = 0; i < studentCnt; i++)
            {
                if (!strcmp(nameIn, students[i].name))
                {
                    printf("%s %d %s\n", students[i].name, students[i].idnumber, students[i].address);
                    goto END;
                }
            }
            printf("등록되지 않은 이름입니다.\n");
            break;
        case 4:
            for (int i = 0; i < studentCnt; i++)
            {
                printf("%s %d %s\n", students[i].name, students[i].idnumber, students[i].address);
            }
            break;
        case 5:
            grade();
            break;
        case 6:
            system("cls");
            book();
            break;
        case 7:
            return;
        default:
            continue;
        }

    END:
        printf("[Y]계속 | [N]끝내기: ");
        fflush(stdout);
        scanf("%c", &isHalt);
        system("cls");
        if (isHalt == 'N' || isHalt == 'n')
            break;
    }
}

// End of School-related function and macros

int main()
{
    school();
}
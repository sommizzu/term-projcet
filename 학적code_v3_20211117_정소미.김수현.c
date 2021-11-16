#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    printf("%d\n", studentCnt);
    studentCnt = 2;

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
        if (isHalt == 'N' || isHalt == 'n')
            break;
    }
}

int main(int argc, char **argv)
{
    school();
    return 0;
}
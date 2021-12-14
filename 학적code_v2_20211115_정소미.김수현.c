#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct student
{
    int idnumber;
    char name[10];
    char address[30];
};
void main()
{
    struct student table[3];
    int SIZE = 0;
    char sch_name[20];
    struct student s;
    FILE *fp = NULL;
    int i, k, sch_nb;
    double sum = 0;
    char yn = NULL;
    while (1)
    {
        printf("\t******************\n");
        printf("\t* 1. *\n");
        학 생 등 록
            printf("\t* 2. *\n");
        학번으로조회
        printf("\t* 3. *\n");
        이름으로조회
        printf("\t* 4. *\n");
        학생전체목록
        printf("\t* 5. *\n");
        프로그램종료
        printf("\t******************\n");
        scanf("%d", &k);
        switch (k)
        {
        case 1:
            if (SIZE < 3)
            {
                printf(" : ");
                학생이름
                flushall();
                gets(s.name);
                printf(" : ");
                학생학번
                scanf("%d", &s.idnumber);
                printf(" : ");
                학생주소
                flushall();
                gets(s.address);
                fwrite(&s, sizeof(struct student), SIZE, fp);
                fclose(fp);
                SIZE++;
            }
            else
                printf(" .\n");
            이미 모두 등록되었습니다 break;
        case 2:
            printf(" ");
            학번을 입력하세요
                scanf("%d", &sch_nb);
            for (i = 0; i < SIZE; i++)
            {
                fread(&s, sizeof(struct student), 1, fp);
                if (s.idnumber == sch_nb)
                {
                    printf("\t :%d\n\t :%s\n\t 학번 이름 주소:%s\n\n", s.idnumber, s.name, s.address);
                    break;
                }
                if (i == SIZE - 1 && sch_nb != s.idnumber)
                {
                    printf(" .\n");
                    등록되어 있지 않는 학번입니다
                }
            }
            break;
        case 3:
            printf(" ");
            이름을 입력하세요
            flushall();
            gets(sch_name);
            for (i = 0; i < SIZE; i++)
            {
                fread(&s, sizeof(struct student), 1, fp);
                if (strcmp(s.name, sch_name) == 0)
                {
                    printf("\t :%d\n\t :%s\n\t 학번 이름 주소:%s\n\n", s.idnumber, s.name, s.address);
                    break;
                }
                if (i == SIZE - 1 && strcmp(s.name, sch_name) != 0)
                {
                    printf(" .");
                    등록되어 있지 않은 이름입니다
                }
            }
            break;
        case 4:
            for (i = 0; i < SIZE; i++)
            {
                fread(&s, sizeof(struct student), 1, fp);
                print f("\t :%d\n\ t :%s\n\t 학번 이름 주소:%s\n\n", s.idnumber, s.name, s.address);
            }
        }
        fclose(fp);
        printf("[Y] [N] ");
        계속 끝내기
        flushall();
        scanf("%c", &yn);
        if (yn == 'N' || yn == 'n')
            break;
    }
}

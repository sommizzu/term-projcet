#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int school(void);
void grade();

enum {
    BLACK,
    DARK_BLUE,
    DARK_GREEN,
    DARK_SKYBLUE,
    DARK_RED,
    DARK_VOILET,
    DAKR_YELLOW,
    GRAY,
    DARK_GRAY,
    BLUE,
    GREEN,
    SKYBLUE,
    RED,
    VIOLET,
    YELLOW,
    WHITE,
};

void setColor(unsigned short text) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text);
}

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

struct student {
    int idnumber;
    char  name[10];
    char  address[30];
};

int ranking(struct Student* st, int tmp);
int search(struct Student* st);

void menu()
{
    setColor(WHITE);
    printf("\t******************\n");
    setColor(WHITE);
    printf("\t* 1.성적 입력    *\n");
    printf("\t* 2.성적 출력    *\n");
    printf("\t* 3.성적 수정    *\n");
    printf("\t* 4.성적 삭제    *\n");
    printf("\t* 5.성적 정렬    *\n");
    setColor(YELLOW);
    printf("\t* 6.학적으로 이동*\n");
    printf("\t* 7.도서로 이동  *\n");
    setColor(RED);
    printf("\t* 0.종  료       *\n");
    setColor(WHITE);
    printf("\t******************\n");
}

void updateStudent(struct Student* st) {
    float sum;
    for (int i = 0; i < 50; i++) {
        sum = 0.0;
        for (int j = 0; j < 5; j++) {
            switch ((*(st + i)).subject[j] / 10) {      // 점수의 십의 자리
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

            (*(st + i)).grade[5] = '\0';        // 학점 문자열 마지막에 널값 추가
            (*(st + i)).avg = (float)sum / 5;   // 평균
            ranking(st, i);
        }
    }
}

void input(struct Student* st)
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

    printf("이름 : ");  scanf("%s", (*(st + i)).name);
    fflush(stdin);
    printf("C 성적 : "); scanf("%d", &(*(st + i)).subject[0]);
    printf("JAVA 성적 : "); scanf("%d", &(*(st + i)).subject[1]);
    printf("논리회로 성적 : "); scanf("%d", &(*(st + i)).subject[2]);
    printf("이산수학 성적 : "); scanf("%d", &(*(st + i)).subject[3]);
    printf("운영체제 성적 : ");  scanf("%d", &(*(st + i)).subject[4]);
    updateStudent(st);
    fflush(stdin);
}

void output(struct Student* st)
{
    printf("----- 출력 ----- \n");
    printf(" %8s | %6s | %4s | %8s | %8s | %8s | %8s | %5s | %4s | \n", "이름", "C 언어", "JAVA", "논리회로", "이산수학", "운영체제", "이수학점", "평균", "석차");
    for (int i = 0; i < 50; i++) {
        if ((*(st + i)).subject[0] != -1) {     // 입력된 점수만
            printf(" %8s | %6c | %4c | %8c | %8c | %8c | %8d | %5.2f | %4d | \n", (*(st + i)).name, (*(st + i)).grade[0], (*(st + i)).grade[1], (*(st + i)).grade[2], (*(st + i)).grade[3], (*(st + i)).grade[4], 15, (*(st + i)).avg, ranking(st, i));

        }
    }
}


int ranking(struct Student* st, int tmp)
{
    int rank = 1;
    for (int i = 0; i < 50; i++)
    {
        if ((*(st + i)).subject[0] != -1)
        {
            float avg = (*(st + i)).avg;        // 비교 대상 (평균)
            float avg1 = (*(st + tmp)).avg;     // 순위를 구할 학생의 평균
            if (avg1 < avg)
            {
                rank++;         // 비교 대상 평균보다 작을 경우에만 석차 1씩 증가
            }
        }
    }
    return rank;
}

void mod(struct Student* st)
{
    printf("----- 수정 ----- \n");
    printf("수정 할 이름 > ");
    int i = search(st);     // 수정할 학생의 인덱스 반환
    if (i >= 0)
    {
        printf("C 언어 성적 : "); scanf("%d", &(*(st + i)).subject[0]);
        printf("JAVA 성적 : "); scanf("%d", &(*(st + i)).subject[1]);
        printf("논리회로 성적 : "); scanf("%d", &(*(st + i)).subject[2]);
        printf("이산수학 성적 : "); scanf("%d", &(*(st + i)).subject[3]);
        printf("운영체제 성적 : ");  scanf("%d", &(*(st + i)).subject[4]);
        updateStudent(st);
        fflush(stdin);      // 입력 버퍼 지움
    }
    else
    {
        printf(" 해당 이름이 없습니다 \n");
        printf(" 메뉴로 돌아가겠습니다 \n");
    }
}

void del(struct Student* st)
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

int search(struct Student* st)
{
    int i;
    char selName[10];
    scanf("%s", selName);       // 학생이름 입력
    fflush(stdin);
    for (i = 0; i < 50; i++)
    {
        if (strcmp(selName, (*(st + i)).name) == 0)     // 학생이름 비교
            return i;
    }
    return -1;
}

void sort(struct Student* st)
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

            printf(" %8s | %6c | %4c | %8c | %8c | %8c | %8d | %5.2f | %4d | \n"
                , (*(st + i)).name, (*(st + i)).grade[0], (*(st + i)).grade[1], (*(st + i)).grade[2], (*(st + i)).grade[3], (*(st + i)).grade[4], 15, (*(st + i)).avg, ranking(st, i));
        }
    }
}

void book() {
    struct bookinfo* t = malloc(sizeof(struct bookinfo) * 20);
    if (t == NULL)
        return;
    int k;
    int i;
    int q = 1;
    FILE* fp;
    char a, c;
    char word[100];
    int line = 0;
    char buffer[255];

    while (1)
    {
        setColor(WHITE);
        printf("\t*******************\n");
        setColor(WHITE);
        printf("\t* 1. 도서 목록    *\n");
        printf("\t* 2. 도서 검색    *\n");
        printf("\t* 3. 대출 현황    *\n");
        setColor(YELLOW);
        printf("\t* 4. 학적으로이동 *\n");
        printf("\t* 5. 성적으로이동 *\n");
        setColor(RED);
        printf("\t* 6. 종     료   *\n");
        setColor(WHITE);
        printf("\t******************\n");
        printf(">> ");
        scanf("%d", &k);
        getchar();
        switch (k)
        {

        case 1:
        {

            fp = fopen("도서관 도서정보.txt", "r"); // 미리 정보가 저장된 파일을 찾아 엶

            for (i = 0; i < 20; i++)

                fscanf(fp, "%d %s", &t[i].bknum, &t[i].bkname); // 파일에 저장된 형식대로 읽어와 구조체에 순서대로 저장한다.

            system("cls");
            fclose(fp);

            for (i = 0; i < 20; i++)
                printf(" %d, - [책 번호 : %d]  - [책 이름 : %s] \n\n", i + 1, t[i].bknum, t[i].bkname); // 저장한 순서대로 출력

            
            goto EXIT; // 확인하였는지 판단하는 레이블로 이동
        }


        case 2:



            (fp = fopen("도서관 도서상세정보.txt", "r"));

            printf("찾으시는 도서번호 또는 도서명을 입력해주십시오. : ");
            scanf("%s", &word); // 찾고있는 도서의 정보를 받는다.

            system("cls");
            while (fgets(buffer, 255, fp)) // buffer에 파일을 한 줄씩 읽어 받아온다.

            {
                line++;

                if (strstr(buffer, word)) // buffer에 찾고있는 내용과 같은 문자열이 있는 경우 그 순서에 저장한 buffer를 출력함

                {
                    printf("찾으시는 도서의 정보는 다음과 같습니다. \n");
                    printf("%s\n", buffer);
                    q = 0;
                }
                else if (q == 1)
                {
                    printf("등록되지 않은 도서입니다.\n");
                }
            }

            fclose(fp);


            goto EXIT;


        case 3:


            (fp = fopen("도서관 시스템 정보.txt", "r"));

            printf("*학번 또는 이름을 입력해주십시오 : ");
            scanf("%s", &word); // 찾는 학생정보를 입력받음.

            system("cls");
            while (fgets(buffer, 100, fp)) // 2번기능과 동일하게 buffer와 비교후 출력함

            {
                line++;

                if (strstr(buffer, word))

                {
                    printf("- - - 학번 - - - 이름 - - - - - - 대출한 도서명(도서번호) - - - - - - - 대출현황 - - - \n\n");
                    printf("%s", buffer);
                    q = 0;
                }

            }

            fclose(fp);
            goto EXIT;

        case 4:
            system("cls");
            school();
            break;
        case 5:
            grade();
            system("cls");
            break;
        }

    EXIT:
        printf("확인하셨으면 o를 입력해주세요. \n>>>");
        scanf(" %c", &c);
        system("cls");
        if ((c == "o") || (c == "O")) {
            break;
            system("cls");
        }
    }

    free(t);
}

void grade() {
    struct Student* st = malloc(sizeof(struct Student) * 50); //학생 50명
    if (st == NULL)
        return;
    int selMenu;

    //초기화 부분
    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 5; j++)        // 정렬 적용을 위해.
        {
            st[i].subject[j] = -1; // 학생 50명 성적을 -1로 초기화
        }
    }

    while (1)
    {
        system("cls");      // 화면 지움
        menu();
        printf("선택하세요 > "); scanf("%d", &selMenu);
        fflush(stdin);      //입력 버퍼 지움
        system("cls");      // 화면 지움
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
            school();
            system("cls");
            break;
        case 7:
            book();
            system("cls");
            break;
        case 0:
            printf("프로그램을 종료하겠습니다.\n");
            return;
        default:
            break;
        }
        system("pause");       // 일시 정지
    }

    free(st);
}



#define MAX_STUDENTS 100 // 최대 입력가능 학생수
#define MAX(x, y) ((x > y) ? (x) : (y))

typedef struct _Student {
    char name[10];
    int idnumber;
    char address[30];
} Student;


int loadStudents(FILE* fp, Student* students, int maxStudent) {
    int studentCnt = 0;
    fseek(fp, 0, SEEK_END);
    long maxPos = ftell(fp) - 5;
    fseek(fp, 0, SEEK_SET);

    for (int i = 0; i < maxStudent; i++) {
        fscanf(fp, "%s %d %s", students[i].name, &students[i].idnumber, students[i].address);
        studentCnt++;
        if (ftell(fp) > maxPos)
            break;
    }
    return studentCnt;
}

void appendStudent(FILE* fp, Student* students, int studentIndex) {
    fseek(fp, 0, SEEK_END);
    fprintf(
        fp, "%s %d %s\n",
        students[studentIndex].name,
        students[studentIndex].idnumber,
        students[studentIndex].address
    );
    fflush(fp);
}


int school(void) {
    Student* students = malloc(sizeof(Student) * 100);
    if (students == NULL)
        return 1;
    char isHalt, nameIn[50];
    int actionNo, studentCnt = 0, idnumberIn;
    long fileSize;
    FILE* fp = fopen("학적.txt", "r+"); //학적 파일 염
    if (fp == NULL)
        fp = fopen("학적.txt", "w+"); //학적 피일이 없으면 생성
    studentCnt = loadStudents(fp, students, sizeof(students) / sizeof(students[0]));

    while (1) { //프로그램 반복
        setColor(WHITE);
        printf("\t******************\n");
        setColor(WHITE);
        printf("\t* 1.학 생  등 록 *\n");
        printf("\t* 2.학번으로조회 *\n");
        printf("\t* 3.이름으로조회 *\n");
        printf("\t* 4.학생전체목록 *\n");
        setColor(YELLOW);
        printf("\t* 5.성적으로이동 *\n");
        printf("\t* 6.도서로이동   *\n");
        setColor(RED);
        printf("\t* 7.프로그램종료 *\n");
        setColor(WHITE);
        printf("\t******************\n");
        printf(">>> ");
        fflush(stdout);
        scanf("%d", &actionNo); //번호 입력받아 번호에 해당하는 함수로 연결
        getchar();

        switch (actionNo) {
        case 1:
            if (studentCnt < MAX_STUDENTS) {
                printf("학생이름: ");
                fflush(stdout); //입력 버퍼 지움
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
            else { //최대 학생수가 다 채워졌면 "이미 모두 등록되었습니다."을 출력
                printf("이미 모두 등록되었습니다.\n");
            }
            break;
        case 2:
            printf("학번: "); //학번을 입력받음
            fflush(stdout);
            scanf("%d", &idnumberIn);
            getchar();
            for (int i = 0; i < studentCnt; i++) {
                if (idnumberIn == students[i].idnumber) {
                    printf("%s %d %s\n", students[i].name, students[i].idnumber, students[i].address);
                    goto END;
                }
            }
            printf("등록되지 않은 학번입니다.\n");
            break;
        case 3:
            printf("이름: "); //이름을 입력받음
            fflush(stdout);
            gets(nameIn);
            for (int i = 0; i < studentCnt; i++) {
                if (!strcmp(nameIn, students[i].name)) {
                    printf("%s %d %s\n", students[i].name, students[i].idnumber, students[i].address);
                    goto END;
                }
            }
            printf("등록되지 않은 이름입니다.\n");
            break;
        case 4:
            for (int i = 0; i < studentCnt; i++) {
                printf("%s %d %s\n", students[i].name, students[i].idnumber, students[i].address);
            }
            break;
        case 5:
            grade();
            system("cls");
            break;
        case 6:
            system("cls");
            book();
            break;
        case 7:
            return(0);
        default:
            break;
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

int main(int argc, char** argv) {
    return school();
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

switch (n)
{
case 1:

    struct bookinfo // 파일에서 도서목록을 읽어와 저장할 구조체를 만듬
    {
        char bkname[50];
        int bknum;
    };

    int main()
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
            printf("\t****************\n");
            printf("\t* 1. 도서 목록 *\n");
            printf("\t* 2. 도서 검색 *\n");
            printf("\t* 3. 대출 현황 *\n");
            printf("\t* 4. 종     료 *\n");
            printf("\t****************\n");
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

                    if (strstr(buffer, word)) // 찾고있는 내용과 같은 문자열이 있는 경우 그 순서에 저장된 buffer를 출력함

                    {
                        printf("찾으시는 도서의 정보는 다음과 같습니다. \n");
                        printf("%s\n", buffer);
                        q = 0;
                    }
                    else if (q == 1)
                    {
                        printf("일치하는 정보가 없습니다.\n");
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

                    if (strstr(buffer, word)) // 현재 2번기능과 같지만 도서추가 삭제를 위해 추후 다른 방법으로 바꿀계획

                    {
                        printf("- - - 학번 - - - 이름 - - - - - - 대출한 도서명(도서번호) - - - - - - - 대출현황 - - - \n\n");
                        printf("%s", buffer);
                        q = 0;
                    }
                }

                fclose(fp);
                break;
            }
        }
        return 0;
    }
}
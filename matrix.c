#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NORMAL 1;//정상종료
#define ABNORMAL 0;//비정상종료

/* Method Declaration */
int** create_matrix(int row, int col);
void print_matrix(int** matrix, int row, int col);
int free_matrix(int** matrix, int row, int col);
int fill_data(int** matrix, int row, int col);
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);

int Is_Initialize_a = 0;//a행렬이 초기화가 됐는지 확인하는 변수
int Is_Initialize_b = 0;//b행렬이 초기화가 됐는지 확인하는 변수

int main()
{
    char command;//메뉴선택을 위한 변수
    int row, col;//행과 열

    printf("[------- [서종원]  [2018038031] -------]\n");

    srand(time(NULL));//rand()의 시드값 설정

    printf("Input row and col : ");
    fflush(stdout);//eclipse의 scanf 오류를 해결하기 위함
    scanf("%d %d", &row, &col);
    int** matrix_a = create_matrix(row, col);//행렬 a의 공간 할당
    int** matrix_b = create_matrix(row, col);//행렬 b의 공간 할당
    int** matrix_a_t = create_matrix(col, row);//행렬 a_t의 공간 할당

    printf("Matrix Created.\n");

    if (matrix_a == NULL || matrix_b ==NULL || matrix_a_t==NULL) { return -1; }//행렬 이중포인터가 공간을 할당받지 못했다면 프로그램을 종료한다.

    do {//do while문으로 내용을 실행한 후에 조건을 확인한다.
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        fflush(stdout);//eclipse의 scanf 오류를 해결하기 위함
        scanf(" %c", &command);

        switch (command) {
        case 'z': case 'Z'://a,b행렬을 초기화한다.
            Is_Initialize_a = fill_data(matrix_a, row, col);//초기화가 정상적으로 되면 초기화가 됐는지 확인하는 변수에 NORMAL을 대입해준다
            Is_Initialize_b = fill_data(matrix_b, row, col);//초기화가 정상적으로 되면 초기화가 됐는지 확인하는 변수에 NORMAL을 대입해준다
            if (Is_Initialize_a && Is_Initialize_b)//두 행렬 모두 초기화가 됐다면 안내메시지를 출력한다.
                printf("Matrix Initialized\n");
            break;
        case 'p': case 'P'://a,b행렬을 출력한다.
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);
            break;
        case 'a': case 'A'://a+b 연산의 결과를 보여준다.
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col);
            break;
        case 's': case 'S'://a-b 연산의 결과를 보여준다.
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);
            break;
        case 't': case 'T'://a의 전치행렬 a_t를 보여준다.
            if (transpose_matrix(matrix_a, matrix_a_t, col, row)) {//transpose_matrix함수의 연산이 성공할때 NORMAL(1=ture)을 리턴받고 결과값을 출력한다.
                printf("Transpose matrix_a \n");
                printf("matrix_a\n");
                print_matrix(matrix_a_t, col, row);
            }
            break;
        case 'm': case 'M'://a행렬과 a_t행렬의 곱을 보여준다.
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            multiply_matrix(matrix_a, matrix_a_t, row, col);
            break;
        case 'q': case 'Q'://할당받은 메모리공간을 해제하고 프로그램을 종료한다.
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col);
            break;
        default://다른 키값을 입력했을때 안내메시지
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    } while (command != 'q' && command != 'Q');

    return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
    int** address;//동적할당받을 공간의 주소를 임시저장할 이중포인터 선언

    if ((row <= 0) || (col <= 0)) {//전처리검사 - row값과 col값 중 하나라도 0이하이면 잘못된 값을 입력받았다 출력하고 NULL값을 리턴한다.
        printf("wrong row and col\n");
        return NULL;
    }

    address = (int**)malloc(sizeof(int*) * row);//row의 값만큼 주소값을 저장할 공간을 할당받는다.
    for (int i = 0; i < row; i++) {
        address[i] = (int*)malloc(sizeof(int) * col);//위에서 할당받은 공간에 각각의 행의 원소들을 저장할 공간의 주소값을 저장한다.
        for (int j = 0; j < col; j++) {
            address[i][j] = -1;//행렬에 0~19의 값으로 초기화하기 전 행렬의 값을 -1로 초기화해준다.
        }
    }
    if (address == NULL) {//후처리검사 - address에 저장공간이 할당되지 않았다면 안내메시지를 출력하고 NULL값을 리턴한다.
        printf("Unable to allocate adequate space.\n");
        return NULL;
    }
    return address;//전,후처리검사를 통과하면 할당받은 주소값을 리턴한다.
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)
{
    if (!(Is_Initialize_a || Is_Initialize_b))//전처리검사 - 초기화가 진행되지 않았다면 안내메시지를 출력하고 함수가 종료된다.
        printf("It's not initialized.\n");
    else {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                printf("%5d", matrix[i][j]);//이중포인터를 배열처럼 사용하여 저장된 값 출력
            }
            printf("\n");//행 하나가 끝나면 줄바꿈을 한다.
        }
        printf("\n\n");//모든 출력이 끝나면 줄바꿈을 두번한다.
    }
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)
{
    for (int i = 0; i < row; i++) {
        if (matrix[i] == NULL) {//전처리 검사 - 매개변수로 받은 이중포인터값이 NULL이라면 안내메시지를 출력하고 ABNORMAL을 리턴한다.
            printf("Invalid value entered\n");
            return ABNORMAL;
        }
    }
    if (matrix == NULL) {//전처리 검사 - 매개변수로 받은 이중포인터값이 NULL이라면 안내메시지를 출력하고 ABNORMAL을 리턴한다.
        printf("Invalid value entered\n");
        return ABNORMAL;
    }
    for (int i = 0; i < row; i++) {//이중포인터 matrix에 저장된 단일포인터를 각각 해제한 후 NULL값으로 초기화 한다.
        free(matrix[i]);
        matrix[i] = NULL;
    }
    free(matrix);//이중포인터 matrix를 해제한다.
    matrix = NULL;//NULL값으로 초기화한다.

    if (matrix != NULL)//후처리 검사 - matrix가 제대로 해제되지 않았다면 안내메시지를 출력하고 ABNORMAL을 리턴한다.
    {
        printf("free matrix failed\n");
        return ABNORMAL;
    }
    return NORMAL;//함수가 정상적으로 종료하면 NORMAL을 리턴한다.
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)
{
    if (matrix == NULL || row <= 0 || col <= 0) {//전처리 검사 - 인수로 받은 값중 잘못된 값이 있다면 안내메시지를 출력하고 ABNORMAL을 리턴한다.
        printf("Invalid value entered");
        return ABNORMAL;
    }
    for (int i = 0; i < row; i++) {//이중포인터를 배열처럼 사용하여 각각의 행렬에 랜덤한 값을 저장한다.
        for (int j = 0; j < col; j++) {
            matrix[i][j] = rand() % 20;
        }
    }
    for (int i = 0; i < row; i++) {//후처리검사 - 행렬의 원소중 -1이 포함되어있다면 안내메시지를 출력하고 ABNORMAL을 리턴한다.
        for (int j = 0; j < col; j++) {
            if (matrix[i][j] == -1) {
                printf("Initialization failed. Please try again\n");
                return ABNORMAL;
            }
        }
    }
    return NORMAL;//초기화가 정상적으로 됐다면 NORMAL을 리턴한다.
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** result_matrix = NULL;//연산값을 저장할 행렬을 임시로 생성

    if (!(Is_Initialize_a || Is_Initialize_b)) {//전처리검사 - 초기화가 진행되지 않았다면 안내메시지를 출력하고 함수를 종료한다.
        printf("It's not initialized.\n");
        return ABNORMAL;
    }
    result_matrix = create_matrix(row, col);//전처리검사를 통과하면 행렬에 임시공간을 할당받은 후 연산을 실행한다.
    if (result_matrix == NULL) { //임시행렬 생성을 실패하면 함수를 종료한다.
        printf("Temporary matrix assignment failed\n");
        return ABNORMAL;
    }
        
    for (int i = 0; i < row; i++) {//이중포인터를 배열처럼 사용하여 각각의 행렬의 값을 서로 더한 후 저장한다.
        for (int j = 0; j < col; j++) {
            result_matrix[i][j] = matrix_a[i][j] + matrix_b[i][j];
        }
    }
    for (int i = 0; i < row; i++) {//후처리 검사 - 연산값이 38초과 0미만이라면 연산을 실패했다 판단하고 안내메시지 출력, 임시할당행렬 해제 후 함수를 종료한다.
        for (int j = 0; j < col; j++) {
            if (result_matrix[i][j] > 38 || result_matrix[i][j] < 0) {
                printf("addition_matrix failed, Please try again\n");
                free_matrix(result_matrix, row, col);//임시 할당받은 행렬을 해제한다.
                return ABNORMAL;
            }
        }
    }
    print_matrix(result_matrix, row, col);//정상적으로 연산이 됐다면 결과를 출력한다.
    free_matrix(result_matrix, row, col);//임시 할당받은 행렬을 해제한다.
    return NORMAL;//정상적으로 합산이 됐다면 NORMAL을 리턴한다.
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** result_matrix = NULL;//연산값을 저장할 행렬을 임시로 생성

    if (!(Is_Initialize_a || Is_Initialize_b)) {//전처리검사 - 초기화가 진행되지 않았다면 안내메시지를 출력하고 함수를 종료한다.
        printf("It's not initialized.\n");
        return ABNORMAL;
    }
    result_matrix = create_matrix(row, col);//전처리검사를 통과하면 행렬에 임시공간을 할당받은 후 연산을 실행한다.
    if (result_matrix == NULL) { //임시행렬 생성을 실패하면 함수를 종료한다.
        printf("Temporary matrix assignment failed\n");
        return ABNORMAL;
    }
    for (int i = 0; i < row; i++) {//이중포인터를 배열처럼 사용하여 a행렬-b행렬 연산을 실행한다.
        for (int j = 0; j < col; j++) {
            result_matrix[i][j] = matrix_a[i][j] - matrix_b[i][j];
        }
    }
    for (int i = 0; i < row; i++) {//후처리 검사 - 연산값이 19초과 -19미만이라면 연산을 실패했다 판단하고 안내메시지 출력, 임시할당행렬 해제 후 함수를 종료한다.
        for (int j = 0; j < col; j++) {
            if (result_matrix[i][j] > 19 || result_matrix[i][j] < -19) {
                printf("subtraction_matrix failed, Please try again\n");
                free_matrix(result_matrix, row, col);//임시 할당받은 행렬을 해제한다.
                return ABNORMAL;
            }
        }
    }
    print_matrix(result_matrix, row, col);//정상적으로 연산이 됐다면 결과를 출력한다.
    free_matrix(result_matrix, row, col);//임시 할당받은 행렬을 해제한다.
    return NORMAL;//정상적으로 합산이 됐다면 NORMAL을 리턴한다.
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
    if (!(Is_Initialize_a || Is_Initialize_b)) {//전처리검사 - 초기화가 진행되지 않았다면 안내메시지를 출력하고 함수를 종료한다.
        printf("It's not initialized.\n");
        return ABNORMAL;
    }
    for (int i = 0; i < col; i++) {//이중포인터를 배열처럼 사용하여 a행렬의 행과 열을 바꾼다.
        for (int j = 0; j < row; j++) {
            matrix_t[j][i] = matrix[i][j];
        }
    }
    for (int i = 0; i < col; i++) {//후처리함수 - 원래 행렬의 i,j원소와 전치행렬의 j,i원소가 같이 않다면 연산을 실패했다 판단하고 안내메시지 출력 후 함수를 종료한다.
        for (int j = 0; j < row; j++) {
            if (matrix[i][j] != matrix_t[j][i]) {
                printf("transpose_matrix failed, Please try again\n");
                return ABNORMAL;
            }
        }
    }
    printf("\n");
    return NORMAL;//정상적으로 합산이 됐다면 NORMAL을 리턴한다.
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
    int sum = 0;//원소들을 곱한 값을 더한 후 저장하는 변수
    int** result_matrix = NULL;//연산값을 저장할 행렬을 임시로 생성

    /*행렬의 곱 AB에서 A의 열과 B의 행의 수가 같아야 행렬의 곱이 성립하지만 이 함수는 행렬 a와 a의 전치행렬 a_t의 곱을 연산하기때문에 a의 열과 a_t의 행의 수는 같을 수 밖에 없다. 따라서 열과 행의 수를 비교하는 전처리검사는 불필요하다.*/
    if (!(Is_Initialize_a || Is_Initialize_b)) {//전처리검사 - 초기화가 진행되지 않았다면 안내메시지를 출력하고 함수를 종료한다.
        printf("It's not initialized.\n");
        return ABNORMAL;
    }
    result_matrix = create_matrix(row, row);//전처리검사를 통과하면 행렬에 임시공간을 할당받은 후 연산을 실행한다.
    if (result_matrix == NULL) { //임시행렬 생성을 실패하면 함수를 종료한다.
        printf("Temporary matrix assignment failed\n");
        return ABNORMAL;
    }
    for (int i = 0; i < row; i++) {//이중포인터를 배열처럼 사용하여 a행렬과 a의 전치행렬의 곱을 구한다.
        for (int j = 0; j < row; j++) {
            for (int k = 0; k < col; k++) {//a행렬의 i행의 원소들과 전치행렬의 j열의 원소들을 곱한 후에 더한다.
                sum += matrix_a[i][k] * matrix_t[k][j];
            }
            result_matrix[i][j] = sum;//더한 값을 임시행렬에 저장한다.
            sum = 0;//연산하기 위해 다시 0으로 초기화한다.
        }
    }
    for (int i = 0; i < row; i++) {//후처리검사 - 연산값이 19*19*col을 초과하고 0미만이라면 연산을 실패했다 판단하고 안내메시지 출력출력, 임시할당행렬 해제 후 함수를 종료한다.
        for (int j = 0; j < row; j++) {
            if (result_matrix[i][j] > 361 * col || result_matrix[i][j] < 0) {
                printf("transpose_matrix failed, Please try again\n");
                free_matrix(result_matrix, row, row);//임시 할당받은 행렬을 해제한다.
                return ABNORMAL;
            }
        }
    }
    print_matrix(result_matrix, row, row);//정상적으로 연산이 됐다면 결과를 출력한다.
    free_matrix(result_matrix, row, row);//임시 할당받은 행렬을 해제한다.
    return NORMAL;//정상적으로 합산이 됐다면 NORMAL을 리턴한다.
}

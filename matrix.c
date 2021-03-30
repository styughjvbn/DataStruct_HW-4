#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NORMAL 1;//��������
#define ABNORMAL 0;//����������

/* Method Declaration */
int** create_matrix(int row, int col);
void print_matrix(int** matrix, int row, int col);
int free_matrix(int** matrix, int row, int col);
int fill_data(int** matrix, int row, int col);
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);

int Is_Initialize_a = 0;//a����� �ʱ�ȭ�� �ƴ��� Ȯ���ϴ� ����
int Is_Initialize_b = 0;//b����� �ʱ�ȭ�� �ƴ��� Ȯ���ϴ� ����

int main()
{
    char command;//�޴������� ���� ����
    int row, col;//��� ��

    printf("[------- [������]  [2018038031] -------]\n");

    srand(time(NULL));//rand()�� �õ尪 ����

    printf("Input row and col : ");
    fflush(stdout);//eclipse�� scanf ������ �ذ��ϱ� ����
    scanf("%d %d", &row, &col);
    int** matrix_a = create_matrix(row, col);//��� a�� ���� �Ҵ�
    int** matrix_b = create_matrix(row, col);//��� b�� ���� �Ҵ�
    int** matrix_a_t = create_matrix(col, row);//��� a_t�� ���� �Ҵ�

    printf("Matrix Created.\n");

    if (matrix_a == NULL || matrix_b ==NULL || matrix_a_t==NULL) { return -1; }//��� ���������Ͱ� ������ �Ҵ���� ���ߴٸ� ���α׷��� �����Ѵ�.

    do {//do while������ ������ ������ �Ŀ� ������ Ȯ���Ѵ�.
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        fflush(stdout);//eclipse�� scanf ������ �ذ��ϱ� ����
        scanf(" %c", &command);

        switch (command) {
        case 'z': case 'Z'://a,b����� �ʱ�ȭ�Ѵ�.
            Is_Initialize_a = fill_data(matrix_a, row, col);//�ʱ�ȭ�� ���������� �Ǹ� �ʱ�ȭ�� �ƴ��� Ȯ���ϴ� ������ NORMAL�� �������ش�
            Is_Initialize_b = fill_data(matrix_b, row, col);//�ʱ�ȭ�� ���������� �Ǹ� �ʱ�ȭ�� �ƴ��� Ȯ���ϴ� ������ NORMAL�� �������ش�
            if (Is_Initialize_a && Is_Initialize_b)//�� ��� ��� �ʱ�ȭ�� �ƴٸ� �ȳ��޽����� ����Ѵ�.
                printf("Matrix Initialized\n");
            break;
        case 'p': case 'P'://a,b����� ����Ѵ�.
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);
            break;
        case 'a': case 'A'://a+b ������ ����� �����ش�.
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col);
            break;
        case 's': case 'S'://a-b ������ ����� �����ش�.
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);
            break;
        case 't': case 'T'://a�� ��ġ��� a_t�� �����ش�.
            if (transpose_matrix(matrix_a, matrix_a_t, col, row)) {//transpose_matrix�Լ��� ������ �����Ҷ� NORMAL(1=ture)�� ���Ϲް� ������� ����Ѵ�.
                printf("Transpose matrix_a \n");
                printf("matrix_a\n");
                print_matrix(matrix_a_t, col, row);
            }
            break;
        case 'm': case 'M'://a��İ� a_t����� ���� �����ش�.
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            multiply_matrix(matrix_a, matrix_a_t, row, col);
            break;
        case 'q': case 'Q'://�Ҵ���� �޸𸮰����� �����ϰ� ���α׷��� �����Ѵ�.
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col);
            break;
        default://�ٸ� Ű���� �Է������� �ȳ��޽���
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    } while (command != 'q' && command != 'Q');

    return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col)
{
    int** address;//�����Ҵ���� ������ �ּҸ� �ӽ������� ���������� ����

    if ((row <= 0) || (col <= 0)) {//��ó���˻� - row���� col�� �� �ϳ��� 0�����̸� �߸��� ���� �Է¹޾Ҵ� ����ϰ� NULL���� �����Ѵ�.
        printf("wrong row and col\n");
        return NULL;
    }

    address = (int**)malloc(sizeof(int*) * row);//row�� ����ŭ �ּҰ��� ������ ������ �Ҵ�޴´�.
    for (int i = 0; i < row; i++) {
        address[i] = (int*)malloc(sizeof(int) * col);//������ �Ҵ���� ������ ������ ���� ���ҵ��� ������ ������ �ּҰ��� �����Ѵ�.
        for (int j = 0; j < col; j++) {
            address[i][j] = -1;//��Ŀ� 0~19�� ������ �ʱ�ȭ�ϱ� �� ����� ���� -1�� �ʱ�ȭ���ش�.
        }
    }
    if (address == NULL) {//��ó���˻� - address�� ��������� �Ҵ���� �ʾҴٸ� �ȳ��޽����� ����ϰ� NULL���� �����Ѵ�.
        printf("Unable to allocate adequate space.\n");
        return NULL;
    }
    return address;//��,��ó���˻縦 ����ϸ� �Ҵ���� �ּҰ��� �����Ѵ�.
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)
{
    if (!(Is_Initialize_a || Is_Initialize_b))//��ó���˻� - �ʱ�ȭ�� ������� �ʾҴٸ� �ȳ��޽����� ����ϰ� �Լ��� ����ȴ�.
        printf("It's not initialized.\n");
    else {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                printf("%5d", matrix[i][j]);//���������͸� �迭ó�� ����Ͽ� ����� �� ���
            }
            printf("\n");//�� �ϳ��� ������ �ٹٲ��� �Ѵ�.
        }
        printf("\n\n");//��� ����� ������ �ٹٲ��� �ι��Ѵ�.
    }
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col)
{
    for (int i = 0; i < row; i++) {
        if (matrix[i] == NULL) {//��ó�� �˻� - �Ű������� ���� ���������Ͱ��� NULL�̶�� �ȳ��޽����� ����ϰ� ABNORMAL�� �����Ѵ�.
            printf("Invalid value entered\n");
            return ABNORMAL;
        }
    }
    if (matrix == NULL) {//��ó�� �˻� - �Ű������� ���� ���������Ͱ��� NULL�̶�� �ȳ��޽����� ����ϰ� ABNORMAL�� �����Ѵ�.
        printf("Invalid value entered\n");
        return ABNORMAL;
    }
    for (int i = 0; i < row; i++) {//���������� matrix�� ����� ���������͸� ���� ������ �� NULL������ �ʱ�ȭ �Ѵ�.
        free(matrix[i]);
        matrix[i] = NULL;
    }
    free(matrix);//���������� matrix�� �����Ѵ�.
    matrix = NULL;//NULL������ �ʱ�ȭ�Ѵ�.

    if (matrix != NULL)//��ó�� �˻� - matrix�� ����� �������� �ʾҴٸ� �ȳ��޽����� ����ϰ� ABNORMAL�� �����Ѵ�.
    {
        printf("free matrix failed\n");
        return ABNORMAL;
    }
    return NORMAL;//�Լ��� ���������� �����ϸ� NORMAL�� �����Ѵ�.
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)
{
    if (matrix == NULL || row <= 0 || col <= 0) {//��ó�� �˻� - �μ��� ���� ���� �߸��� ���� �ִٸ� �ȳ��޽����� ����ϰ� ABNORMAL�� �����Ѵ�.
        printf("Invalid value entered");
        return ABNORMAL;
    }
    for (int i = 0; i < row; i++) {//���������͸� �迭ó�� ����Ͽ� ������ ��Ŀ� ������ ���� �����Ѵ�.
        for (int j = 0; j < col; j++) {
            matrix[i][j] = rand() % 20;
        }
    }
    for (int i = 0; i < row; i++) {//��ó���˻� - ����� ������ -1�� ���ԵǾ��ִٸ� �ȳ��޽����� ����ϰ� ABNORMAL�� �����Ѵ�.
        for (int j = 0; j < col; j++) {
            if (matrix[i][j] == -1) {
                printf("Initialization failed. Please try again\n");
                return ABNORMAL;
            }
        }
    }
    return NORMAL;//�ʱ�ȭ�� ���������� �ƴٸ� NORMAL�� �����Ѵ�.
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** result_matrix = NULL;//���갪�� ������ ����� �ӽ÷� ����

    if (!(Is_Initialize_a || Is_Initialize_b)) {//��ó���˻� - �ʱ�ȭ�� ������� �ʾҴٸ� �ȳ��޽����� ����ϰ� �Լ��� �����Ѵ�.
        printf("It's not initialized.\n");
        return ABNORMAL;
    }
    result_matrix = create_matrix(row, col);//��ó���˻縦 ����ϸ� ��Ŀ� �ӽð����� �Ҵ���� �� ������ �����Ѵ�.
    if (result_matrix == NULL) { //�ӽ���� ������ �����ϸ� �Լ��� �����Ѵ�.
        printf("Temporary matrix assignment failed\n");
        return ABNORMAL;
    }
        
    for (int i = 0; i < row; i++) {//���������͸� �迭ó�� ����Ͽ� ������ ����� ���� ���� ���� �� �����Ѵ�.
        for (int j = 0; j < col; j++) {
            result_matrix[i][j] = matrix_a[i][j] + matrix_b[i][j];
        }
    }
    for (int i = 0; i < row; i++) {//��ó�� �˻� - ���갪�� 38�ʰ� 0�̸��̶�� ������ �����ߴ� �Ǵ��ϰ� �ȳ��޽��� ���, �ӽ��Ҵ���� ���� �� �Լ��� �����Ѵ�.
        for (int j = 0; j < col; j++) {
            if (result_matrix[i][j] > 38 || result_matrix[i][j] < 0) {
                printf("addition_matrix failed, Please try again\n");
                free_matrix(result_matrix, row, col);//�ӽ� �Ҵ���� ����� �����Ѵ�.
                return ABNORMAL;
            }
        }
    }
    print_matrix(result_matrix, row, col);//���������� ������ �ƴٸ� ����� ����Ѵ�.
    free_matrix(result_matrix, row, col);//�ӽ� �Ҵ���� ����� �����Ѵ�.
    return NORMAL;//���������� �ջ��� �ƴٸ� NORMAL�� �����Ѵ�.
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** result_matrix = NULL;//���갪�� ������ ����� �ӽ÷� ����

    if (!(Is_Initialize_a || Is_Initialize_b)) {//��ó���˻� - �ʱ�ȭ�� ������� �ʾҴٸ� �ȳ��޽����� ����ϰ� �Լ��� �����Ѵ�.
        printf("It's not initialized.\n");
        return ABNORMAL;
    }
    result_matrix = create_matrix(row, col);//��ó���˻縦 ����ϸ� ��Ŀ� �ӽð����� �Ҵ���� �� ������ �����Ѵ�.
    if (result_matrix == NULL) { //�ӽ���� ������ �����ϸ� �Լ��� �����Ѵ�.
        printf("Temporary matrix assignment failed\n");
        return ABNORMAL;
    }
    for (int i = 0; i < row; i++) {//���������͸� �迭ó�� ����Ͽ� a���-b��� ������ �����Ѵ�.
        for (int j = 0; j < col; j++) {
            result_matrix[i][j] = matrix_a[i][j] - matrix_b[i][j];
        }
    }
    for (int i = 0; i < row; i++) {//��ó�� �˻� - ���갪�� 19�ʰ� -19�̸��̶�� ������ �����ߴ� �Ǵ��ϰ� �ȳ��޽��� ���, �ӽ��Ҵ���� ���� �� �Լ��� �����Ѵ�.
        for (int j = 0; j < col; j++) {
            if (result_matrix[i][j] > 19 || result_matrix[i][j] < -19) {
                printf("subtraction_matrix failed, Please try again\n");
                free_matrix(result_matrix, row, col);//�ӽ� �Ҵ���� ����� �����Ѵ�.
                return ABNORMAL;
            }
        }
    }
    print_matrix(result_matrix, row, col);//���������� ������ �ƴٸ� ����� ����Ѵ�.
    free_matrix(result_matrix, row, col);//�ӽ� �Ҵ���� ����� �����Ѵ�.
    return NORMAL;//���������� �ջ��� �ƴٸ� NORMAL�� �����Ѵ�.
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
    if (!(Is_Initialize_a || Is_Initialize_b)) {//��ó���˻� - �ʱ�ȭ�� ������� �ʾҴٸ� �ȳ��޽����� ����ϰ� �Լ��� �����Ѵ�.
        printf("It's not initialized.\n");
        return ABNORMAL;
    }
    for (int i = 0; i < col; i++) {//���������͸� �迭ó�� ����Ͽ� a����� ��� ���� �ٲ۴�.
        for (int j = 0; j < row; j++) {
            matrix_t[j][i] = matrix[i][j];
        }
    }
    for (int i = 0; i < col; i++) {//��ó���Լ� - ���� ����� i,j���ҿ� ��ġ����� j,i���Ұ� ���� �ʴٸ� ������ �����ߴ� �Ǵ��ϰ� �ȳ��޽��� ��� �� �Լ��� �����Ѵ�.
        for (int j = 0; j < row; j++) {
            if (matrix[i][j] != matrix_t[j][i]) {
                printf("transpose_matrix failed, Please try again\n");
                return ABNORMAL;
            }
        }
    }
    printf("\n");
    return NORMAL;//���������� �ջ��� �ƴٸ� NORMAL�� �����Ѵ�.
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
    int sum = 0;//���ҵ��� ���� ���� ���� �� �����ϴ� ����
    int** result_matrix = NULL;//���갪�� ������ ����� �ӽ÷� ����

    /*����� �� AB���� A�� ���� B�� ���� ���� ���ƾ� ����� ���� ���������� �� �Լ��� ��� a�� a�� ��ġ��� a_t�� ���� �����ϱ⶧���� a�� ���� a_t�� ���� ���� ���� �� �ۿ� ����. ���� ���� ���� ���� ���ϴ� ��ó���˻�� ���ʿ��ϴ�.*/
    if (!(Is_Initialize_a || Is_Initialize_b)) {//��ó���˻� - �ʱ�ȭ�� ������� �ʾҴٸ� �ȳ��޽����� ����ϰ� �Լ��� �����Ѵ�.
        printf("It's not initialized.\n");
        return ABNORMAL;
    }
    result_matrix = create_matrix(row, row);//��ó���˻縦 ����ϸ� ��Ŀ� �ӽð����� �Ҵ���� �� ������ �����Ѵ�.
    if (result_matrix == NULL) { //�ӽ���� ������ �����ϸ� �Լ��� �����Ѵ�.
        printf("Temporary matrix assignment failed\n");
        return ABNORMAL;
    }
    for (int i = 0; i < row; i++) {//���������͸� �迭ó�� ����Ͽ� a��İ� a�� ��ġ����� ���� ���Ѵ�.
        for (int j = 0; j < row; j++) {
            for (int k = 0; k < col; k++) {//a����� i���� ���ҵ�� ��ġ����� j���� ���ҵ��� ���� �Ŀ� ���Ѵ�.
                sum += matrix_a[i][k] * matrix_t[k][j];
            }
            result_matrix[i][j] = sum;//���� ���� �ӽ���Ŀ� �����Ѵ�.
            sum = 0;//�����ϱ� ���� �ٽ� 0���� �ʱ�ȭ�Ѵ�.
        }
    }
    for (int i = 0; i < row; i++) {//��ó���˻� - ���갪�� 19*19*col�� �ʰ��ϰ� 0�̸��̶�� ������ �����ߴ� �Ǵ��ϰ� �ȳ��޽��� ������, �ӽ��Ҵ���� ���� �� �Լ��� �����Ѵ�.
        for (int j = 0; j < row; j++) {
            if (result_matrix[i][j] > 361 * col || result_matrix[i][j] < 0) {
                printf("transpose_matrix failed, Please try again\n");
                free_matrix(result_matrix, row, row);//�ӽ� �Ҵ���� ����� �����Ѵ�.
                return ABNORMAL;
            }
        }
    }
    print_matrix(result_matrix, row, row);//���������� ������ �ƴٸ� ����� ����Ѵ�.
    free_matrix(result_matrix, row, row);//�ӽ� �Ҵ���� ����� �����Ѵ�.
    return NORMAL;//���������� �ջ��� �ƴٸ� NORMAL�� �����Ѵ�.
}

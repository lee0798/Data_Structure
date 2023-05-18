#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_URL_LENGTH	21

// DO NOT MODIFY //
struct Node {
    char url[MAX_URL_LENGTH];
    struct Node* prev;
    struct Node* next;//����ũ�� ����Ʈ�� �� �� ���
};

typedef struct {
    struct Node* head;
    struct Node* cursor;// Ŀ���� ���� ��ġ
} BrowserHistory;
// DO NOT MODIFY //

BrowserHistory* browserHistoryCreate(char* homepage) {//�ʱ� url�� ���鶧 ��� �� �� ���ʹ� visit���
    BrowserHistory* urlhis = (BrowserHistory*)malloc(sizeof(BrowserHistory));
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    strcpy(node->url, homepage); // Ȩ�������ּҸ� url�� �����ϱ�
    urlhis->head = node;
    urlhis->cursor = node;
    node->prev = NULL;
    node->next = NULL;
    return urlhis;
}

void browserHistoryVisit(BrowserHistory* obj, char* url) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->url, url);
    if (obj->cursor->next != NULL)
    {//���� �湮 �ϸ� ������ ���Ⱑ �� ���� �ؾ��ϴϱ�
        obj->cursor->next->prev = NULL;
    }
    newNode->prev = obj->cursor;
    newNode->next = NULL;
    //�������� ����Ͻ� �� �߿� ���� �湮�� ��� ���� ��ϵ��� �� ������ �Ѵ�..
    obj->cursor->next = newNode;
    obj->cursor = newNode;// ���� ��ũ�帮��Ʈ Ȱ�� ���ο� url�����ϱ� Ŀ���� ��ġ�� visit�Լ����� ������ url�ּ��̴�.
}

char* browserHistoryBack(BrowserHistory* obj, int steps) {//���� �Լ����� obj�� ��ĭ �̵� �� �� ������ �޾ƿ´�(cmd,parm)�� ���ؼ� steps���� ���±��� forward ���Ǻ��� ���ٸ� �ݺ��� ����
    while (obj->cursor->prev != NULL && steps > 0)
    {
        obj->cursor = obj->cursor->prev;
        steps--;
    }
    return obj->cursor->url;
}

char* browserHistoryForward(BrowserHistory* obj, int steps) {//���� �Լ����� obj�� ��ĭ �̵� �� �� ������ �޾ƿ´�(cmd,parm)�� ���ؼ� steps���� ���±��� back ���Ǻ��� ���ٸ� �ݺ��� ����
    while (obj->cursor->next != NULL && steps > 0)
    {
        obj->cursor = obj->cursor->next;
        steps--;
    }
    return obj->cursor->url;
}

void browserHistoryFree(BrowserHistory* obj) {//���� �Ҵ� �ߴ� ����ü�� free�������ֱ� ���� ��ũ�� ����Ʈ���� temp������ temp free���־��� �� Ȱ���غ���
    struct Node* cur = obj->head;
    while (cur != NULL)
    {
        struct Node* temp = cur;
        cur = cur->next;
        free(temp);
    }
}

// DO NOT MODIFY //
int main() {
    int i = 0, count = 0;
    char arg1[500];
    char arg2[500];
    char cmd[100][500];
    char parm[100][500];
    char output[100][500];

    fgets(arg1, 500, stdin);//���� �Է� �ޱ�
    fgets(arg2, 500, stdin);
    arg1[strlen(arg1) - 1] = '\0';//������ ���ڿ��� NULL������ �����ν� fget�ޱ� ����
    arg2[strlen(arg2) - 1] = '\0';

    char* token = strtok(arg1, " "); // �������� ���ڿ� ������

    while (token != NULL) {
        strcpy(cmd[i], token); // ���� ���ڿ��� �迭�� �����ϱ�
        token = strtok(NULL, " ");
        i++;
    }

    count = i;

    i = 0;
    token = strtok(arg2, " "); // �������� ���ڿ� ������
    while (token != NULL) {
        strcpy(parm[i], token); // ���� ���ڿ��� �迭�� �����ϱ�
        token = strtok(NULL, " ");
        i++;
    }


    BrowserHistory* obj;
    for (i = 0; i < count; i++) {//for���� ���鼭 cmd, parm�� �迭���� ��Ʈ�� �޾ƿ� 
        if (strcmp(cmd[i], "BrowserHistory") == 0) {
            obj = browserHistoryCreate(parm[i]);
        }
        else if (strcmp(cmd[i], "visit") == 0) {
            browserHistoryVisit(obj, parm[i]);
        }
        else if (strcmp(cmd[i], "back") == 0) {
            printf("%s ", browserHistoryBack(obj, atoi(parm[i])));//atoi ���ڸ��� �̻� ���ڿ��� ���ڷ� �ٲܼ� ���� 
        }
        else if (strcmp(cmd[i], "forward") == 0) {
            printf("%s ", browserHistoryForward(obj, atoi(parm[i])));
        }
    }
    browserHistoryFree(obj);
    return 0;
}
// DO NOT MODIFY //
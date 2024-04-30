/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
} headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----[son seunghye] [2023078010]-----\n");
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
    listNode* newNode = (listNode*)malloc(sizeof(listNode));
    newNode->key = key;
    newNode->link = NULL;

    if (h->first == NULL || key < h->first->key) {
        // 리스트가 비어있거나, 새로운 키가 첫 번째 노드의 키보다 작을 경우
        newNode->link = h->first;
        h->first = newNode;
        return 0;
    }

    // 리스트를 순회하여 적절한 위치를 찾습니다.
    listNode* current = h->first;
    while (current->link != NULL && current->link->key < key) {
        current = current->link;
    }
    
    // 새로운 노드를 적절한 위치에 삽입합니다.
    newNode->link = current->link;
    current->link = newNode;
    
    return 0;
}


/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
    listNode* newNode = (listNode*)malloc(sizeof(listNode));
    newNode->key = key;
    newNode->link = NULL;

    if (h->first == NULL) {
        // 리스트가 비어있으면, 새로운 노드를 첫 번째로 추가합니다.
        h->first = newNode;
    } else {
        // 리스트를 마지막 노드까지 순회합니다.
        listNode* current = h->first;
        while (current->link != NULL) {
            current = current->link;
        }
        // 새로운 노드를 마지막 노드에 연결합니다.
        current->link = newNode;
    }

    return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
    if (h->first != NULL) {
        listNode* temp = h->first;
        h->first = h->first->link;
        free(temp);
    }
    return 0;
}



/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
    listNode* current = h->first;
    listNode* prev = NULL;

    while (current != NULL && current->key != key) {
        prev = current;
        current = current->link;
    }

    if (current != NULL) {
        if (prev == NULL) {
            h->first = current->link;
        } else {
            prev->link = current->link;
        }
        free(current);
    }

    return 0;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
    if (h->first == NULL) {
        return 0; // 리스트가 비어있으면 삭제할 것이 없습니다.
    }
    if (h->first->link == NULL) {
        // 리스트에 노드가 하나만 있을 경우
        free(h->first);
        h->first = NULL;
        return 0;
    }
    listNode* current = h->first;
    while (current->link->link != NULL) {
        current = current->link;
    }
    free(current->link);
    current->link = NULL;
    return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
    listNode* prev = NULL;
    listNode* current = h->first;
    listNode* next = NULL;

    while (current != NULL) {
        next = current->link;
        current->link = prev;
        prev = current;
        current = next;
    }

    h->first = prev; // 헤드를 새로운 첫 번째 노드로 업데이트합니다.

    return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}


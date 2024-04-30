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
	int key; // 노드의 데이터를 저장한는 변수
	struct Node* link;// 다음 노드를 가리키는 포인터

} listNode;// 노드 구조체

typedef struct Head {
	struct Node* first;// 첫번째 노드를 가리키는 포인터
} headNode;// 헤드 구조체


/* 함수 리스트 */
headNode* initialize(headNode* h);//리스트 초기화
int freeList(headNode* h);//리스트 메모리 해제

int insertFirst(headNode* h, int key);//리스트의 첫번째에 노드 추가
int insertNode(headNode* h, int key);//리스트에 key에 대한 노드 추가
int insertLast(headNode* h, int key);//리스트의 마지막에 노드 추가

int deleteFirst(headNode* h);//리스트의 첫번째 노드 삭제
int deleteNode(headNode* h, int key);//리스트에서 key에 대한 노드 삭제
int deleteLast(headNode* h);//리스트의 마지막 노드 삭제
int invertList(headNode* h);//리스트의 순서를 역순으로 재배치

void printList(headNode* h);//리스트 모든 노드 출력

int main()
{
	char command;//사용자로부터 입력 저장하는 변수
	int key;//사용자로부터 입력 받는 변수
	headNode* headnode=NULL;//리스트의 헤드를 가리키는 포인터

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
		scanf(" %c", &command);//사용자로부터 명령 입력받음

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);//리스트 초기화
			break;
		case 'p': case 'P':
			printList(headnode);//리스트 출력
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);//리스트에 key에 대한 노드 추가
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);//리스트에서 key에 대한 노드 삭제
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);//리스트의 마지막에 노드 추가
			break;
		case 'e': case 'E':
			deleteLast(headnode);//리스트의 마지막 노드 삭제
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);//리스트의 첫번재에 노드 추가
			break;
		case 't': case 'T':
			deleteFirst(headnode);//리스트의 첫번째 노드 삭제
			break;
		case 'r': case 'R':
			invertList(headnode);//리스트의 순서를 역순으로 재배치
			break;
		case 'q': case 'Q':
			freeList(headnode);//리스트 메모리 해제
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');//q나 Q가 입력될 때까지 반복

	return 1;
}
//리스트 초기화 함수
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

    // 리스트를 순회하여 적절한 위치 찾음
    listNode* current = h->first;
    while (current->link != NULL && current->link->key < key) {
        current = current->link;
    }
    
    // 새로운 노드를 적절한 위치에 삽입
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
        // 리스트가 비어있으면, 새로운 노드를 첫 번째로 추가
        h->first = newNode;
    } else {
        // 리스트를 마지막 노드까지 순회
        listNode* current = h->first;
        while (current->link != NULL) {
            current = current->link;
        }
        // 새로운 노드를 마지막 노드에 연결
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
        return 0; // 리스트가 비어있으면 삭제할 것이 없음
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

    h->first = prev; // 헤드를 새로운 첫 번째 노드로 업데이트

    return 0;
}


void printList(headNode* h) {
	int i = 0;//노드의 인덱스를 나타내는 변수
	listNode* p;//현재 노드 가리키는 포인터

	printf("\n---PRINT\n");

	if(h == NULL) {//리스트가 비어있을 경우
		printf("Nothing to print....\n");//출력할 것이 없다고 출력
		return;
	}

	p = h->first;//첫번째 노드부터 시작

	while(p != NULL) {//노드가 NULL이 될때까지 반복
		printf("[ [%d]=%d ] ", i, p->key);//노드의 인덱스와 데이터 출력
		p = p->link;//다음 노드로 이동
		i++;//인덱스 증가
	}

	printf("  items = %d\n", i);//리스트의 노드개수 출력
}


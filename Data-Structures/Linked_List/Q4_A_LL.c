//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 4 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


//////////////////////// function prototypes /////////////////////////////////////

// You should not change the prototype of this function
void moveEvenItemsToBack(LinkedList *ll);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;
	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;


	printf("1: Insert an integer to the linked list:\n");
	printf("2: Move all even integers to the back of the linked list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			moveEvenItemsToBack(&ll); // You need to code this function
			printf("The resulting linked list after moving even integers to the back of the linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void moveEvenItemsToBack(LinkedList *ll)
{
    // 리스트가 존재하지 않거나, 빈 리스트일 경우 함수 종료
    if (ll == NULL || ll->head == NULL)
        return;

    ListNode *cur = ll->head;   // 현재 순회 중인 노드를 가리키는 포인터 (초기엔 head부터)
    ListNode *prev = NULL;      // 현재 노드의 바로 이전 노드를 기억하는 포인터 (head 이전은 NULL)
    ListNode *tail = NULL;      // 리스트의 마지막 노드를 찾기 위한 포인터

    // 리스트의 마지막 노드(tail) 찾기
    while (cur != NULL) {
        tail = cur;             // tail에 현재 노드를 임시 저장
        cur = cur->next;        // 다음 노드로 이동
    }

    // tail을 찾았으니, 다시 처음부터 리스트를 순회하기 위해 cur을 초기화
    cur = ll->head;
    prev = NULL;                   // prev도 다시 초기화
	int count = ll->size; 		   // 처음에 있던 노드 개수만큼만 탐색

    while (count > 0) {
        count--;
		
        // 현재 노드가 짝수인지 확인
        if (cur->item % 2 == 0) { // 짝수인 경우
            ListNode *evenNode = cur; // 짝수 노드를 따로 저장해둠 (나중에 tail 뒤에 붙일 것)

            if (cur == ll->head) {     // 현재 노드가 head이면
                ll->head = cur->next;  // head를 다음 노드로 갱신
                cur = ll->head;        // cur도 head로 이동
            } 
			else {
                // 현재 노드가 중간 노드일 경우, 이전 노드(prev)가 다음 노드를 가리키도록 연결을 끊고 이동
                prev->next = cur->next;
                cur = cur->next;       // 다음 노드로 이동
            }

            // 짝수 노드를 리스트의 tail 뒤에 붙임
            tail->next = evenNode;     // 기존 tail의 next가 이 짝수 노드를 가리키게 함
            tail = evenNode;           // tail 포인터를 이 짝수 노드로 갱신
            tail->next = NULL;         // 새 tail의 다음은 NULL (리스트 끝이므로)
        }
        else {
            // 현재 노드가 홀수이면 위치 변경하지 않고 그대로 두고, 다음으로 넘어감
            prev = cur;               // 이전 노드를 현재로 갱신
            cur = cur->next;          // 다음 노드로 이동
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}

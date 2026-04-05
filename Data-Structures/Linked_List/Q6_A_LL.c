//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 6 */

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
int moveMaxToFront(ListNode **ptrHead);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	int c, i, j;
	c = 1;

	LinkedList ll;
	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;


	printf("1: Insert an integer to the linked list:\n");
	printf("2: Move the largest stored value to the front of the list:\n");
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
			j=insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			moveMaxToFront(&(ll.head));  // You need to code this function
			printf("The resulting linked list after moving largest stored value to the front of the list is: ");
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

////////////////////////////////////////////////////////////////////////

int moveMaxToFront(ListNode **ptrHead)
{
    /*
     * 반환 타입에 대한 말이 없는데... 왜 int지? 그냥 Max 값 반환한다고 생각하기
     * 이것도 3번 문제처럼 그냥 한번 추가,삭제시키면 됨. - 아 근데 포인터 타입이 ptrHead네
     * 기존 함수 못쓰는 문제가 있다는게 이런말이였네
     * 그러면 그냥 쭉 읽으면서 max와 max_prev 기억해두고 끝까지 가고 나서 갈아끼우면 되는거 아닌가?
     * 문제는 max_prev가 없는 경우? 이러면 NULL로 두고 걍 prev 연결하는 과정 건너뛰면 됨.
     * --------------
     * 아닌가? 2중이면 이거 배열인건가? 그건 아닌거 같은데? 왜 굳이 node가 아닌 node 포인터를 타입으로 받는거지?
     * 구조체 포인터를 포인터로 넘겨줄라는거 같은데, 뭔가 명확하게 이해가 안가네
     * 아 근데 맨 뒤로 보내는줄 잘못 알고 풀었네;;;
     *
     * 포인터가 넘 많은데... 풀긴 풀었음
     * 2중 포인터를 쓰는 이유는 ListNode* 를 바라보는 포인터가 필요함.
     * 왜냐면 지금 보는 head가 바뀌는게 확정이라서 새롭게 바뀐 head를 기준으로 보려면 ListNode*를 바라보는 포인터가 필요함.
     * 안그러면 이전 head인 중간 위치부터 읽게 되기 때문에...
     *
     * 1차 개선
     * 9 -> 3 -> 1일 떄 무한루프 도는거 확인
     * 맨 앞이 max일 때 max->next 설정이 항상 실행됨. 같으면 안되게 막음.
     * return 값 정의는 과제 요구사항에 없긴 한데, 그냥 max 값 반환하게 함.
     */

	if (*ptrHead == NULL) {
		return -1;
	}

	// 포인터는 초기 값 세팅
	ListNode* head = *ptrHead;
	ListNode* curr = head;
	ListNode* max = curr;
	ListNode* max_prev = NULL;
	while (curr->next != NULL) {
		if (curr->next->item > max->item) {
			max = curr->next;
			max_prev = curr;
		}
		curr = curr->next;
	}

	if (max_prev != NULL) {
		max_prev->next = max->next;
	}
	if (max != head) {
		max->next = head;
	}
	*ptrHead = max;

	return max->item;
}

//////////////////////////////////////////////////////////////////////////////////

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

ListNode * findNode(LinkedList *ll, int index){

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

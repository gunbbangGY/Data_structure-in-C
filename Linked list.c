#include <stdio.h>
#include <stdlib.h>
typedef int element;
typedef struct ListNode {
	element data;
	struct ListNode* link;
} ListNode;
typedef struct Array {
	int size;
	struct ListNode* link;
} Array;
Array* Make_Array(void) {
	Array *a = (Array*)malloc(sizeof(Array));
	a->size = 0;
	return a;
}
void Delete_Array(Array *a){
	if (a == NULL) {
		printf("존재하지 않는 집합\n");
		return;
	}
	ListNode *removed = a->link;
	for(int i=0; i<a->size; i++){
		ListNode *p = removed->link;
		free(removed);
		removed = p;
	}
	free(a);
	return;
}
int Is_Member(Array *a, element member) {
	if (a == NULL) {
		printf("존재하지 않는 집합\n");
		return NULL;
	}
	ListNode* p = a->link;
	for (int i = 0; i < a->size; i++) {
		if (p->data == member) {
			break;
			return 1;
		}
		p = p->link;
	}
	return a;
}
Array* Insert_mem(Array *a, element member) {
	if (a == NULL) {
		printf("존재하지 않는 집합\n");
		return NULL;
	}
	if (Is_Member(a, member)) {
		return a;
	}
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	if (a->size == 0) {
		p->data = member;
		p->link = NULL;
		a->link = p;
		a->size++;
		return a;
	}
	p->data = member;
	p->link = a->link;
	a->link = p;
	a->size++;
	return a;
}
Array* Delete_mem(Array *a, element member) {
	if (a == NULL) {
		printf("존재하지 않는 집합\n");
		return NULL;
	}
	if (!Is_Member(a, member)) return a;
	ListNode* removed = a->link;
	ListNode* pre = NULL;
	for (int i = 0; i < a->size; i++) {
		if (removed->data == member) {
			if (pre == NULL) a->link = removed->link;
			else pre->link = removed->link;
			free(removed);
			return a;
		}
		pre = removed;
		removed = removed->link;
	}
	a->size--;
	return a;
}
Array* Union_Array(Array *a1, Array *a2, Array *a3) {
	if (a1 == NULL || a2 == NULL) {
		printf("존재하지 않는 집합\n");
		return NULL;
	}
	ListNode *p = a1->link;
	while (p != NULL) {
		Insert_mem(a3, p->data);
		p = p->link;
	}
	p = a2->link;
	while (p != NULL) {
		if (!Is_Member(a1, p->data)) Insert_mem(a3, p->data);
		p = p->link;
	}
	return a3;
}
Array* Intersection_Array(Array *a1, Array* a2, Array* a3){
	if (a1 == NULL || a2 == NULL) {
		printf("존재하지 않는 집합\n");
		return 0;
	}
	ListNode *p = a1->link;
	while (p != NULL) {
		if (Is_Member(a2, p->data)) {
			Insert_mem(a3, p->data);
		}
	p = p->link;
	}
	return a3;
}
Array* Subtraction_Array(Array* a1, Array* a2, Array* a3) {
	if (a1 == NULL || a2 == NULL) {
		printf("존재하지 않는 집합\n");
		return 0;
	}
	ListNode* p = a1->link;
	while (p != NULL) {
		if (!Is_Member(a2, p->data)) {
			Insert_mem(a3, p->data);
		}
		p = p->link;
	}
	return a3;
}
void print_array(Array *a){
	ListNode* p = a->link;
	while(p!=NULL){
		if (a->link == NULL) return;
		printf("%d->", p->data);
		p = p->link;
	}
	printf("\n");
}
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

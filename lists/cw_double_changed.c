#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct sample {
	time_t timestamp;
	double value;
	struct sample *next;
	struct sample *prev;
};
struct sample *head, *tail;

void print_list(struct sample *head) {
	// iterate through list
	for (struct sample *s = head; s; s = s->next) {
		printf("registered event at %lld: %f\n", (long long)s->timestamp, s->value);
	}
	puts("");
}

void print_list_reversed(struct sample *tail) {	
	// iterate through list
	for (struct sample *s = tail; s; s = s->prev) {
		printf("registered event at %lld: %f\n", (long long)s->timestamp, s->value);
	}
	puts("");
}

int delete_item(struct sample *item_to_delete) {
	if (item_to_delete->next)
		item_to_delete->next->prev = item_to_delete->prev;
	if (item_to_delete->prev)
		item_to_delete->prev->next = item_to_delete->next;

	if (item_to_delete == head)
		head = item_to_delete->next;
	if (item_to_delete == tail)
		tail = item_to_delete->prev;

	free(item_to_delete);
	return 1;
}

int insert_item(struct sample *item_to_insert, struct sample *previous) {
	for (struct sample *compare = head; compare; compare = compare->next) {
		if (compare == item_to_insert) {
        	return 0;//fail
    	}
	}

	if (previous == NULL) {//вставка в начало 
		head->prev = item_to_insert;
		item_to_insert->next = head;
		head = item_to_insert;
	} else {
		if (previous->next == NULL) {//вставка в конец
			previous->next = item_to_insert;
			item_to_insert->next = NULL;
			item_to_insert->prev = previous;
			tail = item_to_insert;			
		}
		else {//вставка в середину 
			
			previous->next->prev = item_to_insert;
			item_to_insert->prev = previous;
			item_to_insert->next = previous->next;
			previous->next = item_to_insert;
			
			
		}
	}

	return 1;
}

int main(int argc, char **argv) {
	struct sample *s1 = malloc(sizeof(struct sample));
	s1->timestamp = 12345678;
	s1->value = 123;

	struct sample *s2 = malloc(sizeof(struct sample));
	s2->timestamp = 12345978;
	s2->value = 234;

	head = s1;
	s1->prev = NULL;
	s1->next = s2;
	s2->prev = s1;
	s2->next = NULL;
	tail = s2;

	print_list(head);

	//data for check 
	struct sample *s12 = malloc(sizeof(struct sample));
	s12->timestamp = 1212121212;
	s12->value = 1212;

	struct sample *s3 = malloc(sizeof(struct sample));
	s3->timestamp = 3333333333;
	s3->value = 3333;

	struct sample *s4 = malloc(sizeof(struct sample));
	s4->timestamp = 4444444444;
	s4->value = 4444;

	insert_item(s12, s1);//middle
	insert_item(s3, NULL);//front
	insert_item(s4, s2);//back

	print_list(head);
	print_list_reversed(tail);

	//functions for check
	
	delete_item(head);
	print_list(head);
	print_list_reversed(tail);

	delete_item(tail);
	print_list(head);
	print_list_reversed(tail);

	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct sample {
	time_t timestamp;
	double value;
};

struct item {
	struct sample *data;
	struct item *next;
	struct item *prev;
};

struct item *head, *tail;

void print_item(struct item *item_to_print) {
    printf("registered event at %lld: %f\n", (long long)item_to_print->data->timestamp, item_to_print->data->value);
}

void print_list(struct item *head) {
	// iterate through list
	for (struct item *it = head; it; it = it->next) {
		print_item(it);
	}
	puts("");
}

void print_list_reversed(struct item *tail) {	// TODO
	// iterate through list
	for (struct item *it = tail; it; it = it->prev) {
		print_item(it);
	}
	puts("");
}

int delete_item(struct item *item_to_delete) {
	if (item_to_delete->next)
		item_to_delete->next->prev = item_to_delete->prev;
	if (item_to_delete->prev)
		item_to_delete->prev->next = item_to_delete->next;

	if (item_to_delete == head)
		head = item_to_delete->next;
	if (item_to_delete == tail)
		tail = item_to_delete->prev;

	return 1;
}

int delete_list_to_end(struct item *item_to_delete_from) {
	for (struct item *it = item_to_delete_from; it; it = it->next) {
		delete_item(it);
	}
	return 1;
}

int delete_list_to_begin(struct item *item_to_delete_from) {
	for (struct item *it = item_to_delete_from; it; it = it->prev) {
		delete_item(it);
	}
	return 1;
}

int insert_item(struct item *item_to_insert, struct item *previous, struct sample *data_insert) {
	item_to_insert = calloc(1, sizeof(struct item));
	
	if (item_to_insert == NULL) {
		return 0;
	}

	item_to_insert->data = data_insert;

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

int insert_item_back(struct item *item_to_insert, struct sample *data_insert) { 
	item_to_insert = calloc(1, sizeof(struct item));
	
	if (item_to_insert == NULL) {
		return 0;
	}

	item_to_insert->data = data_insert;

	item_to_insert->next = NULL;
	tail->next = item_to_insert;
	item_to_insert->prev = tail;
	tail = item_to_insert;
	return 1;
}

int insert_item_front(struct item *item_to_insert, struct sample *data_insert) {
	item_to_insert = calloc(1, sizeof(struct item));
	
	if (item_to_insert == NULL) {
		return 0;
	}

	item_to_insert->data = data_insert;

	item_to_insert->prev = NULL;
	head->prev = item_to_insert;
	item_to_insert->next = head;
	head = item_to_insert;
	return 1;
}

int main(int argc, char **argv) {
	struct sample *s1 = malloc(sizeof(struct sample));
	s1->timestamp = 11111111;
	s1->value = 1111;

	struct sample *s2 = malloc(sizeof(struct sample));
	s2->timestamp = 22222222;
	s2->value = 2222;

	struct item *item1 = calloc(1, sizeof(struct item));
	item1->data = s1;

	struct item *item2 = calloc(1, sizeof(struct item));
	item2->data = s2;

	item1->next = item2;
	item2->prev = item1;
    item2->next = NULL;

	head = item1;

	print_list(head);

	// insert into list
	struct sample *s12 = malloc(sizeof(struct sample));
	s12->timestamp = 12121212;
	s12->value = 1212;

    struct sample *s3 = malloc(sizeof(struct sample));
	s3->timestamp = 33333333;
	s3->value = 3333;

	struct sample *s4 = malloc(sizeof(struct sample));
	s4->timestamp = 44444444;
	s4->value = 4444;

	struct sample *s5 = malloc(sizeof(struct sample));
	s5->timestamp = 55555555;
	s5->value = 5555;

	struct sample *s6 = malloc(sizeof(struct sample));
	s6->timestamp = 66666666;
	s6->value = 6666;

    struct item *item12;
	struct item *item3;
	struct item *item4;
	struct item *item5;
	struct item *item6;
    
    insert_item(item12, item1, s12);
	insert_item(item3, item2, s3);
	insert_item(item4, NULL, s4);
	
	print_list(head);
    print_list_reversed(tail);

	insert_item_back(item5, s5);
	print_list(head);
    print_list_reversed(tail);

	insert_item_front(item6, s6);
	print_list(head);
    print_list_reversed(tail);

	delete_list_to_end(item2);
	print_list(head);
	print_list_reversed(tail);

	delete_list_to_begin(item1);
	print_list(head);
	print_list_reversed(tail);

    delete_list_to_end(head);

	return 0;
}

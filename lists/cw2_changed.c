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
};

struct item *head;

void print_item(struct item *item_to_print){
	printf("registered event at %lld: %f\n", (long long)item_to_print->data->timestamp, item_to_print->data->value);
}

void print_list(struct item *head) {
	// iterate through list
	for (struct item *it = head; it; it = it->next) {
		print_item(it);
	}
	puts("");
}

int delete_item(struct item *item_to_delete) {
	if (item_to_delete != head) {
		struct item *prev = head;    // previous of item_to_delete

		while (prev != NULL && prev->next != item_to_delete)
			prev = prev->next;
		if (prev == NULL)
			return 0;
		prev->next = item_to_delete->next;
	} else {
		head = head->next;
	}
	free(item_to_delete);
	return 1;
}

int delete_list(struct item *item_to_delete_from){
	for (struct item *s = item_to_delete_from; s; s = s->next) {
		delete_item(s);
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
		item_to_insert->next = head;
		head = item_to_insert;
	} else {
		if (previous->next == NULL) {//вставка в конец
			previous->next = item_to_insert;
			item_to_insert->next = NULL;
		}
		else {//вставка в середину 
			item_to_insert->next = previous->next;
			previous->next = item_to_insert;
		}
	}
	
    return 1;
}

int insert_item_back(struct item *item_to_insert, struct sample *data_insert){
	item_to_insert = calloc(1, sizeof(struct item));
	
	if (item_to_insert == NULL) {
		return 0;
	}

	item_to_insert->data = data_insert;

	struct item *current = head; 

	if (current == NULL) {
		current->next = item_to_insert;
	}
	else {
		while (current->next != NULL) {
		current = current->next;
		}

		current->next = item_to_insert;
		item_to_insert->next = NULL;
	}
	return 1;
}

int insert_item_front(struct item *item_to_insert, struct sample *data_insert){
	item_to_insert = calloc(1, sizeof(struct item));
	
	if (item_to_insert == NULL) {
		return 0;
	}

	item_to_insert->data = data_insert;

	item_to_insert->next = head;
	head = item_to_insert;
	return 1;
}

int main(int argc, char **argv) {
	struct sample *s1 = malloc(sizeof(struct sample));
	s1->timestamp = 12345678;
	s1->value = 123;

	struct sample *s2 = malloc(sizeof(struct sample));
	s2->timestamp = 12345978;
	s2->value = 234;

	struct item *item1 = calloc(1, sizeof(struct item));
	item1->data = s1;

	struct item *item2 = calloc(1, sizeof(struct item));
	item2->data = s2;
	item1->next = item2;

	head = item1;

	print_list(head);

	// insert into list
	struct sample *s12 = malloc(sizeof(struct sample));
	s12->timestamp = 1212121212;
	s12->value = 1212;

	struct sample *s3 = malloc(sizeof(struct sample));
	s3->timestamp = 3333333333;
	s3->value = 3333;

	struct sample *s4 = malloc(sizeof(struct sample));
	s4->timestamp = 4444444444;
	s4->value = 4444;

	struct sample *s5 = malloc(sizeof(struct sample));
	s5->timestamp = 555555555;
	s5->value = 5555;

	struct sample *s6 = malloc(sizeof(struct sample));
	s6->timestamp = 66666666666;
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

	insert_item_back(item5, s5);
	print_list(head);

	insert_item_front(item6, s6);
	print_list(head);

	delete_item(head);
	print_list(head);

	delete_list(item12);
	print_list(head);

	return 0;
}

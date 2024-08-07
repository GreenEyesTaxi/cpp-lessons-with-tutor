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


void print_list(struct item *head) {
	// iterate through list
	for (struct item *it = head; it; it = it->next) {
		printf("registered event at %lld: %f\n", (long long)it->data->timestamp, it->data->value);
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

int insert_item_between(struct item *item_to_insert, struct item *previous, struct sample *data_insert) {
	item_to_insert = calloc(1, sizeof(struct item));
	
	if (item_to_insert == NULL) {
		return 0;
	}

	item_to_insert->data = data_insert;

	if (previous == NULL) {
		item_to_insert->next = head;
		head = item_to_insert;
	} else {
		if (previous->next == NULL) {//вставка в конец
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
		}
		else {//вставка в середину 
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

	struct item *item1 = calloc(1, sizeof(struct item));
	item1->data = s1;

	struct item *item2 = calloc(1, sizeof(struct item));
	item2->data = s2;
	item1->next = item2;

	head = item1;

	// insert into list
	struct sample *s12= malloc(sizeof(struct sample));
    time_t timestamp_insert12;
    double value_insert12;

    scanf("%ti%lf", &timestamp_insert12, &value_insert12);

	s12->timestamp = timestamp_insert12;
	s12->value = value_insert12;

	struct sample *s3 = malloc(sizeof(struct sample));
    time_t timestamp_insert3;
    double value_insert3;

    scanf("%ti%lf", &timestamp_insert3, &value_insert3);

	s3->timestamp = timestamp_insert3;
	s3->value = value_insert3;

	struct sample *s4 = malloc(sizeof(struct sample));
    time_t timestamp_insert4;
    double value_insert4;

    scanf("%ti%lf", &timestamp_insert4, &value_insert4);

	s4->timestamp = timestamp_insert4;
	s4->value = value_insert4;

	struct item *item12;
	struct item *item3;
	struct item *item4;

	insert_item_between(item12, item1, s12);
	insert_item_between(item3, item2, s3);
	insert_item_between(item4, NULL, s4);
	
	print_list(head);

	delete_item(head);
	print_list(head);

	return 0;
}

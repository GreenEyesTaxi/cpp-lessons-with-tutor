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

int insert_item_between(struct item *item_to_insert, struct item *previous, struct item *following, struct sample *data_insert) {
	item_to_insert = calloc(1, sizeof(struct item));
	item_to_insert->data = data_insert;

	item_to_insert->next = following;
	previous->next = item_to_insert;
    return 1;
}

int insert_item_back(struct item *item_to_insert, struct sample *data_insert) {
	item_to_insert = calloc(1, sizeof(struct item));
	item_to_insert->data = data_insert;

	item_to_insert->next = NULL;

	struct item *prev = head;

	while (prev != NULL) {
		prev = prev->next;
	}
		
	if (prev == NULL) {
		prev->next = item_to_insert;
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
	item2->next = item1;

	head = item2;

	print_list(head);

	// insert into list
	struct sample *s12;
    time_t timestamp_insert;
    double value_insert;

    scanf("%ti%lf", &timestamp_insert, &value_insert);

	s12->timestamp = timestamp_insert;
	s12->value = value_insert;

	struct item *item12;
	struct item *item3;

	insert_item_between(item12, item1, item2, s12);
	insert_item_back(item12, s12);
	insert_item_back(item3, s12);
	
	print_list(head);

	if (delete_item(item2) == 0)
		fprintf(stderr, "delete(item2) failed\n");
	print_list(head);

	if (delete_item(item1) == 0)
		fprintf(stderr, "delete(item1) failed\n");
	print_list(head);

	return 0;
}

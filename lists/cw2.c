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
	struct sample *s12 = malloc(sizeof(struct sample));
	s12->timestamp = 84848594;
	s12->value = 4242;

	struct item *item12 = calloc(1, sizeof(struct item));
	item12->data = s12;
	item12->next = item1;
	item2->next = item12;

	print_list(head);

	if (delete_item(item2) == 0)
		fprintf(stderr, "delete(item2) failed\n");
	print_list(head);

	if (delete_item(item1) == 0)
		fprintf(stderr, "delete(item1) failed\n");
	print_list(head);

	return 0;
}

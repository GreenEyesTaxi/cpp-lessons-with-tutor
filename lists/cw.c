#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct sample {
	time_t timestamp;
	double value;
	struct sample *next;
};
struct sample *head;

void print_list(struct sample *head) {
	// iterate through list
	for (struct sample *s = head; s; s = s->next) {
		printf("registered event at %lld: %f\n", (long long)s->timestamp, s->value);
	}
	puts("");
}

int delete_item(struct sample *item_to_delete) {
	if (item_to_delete != head) {
		struct sample *prev = head;    // previous of item_to_delete

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

	head = s1;
	s1->next = s2;
	s2->next = NULL;

	print_list(head);

	// insert into list
	struct sample *s12 = malloc(sizeof(struct sample));
	s12->timestamp = 84848594;
	s12->value = 4242;

	s12->next = s2;
	s1->next = s12;

	print_list(head);

	if (delete_item(s2) == 0)
		fprintf(stderr, "delete(s2) failed\n");
	print_list(head);

	if (delete_item(s1) == 0)
		fprintf(stderr, "delete(s1) failed\n");
	print_list(head);

	return 0;
}

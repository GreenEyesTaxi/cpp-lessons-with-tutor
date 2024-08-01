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

int insert_item_between(struct sample *item_to_insert, struct sample *previous, struct sample *following, time_t some_timestamp, double some_value) {
    item_to_insert = malloc(sizeof(struct sample));
	item_to_insert->timestamp = some_timestamp;
	item_to_insert->value = some_value;

	item_to_insert->next = following;
	previous->next = item_to_insert;
	
	for (struct sample *compare = head; compare; compare = compare->next) {
		if (compare == item_to_insert) {
        	return 0;//fail
    	}
    	else {
        	return 1;//success
    	}
	}    
} 

int insert_item_back(struct sample *item_to_insert, time_t some_timestamp, double some_value) {
	item_to_insert = malloc(sizeof(struct sample));
	item_to_insert->timestamp = some_timestamp;
	item_to_insert->value = some_value;

	item_to_insert->next = NULL;

	struct sample *prev = head; 

	while (prev != NULL) {
		prev = prev->next;
	}
		
	if (prev == NULL) {
		prev->next = item_to_insert;
	}
			
	for (struct sample *compare = head; compare; compare = compare->next) {
		if (compare == item_to_insert) {
        	return 0;//fail
    	}
    	else {
        	return 1;//success
    	}
	}
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
	struct sample *s12;
	struct sample *s3;
    time_t timestamp_insert;
    double value_insert;

    scanf("%ti%lf", &timestamp_insert, &value_insert);
	
    insert_item_between(s12, s1, s2, timestamp_insert, value_insert);
	insert_item_back(s12, timestamp_insert, value_insert);
	insert_item_back(s3, timestamp_insert, value_insert);

	print_list(head);

	if (delete_item(s2) == 0)
		fprintf(stderr, "delete(s2) failed\n");
	print_list(head);

	if (delete_item(s1) == 0)
		fprintf(stderr, "delete(s1) failed\n");
	print_list(head);

	return 0;
}

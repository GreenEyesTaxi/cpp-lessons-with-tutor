#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

int insert_item_between(struct sample *item_to_insert, struct sample *previous, time_t some_timestamp, double some_value) {
	item_to_insert->timestamp = some_timestamp;
	item_to_insert->value = some_value;
	
	for (struct sample *compare = head; compare; compare = compare->next) {
		if (compare == item_to_insert) {
        	return 0;//fail
    	}
	}

	if (previous == NULL) {//вставка в начало 
		item_to_insert->next = head;
		head = item_to_insert;
	} else {
		if (previous->next == NULL) {//вставка в конец
			struct sample *current = head; 

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

	return 1;//success    
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

	// insert into list
	struct sample *s12  = malloc(sizeof(struct sample));
	time_t timestamp_insert12;
    double value_insert12;
    scanf("%ti%lf", &timestamp_insert12, &value_insert12);

	struct sample *s3 = malloc(sizeof(struct sample));
	time_t timestamp_insert3;
    double value_insert3;
    scanf("%ti%lf", &timestamp_insert3, &value_insert3);

    struct sample *s4 = malloc(sizeof(struct sample));
	time_t timestamp_insert4;
    double value_insert4;
    scanf("%ti%lf", &timestamp_insert4, &value_insert4);
	
    insert_item_between(s12, s1, timestamp_insert12, value_insert12); //между s1 и s2
	insert_item_between(s3, s2, timestamp_insert3, value_insert3);//в конец
	insert_item_between(s4, NULL, timestamp_insert4, value_insert4);//в начало 

	print_list(head);
	
	delete_item(head);
	/*if (delete_item(s2) == 0)
		fprintf(stderr, "delete(s2) failed\n");
	//print_list(head);

	if (delete_item(s1) == 0)
		fprintf(stderr, "delete(s1) failed\n");
	//print_list(head);*/

	return 0;
}

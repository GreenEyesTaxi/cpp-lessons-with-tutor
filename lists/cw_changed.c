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

void print_item(struct sample *item_to_print) {
	printf("registered event at %lld: %f\n", (long long)item_to_print->timestamp, item_to_print->value);
}


void print_list(struct sample *head) {
	// iterate through list
	for (struct sample *s = head; s; s = s->next) {
		print_item(s);
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

int delete_list(struct sample *item_to_delete_from) {
	for (struct sample *s = item_to_delete_from; s; s = s->next) {
		delete_item(s);
	}
	return 1;
}

int insert_item(struct sample *item_to_insert, struct sample *previous) {
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
			previous->next = item_to_insert;
			item_to_insert->next = NULL;
		}
		else {//вставка в середину 
			item_to_insert->next = previous->next;
			previous->next = item_to_insert;
		}
	}

	return 1;//success    
} 

int insert_item_back(struct sample *item_to_insert) {
	for (struct sample *compare = head; compare; compare = compare->next) {
		if (compare == item_to_insert) {
        	return 0;//fail
    	}
	}

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
	return 1;
}

int insert_item_front(struct sample *item_to_insert) {
	for (struct sample *compare = head; compare; compare = compare->next) {
		if (compare == item_to_insert) {
        	return 0;//fail
    	}
	}

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

	head = s1;
	s1->next = s2;
	s2->next = NULL;

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
	
    insert_item(s12, s1); //между s1 и s2
	insert_item(s3, s2);//в конец
	insert_item(s4, NULL);//в начало 

	print_list(head);

	insert_item_back(s5);
	print_list(head);

	insert_item_front(s6);
	print_list(head);

	if (delete_item(s2) == 0)
		fprintf(stderr, "delete(s2) failed\n");
	print_list(head);

	if (delete_list(s12) == 0)
		fprintf(stderr, "delete list failed\n");
	print_list(head);

	delete_list(head);
	return 0;
}

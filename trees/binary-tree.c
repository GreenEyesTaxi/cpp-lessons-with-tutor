#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct car {
	char vin[30];
	char owner[200];
};

struct tree_item {
	struct tree_item *left, *right, *parent;

	char regnum[10];
	struct car car;
};



struct tree_item* add_tree_item(struct tree_item *root, const char *regnum, const struct car *car) {
	struct tree_item *item, *t;

	if ((item = calloc(1, sizeof(*item))) == NULL)
		return NULL;
	memcpy(item->regnum, regnum, sizeof(item->regnum));

	if (root == NULL) {
		root = item;
		return root;
	}

	// Пройти по дереву и найти подходящее место для вставки элемента
	t = root;
	for (;;) {
		int rv = strcmp(regnum, t->regnum);    // -1, 0, 1 — раньше, равно, позже
		if (rv == 0) {
			// уже есть такой узел
			free(item);
			errno = EEXIST;
			return NULL;
		}
		if (rv < 0) {
			if (t->left == NULL) {
				t->left = item;
				return item;
			}
			t = t->left;
		} else {
			if (t->right == NULL) {
				t->right = item;
				return item;
			}
			t = t->right;
		}
	}
}

void delete_tree_item(struct tree_item *item) {
	// если есть потомки, то один из них должен встать на наше место
}

int delete_tree_item_by_key(const char *regnum) {
	// 0 if OK, -1 if not found
	// calls delete_tree_item()
}

struct tree_item* search_tree(struct tree_item *root, const char *regnum) {
	// return NULL if such key doesn't exist, or pointer to tree item if it exists
}

void print_tree(const struct tree_item *root) {
}

int main(int argc, char **argv) {
	struct tree_item *root, *item;
	struct car car;

	strncpy(car.vin, "1234567890", sizeof(car.vin));
	strncpy(car.owner, "Vasiliy Vasilyev", sizeof(car.owner));
	root = add_tree_item(NULL, "a123bc", &car);

	print_tree(root);
	return 0;
}

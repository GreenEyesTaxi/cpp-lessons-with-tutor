#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int rec[1000006];

char regnum_test[9][10] = {
	"AA1111",//0
	"II9999",//1
    "BB2222",//2
    "CC3333",//3
	"HH8888",//4
    "DD4444",//5
	"FF6666",//6
    "EE5555",//7
    "GG7777",//8
};

struct car {
	char vin[30];
	char owner[200];
}
car_test[] = {
	{"VIN1111", "John Doe"},
	{"VIN2222", "Jane Doe"},
	{"VIN3333", "Bob Smith"},
	{"VIN4444", "Alice Johnson"},
	{"VIN5555", "Mike Brown"},
	{"VIN6666", "Emily Davis"},
	{"VIN7777", "Tom Harris"},
	{"VIN8888", "Sarah Lee"},
	{"VIN9999", "David Kim"},
};

struct tree_item {
	struct tree_item *left, *right, *parent;

	char regnum[10];//key value
	struct car car;
};

struct tree_item* add_tree_item(struct tree_item *root, const char *regnum, const struct car *car) {
	struct tree_item *item, *t;//t = temp

	if ((item = calloc(1, sizeof(*item))) == NULL)
		return NULL;
	memcpy(item->regnum, regnum, sizeof(item->regnum));//копирует байты из одного места в другое 

	if (root == NULL) {
		root = item;
		return root;
	}

	// Пройти по дереву и найти подходящее место для вставки элемента
	t = root;
	for (;;) {
		int rv = strcmp(regnum, t->regnum);    // -1, 0, 1 — раньше, равно, позже  -- сравнение строк, по байтово сравнивает значенияпод указателями 
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
			t = t->left;//переходим на следующую вершину цикла для сравнения 
		} else {
			if (t->right == NULL) {
				t->right = item;
				return item;
			}
			t = t->right;//переходим на следующую вершину цикла для сравнения 
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
	struct tree_item *t;

	t = root;
	if (t == NULL) {
		return t;
	}

	for (;;) {
		int rv = strcmp(regnum, t->regnum);    // -1, 0, 1 — раньше, равно, позже  -- сравнение строк, по байтово сравнивает значенияпод указателями 
		if (rv == 0) {
			// found item
			return t;
		}
		if (rv < 0) {
			if (t->left != NULL) {
				t = t->left;//переходим на следующую вершину цикла для сравнения 
			}
			else {
				return NULL;
			}
			
		} else {
			if (t->right != NULL) {
				t = t->right;//переходим на следующую вершину цикла для сравнения
			}
			else {
				return NULL;
			}
		}
	}	


}

void print_tree(const struct tree_item *root, int depth) {
	struct tree_item *t;

	t = root;
	if (t == NULL) {
		printf("Your tree is ampty");
	}

	printf("\t");
	for(int i = 0; i < depth; i++) {
        if(i == depth - 1)
            printf("%s\u2014\u2014\u2014",rec[depth-1]?"\u0371":"\u221F");
        else
            printf("%s   ",rec[i]?"\u23B8":"  ");
	}

    printf("%s\n", t->regnum);
    rec[depth] = 1;
    print_tree(t->left, depth + 1);
    rec[depth]=0;
    print_tree(t->right, depth + 1);
}

int main(int argc, char **argv) {
	struct tree_item *root;
	struct car car;

	strncpy(car.vin, "1234567890", sizeof(car.vin));//копирует из в указанного колва элементов n
	strncpy(car.owner, "Vasiliy Vasilyev", sizeof(car.owner));
	root = add_tree_item(NULL, "a123bc", &car);

	struct tree_item *item0;
	struct tree_item *item1;
	struct tree_item *item2;
	struct tree_item *item3;
	struct tree_item *item4;
	struct tree_item *item5;
	struct tree_item *item6;
	struct tree_item *item7;
	struct tree_item *item8;

	item0 = add_tree_item(root, regnum_test[0], &car_test[0]);
	item1 = add_tree_item(root, regnum_test[1], &car_test[1]);
	item2 = add_tree_item(root, regnum_test[2], &car_test[2]);
	item3 = add_tree_item(root, regnum_test[3], &car_test[3]);
	item4 = add_tree_item(root, regnum_test[4], &car_test[4]);
	item5 = add_tree_item(root, regnum_test[5], &car_test[5]);
	item6 = add_tree_item(root, regnum_test[6], &car_test[6]);
	item7 = add_tree_item(root, regnum_test[7], &car_test[7]);
	memcpy(item8->regnum, regnum_test[8], sizeof(item8->regnum));

	if (search_tree(root, item8->regnum))
		printf("your item regnum is %s\n", item8->regnum);	
	//print_tree(root,0);
	return 0;
}

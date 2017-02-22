#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*  Node structure that contains a word,
 *  its frequency and
 *  pointers to its left and right children.
 */
typedef struct TreeNode {
        struct TreeNode *left;
        struct TreeNode *right;
        char            *word;
        unsigned        freq;
} TreeNode;

/*  Tree structure that contains its size
 *  to keep track of the number of nodes in the tree
 *  and a pointer to its root node.
 */
typedef struct Tree {
    TreeNode *root;
    size_t size;
} Tree;

int findNextAlphaChar(char *word, const int currIndex);
void lowerCase (char *word);
void cleanWord (char *word);

TreeNode *createTreeNode(const char *word);
void insertBinarySearchTree(Tree *tree, const char *word);
TreeNode *searchBinarySearchTree(Tree *tree, const char *word);

int addToArray(int i, TreeNode *root, TreeNode *array[]);
void printArray (int arr_sz, TreeNode **array);
int compare(const void * a, const void * b);
void printNodes(TreeNode *root);
void cleanBinaryTree(TreeNode *root);

int main(void){

    FILE *file;
    char word[80];
    char filename[30];
    int c = 0;
    int i = 0;
    Tree tree;
    tree.root = NULL;
    tree.size = 0;
    TreeNode *node;
    TreeNode **nodes;

    printf("Enter filename \n>");
    scanf("%s", filename);
    file = fopen(filename, "r");

	    if (file == NULL) {
        printf( "File not found.\n");
        return 0;
        }

         while (c != EOF) {
            c = fscanf(file, "%s", word);

            if (c != EOF) {
                if (findNextAlphaChar(word, 0) != -1) { // words without alpha characters are ignored
                    lowerCase(word);
                    cleanWord(word);
                    node = (searchBinarySearchTree(&tree, word));//If node already exists in the tree, its frequency is incremented
                    if (node != NULL) {
                        node->freq += 1;
                    }
                    else if (node == NULL) {
                        insertBinarySearchTree(&tree, word);  // Otherwise, the node is inserted to the tree
                        tree.size += 1;       //keeps track of the amount of nodes in the tree (and unique words in the text file)
                    }
                }
            }
        }
     fclose(file);
    //printNodes(tree.root);
     nodes = malloc (tree.size * sizeof(*nodes));
     addToArray(i, tree.root, nodes);
     qsort(nodes, tree.size, sizeof(TreeNode*), compare);
     printArray(tree.size, nodes);
     cleanBinaryTree(tree.root);

    return 0;
}

/* Creates a new node from a word
*  Parameter: word
*  Returns: node that was created
*/

TreeNode *createTreeNode(const char *word) {

        TreeNode *new_node;

        new_node = malloc(sizeof *new_node);

        new_node->left  = NULL;
        new_node->right = NULL;
        new_node->word  = malloc((strlen(word)+1) * sizeof *word);

        strncpy(new_node->word, word, strlen(word));

        new_node->word[strlen(word)] = '\0';
        new_node->freq = 1;

        return new_node;
}
/*  Inserts node into binary search tree by alphabetic order
 *  Parameter: tree, word
 */
void insertBinarySearchTree(Tree *tree, const char *word) {

        TreeNode *new_node, *curr_node, *prev_node;
        int       dir;

        new_node = createTreeNode(word);

        if(tree->root == NULL) {
                tree->root = new_node;
                return;
        }
        curr_node = tree->root;

        while (curr_node != NULL) {
                prev_node = curr_node;
                dir       = strcmp(word, curr_node->word);

                if (dir < 0) {
                        curr_node = curr_node->left;
                }
                else if (dir > 0) {
                        curr_node = curr_node->right;
                }
        }

        if (dir < 0) {
                prev_node->left = new_node;
        }
        else {
                prev_node->right = new_node;
        }
}
/*  Checks if node with a certain word exists in binary search tree
 *  Parameter: tree, word
 *  Returns: the node if it was found, null if node was not found
 */
TreeNode *searchBinarySearchTree(Tree *tree, const char *word) {

        TreeNode *curr_node;
        int       dir;

        if (tree->root == NULL) {
            return NULL;
        }
        curr_node = tree->root;
        while (curr_node != NULL) {
                dir       = strcmp(word, curr_node->word);

                if (dir == 0) {
                    return curr_node;
                }

                else if (dir < 0) {
                        curr_node = curr_node->left;
                }
                else {
                        curr_node = curr_node->right;
                }
        }

   return curr_node;
}
/*  Turns a word into lowercase
 *  Parameter: word
 */
void lowerCase (char *word) {
    int  i;

    for (i = 0; i < strlen(word); i++) {
    word[i] = tolower(word[i]);
    }
}
/* Finds next alphabetic character in word from given index
*  Parameter: word
*  Returns: index where alphabetic character was found,
*  -1 if there is no alpha chars
*/
int findNextAlphaChar(char *word, const int currIndex) {

        int i;

        for (i = currIndex + 1; i < strlen(word); i++) {
                if (isalpha(word[i]))
                        return i;
        }

        return -1;
}
/*  Cleans the word from non-alphabetic characters
 *  Parameter: word
 */
void cleanWord (char *word) {

    int  i,j, k;
    int nextAlpha;

    for (i = 0; i <= strlen(word); i++) {

        if (!isalpha(word[i]) && word[i] != '’' && word[i] != '\'' && word[i] != '‘' ) {
            nextAlpha = (findNextAlphaChar(word, i));

            if (nextAlpha == -1) {
                 word[i] ='\0';
                 return;
            }

            else {
                k = i;
                for (j = nextAlpha; j < strlen(word)+1; j++) {
                    word[k] = word[j];
                    k++;
                }
            }
        }
    }
}

/*  Adds the tree's nodes into an array'
 *  Parameter: i: array's index,
 *           root: node that's being added
 *           array: array of nodes
 *
 *  Returns: incremented index
 */

int addToArray(int i, TreeNode *root, TreeNode *array[]) {

  if (root->left != NULL) {
        i = addToArray(i, root->left, array);
  }

  if (root->right != NULL) {
        i = addToArray(i, root->right, array);
  }

    if (root != NULL) {
        array[i] = malloc(sizeof(TreeNode));
        array[i]->word = root->word;
        array[i]->freq = root->freq;
    }

    return i+1;
}
/*  Compares two nodes' word frequencies
*   Parameters:  a - first node
*               b - second node
*   Returns: subtraction of frequencies
*/
int compare(const void * a, const void * b){

    TreeNode *tree1 = *(TreeNode * const *)a;
    TreeNode *tree2 = *(TreeNode * const *)b;

   return ( tree2->freq - tree1->freq );
}
/*  Prints tree's nodes' words and frequencies in-order
 *  Parameter: root - node that's being printed
 */
void printNodes(TreeNode *root) {

  if (root != NULL ) {
    printNodes(root->left);

    printf("%-20s %d\n", root->word, root->freq);

    printNodes(root->right);
  }
}

/*  Prints array's nodes' words and frequencies from first to last
 *  Parameter: root - node that's being printed
 */
void printArray (int arr_sz, TreeNode **array) {

    int i = 0;

    while (i < arr_sz && i < 100) {
        printf("%-20s %d\n", array[i]->word, array[i]->freq);
        i++;
    }
}

/*  Frees tree's nodes and words, starting from root node
 *  Parameter: root - node that's being freed
 */
void cleanBinaryTree(TreeNode *root){

    if (root == NULL) {
        return;
    }
    cleanBinaryTree(root->left);
    cleanBinaryTree(root->right);
    free(root->word);
    free(root);
}

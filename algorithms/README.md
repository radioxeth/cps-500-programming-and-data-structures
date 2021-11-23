# Algorithms and Data-Structures
- [Home](/README.md#cps-500-programming-and-data-structures)
- [Sorting](#Sorting)
  - [Bubble Sort](#Bubble-Sort)
  - [Insertion Sort](#Insertion-Sort)
  - [Selection Sort](#Selection-Sort)
  - [Merge Sort](#Merge-Sort)
  - [Quick Sort](#Quick-Sort)
- [Searching](#Searching)
  - [Binary Search](#Binary-search)
- [Linked List](#Linked-List)
  - [Add Head](#add-head)
  - [Reverse Linked-List](#reverse-linked-list)
  - [Traverse Linked-List](#traverse-linked-list)
- [Queue](#queue)
- [Stack](#stack)
- [Binary Tree](#Binary-Tree)
  - [Depth-First Search](#depth-first-search)
    - [In-Order](#in-order)
    - [Pre-Order](#pre-order)
    - [Post-Order](#post-order)
  - [Breadth-First Search](#Breadth-first-search)

## Sorting
[top](#Algorithms-and-Data-Structures)

### Bubble Sort
[top](#Algorithms-and-Data-Structures)
```C
void bubbleSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int swapped = 0;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp1 = arr[j];
                int temp2 = arr[j + 1];
                arr[j] = temp2;
                arr[j + 1] = temp1;
                swapped = 1;
            }
        }
        if (!swapped)
            break;
    }
}
```

### Insertion Sort
[top](#Algorithms-and-Data-Structures)
```C
void insertionSort(int *a, int N)
{
    for (int i = 1; i < N; i++)
    {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key)
        {
            a[j + 1] = a[j];
            j = j - 1;
        }
        a[j + 1] = key;
    }
}
```

### Selection Sort
[top](#Algorithms-and-Data-Structures)
```C
void selectionSort(int *a, int N)
{
    int minJ, minVal;
    for (int i = 0; i < N - 1; i++)
    {
        minJ = i;
        minVal = a[i];
        for (int j = i + 1; j <= N - 1; j++)
        {
            if (a[j] < minVal)
            {
                minJ = j;
                minVal = a[j];
            }
        }
        //swap the values of a[i] and a[minJ]
        a[minJ] = a[i];
        a[i] = minVal;
    }
}
```

### Merge Sort
[top](#Algorithms-and-Data-Structures)
```C
void mergeSort(int array[], int left, int right)
{
    if (left < right)
    {
        int middle = left + (right - left) / 2;
        mergeSort(array, left, middle);
        margeSort(array, middle + 1, right);
        merge(array, left, middle, right);
    }
}

void merge(int array[], int left, int middle, int right)
{
    int temp[right - left];
    int i = left;
    int j = middle;
    int index = 0;
    while (i < middle && j < right)
    {
        if (array[i] < array[j])
        {
            temp[index] = array[i];
            i++;
        }
        else
        {
            temp[index] = array[j];
            j++;
        }
        index++;
    }
    while (i < middle)
    {
        temp[index] = array[i];
        i++;
        index++;
    }
    while (j < right)
    {
        temp[index] = array[j];
        j++;
        index++;
    }
    for (int k = 0; k < right - left; k++)
    {
        array[left + k] = temp[k];
    }
}
```

### Quick Sort
[top](#Algorithms-and-Data-Structures)
```C
void quickSort(int array[], int low, int high){
    if(low<high){
        int p = partition(array,low,high);
        quickSort(array,low,p-1);
        quickSort(array,p+1,high);
    }
}
int partition(int array[], int low, int high){
    int pivot = array[high];
    int i= low-1;
    for(int j=low;j<high;j++){
        if(array[j]<=pivot){
            i++;
            swap(array, i, j);
        }
    }
    swap(array,i+i,high);
    return i+1;
}
```

## Searching
[top](#Algorithms-and-Data-Structures)
### Binary Search
[top](#Algorithms-and-Data-Structures)
```C
int binarySearch(int *array, int value, int lo, int hi)
{
    if (lo > hi)
    {
        return -1;
    }
    int middle = lo + (hi - lo) / 2;
    if (array[middle] == value)
    {
        return middle;
    }
    else if (array[middle] < value)
    {
        return binarySearch(array, value, middle + 1, hi);
    }
    else
    {
        return binarySearch(array, value, lo, middle - 1);
    }
}
```

## Linked List
[top](#Algorithms-and-data-structures)
```C
typedef struct listNode
{
    int data;
    struct listNode *next;
} ListNode;

typedef struct list
{
    ListNode *head;
    ListNode *tail; //optional!
} List;

typedef struct doublyListNode
{
    int data;
    struct doublyListNode *next;
    struct doublyListNode *prev;
} DoublyListNode;
```
### Add Head
[top](#algorithms-and-data-structures)
```C
void addHead(List *list, int value)
{
    //Create a new node to hold value.
    ListNode *node = malloc(sizeof(ListNode));
    //Assign the data to the value
    node->data = value;
    //Assign the next element to what head points to.
    node->next = list->head; // whatever list->head points to, point node->next to the same thing
    //assign the head of the list to the node
    list->head = node;
}
```
### Reverse Linked-List
[top](#algorithms-and-data-structures)
```C
void reverse(List *list)
{
    if (list->head == NULL)
        return;
    ListNode *prev = NULL;
    ListNode *ptr = list;
    while (ptr != NULL)
    {
        ListNode *tmp = ptr->next;
        ptr->next = prev;
        prev = ptr;
        ptr = tmp;
    }
    list->head = prev;
}
```
### Traverse Linked-List
[top](#algorithms-and-data-structures)
```C
void traverse(List *list)
{
    ListNode *current = list->head; //this is a POINTER to a list node, not a new ListNode
    while (current != NULL)
    {
        printf("%d->", current->data);
        current = current->next;
    }
    printf("NULL\n");
}
```

## Queue
[top](#algorithms-and-data-structures)
```C
//Coming soon
```
## Stack
[top](#algorithms-and-data-structures)
```C
//Coming soon
```

## Binary Tree
[top](#algorithms-and-data-structures)
```C
typedef struct treeNode{
    int data;
    TreeNode *left;
    TreeNode *right;
} TreeNode;

typedef struct tree{
    TreeNode *root;
} Tree;
```

### Depth-First Search
[top](#algorithms-and-data-structures)
    ### In-Order
    [top](#algorithms-and-data-structures)
    ```C
    void inOrder (TreeNode* node){
        if(node==NULL) return;
        inOrder(node->left);
        visit(node);
        inOrder(node->right);
    }
    ```

    ### Pre-Order
    [top](#algorithms-and-data-structures)
    ```C
    void preOrder (TreeNode* node){
        if(node==NULL) return;
        visit(node);
        inOrder(node->left);
        inOrder(node->right);
    }
    ```

    ### Post-Order
    [top](#algorithms-and-data-structures)
    ```C
    void postOrder (TreeNode* node){
        if(node==NULL) return;
        inOrder(node->left);
        inOrder(node->right);
        visit(node);
    }
    ```

### Breadth-First Search
[top](#algorithms-and-data-structures)
```C
void bfs(Tree* tree){
    Queue q;
    enqueue(&q,tree->root);
    while(!isEmpty(&q)){
        TreeNode *next = dequeue(&q);
        visit(next);
        if(next->left!=NULL){
            enqueue(&q, next->left);
        }
        if(next->right!=NULL){
            enqueue(&q, next->right);
        }
    }
}
```
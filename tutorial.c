#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TRACE {printf("Executing Line: %d\n", __LINE__);}

typedef enum {
  GREATER,
  EQUAL,
  LESS
}comparison;
typedef enum {
  ASCENDING,
  DESCENDING,
  NONE
}ordering;

typedef struct student {
  char * first_name;
  char * last_name;
  char * address;
} student;

student * create_student(char *, char *, char *);
void destroy_student(student *);

comparison student_sort_by_first_name(void *, void *);
comparison student_sort_by_last_name(void *, void *);
comparison student_sort_by_adress(void *, void *);

//###########################################
//	LINKED LIST STRUCTS
//##########################################
// Description:
//	The master node struct and linked-list struct are both
//used to implement a linked list, stack, and queue.
//###########################################


//###########################################
//	LINKED LIST NODE
//###########################################
typedef struct linked_list_node {
  struct linked_list_node * previous;
  struct linked_list_node * next;
  void * data_object;
} ll_node;

//###########################################
//	MASTER LIST NODE
//###########################################
typedef struct master_linked_list_node {
  ll_node * head;
  ll_node * tail;
  
  void (* insertion) (struct master_linked_list_node *, void *);
  void (* deletion) (struct master_linked_list_node *, ll_node *);
  void * (* get_next_element) (struct master_linked_list_node *);
  void (* sort_algorithm) (struct master_linked_list_node *);
  comparison (* sort_by) (void *, void*);
  ordering ord_t;
  
} master_node;
//############################################
//############################################




//Memory Management
ll_node * create_ll_node(void *);
master_node * create_master_node(void (* insertion) (master_node *, void *),
				 void (* deletion) (master_node *, ll_node *),
				 void * (* get_next_element) (master_node *),
				 void (* sort_algorithm) (master_node *),
				 comparison (* sort_by) (void *, void*),
				 ordering ord_t);
void destroy_linked_list(master_node*);
void destroy_ll_node(ll_node*);



//Data Structure Operations
void linked_list_insertion(master_node*, void *);
void * get_next_for_stacks(master_node *);
void * get_next_for_queues(master_node *);
void deletion_for_linked_list(master_node *, ll_node *);
void quick_sort_for_linked_list(master_node *);
ll_node * quick_sort(master_node* , ll_node *);
void no_sort(master_node *);
comparison no_sort_by(void *, void *);

//################################
// Linked list 
// 
// Supported Operations:
//	insertion
//	delete
// Optional:
//	sort
//	length
//################################
// Stack
//
// Supported Operations:
//	insertion - put an object on top of the stack O(1)
//	pop - remove the top item from stack	 O(1)
//	search - find element x			 O(n)
//	delete - remove element x		 O(n)
//############################################
// Queue
//
//Supported Functions:
//	enqueue: add element to the tail O(1)
//	dequeue: remove first element    O(1)
//	search: find element x		 O(n)
//	remove: remove element x	 O(n)
//Variations:
//	circular queue - fixed length queue implement with array
//############################################





//#############################################
// Heap - container for objects with keys
//
// Supported Functions
//	insertion -  O(log n)	
//	get-Minimum -  O(log n)
//	Delete - O(log n)

//	Internals:
//	Heapify- O(n)
//	resize
//	"bubble up"
//	"bubble down"

typedef struct heap {
  
  int capacity;
  int number_of_elements;
  
  void * data_object; 
}heap;


//#########################################
//Balanced Binary Search Tree
//
// Supported Operations
//	insertion - O(log n)
//	deletion - O(log n)
//	(binary) search - O(log n)
//	min/max - O(log n)
//	predecessor/successor - O(log n)
//	output tree in sorted order - O(n)
typedef struct balanced_binary_tree {
  struct balanced_binary_tree * left;
  struct balanced_binary_tree * right;
  void * data_object;
} bbt;


//#######################################
// Hash Table 
//
// Supported Operations
//
//	insertion - O(1)
//	deletion - ???
//	look up - O(1)
//#######################################

typedef struct hash_table {
  int capacity;
  int number_of_elements;
  
  void * data_object;
} hash_table;






int main(int argc, char **argv) {
  // CREATE MASTER NODE
  //	1. insertion fx { stack, queue}
  //	2. deletion fx { ????}
  //	3. next_element fx {stack, queue}
  //	4. sort Algorithm {QUICK_SORT}
  //	5. field to sort by {f_name, l_name, address}
  //	6. ordering {ASCENDING, DESCENDING}
  master_node * stack = create_master_node(linked_list_insertion,
					   deletion_for_linked_list,
					   get_next_for_stacks,
					   no_sort,
					   no_sort_by,
					   NONE);
  master_node * queue = create_master_node(linked_list_insertion,
					   deletion_for_linked_list,
					   get_next_for_queues,
					   quick_sort_for_linked_list,
					   student_sort_by_first_name,
					   ASCENDING);
  // CREATE STUDENT
  //	1. f_name
  //	2. l_name
  //	3. address
 
  char l_name[6] = "Rush";
  char address[10] = "100 Way";
  student * student1 = create_student("Everett", l_name, address);
  student * student2 = create_student("John", l_name, address);
  student * student3 = create_student("Tim", l_name, address);
  
  stack->insertion(stack, (void *) student1);
  stack->insertion(stack, (void *) student2);
  stack->insertion(stack, (void *) student3);

  student * current = NULL;
  while(stack->head)
  {
    current = (student *) stack->get_next_element(stack);
    printf("First Name:%s\n", current->first_name);
//     printf("Last Name:%s\n", current->last_name);
//     printf("Address:%s\n", current->address);  
 
  }
  
  student * student4 = create_student("Everett", l_name, address);
  student * student5 = create_student("John", l_name, address);
  student * student6 = create_student("Tim", l_name, address);
  
  queue->insertion(queue, (void *) student4);
  queue->insertion(queue, (void *) student5);
  queue->insertion(queue, (void *) student6);
  while(queue->head)
  {
    current = (student *) queue->get_next_element(queue);
    printf("First Name:%s\n", current->first_name);
//     printf("Last Name:%s\n", current->last_name);
//     printf("Address:%s\n", current->address);  
 
  }
  
  
  
  return 0;
  
  
}




student * create_student(char * f_name, char * l_name, char * address)
{
  student* student_ptr = (student *) malloc(sizeof(student));
  student_ptr->first_name = strdup(f_name);
  student_ptr->last_name = strdup(l_name);
  student_ptr->address = strdup(address);
  return student_ptr;
}
void free_student(student* delete_student)
{
  free(delete_student->first_name);
  free(delete_student->last_name);
  free(delete_student->address);
  free(delete_student);
}



comparison get_comparison_enum(int comp_value)
{
  if (comp_value>0)
  {
    return GREATER;
  }
  else if (comp_value < 0)
  {
    return LESS;
  }
  else
  {
    return EQUAL;
  }
}
comparison student_sort_by_first_name(void * v_student1, void * v_student2)
{
  student * student1 = (student *) v_student1,
	    * student2 = (student *) v_student2;
  char * string_1 = student1->first_name,
  * string_2 = student2->first_name;
  int comp_value = strcmp(string_1, string_2);
  return get_comparison_enum(comp_value);
}
comparison student_sort_by_last_name(void * v_student1, void * v_student2)
{
  student * student1 = (student *) v_student1,
	    * student2 = (student *) v_student2;
  char * string_1 = student1->last_name,
  * string_2 = student2->last_name;
  int comp_value = strcmp(string_1, string_2);
  return get_comparison_enum(comp_value);
}
comparison student_sort_by_address(void * v_student1, void * v_student2)
{
  student * student1 = (student *) v_student1,
	    * student2 = (student *) v_student2;
  char * string_1 = student1->address,
  * string_2 = student2->address;
  int comp_value = strcmp(string_1, string_2);
  return get_comparison_enum(comp_value);
}



//Memory Management

master_node * create_master_node(void (* insertion) (master_node *, void *),
				 void (* deletion) (master_node *, ll_node *),
				 void * (* get_next_element) (master_node *),
				 void (* sort_algorithm) (master_node *),
				 comparison (* sort_by) (void *, void*),
				 ordering ord_t)
{
  master_node * master_p = (master_node *) malloc(sizeof(master_node));
  master_p->head = NULL;
  master_p->tail = NULL;
  master_p->insertion = insertion;
  master_p->deletion = deletion;
  master_p->get_next_element = get_next_element;
  master_p->sort_algorithm = sort_algorithm;
  master_p->sort_by = sort_by;
  master_p->ord_t = ord_t;
  return master_p;
}

ll_node * create_ll_node(void * data_object)
{  
  ll_node * node_p = (ll_node *) malloc(sizeof(ll_node));
  node_p->next = NULL;
  node_p->previous = NULL;
  node_p->data_object = data_object;
  return node_p;
}

void destroy_linked_list(master_node* master_p)
{
  ll_node * current = master_p->head,
	   * temp = NULL;
	   
  while (current)
  {
    temp = current;
    current = current->next;
    destroy_ll_node(temp);
  }
  free(master_p);
}
void destroy_ll_node(ll_node* node_to_be_destroyed)
{
  if (node_to_be_destroyed->data_object)
  {
    free(node_to_be_destroyed->data_object);
  }
  
  free(node_to_be_destroyed);
}

//Data Structure Operations
void linked_list_insertion(master_node* master_p, void * data_to_be_inserted )
{

  
  ll_node * node_to_be_inserted = create_ll_node(data_to_be_inserted);
  if (!master_p->tail)
  {
    master_p->head = node_to_be_inserted;
    master_p->tail = node_to_be_inserted;
    return;
  }
  master_p->tail->next = node_to_be_inserted;
  node_to_be_inserted->previous = master_p->tail;
  master_p->tail = node_to_be_inserted;
}
void * get_next_for_stacks(master_node * master_p)
{
  ll_node * temp = master_p->tail;
  void * data_to_return = temp->data_object;
  temp->data_object = NULL;

  master_p->tail = temp->previous;
 
  if (master_p->tail)
  {
    master_p->tail->next = NULL;
  }
  else
  {
    master_p->head = NULL;
  }
  destroy_ll_node(temp);
  return data_to_return;
}
void * get_next_for_queues(master_node * master_p)
{
  ll_node * temp = master_p->head;
  void * data_to_return = temp->data_object;
  temp->data_object = NULL;
  
  master_p->head = temp->next;
  if (master_p->head)
  {
    master_p->head->previous = NULL;
  }
  else
  {
    master_p->head = NULL;
  }
  destroy_ll_node(temp);
  return data_to_return;
}
void deletion_for_linked_list(master_node * master_p, ll_node * node_to_delete)
{
  return;
}

//###################################################################################
//###################################################################################
//Sort Algorithms
//###################################################################################
//###################################################################################
void insertion_sort(master_node * m_node_ptr)
{
return;
}
void quick_sort_for_linked_list(master_node* master_p)
{
  master_p->head = quick_sort(master_p, master_p->head);
}
ll_node * quick_sort(master_node* m_node_ptr, ll_node * list_to_sort)
 {
  ll_node * temp = NULL;
  //###########################################################################
  //	FIND THE PIVOT
  //###########################################################################
  ll_node * smaller = list_to_sort;
  if (smaller == NULL)
  {
    return smaller;
  }
  ll_node * pivot = smaller->next;
  smaller->next = NULL;
  if (pivot==NULL)
  {
    return smaller;
  }
  ll_node * bigger = pivot->next;
  pivot->next = NULL;
  if (m_node_ptr->sort_by(smaller->data_object, pivot->data_object) == GREATER)
  {
    temp = pivot;
    pivot = smaller;
    smaller = temp;
  }
  if (bigger == NULL)
  {
    if (m_node_ptr->ord_t == ASCENDING)
    {
      smaller->next = pivot;
      return smaller;
    }
    else
    {
      pivot->next = smaller;
      return pivot;
    }
  }
  ll_node* place_holder = bigger->next;
  bigger->next = NULL;
  if (m_node_ptr->sort_by(smaller->data_object, bigger->data_object) == GREATER)
  {
    temp = pivot;
    pivot = smaller;
    smaller = bigger;
    bigger = temp;
  }
  //bigger is greater than or equal to smaller
  else if (m_node_ptr->sort_by(bigger->data_object, pivot->data_object) == LESS)
  {
    temp = pivot;
    pivot = bigger;
    bigger = temp;
  }
  //################################################################################
  //	COMPARE WITH PIVOT
  //################################################################################
  while (place_holder!=NULL)
  {
    temp = place_holder;
    place_holder = place_holder->next;
    temp->next = NULL;
    if (m_node_ptr->sort_by(temp->data_object, pivot->data_object)==GREATER)
    {
      temp->next = bigger;
      bigger= temp;
    }
    else
    {
      temp->next = smaller;
      smaller = temp;
    }
  }
  //#################################################################################
  //	SORT THE BIGGER THEN SORT THE SMALLER LISTS 
  //#################################################################################
  bigger = quick_sort(m_node_ptr, bigger);
  smaller = quick_sort(m_node_ptr, smaller);
  if (m_node_ptr->ord_t == ASCENDING)
  {
    temp = smaller;
    while (temp->next!=NULL)
    {
      temp = temp->next;
    }
    temp->next = pivot;
    pivot->next = bigger;
    return smaller;
    }
  else
  {
    temp = bigger;
    while (temp->next!=NULL)
    {
      temp = temp->next;
    }
    temp->next = pivot;
    pivot->next = smaller;
    return bigger;
  }
}

void no_sort(master_node * master_p)
{
  return;
}
comparison no_sort_by(void * v_student1, void * v_student2)
{
  return EQUAL;
}
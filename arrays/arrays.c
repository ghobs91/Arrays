#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct Array {
  int capacity;  // How many elements can this array hold?
  int count;  // How many states does the array currently hold?
  char **elements;  // The string elements contained in the array
} Array;


/************************************
 *
 *   CREATE, DESTROY, RESIZE FUNCTIONS
 *
 ************************************/

/*****
 * Allocate memory for a new array
 *****/
Array *create_array (int capacity) {
  // Allocate memory for the Array struct
  Array *array = malloc(sizeof(Array));
  // Set initial values for capacity and count
  array->capacity = capacity;
  array->count = 0;
  // Allocate memory for elements
  array->elements = calloc(capacity, sizeof(char *));
  return array;
}


/*****
 * Free memory for an array and all of its stored elements
 *****/
void destroy_array(Array *array) {
  // Free all elements
  if (array->elements != NULL)
  {    
      free(array->elements);
  }
  // Free array
  if (array != NULL)
  {
      free(array);
  }
}

/*****
 * Create a new elements array with double capacity and copy elements
 * from old to new
 *****/
void resize_array(Array *array) {

  // Create a new element storage with double capacity
  int dbl_capacity = array->capacity * 2;
  char **new_elem_storage = malloc(sizeof(char) * dbl_capacity);

  // Copy elements into the new storage
  for (int i = 0; i < array->count; i++)
  {
    new_elem_storage[i] = array->elements[i];
  }

  // Free the old elements array (but NOT the strings they point to)
  free(array->elements);

  // Update the elements and capacity to new values
  array->elements = new_elem_storage;
  array->capacity = dbl_capacity;
}



/************************************
 *
 *   ARRAY FUNCTIONS
 *
 ************************************/

/*****
 * Return the element in the array at the given index.
 *
 * Throw an error if the index is out of range.
 *****/
char *arr_read(Array *array, int index) {

  // Throw an error if the index is greater than the current count
  if (index > array->count)
  {
    return -1;
  }
  // Otherwise, return the element at the given index
  return array->elements[index];
}


/*****
 * Insert an element to the array at the given index
 *****/
void arr_insert(Array *array, char *element, int index) {

  // Throw an error if the index is greater than the current count
  if (index > array->count)
  {
    return -1;
  }
  // Resize the array if the number of elements is over capacity
  if (array->count > array->capacity)
  {
    resize_array(array);
  }
  // Move every element after the insert index to the right one position
  for (int i = array->count - 1; i >= index; i--)
  {
    array->elements[i + 1] = array->elements[i];
  }
  // Copy the element and add it to the array
  array->elements[index] = element;
  // Increment count by 1
  array->count++;
}

/*****
 * Append an element to the end of the array
 *****/
void arr_append(Array *array, char *element) {

  // Resize the array if the number of elements is over capacity
  // or throw an error if resize isn't implemented yet.
  char *copy = (char *)element;
  // Copy the element and add it to the end of the array
  array->elements[array->count] = copy;
  // Increment count by 1
  array->count++;
}

/*****
 * Remove the first occurence of the given element from the array,
 * then shift every element after that occurence to the left one slot.
 *
 * Throw an error if the value is not found.
 *****/
void arr_remove(Array *array, char *element) {

  // Search for the first occurence of the element and remove it.
  // Don't forget to free its memory!
      for (int i = 0; i < array->count; i++)
    {
        if (strcmp(array->elements[i], element) == 0)
        {
            free(array->elements[i]);
            for (int x = i; x < array->count - i; x++)
            {
                array->elements[x] = array->elements[x + 1];
            }
        }
    }
  // Shift over every element after the removed element to the left one position
  // Decrement count by 1
  array->count--;

}


/*****
 * Utility function to print an array.
 *****/
void arr_print(Array *arr) {
  printf("[");
  for (int i = 0 ; i < arr->count ; i++) {
    printf("%s", arr->elements[i]);
    if (i != arr->count - 1) {
      printf(",");
    }
  }
  printf("]\n");
}


#ifndef TESTING
int main(void)
{

  Array *arr = create_array(1);

  arr_insert(arr, "STRING1", 0);
  arr_append(arr, "STRING4");
  arr_insert(arr, "STRING2", 0);
  arr_insert(arr, "STRING3", 1);
  arr_print(arr);
  arr_remove(arr, "STRING3");
  arr_print(arr);

  destroy_array(arr);

  return 0;
}
#endif

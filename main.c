#include "grouper.h"
#include <stdio.h>
#include <string.h>

#define MAX_OPERATIONS 50
typedef struct operation {
  int tLeft;
  int index;
  struct operation *next;
  struct operation *prev;
} operation;

int insert(int duration, operation *head, int index);
int execute(int shareTime, operation *head);
int main() {

  char history[MAX_OPERATIONS][MAX_OPERATIONS];
  for (int i = 0; i < MAX_OPERATIONS; i++) {
    history[i][0] = '\0';
  }

  int shareTime = 0;
  int queueLength = 0;
  do {
    printf("How many programs you will run ? : ");
    getInt(&queueLength);
  } while (queueLength <= 0);
  operation *op = NULL;
  do {
    printf("Share Time  : ");
    getInt(&shareTime);
  } while (shareTime <= 0);
  // printf("there is %d apps and %d share Time \n", queueLength, shareTime);
  for (int i = 0; i < queueLength; i++) {
    int duration = 0;
    do

    {
      printf("what is the duration of the operation number %i : ", i + 1);
      getInt(&duration);
    } while (duration <= 0);
    if (op)
      insert(duration, op, i);
    else {
      op = malloc(sizeof(operation));
      op->next = NULL;
      op->prev = NULL;
      op->tLeft = duration;
      op->index = i;
    }
  }
  // update history and simulate
  int queued = queueLength;
  while (queued > 0) {
    operation *active = op;
    int done = 0;
    do {
      if (active->tLeft > shareTime) {
        active->tLeft -= shareTime;
        for (int i = 0; i < done; i++) {
          strcat(history[active->index], "-");
        }
        strcat(history[active->index], "+");
        active = active->next;

      } else {
        operation *temp = active;
        active = active->next;
        if (temp->prev != NULL)
          temp->prev->next = temp->next;
        if (temp->next != NULL)
          temp->next->prev = temp->prev;
        free(temp);
        queued--;
      }
      done++;

    } while (active != NULL);
  }
  // print data
  for (int i = 0; i < queueLength; i++) {
    printf("operation N %i", i + 1);
    puts(history[i]);
  }
}

int insert(int duration, operation *head, int index) {
  if (head == NULL) {
    return 1;
  }
  if (head->next == NULL) {
    operation *temp = malloc(sizeof(operation));
    if (temp == NULL)
      return 69;
    temp->next = NULL;
    temp->prev = head;
    temp->tLeft = duration;
    temp->index = index;
    head->next = temp;
    return 0;
  } else {
    return insert(duration, head->next, index);
  }
}
int execute(int shareTime, operation *head) {}

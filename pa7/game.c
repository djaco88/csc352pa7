/* Author: Jacob Davis
Purpose:
*/
 
#include <stdlib.h>
#include <stdio.h>
#include "mq.h"


int checkItem(char item[]){
  int index = 1;
  printf("is it a "); 
  while (item[index] != '\0' && item[index] != '\n'){
    printf("%c", item[index]);
    index++;
  }
  printf("?\n");
  char yN = 'n';
  scanf("%c", &yN);
  fflush(stdin);
  if (yN == 'y'){
    printf("I guessed it!");
    return 1;
  }
  return 0;
}

void endGame(MQDecisionTreeNode * node){
    char yN = '1';
    printf("%s (y/n)\n", node->text);
    scanf("%c", &yN);
    fflush(stdin);
    if (yN == 'y'){
      yN = '1';
    } else if (yN == 'n'){
      yN = '0';
    } else {
      printf("input must be either 'y' or 'n'");
      endGame(node);
      return;
    }
    for (int i = 0; i < node->num_answers; i++){
      if (node->answers[i][0] == yN){
        if (checkItem(node->answers[i]) == 1){
          return;
        }
      }
    }
    printf("You got me :)");
}


/* MAIN: opens and reads file, calls necessary functions
*/
int main(int argc, char * argv[]){
  char direction = '1';
  MQDecisionTree* tree = MQ_build_tree(argv[1]);
  MQ_populate_tree(tree, argv[1]);
  // mqPrintTree(tree);
  MQDecisionTreeNode* cur = tree->root;
  while(cur->yes != NULL && cur->no != NULL){
    printf("%s (y/n)\n", cur->text);
    scanf("%c", &direction);
    fflush(stdin);
    if (direction == 'y'){
      cur = cur->yes;
    } else if (direction == 'n'){
      cur = cur->no;
    } else {
      printf("input must be either 'y' or 'n'");
    }
  }
  endGame(cur);
  MQ_free_tree(tree); 
  return 0;
}

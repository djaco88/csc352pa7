/* Author: Jacob Davis                                                                                                                                                                                                                      
Purpose: implement the zstr library fucntion
*/
 
#include <stdlib.h>
#include <stdio.h>
#include "mq.h"

//                                         
void MQ_print_tree(MQDecisionTree* root){
  // may have to do root->root->variable
  printf("%s\n", root->txt);
  printf("-y-> ");
  MQ_print_tree(root->yes);
  printf("-n-> ");
  MQ_print_tree(root->no);
}

// build single node
// this needs a lot of work
MQDecisionTreeNode* createNode(char txt[]){
  MQDecisionTreeNode* mq = malloc(sizeof(MQDecisionTreeNode));
  mq->text = txt;
  mq->yes = NULL;
  mq->no = NULL;
  mq->num_answers = 0;
  mq->answers = NULL; 
}

void addNode(MQDecisionTreeNode* node, char txt[], int levels){
  if (node->yes == NULL || node->no == NULL){
    node->yes = createNode(txt);
    node->no = createNode(txt);
    return;
  } else {
    addNode(node->yes, txt);
    addNode(node->no, txt);
  }
}
//                                         
MQDecisionTree* mqBuildTree(char* file_name){

  FILE* mqFile = fopen(argv[1], "r");

  if (mqFile == NULL){ fprintf(stderr, "bad\n"); return 1;} 
  
  int numItems = 0;
  int flag = 0; 
  MQDecisionTree* root = malloc(sizeof(MQDecisionTree));
  // the buffer limit may be iffy.
  // change to large number before submission-------------------------------------------------------------------
  char buffer[1051];
  while (fgets(buffer,1050,playersData) != NULL){
    if (flag == 0){
      numItems = atoi(buffer);
      flag++;
    }
    int bufferIndex=0;
    int questionIndex=0;
    char question[51];
    int qNumber = 0;
    while(buffer[bufferIndex] != '\0'){
      //Just in case, make sure no question in more than 50 chars
      if (questionIndex == 52 || bufferIndex > 1050){
        printf("ERROR: question length out of bounds OR buffer line wrap issues");
      }
      // need to connect nodes to tree
      if (buffer[index] == ','){
        question[questionIndex] = '\0';
        qNumber++;
        if (qNumber == 1){
          root->root = createNode(question);
        } else {
	  addNode(root->root, question, qNum);
        }
        questionIndex = 0;
        bufferIndex++;
      } 
      else {
        question[questionIndex] = buffer[bufferIndex]; 
        questionIndex++;
        bufferIndex++;
    }
  }
  fflush(mqFile);
  fclose(mqFile);
  return newMq;
}
                                           
//                                         
void MQ_populate_tree(MQDecisionTree* tree, char* file_name){

}
                                           
//                                         
void MQ_free_tree(MQDecisionTree* tree){

} 

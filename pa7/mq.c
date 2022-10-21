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

// this helper function should traverse the tree,
// find the leaf nodes, and create new leaf nodes
// as the childen of the previous leaf nodes
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

// This function will look at only the second line of the input file
// This line will house all of the questions for the mq game
// The first question will be used to create the root node
// Each question will be added as both children of all the 
// leaf nodes on the tree.
// The tree will be returned                                        
MQDecisionTree* mqBuildTree(char* file_name){

  FILE* mqFile = fopen(argv[1], "r");
  if (mqFile == NULL){ fprintf(stderr, "bad\n"); return 1;} 
 
  // flag to locate the second line in the file 
  int flag = 0; 
  
  // create the tree
  MQDecisionTree* root = malloc(sizeof(MQDecisionTree));

  // the buffer limit may be iffy.
  // change to large number before submission-------------------------------------------------------------------
  char buffer[1051];
  while (fgets(buffer,1050,playersData) != NULL){
    if (flag == 0){
      flag++;
    }
    int bufferIndex=0;
    int questionIndex=0;
    char question[51];
    int qNumber = 0;
    // loop through each char in the 2nd line of the buffer
    // at each ',' add the stored char[] as nodes to all leaves
    // in the tree
    while(buffer[bufferIndex] != '\0'){
      //Just in case, make sure no question in more than 50 chars
      if (questionIndex == 52 || bufferIndex > 1050){
        printf("ERROR: question length out of bounds OR buffer line wrap issues");
      }
      // need to connect nodes to tree
      if (buffer[index] == ','){
        question[questionIndex] = '\0';
        qNumber++;
        // create the root node and set it in the tree
        if (qNumber == 1){
          root->root = createNode(question);
        } 
        // add new nodes to leaves
        else {
	  addNode(root->root, question);
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
  }
  // *I think I fixed this lol*
  // NEED TO ADD THE LAST QUESTION!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  addNode(root->root, question);
  fflush(mqFile);
  fclose(mqFile);
  return newMq;
}
                                           
// goes through all the items in the file and adds
// them to the tree in the correct places                                         
void mqPopulateTree(MQDecisionTree* tree, char* file_name){

  FILE* mqFile = fopen(argv[1], "r");
  if (mqFile == NULL){ fprintf(stderr, "bad\n"); return 1;} 
 
  // flag to locate the 3+ lines in the file 
  int flag = 0;
  // set root as cur 
  MQDecisionTreeNode* cur = tree->root;   

  // the buffer limit may be iffy.
  // change to large number before submission-------------------------------------------------------------------
  char buffer[1051];
  while (fgets(buffer,1050,playersData) != NULL){
    if (flag == 0){
      numItems = atoi(buffer);
      flag++;
    } else if (flag == 1){
      flag++;
    } else {
      int bufferIndex=0;
      int itemIndex=0;
      char item[51];
      char itemName[51];
      int qNumber = 0;
      // loop through each char in the 2nd line of the buffer
      // at each ',' add the stored char[] as nodes to all leaves
      // in the tree
      while(buffer[bufferIndex] != '\0'){
	//Just in case, make sure no item in more than 50 chars
	if (itemIndex == 52 || bufferIndex > 1050){
	  printf("ERROR: item length out of bounds OR buffer line wrap issues");
	}
	if (buffer[index] == ','){
	  item[itemIndex] = '\0';
	  qNumber++;
	  // save name and find where to insert the node
	  if (qNumber == 1){
	    // this may cause problems ----------------------------------------------------------------
	    itemName == item;
	  }
	  // go down the tree  
	  else if (item[0] == '1'){
	    cur = cur->yes;
	  } else {
	    cur = cur->no;
	  }
	  itemIndex = 0;
	  bufferIndex++;
	} 
	else {
	  item[itemIndex] = buffer[bufferIndex]; 
	  itemIndex++;
	  bufferIndex++;
	}
      }
    }
  }
  // TODO: finish the process. at this point i should have the last y/n value stored at item[0]
  // I need to malloc space for the name, add the count of answers, and somehow differenciate between yes and no answers
  fflush(mqFile);
  fclose(mqFile);
}
                       
void freeNodes(MQDecisionTreeNode* cur){
  if (cur->yes == NULL){
    // TODO: FREE THE ANSWER SPACE############################################################################
    free(cur);
    return;
  }
  freeNodes(cur->yes);
  freeNodes(cur->no);
  free(cur);
}                    
//                                         
void mqFreetree(MQDecisionTree* tree){
  freeNodes(tree->root);

} 

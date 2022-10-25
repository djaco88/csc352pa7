/* Author: Jacob Davis
Purpose: implement the zstr library fucntion
*/
#include <stdlib.h>
#include <stdio.h>
#include "mq.h"

//
void printNodes(MQDecisionTreeNode* node){
  if (node->yes == NULL){
    printf("-y-> ");
    printf("-n-> ");
    return;
  }
  printf("%s\n", node->text);
  printf("-y-> ");
  printNodes(node->yes);
  printf("-n-> ");
  printNodes(node->no);
}

//                                         
void MQ_print_tree(MQDecisionTree* root){
  printNodes(root->root);
}

// build single node
// this needs a lot of work
MQDecisionTreeNode* createNode(char txt[]){
  MQDecisionTreeNode* mq = malloc(sizeof(MQDecisionTreeNode));
  // copy the given string into the text var in the node
  for (int i = 0; i < 49; i++){
    mq->text[i] = txt[i];
    if (txt[i] == '\0'){
      break;
    }
  }
  mq->yes = NULL;
  mq->no = NULL;
  mq->num_answers = 0;
  mq->answers = NULL;
  return mq;
}

// this helper function should traverse the tree,
// find the leaf nodes, and create new leaf nodes
// as the childen of the previous leaf nodes
void addNode(MQDecisionTreeNode* node, char txt[]){
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
MQDecisionTree* mqBuildTree(char* fileName){

  FILE* mqFile = fopen(fileName, "r");
  if (mqFile == NULL){ fprintf(stderr, "bad\n"); return NULL;} 
 
  // flag to locate the second line in the file 
  int flag = 0; 
  char question[51];
  
  // create the tree
  MQDecisionTree* root = malloc(sizeof(MQDecisionTree));

  // the buffer limit may be iffy.
  // change to large number before submission-------------------------------------------------------------------
  char buffer[1051];
  while (fgets(buffer,1050,mqFile) != NULL){
    if (flag == 0){
      flag++;
    }
    int bufferIndex=0;
    int questionIndex=0;
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
      if (buffer[bufferIndex] == ','){
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
  return root;
}
                                      
// goes through all the items in the file and adds
// them to the tree in the correct places                                         
void mqPopulateTree(MQDecisionTree* tree, char* fileName){

  FILE* mqFile = fopen(fileName, "r");
  if (mqFile == NULL){ fprintf(stderr, "bad\n"); return;} 
 
  // flag to locate the 3+ lines in the file 
  int flag = 0;
  // set root as cur 
  MQDecisionTreeNode* cur = tree->root;   
  int numItems;

  // the buffer limit may be iffy.
  // change to large number before submission-------------------------------------------------------------------
  char buffer[1051];
  while (fgets(buffer,1050,mqFile) != NULL){
    if (flag == 0){
      numItems = atoi(buffer);
      printf("Number of items: %d\n", numItems);
      flag++;
    } else if (flag == 1){
      flag++;
    } else {
      int bufferIndex=0;
      int itemIndex=0;
      char item[50];
      char itemName[50];
      int qNumber = 0;
      // loop through each char in the 2nd line of the buffer
      // at each ',' add the stored char[] as nodes to all leaves
      // in the tree
      while(buffer[bufferIndex] != '\0'){
	//Just in case, make sure no item in more than 50 chars
	if (itemIndex == 52 || bufferIndex > 1050){
	  printf("ERROR: item length out of bounds OR buffer line wrap issues");
	}
	if (buffer[bufferIndex] == ','){
	  item[itemIndex] = '\0';
	  qNumber++;
	  // save name and find where to insert the node
	  if (qNumber == 1){
            // copy name into new char[]
            for (int i = 0; i < 49; i++){
              itemName[i] = item[i];
              if (item[i] == '\0'){
                break;
              }
            }
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
  // TODO: finish the process. at this point i should have the last y/n value stored at item[0] (either 1 or 0)
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

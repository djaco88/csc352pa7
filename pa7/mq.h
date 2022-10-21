/* Author: Jacob Davis
Purpose:
*/

#ifndef BT_H   
#define BT_H
            
typedef struct MQDecisionTreeNode {
char text[50];
int num_answers;
char** answers;
struct MQDecisionTreeNode* yes;
struct MQDecisionTreeNode* no; 
} MQDecisionTreeNode;
            
               
typedef struct MQDecisionTree {
MQDecisionTreeNode* root;                                                                                                                                                                                                                   
} MQDecisionTree;



//
void MQ_print_tree(MQDecisionTree* root);

//
MQDecisionTree* MQ_build_tree(char* file_name);

//
void MQ_populate_tree(MQDecisionTree* tree, char* file_name);

//
void MQ_free_tree(MQDecisionTree* tree);

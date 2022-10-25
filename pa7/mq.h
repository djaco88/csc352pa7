/* Author: Jacob Davis
Purpose:
*/

//#ifndef BT_H   
//#define BT_H
            
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
void mqPrintTree(MQDecisionTree* root);

//
MQDecisionTree* mqBuildTree(char* file_name);

//
void mqPopulateTree(MQDecisionTree* tree, char* file_name);

//
void mqFreeTree(MQDecisionTree* tree);

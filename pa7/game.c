/* Author: Jacob Davis
Purpose:
*/
 
#include <stdlib.h>
#include <stdio.h>
#include "mq.h"


/* MAIN: opens and reads file, calls necessary functions
*/
int main(int argc, char * argv[]){
  MQDecisionTree* tree = mqBuildTree(argv[1]);
  mqPrintTree(tree);
  mqFreeTree(tree); 
  return 0;
}

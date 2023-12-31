// Created by Ethan Edwards for CS315 at SSU
#include <iostream>

#include "BinSearchTree.hpp"
#include "TreeNode.hpp"

#include <fstream>
#include <vector>
#include <chrono>

// TEST SOLUTIONS
#define TEST_SIZE 28
#define TEST_MAXDEPTH 10
#define TEST_FIND 1
#define TEST_INSERT_ONE 84
#define TEST_INSERT_TWO 100
// TOGGLES
#define VERBOSE false

// Utils
BinSearchTree* treeBuilder(std::string fName){
    std::fstream inputStream;
    inputStream.open(fName, std::ios::in);
    if(!inputStream.is_open()) {
        std::cout << "Unable to open the input file " << fName << std::endl;
        std::cout << "Terminating...\n";
        exit(7);
    }

    BinSearchTree *tree = new BinSearchTree();
    int aValue;
    while( inputStream >> aValue ) {
        tree->insert(aValue);
    }
    return tree;
}

// Tests
int testZero(BinSearchTree& tree){
    return tree.size() == TEST_SIZE;
}

int testOne(BinSearchTree& tree){
    return tree.maxDepth() == TEST_MAXDEPTH;
}

int testTwo(BinSearchTree& tree){
    return tree.find(TEST_INSERT_ONE) == TEST_FIND && tree.find(TEST_INSERT_TWO) != TEST_FIND;
}

int testThree(BinSearchTree& tree){
    return tree.iterFind(TEST_INSERT_ONE) == TEST_FIND && tree.iterFind(TEST_INSERT_TWO) != TEST_FIND;
}

void testFour(BinSearchTree& tree){
    std::cout << "Testing inorder dump...\n";
    tree.inorderDump();
    std::cout << "\n30 31 32 34 35 36 38 39 41 43 54 55 56 67 72 75 79 84 85 87 89 101 104 108 116 117 120 122" << std::endl;
    std::cout << "Test should equal the above ^\n";
}

int testFive(BinSearchTree& tree){
    tree.insert(100);
    return tree.find(100) == TEST_FIND;
}

void testSix(BinSearchTree& tree){
    std::cout << "Testing level order dump...\n";
    tree.levelOrderDump();
    std::cout << "\n36 32 104 30 35 89 120 31 34 43 101 117 122 41 79 108 39 54 85 116 38 56 84 87 55 75 67 72" << std::endl;
    std::cout << "Test should equal the above ^\n";
}

std::vector<int> testSeven(BinSearchTree& tree){
    std::vector<int> tests;
    std::vector<int> testIntsTrue = {34, 38, 101};
    std::vector<int> testIntsFalse = {100, 200, 300};
    for (int i : testIntsTrue){ // These should all be true
        tests.push_back(tree.remove(i) && !tree.find(i));
    }
    for (int i : testIntsFalse){ // These should all be false
        tests.push_back(!tree.remove(i) && !tree.find(i));
    }
    return tests;
}

std::vector<int> testEight(BinSearchTree& tree){
    std::vector<int> tests;
    std::vector<int> testInts = {4, 8, 10, 20, 11, 9};
    std::vector<int> answerInts = {34, 39, 43, 87, 54, 41};
    for (int i = 0; i < testInts.size(); i++){
        int tmp = tree.kthSmallest(testInts.at(i));
        if (tmp != answerInts.at(i)){
            tests.push_back(0);
        }
        else {
            tests.push_back(1);
        }
    }
    return tests;
}

void testNine(BinSearchTree& tree){
    std::cout << "Testing values at level [1]:\n";
    tree.valuesAtLevel(1);
    std::cout << "\n36" << std::endl;
    std::cout << "Test should equal the above ^\n";

    std::cout << "Testing values at level [3]:\n";
    tree.valuesAtLevel(3);
    std::cout << "\n30 35 89 120" << std::endl;
    std::cout << "Test should equal the above ^\n";

    std::cout << "Testing values at level [4]:\n";
    tree.valuesAtLevel(4);
    std::cout << "\n31 34 43 101 117 122" << std::endl;
    std::cout << "Test should equal the above ^\n";

    std::cout << "Testing values at level [8]:\n";
    tree.valuesAtLevel(8);
    std::cout << "\n55 75" << std::endl;
    std::cout << "Test should equal the above ^\n";
}

void testTen(BinSearchTree& tree){
    std::cout << "Testing iterative values at level [1]:\n";
    tree.iterValuesAtLevel(1);
    std::cout << "\n36" << std::endl;
    std::cout << "Test should equal the above ^\n";

    std::cout << "Testing iterative values at level [3]:\n";
    tree.iterValuesAtLevel(3);
    std::cout << "\n30 35 89 120" << std::endl;
    std::cout << "Test should equal the above ^\n";

    std::cout << "Testing iterative values at level [4]:\n";
    tree.iterValuesAtLevel(4);
    std::cout << "\n31 34 43 101 117 122" << std::endl;
    std::cout << "Test should equal the above ^\n";

    std::cout << "Testing iterative values at level [8]:\n";
    tree.iterValuesAtLevel(8);
    std::cout << "\n55 75" << std::endl;
    std::cout << "Test should equal the above ^\n";
}

bool testEleven(BinSearchTree& tree){
    return tree.iterMaxDepth() == TEST_MAXDEPTH;
}

std::vector<int> testTwelve(BinSearchTree& tree){
    std::vector<int> testResults, testsTrue = {137, 675, 485}, testsFalse = {100, 110, 5};
    for (int i : testsTrue){testResults.push_back(tree.hasRootToLeafSum(i));}
    for (int i : testsFalse){testResults.push_back(!tree.hasRootToLeafSum(i));}
    return testResults;
}

std::vector<int> testThirteen(BinSearchTree& firstTree, std::string fName){
    BinSearchTree *secondTree = treeBuilder(fName), *thirdTree = treeBuilder(fName), *fourthTree = treeBuilder(fName);
    thirdTree->insert(100); thirdTree->insert(200); thirdTree->insert(300);
    fourthTree->insert(10); fourthTree->insert(20); fourthTree->insert(15);
    std::vector<int> testResults;
    testResults.push_back(firstTree.areIdentical(secondTree));
    testResults.push_back(!firstTree.areIdentical(thirdTree));
    testResults.push_back(!firstTree.areIdentical(fourthTree));
    return testResults;
}

void testFourteen(BinSearchTree *tree){
    std::cout << "Testing intersect...\n";
    BinSearchTree *secondTree = treeBuilder("moreInputNumbers.txt");
    std::cout << "Intersection 1:\n";
    BinSearchTree *intersectTree = tree->intersectWith(secondTree);
    intersectTree->inorderDump();
    std::cout << "\n38 41 85 101\n";
    std::cout << "Test should equal the above ^\n";
    std::cout << "Intersection 2:\n";
    BinSearchTree *thirdTree = treeBuilder("moreInputNumbers2.txt");
    intersectTree = secondTree->intersectWith(thirdTree);
    intersectTree->inorderDump();
    std::cout << "\n421 478 500 942\n";
    std::cout << "Test should equal the above ^\n";
}

void testFifteen(BinSearchTree *tree){
    std::cout << "Testing union...\n";
    BinSearchTree *secondTree = treeBuilder("moreInputNumbers.txt");
    BinSearchTree *thirdTree = treeBuilder("moreInputNumbers2.txt");
    std::cout << "Union 1:\n";
    BinSearchTree *unionTree = tree->unionWith(secondTree);
    unionTree->inorderDump();
    std::cout << "\n\n";
    std::cout << "Test should equal the above ^\n";
    std::cout << "Union 2:\n";
    unionTree = secondTree->unionWith(thirdTree);
    unionTree->inorderDump();
    std::cout << "\n\n";
    std::cout << "Test should equal the above ^\n";
    std::cout << "Union 3:\n";
    unionTree = tree->unionWith(thirdTree);
    unionTree->inorderDump();
    std::cout << "\n\n";
    std::cout << "Test should equal the above ^\n";
}

void testSixteen(BinSearchTree *tree){
    std::cout << "Testing difference...\n";
    BinSearchTree *secondTree = treeBuilder("moreInputNumbers.txt");
    BinSearchTree *thirdTree = treeBuilder("moreInputNumbers2.txt");
    BinSearchTree *differenceTree = tree->differenceOf(secondTree);
    std::cout << "Difference 1:\n";
    differenceTree->inorderDump();
    std::cout << "\n\n";
    std::cout << "Test should equal the above ^\n";
    differenceTree = secondTree->differenceOf(thirdTree);
    std::cout << "Difference 2:\n";
    differenceTree->inorderDump();
    std::cout << "\n\n";
    std::cout << "Test should equal the above ^\n";
}

bool bigTestsSingle(){
    bool testResult = true;
    auto start = std::chrono::high_resolution_clock::now();
    BinSearchTree *bigTree = treeBuilder("bigTest1.txt");
    // Stress testing only, not for actual checking
    try {
        bigTree->size();
        bigTree->maxDepth();
        bigTree->iterMaxDepth();
        bigTree->find(100);
        bigTree->iterFind(100);
        bigTree->hasRootToLeafSum(1000);
        bigTree->kthSmallest(100);
        bigTree->remove(100);
        bigTree->valuesAtLevel(25);
        bigTree->iterValuesAtLevel(25);
    } catch (std::exception &e){
        std::cout << "Exception caught: " << e.what() << std::endl;
        testResult = false;
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);
    std::cout << "Time taken by single-tree tests: " << duration.count() << " microseconds" << std::endl;
    return testResult;
}

bool bigTestsMult(){
    bool testResult = true;
    auto start = std::chrono::high_resolution_clock::now();
    BinSearchTree *bigTree = treeBuilder("bigTest1.txt");
    BinSearchTree *bigTree2 = treeBuilder("bigTest2.txt");
    try{
        bigTree->areIdentical(bigTree2);
        bigTree->intersectWith(bigTree2);
        bigTree->unionWith(bigTree2);
        bigTree->differenceOf(bigTree2);
    } catch (std::exception &e){
        std::cout << "Exception caught: " << e.what() << std::endl;
        testResult = false;
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);
    std::cout << "Time taken by multi-tree tests: " << duration.count() << " microseconds" << std::endl;
    return testResult;
}

// Utils
void randomNumberGenerator(int n){
    for (int i = 0; i < n; i++){
        std::cout << rand() % 100 << "\n";
    }
}

// Main
int main( int argc, char *argv[] ) {
    // create a tree and then print the values of its nodes
    // from the smallest to the largest.

    if( argc != 2 ) {
        std::cout << "usage: executable name-of-input-file\n";
        exit(5);
    }
    std::string fName = argv[1];

    BinSearchTree *tree = treeBuilder(fName);

    bool testResult = bigTestsSingle();
    if (testResult){std::cout << "Big tests passed.\n";}
    else {std::cout << "Big tests failed.\n";}

    testResult = bigTestsMult();
    if (testResult){std::cout << "Big tests mult passed.\n";}
    else {std::cout << "Big tests mult failed.\n";}

    // Utils
    //randomNumberGenerator(32);

    // Tests
    int testNum = 0;
    std::vector<int> testResults;
    std::vector<std::vector<int>> multiTestResults;
    testResults.push_back(testZero(*tree));
    testResults.push_back(testOne(*tree));
    testResults.push_back(testTwo(*tree));
    testResults.push_back(testThree(*tree));
    if (VERBOSE){testFour(*tree);} else {std::cout << "Skipping inorder dump [4]\n";}
    testResults.push_back(testFive(*tree));
    tree = treeBuilder(fName);
    if (VERBOSE){testSix(*tree);} else {std::cout << "Skipping level order dump [6]\n";}
    std::cout << "Running simple tests...\n";
    for (int i : testResults){
        if (i == 0){
            std::cout << "Test " << testNum << " failed." << std::endl;
        }
        else {
            std::cout << "Test " << testNum << " passed." << std::endl;
        }
        if (testNum == 3 || testNum == 5){
            testNum += 2;
        }
        else {
            testNum++;
        }
    }
    std::cout << "Running multi tests...\n";
    multiTestResults.push_back(testSeven(*tree));
    tree = treeBuilder(fName);
    multiTestResults.push_back(testEight(*tree));
    int iter = 7;
    for (std::vector<int> i : multiTestResults){
        std::cout << "Results for test " << iter << ":" << std::endl;
        for (int j = 0; j < i.size(); j++){
            if (i.at(j) == 0){std::cout << "FAILED TEST: " << j << std::endl;}
            else {std::cout << "OK" << std::endl;}
        }
        iter++;
    }
    if (VERBOSE){
        std::cout << "Running level tests...\n";
        tree = treeBuilder(fName);
        std::cout << "Results for test 9:" << std::endl;
        testNine(*tree);
        std::cout << "Results for test 10:" << std::endl;
        testTen(*tree);
    } else {std::cout << "Skipping level tests [9-10]\n";}

    std::cout << "Results for test 11:" << std::endl;
    if (testEleven(*tree)){std::cout << "OK" << std::endl;}
    else {std::cout << "FAILED TEST 11" << std::endl;}

    std::cout << "Results for test 12:" << std::endl;
    for (int i : testTwelve(*tree)){
        if (i == 0){std::cout << "FAILED TEST" << std::endl;}
        else {std::cout << "OK" << std::endl;}
    }

    std::cout << "Results for test 13:" << std::endl;
    for (int i : testThirteen(*tree, fName)){
        if (i == 0){std::cout << "FAILED TEST" << std::endl;}
        else {std::cout << "OK" << std::endl;}
    }

    std::cout << "Results for test 14:" << std::endl;
    testFourteen(tree);

    std::cout << "Results for test 15:" << std::endl;
    testFifteen(tree);

    std::cout << "Results for test 16:" << std::endl;
    testSixteen(tree);

    return 0;
}

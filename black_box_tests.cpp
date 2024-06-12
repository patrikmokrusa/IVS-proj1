//======= Copyright (c) 2024, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     Patrik Mokruša <xmokrup00@stud.fit.vutbr.cz>
// $Date:       $2024-02-14
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author Patrik Mokruša
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include "gtest/gtest.h"

#include "red_black_tree.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//



class EmptyTree : public ::testing::Test{
protected:
    BinaryTree tree;
};

class NonEmptyTree : public ::testing::Test{
protected:
    BinaryTree tree;
    virtual void SetUp(){
        int val []= {2,1,5};
        for (int val :val) {
            tree.InsertNode(val);
        }
    }
};

class TreeAxioms : public ::testing::Test{
protected:
    BinaryTree tree;
    virtual void SetUp(){
        int val []= {2,1,5};
        for (int val :val) {
            tree.InsertNode(val);
        }
    }
};


TEST_F(EmptyTree, InsertNode){
    auto result = tree.InsertNode(2);
    EXPECT_TRUE (result.first);
    EXPECT_EQ( result.second->key, 2);

    auto result2 = tree.InsertNode(2);
    EXPECT_FALSE(result2.first);
    EXPECT_EQ(result2.second, result.second);
}

TEST_F(EmptyTree, DeleteNode){
    tree.InsertNode(2);
    auto result = tree.DeleteNode(2);
    EXPECT_TRUE(result);

    auto result2 = tree.DeleteNode(99);
    EXPECT_FALSE(result2);
}

TEST_F(EmptyTree, FindNode){
    tree.InsertNode(2);
    tree.InsertNode(5);
    tree.InsertNode(1);

    auto result = tree.FindNode(2);
    EXPECT_TRUE(result);
    
    auto result2 = tree.FindNode(69);
    EXPECT_EQ(result2, nullptr);
}

TEST_F(NonEmptyTree, InsertNode){
    auto result = tree.InsertNode(6);
    EXPECT_TRUE (result.first);
    EXPECT_EQ( result.second->key, 6);

    auto result2 = tree.InsertNode(6);
    EXPECT_FALSE(result2.first);
    EXPECT_EQ(result2.second, result.second);
}

TEST_F(NonEmptyTree, FindNode){
    auto result = tree.FindNode(2);
    EXPECT_TRUE(result);

    auto result2 = tree.FindNode(69);
    EXPECT_EQ(result2, nullptr);    
}

TEST_F(NonEmptyTree, DeleteNode){
    auto result = tree.DeleteNode(2);
    EXPECT_TRUE(result);

    auto result2 = tree.DeleteNode(99);
    EXPECT_FALSE(result2);
}

TEST_F(TreeAxioms, Axiom1){ //vsechny listove (bezpotomku) uzly jsou cerne
    std::vector<Node_t *> leaf;

    tree.GetLeafNodes(leaf);
    for(auto result : leaf){
        EXPECT_EQ(result->color, BLACK);
    }
}

TEST_F(TreeAxioms, Axiom2){ //pokud je uzel cerveny, tak oba jeho potomci jsou cerne
    for(int i : {2,1,5}){
        auto result = tree.FindNode(i);
        if(result->color==RED){
            EXPECT_EQ(result->pLeft->color, BLACK);
            EXPECT_EQ(result->pRight->color, BLACK);
        }
        else{
            EXPECT_EQ(result->color, BLACK);
        }
        
    }
}

TEST_F(TreeAxioms, Axiom3){ //kazda cesta od kazdeho listoveho uzlu ke koreni obsahuje stejny pocet cernych uzlu
    std::vector<Node_t *> leaf;

    tree.GetLeafNodes(leaf);
    auto topnode = tree.FindNode(2);

    for(auto result: leaf){
        EXPECT_EQ(result->pParent->pParent,topnode);
        EXPECT_EQ(result->pParent->pParent, tree.FindNode(2));
    }
}

/*** Konec souboru black_box_tests.cpp ***/

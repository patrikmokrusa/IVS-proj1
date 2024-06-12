//======= Copyright (c) 2024, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - test suite
//
// $NoKeywords: $ivs_project_1 $white_box_tests.cpp
// $Author:     Patrik Mokruša <xmokrup00@stud.fit.vutbr.cz>
// $Date:       $2024-02-14
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author Patrik Mokruša
 * 
 * @brief Implementace testu hasovaci tabulky.
 */

#include <vector>

#include "gtest/gtest.h"

#include "white_box_code.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy hasovaci tabulky, testujte nasledujici:
// 1. Verejne rozhrani hasovaci tabulky
//     - Vsechny funkce z white_box_code.h
//     - Chovani techto metod testuje pro prazdnou i neprazdnou tabulku.
// 2. Chovani tabulky v hranicnich pripadech
//     - Otestujte chovani pri kolizich ruznych klicu se stejnym hashem 
//     - Otestujte chovani pri kolizich hashu namapovane na stejne misto v 
//       indexu
//============================================================================//

class EmptyHashMap : public ::testing::Test {

protected:
    hash_map_t* map = hash_map_ctor();    
};


class NonEmptyHashMap : public ::testing::Test {

protected:
    hash_map_t* map = hash_map_ctor();    
    virtual void SetUp(){
        hash_map_state_code_t is_value_overwritten = hash_map_put(map, "aloha", 5);
    }
};

TEST_F(EmptyHashMap, re_alloc_ctor){
     
    EXPECT_NO_THROW(map = hash_map_ctor());
};

TEST_F(NonEmptyHashMap, collision){

    hash_map_put(map, "abbc", 1);
    int value1;
    hash_map_get(map,"abbc",&value1);

    hash_map_put(map, "a", 2);
    hash_map_put(map, "ab", 3);
    hash_map_put(map, "ala", 4);

    int value2;
    auto error = hash_map_get(map,"abbc",&value2);
    EXPECT_EQ(error, OK);





    hash_map_put(map, "oha", 6); // tady se to rozbyje
    // predpokladam ze ^^^^ tento zaznam zpusobuje kolizi
    // takze 2 ruzne hashe jsou mapovany na stejny index

    // "oha" prepise "abbc"

    int value3;
    auto error2 = hash_map_get(map,"abbc",&value3);
    EXPECT_EQ(error2, OK);





    hash_map_put(map, "loha", 7);
    hash_map_put(map, "alohfffa", 8);

    EXPECT_EQ(hash_map_size(map), 8);
    int value4;
    auto error3 = hash_map_get(map,"oha",&value4);
    EXPECT_EQ(error3, OK);


    EXPECT_EQ(value1, value2);
    EXPECT_EQ(value2, value3);
};

TEST_F(NonEmptyHashMap, clear_dtor){
    hash_map_clear(map);
    int value;
    auto error = hash_map_get(map, "aloha", &value);
    EXPECT_EQ(error, KEY_ERROR);

    
    EXPECT_NO_THROW(hash_map_dtor(map));
    // auto error2 = hash_map_get(map, "aloha", &value);
    // EXPECT_EQ(error2, MEMORY_ERROR);

};

TEST_F(EmptyHashMap, put_get){
    hash_map_state_code_t is_value_overwritten = hash_map_put(map, "aloha", 5);
    EXPECT_EQ(is_value_overwritten, OK);
    is_value_overwritten = hash_map_put(map, "aloha", 5);
    EXPECT_EQ(is_value_overwritten, KEY_ALREADY_EXISTS);

    int value;
    hash_map_state_code_t error = hash_map_get(map, "aloha", &value);
    EXPECT_EQ(error, OK);
    error = hash_map_get(map, "BRIKULE", &value);
    EXPECT_EQ(error, KEY_ERROR);
};

TEST_F(NonEmptyHashMap, put_extended){
    hash_map_reserve(map, 1);
    hash_map_state_code_t is_value_overwritten = hash_map_put(map, "gregor", 69);
    EXPECT_EQ(is_value_overwritten, OK);
};

TEST_F(EmptyHashMap, reserve){
    auto error = hash_map_reserve(map, 16);
    EXPECT_EQ(error, OK);

    hash_map_put(map, "mamlas", 1);
    hash_map_put(map, "magor", 2);
    auto error2 = hash_map_reserve(map, 1);
    EXPECT_EQ(error2, VALUE_ERROR);    

    hash_map_reserve(map,2);
    auto error3 = hash_map_reserve(map,2);
    EXPECT_EQ(error3, OK);
};

TEST_F(NonEmptyHashMap, pop){
    int value;
    hash_map_state_code_t error = hash_map_pop(map, "aloha", &value);
    EXPECT_EQ(error, OK);
    error = hash_map_pop(map, "aloha", &value);
    EXPECT_EQ(error, KEY_ERROR);
};

TEST_F(NonEmptyHashMap, pop_coverage){
    hash_map_put(map, "gregor", 69);
    hash_map_put(map, "gizmo", 26);

    int value;
    auto error = hash_map_pop(map, "gregor", &value);
    EXPECT_EQ(error, OK);
};

TEST_F(NonEmptyHashMap, remove){
    hash_map_state_code_t error = hash_map_remove(map, "aloha");
    EXPECT_EQ(error, OK);

    error = hash_map_remove(map, "aloha");
    EXPECT_EQ(error, KEY_ERROR);
};

TEST_F(NonEmptyHashMap, contains){
    auto result = hash_map_contains(map, "abarakajna");
    EXPECT_EQ(result, NULL);
};

TEST_F(NonEmptyHashMap, size_capacity){
    auto result = hash_map_size(map);
    EXPECT_EQ(result, 1);

    auto result2 = hash_map_capacity(map);
    EXPECT_EQ(result2, 8);
};


/*** Konec souboru white_box_tests.cpp ***/

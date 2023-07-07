#include "../tree/binarytree.hpp"
#include <catch2/catch_test_macros.hpp>


TEST_CASE( "Simple binary tree", "[binarytree]" ) {
    BinaryTree<int> bt{2};
    REQUIRE( bt.getRootValue() == 2 );
    REQUIRE( bt.getRootLeft() == nullptr );
    REQUIRE( bt.getRootRight() == nullptr );

    bt.insert(1);
    REQUIRE( bt.getRootValue() == 2 );
    REQUIRE( bt.getRootLeft()->value == 1 );
    REQUIRE( bt.getRootRight()== nullptr );

    bt+= 3;
    REQUIRE( bt.getRootValue() == 2 );
    REQUIRE( bt.getRootLeft()->value == 1 );
    REQUIRE( bt.getRootRight()->value == 3);

    BinaryTree<int> bt2 = bt;
    REQUIRE( bt2.getRootValue() == 2 );
    REQUIRE( bt2.getRootLeft()->value == 1 );
    REQUIRE( bt2.getRootRight()->value == 3);
}

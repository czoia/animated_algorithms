#include "../tree/binarytree.hpp"
#include <catch2/catch_test_macros.hpp>
#include <iostream>


TEST_CASE( "Simple binary tree: creation", "[binarytree]" ) {
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


TEST_CASE( "Simple binary tree: search", "[binarytree]" ) {
    BinaryTree<int> bt{2};
    bt.insert(1);
    bt.insert(3);
    REQUIRE( bt.getRootValue() == 2 );
    REQUIRE( bt.getRootLeft()->value == 1 );
    REQUIRE( bt.getRootRight()->value == 3);

    REQUIRE( bt.contains(3));
    REQUIRE( !bt.contains(4));

    bt.insert(4);
    REQUIRE( bt.contains(4));
}


TEST_CASE( "Simple binary tree: print", "[binarytree]" ) {
    BinaryTree<int> bt{2};
    bt.insert(1);
    bt.insert(3);
    bt.insert(4);
    REQUIRE( bt.print() == " 2 1 3 4");

    bt.setOrder(VisitingOrder::PreOrder);
    REQUIRE( bt.print() == " 1 2 3 4");

    bt.setOrder(VisitingOrder::PostOrder);
    REQUIRE( bt.print() == " 1 4 3 2");
}

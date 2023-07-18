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

TEST_CASE( "Simple binary tree: delete", "[binarytree]" ) {
    BinaryTree<int> bt{2};
    bt.insert(1);
    bt.insert(3);
    bt.insert(4);
    REQUIRE( bt.print() == " 2 1 3 4");

    REQUIRE(bt.deleteElement(4));
    REQUIRE( bt.print() == " 2 1 3");

    REQUIRE(bt.deleteElement(2));
    REQUIRE( bt.print() == " 3 1");

    REQUIRE(bt.deleteElement(3));
    REQUIRE( bt.print() == " 1");

    REQUIRE(bt.deleteElement(1));
    REQUIRE( bt.print() == "");

    REQUIRE(!bt.deleteElement(1));

    bt.insert(10);
    bt.insert(7);
    bt.insert(5);
    bt.insert(8);
    bt.insert(9);

    bt.insert(15);
    bt.insert(16);
    bt.insert(14);
    bt.insert(13);
    REQUIRE( bt.print() == " 10 7 5 8 9 15 14 13 16");
    REQUIRE(bt.deleteElement(8));
    REQUIRE( bt.print() == " 10 7 5 9 15 14 13 16");
    REQUIRE(bt.deleteElement(14));
    REQUIRE( bt.print() == " 10 7 5 9 15 13 16");
}

TEST_CASE( "Simple binary tree: min/max", "[binarytree]" ) {
    BinaryTree<int> bt{10};
    bt.insert(7);
    bt.insert(5);
    bt.insert(8);
    bt.insert(9);

    bt.insert(15);
    bt.insert(16);
    bt.insert(14);
    bt.insert(13);

    REQUIRE( bt.getMax() == 16);
    REQUIRE( bt.getMin() == 5);

    BinaryTree<int> bt2;
    REQUIRE_THROWS_AS(bt2.getMax(), EmptyTreeException);
    REQUIRE_THROWS_AS(bt2.getMin(), EmptyTreeException);
}

TEST_CASE( "Simple binary tree: getHeight", "[binarytree]" ) {
    BinaryTree<int> bt{10};
    bt.insert(7);
    bt.insert(5);
    bt.insert(8);
    bt.insert(9);

    bt.insert(15);
    bt.insert(16);
    bt.insert(14);
    bt.insert(13);

    REQUIRE( bt.getHeight() == 4);

    bt.insert(4);
    bt.insert(3);
    bt.insert(2);
    bt.insert(1);

    REQUIRE( bt.getHeight() == 7);


    BinaryTree<int> bt2;
    REQUIRE( bt2.getHeight() == 0);
}


TEST_CASE( "Simple binary tree: balance a tree", "[binarytree]" ) {
    BinaryTree<int> bt{10};
    bt.insert(7);
    bt.insert(5);
    bt.insert(8);
    bt.insert(9);

    bt.insert(15);
    bt.insert(16);
    bt.insert(14);
    bt.insert(13);

    REQUIRE( bt.isBalanced());

    bt.insert(4);
    bt.insert(3);
    bt.insert(2);
    bt.insert(1);

    REQUIRE( !bt.isBalanced());

    bt.balance();
    REQUIRE( bt.isBalanced());
    bt.balance();
    BinaryTree<int> bt2;
    REQUIRE( bt2.isBalanced());
}

#define DOCTEST_CONFIG_IMPLEMENT
#include <vector>
#include <queue>
#include "../doctest.h"
#include "../../Comparator.h"
#include "../../HTree.h"
#include "../../HTree.cpp"

TEST_CASE("TESTING CONSTRUCTORS AND OPERATOR="){
    
    HTree t1;

    CHECK(t1.getCnt() == 0) ;
    CHECK(t1.getCharacterCode('A') == "") ;
    CHECK(t1.getCharacterCode('a') == "") ;

    HTree t2('A', 1);

    CHECK(t2.getCnt() == 1) ;
    CHECK(t2.getCharacterCode('A') == "") ;
    CHECK(t2.getCharacterCode('a') == "") ;

    HTree t3(t2);
    CHECK(t3.getCnt() == 1) ;
    CHECK(t3.getCharacterCode('A') == "") ;
    CHECK(t3.getCharacterCode('a') == "") ;

    t1 = t3;
    CHECK(t1.getCnt() == 1) ;
    CHECK(t1.getCharacterCode('A') == "") ;
    CHECK(t1.getCharacterCode('a') == "") ;

}

TEST_CASE("TESTING COPY CONSTRUCTOR WITH TWO OTHER OBJECTS"){

    HTree t1('C', 1);
    HTree t2('D', 1);
    HTree t3(t1, t2);

    CHECK(t3.getCnt() == 2);
    CHECK(t3.getCharacterCode('C') == "0");
    CHECK(t3.getCharacterCode('D') == "1");
    CHECK(t3.getCharacterCode('A') == "");
    CHECK(t3.getCharacterCode('a') == "");

    HTree t4(HTree('A', 1), t3);
    CHECK(t4.getCnt() == 3);
    CHECK(t4.getCharacterCode('C') == "10");
    CHECK(t4.getCharacterCode('D') == "11");
    CHECK(t4.getCharacterCode('A') == "0");
    CHECK(t4.getCharacterCode('a') == "");

}

TEST_CASE("CONSTRUCTING HUFFMAN TREE"){

    HTree t1('C', 1);
    CHECK(t1.getCnt() == 1);
    HTree t2('D', 1);
    CHECK(t2.getCnt() == 1);
    HTree t3(t1, t2);
          // 0    1

    CHECK(t3.getCnt() == 2);
    HTree t4(HTree('R', 2), t3);
            //      0       1
    CHECK(t4.getCnt() == 4);
    HTree t5(HTree('B', 2), t4);
            //      0       1
    CHECK(t5.getCnt() == 6);
    HTree t6(HTree('A', 5), t5);
            //      0        1
    CHECK(t6.getCnt() == 11);
    CHECK(t6.getCharacterCode('P') == "");
    CHECK(t6.getCharacterCode('a') == "");
    CHECK(t6.getCharacterCode('A') == "0");
    CHECK(t6.getCharacterCode('B') == "10");
    CHECK(t6.getCharacterCode('R') == "110");
    CHECK(t6.getCharacterCode('C') == "1110");
    CHECK(t6.getCharacterCode('D') == "1111");

}

TEST_CASE("TESTING COMPARATOR FOR PRIORITY QUEUE"){

    std::priority_queue<HTree, std::vector<HTree>, Comparator> queue;
    queue.push(HTree('A', 5));
    CHECK(queue.top().getCnt() == 5);
    queue.push(HTree('B', 4));
    CHECK(queue.top().getCnt() == 4);
    queue.push(HTree('R', 3));
    CHECK(queue.top().getCnt() == 3);
    queue.push(HTree('C', 2));
    CHECK(queue.top().getCnt() == 2);
    queue.push(HTree('D', 1));
    CHECK(queue.top().getCnt() == 1);
    queue.pop();
    CHECK(queue.top().getCnt() == 2);
    queue.pop();
    CHECK(queue.top().getCnt() == 3);
    queue.pop();
    CHECK(queue.top().getCnt() == 4);
    queue.pop();
    CHECK(queue.top().getCnt() == 5);
    queue.pop();
    CHECK(queue.empty());

}

int main(){
    
    doctest::Context().run();

    return 0;
}
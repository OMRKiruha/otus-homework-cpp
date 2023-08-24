#include "../MyVector.h"

#include <gtest/gtest.h>

//===================================================================
TEST(MyVector, Empty) {
    MyVector<int> vector;

    ASSERT_EQ(vector.size(), 0);
    ASSERT_EQ(vector.begin(), static_cast<MyVecIterator<int>>(nullptr));
    ASSERT_EQ(vector.begin(), vector.end());
}

//===================================================================
TEST(MyVector, PushBack) {
    const int count = 10;
    MyVector<int> vector;
    int sample[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    for (auto i = 0; i < count; ++i) {
        vector.push_back(i);
    }

    ASSERT_EQ(vector.size(), count);
    for (auto i = 0; i < count; ++i) {
        ASSERT_EQ(vector[i], sample[i]);
    }
}

//===================================================================
TEST(MyVector, InsertFront) {
    const size_t count = 10;
    MyVector<size_t> vector;
    int sample[] = {10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    for (size_t i = 0; i < count; ++i) {
        vector.push_back(i);
    }

    vector.insert(vector.begin(), 10);

    ASSERT_EQ(vector.size(), count + 1);
    for (size_t i = 0; i < vector.size(); ++i) {
        ASSERT_EQ(vector[i], sample[i]);
    }
}

//===================================================================
TEST(MyVector, InsertBack) {
    const size_t count = 10;
    MyVector<size_t> vector;
    int sample[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 20};

    for (size_t i = 0; i < count; ++i) {
        vector.push_back(i);
    }

    vector.insert(vector.end(), 20);

    ASSERT_EQ(vector.size(), count + 1);
    for (size_t i = 0; i < vector.size(); ++i) {
        ASSERT_EQ(vector[i], sample[i]);
    }
}

//===================================================================
TEST(MyVector, InsertMid) {
    const size_t count = 10;
    MyVector<size_t> vector;
    int sample[] = {0, 1, 2, 3, 4, 30, 5, 6, 7, 8, 9};

    for (size_t i = 0; i < count; ++i) {
        vector.push_back(i);
    }

    vector.insert((vector.begin() + (vector.size() / 2)), 30);

    ASSERT_EQ(vector.size(), count + 1);
    for (size_t i = 0; i < vector.size(); ++i) {
        ASSERT_EQ(vector[i], sample[i]);
    }
}

//===================================================================
TEST(MyVector, EraseFront) {
    const size_t count = 10;
    MyVector<size_t> vector;
    int sample[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    for (size_t i = 0; i < count; ++i) {
        vector.push_back(i);
    }

    vector.erase(vector.begin());

    ASSERT_EQ(vector.size(), count - 1);
    for (size_t i = 0; i < vector.size(); ++i) {
        ASSERT_EQ(vector[i], sample[i]);
    }
}

//===================================================================
TEST(MyVector, EraseBack) {
    const size_t count = 10;
    MyVector<size_t> vector;
    int sample[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};

    for (size_t i = 0; i < count; ++i) {
        vector.push_back(i);
    }

    vector.erase(vector.end() - 1);

    ASSERT_EQ(vector.size(), count - 1);
    for (size_t i = 0; i < vector.size(); ++i) {
        ASSERT_EQ(vector[i], sample[i]);
    }
}

//===================================================================
TEST(MyVector, EraseMid) {
    const size_t count = 10;
    MyVector<size_t> vector;
    int sample[] = {0, 1, 2, 3, 4, 6, 7, 8, 9};

    for (size_t i = 0; i < count; ++i) {
        vector.push_back(i);
    }

    vector.erase((vector.begin() + (vector.size() / 2)));

    ASSERT_EQ(vector.size(), count - 1);
    for (size_t i = 0; i < vector.size(); ++i) {
        ASSERT_EQ(vector[i], sample[i]);
    }
}

int main(int argc, char **argv) {
    testing::FLAGS_gtest_color = "yes";
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

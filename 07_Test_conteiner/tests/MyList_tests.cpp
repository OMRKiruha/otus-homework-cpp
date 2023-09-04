//
// Created by Professional on 04.09.2023.
//
#include "../MyList.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

//= Фикстура для инициализации контейнера ===========================
class MyList_f : public ::testing::Test {
protected:
    void SetUp() override {

        for (auto i = 0; i < count; ++i) {
            list.push_back(i);
        }
    }

    void TearDown() override {}

    MyList<int> list;
    const int count = 10;
};

//= Мок для конструктора-деструктора ================================
template<typename T>
class mockObjForList {
    T data{};
public:
    mockObjForList() = default;

    mockObjForList(const mockObjForList &other) : data(other.data) {};

    explicit mockObjForList(T t) : data(t) {};

    ~mockObjForList() { onDtor(); };

    mockObjForList<T> &operator=(const mockObjForList<T> &other) {
        data = other.data;
        return *this;
    };

    MOCK_METHOD0(onDtor, void());
};


//=1=================================================================
TEST(MyList, Empty) {
    MyList<int> list;

    ASSERT_EQ(list.size(), 0);
    ASSERT_EQ(list.begin(), static_cast<MyList<int>::MyListIterator<int>>(nullptr));
    ASSERT_EQ(list.end(), list.begin());
}

//=2=================================================================
TEST_F(MyList_f, PushBack) {

    int sample[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    ASSERT_EQ(list.size(), count);
    for (auto i = 0; i < count; ++i) {
        ASSERT_EQ(list[i], sample[i]);
    }
}

//=3=================================================================
TEST_F(MyList_f, InsertFront) {
    int sample[] = {10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    list.insert(list.begin(), 10);

    ASSERT_EQ(list.size(), count + 1);
    for (size_t i = 0; i < list.size(); ++i) {
        ASSERT_EQ(list[i], sample[i]);
    }
}

//=4=================================================================
TEST_F(MyList_f, InsertBack) {
    int sample[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 20};

    list.insert(list.end(), 20);

    ASSERT_EQ(list.size(), count + 1);
    for (size_t i = 0; i < list.size(); ++i) {
        ASSERT_EQ(list[i], sample[i]);
    }
}

//=5=================================================================
TEST_F(MyList_f, InsertMid) {
    int sample[] = {0, 1, 2, 3, 4, 30, 5, 6, 7, 8, 9};

    list.insert((list.begin() + (list.size() / 2)), 30);

    ASSERT_EQ(list.size(), count + 1);
    for (size_t i = 0; i < list.size(); ++i) {
        ASSERT_EQ(list[i], sample[i]);
    }
}

//=6=================================================================
TEST_F(MyList_f, EraseFront) {
    int sample[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    list.erase(list.begin());

    ASSERT_EQ(list.size(), count - 1);
    for (size_t i = 0; i < list.size(); ++i) {
        ASSERT_EQ(list[i], sample[i]);
    }
}

//=7=================================================================
TEST_F(MyList_f, EraseBack) {
    int sample[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};

    list.erase(list.end() - 1);

    ASSERT_EQ(list.size(), count - 1);
    for (size_t i = 0; i < list.size(); ++i) {
        ASSERT_EQ(list[i], sample[i]);
    }
}

//=8=================================================================
TEST_F(MyList_f, EraseMid) {
    int sample[] = {0, 1, 2, 3, 4, 6, 7, 8, 9};

    list.erase((list.begin() + (list.size() / 2)));

    ASSERT_EQ(list.size(), count - 1);
    for (size_t i = 0; i < list.size(); ++i) {
        ASSERT_EQ(list[i], sample[i]);
    }
}

//=9=================================================================
TEST_F(MyList_f, GetElementOutOfRange) {

    ASSERT_THROW(list[count], std::out_of_range);
    ASSERT_THROW(list[-count], std::out_of_range);
}

//=10=================================================================
TEST(MyList, CopyContainer) {
    const size_t count = 10;
    MyList<size_t> list;
    MyList<size_t> list2;
    int sample[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    for (size_t i = 0; i < count; ++i) {
        list.push_back(i);
    }
    list2 = list;

    ASSERT_EQ(list.size(), list2.size());
    for (size_t i = 0; i < list.size(); ++i) {
        ASSERT_EQ(list[i], sample[i]);
        ASSERT_EQ(list2[i], list[i]);
    }
}

//=11=================================================================
TEST(MyList, InvokeElementDtor) {
    const size_t count = 10;
    MyList<mockObjForList<size_t>> list;

    for (size_t i = 0; i < count; ++i) {
        list.push_back(mockObjForList<size_t>(i));
    }

    for (size_t i = 0; i < count; ++i) {
        EXPECT_CALL(list[i], onDtor());
    }
}

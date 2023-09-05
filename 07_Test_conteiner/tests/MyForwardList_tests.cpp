//
// Created by kiryuhin_ve on 05.09.2023.
//
//
// Created by Professional on 04.09.2023.
//
#include "../MyForwardList.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

//= Фикстура для инициализации контейнера ===========================
class MyForwardList_f : public ::testing::Test {
protected:
    void SetUp() override {

        for (auto i = 0; i < count; ++i) {
            list.push_back(i);
        }
    }

    void TearDown() override {}

    MyForwardList<int> list;
    const int count = 10;
};

//= Мок для конструктора-деструктора ================================
template<typename T>
class mockObjForFwdList {
    T data{};
public:
    mockObjForFwdList() = default;

    mockObjForFwdList(const mockObjForFwdList &other) : data(other.data) {};

    explicit mockObjForFwdList(T t) : data(t) {};

    ~mockObjForFwdList() { onDtor(); };

    mockObjForFwdList<T> &operator=(const mockObjForFwdList<T> &other) {
        data = other.data;
        return *this;
    };

    MOCK_METHOD0(onDtor, void());
};


//=1=================================================================
TEST(MyForwardList, Empty) {
    MyForwardList<int> list;

    ASSERT_EQ(list.size(), 0);
    ASSERT_EQ(list.begin(), static_cast<MyForwardList<int>::MyForwardListIterator<int>>(nullptr));
    ASSERT_EQ(list.end(), list.begin());
}

//=2=================================================================
TEST_F(MyForwardList_f, PushBack) {

    int sample[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    ASSERT_EQ(list.size(), count);
    for (auto i = 0; i < count; ++i) {
        ASSERT_EQ(list[i], sample[i]);
    }
}

//=3=================================================================
TEST_F(MyForwardList_f, InsertFront) {
    int sample[] = {10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    list.insert(list.begin(), 10);

    ASSERT_EQ(list.size(), count + 1);
    for (size_t i = 0; i < list.size(); ++i) {
        ASSERT_EQ(list[i], sample[i]);
    }
}

//=4=================================================================
TEST_F(MyForwardList_f, InsertBack) {
    int sample[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 20};

    list.insert(list.end(), 20);

    ASSERT_EQ(list.size(), count + 1);
    for (size_t i = 0; i < list.size(); ++i) {
        ASSERT_EQ(list[i], sample[i]);
    }
}

//=5=================================================================
TEST_F(MyForwardList_f, InsertMid) {
    int sample[] = {0, 1, 2, 3, 4, 30, 5, 6, 7, 8, 9};

    list.insert((list.begin() + (list.size() / 2)), 30);

    ASSERT_EQ(list.size(), count + 1);
    for (size_t i = 0; i < list.size(); ++i) {
        ASSERT_EQ(list[i], sample[i]);
    }
}

//=6=================================================================
TEST_F(MyForwardList_f, EraseFront) {
    int sample[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    list.erase(list.begin());

    ASSERT_EQ(list.size(), count - 1);
    for (size_t i = 0; i < list.size(); ++i) {
        ASSERT_EQ(list[i], sample[i]);
    }
}


//=7=================================================================
TEST_F(MyForwardList_f, EraseBack) {
    int sample[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};

    auto last = list.begin();
    for (size_t i = 0; i < list.size() - 1; ++i) {
        ++last;
    }
    list.erase(last);

    ASSERT_EQ(list.size(), count - 1);
    for (size_t i = 0; i < list.size(); ++i) {
        ASSERT_EQ(list[i], sample[i]);
    }
}

//=8=================================================================
TEST_F(MyForwardList_f, EraseMid) {
    int sample[] = {0, 1, 2, 3, 4, 6, 7, 8, 9};

    list.erase((list.begin() + (list.size() / 2)));

    ASSERT_EQ(list.size(), count - 1);
    for (size_t i = 0; i < list.size(); ++i) {
        ASSERT_EQ(list[i], sample[i]);
    }
}

//=9=================================================================
TEST_F(MyForwardList_f, GetElementOutOfRange) {

    ASSERT_THROW(list[count], std::out_of_range);
    ASSERT_THROW(list[-count], std::out_of_range);
}

//=10=================================================================
TEST_F(MyForwardList_f, CopyContainer) {
    MyForwardList<int> list2;
    int sample[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    list2 = list;

    ASSERT_EQ(list.size(), list2.size());
    for (size_t i = 0; i < list.size(); ++i) {
        ASSERT_EQ(list[i], sample[i]);
        ASSERT_EQ(list2[i], list[i]);
    }
}

//=11=================================================================
TEST(MyForwardList, InvokeElementDtor) {
    const size_t count = 10;
    MyForwardList<mockObjForFwdList<size_t>> list;

    for (size_t i = 0; i < count; ++i) {
        list.push_back(mockObjForFwdList<size_t>(i));
    }

    for (size_t i = 0; i < count; ++i) {
        EXPECT_CALL(list[i], onDtor());
    }
}

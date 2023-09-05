#include "../MyVector.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

//= Фикстура для инициализации контейнера ===========================
class MyVector_f : public ::testing::Test {
protected:
    void SetUp() override {

        for (auto i = 0; i < count; ++i) {
            vector.push_back(i);
        }
    }

    void TearDown() override {}

    MyVector<int> vector;
    const int count = 10;
};

//= Мок для конструктора-деструктора ================================
template<typename T>
class mockObjForVec {
    T data{};
public:
    mockObjForVec() = default;

    mockObjForVec(const mockObjForVec &other) : data(other.data) {};

    explicit mockObjForVec(T t) : data(t) {};

    ~mockObjForVec() { onDtor(); };

    mockObjForVec<T> &operator=(const mockObjForVec<T> &other) {
        data = other.data;
        return *this;
    };

    MOCK_METHOD0(onDtor, void());
};


//=1=================================================================
TEST(MyVector, Empty) {
    MyVector<int> vector;

    ASSERT_EQ(vector.size(), 0);
    ASSERT_EQ(vector.begin(), static_cast<MyVecIterator<int>>(nullptr));
    ASSERT_EQ(vector.end(), vector.begin());
}

//=2=================================================================
TEST_F(MyVector_f, PushBack) {

    int sample[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    ASSERT_EQ(vector.size(), count);
    for (auto i = 0; i < count; ++i) {
        ASSERT_EQ(vector[i], sample[i]);
    }
}

//=3=================================================================
TEST_F(MyVector_f, InsertFront) {
    int sample[] = {10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    vector.insert(vector.begin(), 10);

    ASSERT_EQ(vector.size(), count + 1);
    for (size_t i = 0; i < vector.size(); ++i) {
        ASSERT_EQ(vector[i], sample[i]);
    }
}

//=4=================================================================
TEST_F(MyVector_f, InsertBack) {
    int sample[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 20};

    vector.insert(vector.end(), 20);

    ASSERT_EQ(vector.size(), count + 1);
    for (size_t i = 0; i < vector.size(); ++i) {
        ASSERT_EQ(vector[i], sample[i]);
    }
}

//=5=================================================================
TEST_F(MyVector_f, InsertMid) {
    int sample[] = {0, 1, 2, 3, 4, 30, 5, 6, 7, 8, 9};

    vector.insert((vector.begin() + (vector.size() / 2)), 30);

    ASSERT_EQ(vector.size(), count + 1);
    for (size_t i = 0; i < vector.size(); ++i) {
        ASSERT_EQ(vector[i], sample[i]);
    }
}

//=6=================================================================
TEST_F(MyVector_f, EraseFront) {
    int sample[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    vector.erase(vector.begin());

    ASSERT_EQ(vector.size(), count - 1);
    for (size_t i = 0; i < vector.size(); ++i) {
        ASSERT_EQ(vector[i], sample[i]);
    }
}

//=7=================================================================
TEST_F(MyVector_f, EraseBack) {
    int sample[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};

    vector.erase(vector.end() - 1);

    ASSERT_EQ(vector.size(), count - 1);
    for (size_t i = 0; i < vector.size(); ++i) {
        ASSERT_EQ(vector[i], sample[i]);
    }
}

//=8=================================================================
TEST_F(MyVector_f, EraseMid) {
    int sample[] = {0, 1, 2, 3, 4, 6, 7, 8, 9};

    vector.erase((vector.begin() + (vector.size() / 2)));

    ASSERT_EQ(vector.size(), count - 1);
    for (size_t i = 0; i < vector.size(); ++i) {
        ASSERT_EQ(vector[i], sample[i]);
    }
}

//=9=================================================================
TEST_F(MyVector_f, GetElementOutOfRange) {

    ASSERT_THROW(vector[count], std::out_of_range);
    ASSERT_THROW(vector[-count], std::out_of_range);
}

//=10=================================================================
TEST(MyVector, CopyContainer) {
    const size_t count = 10;
    MyVector<size_t> vector;
    MyVector<size_t> vec2;
    int sample[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    for (size_t i = 0; i < count; ++i) {
        vector.push_back(i);
    }
    vec2 = vector;

    ASSERT_EQ(vector.size(), vec2.size());
    for (size_t i = 0; i < vector.size(); ++i) {
        ASSERT_EQ(vector[i], sample[i]);
        ASSERT_EQ(vec2[i], vector[i]);
    }
}

//=11=================================================================
TEST(MyVector, InvokeElementDtor) {
    const size_t count = 10;
    MyVector<mockObjForVec<size_t>> vector;

    for (size_t i = 0; i < count; ++i) {
        vector.push_back(mockObjForVec<size_t>(i));
    }

    for (size_t i = 0; i < count; ++i) {
        EXPECT_CALL(vector[i], onDtor());
    }
}

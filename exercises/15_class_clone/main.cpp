#include "../exercise.h"

// READ: 复制构造函数 <https://zh.cppreference.com/w/cpp/language/copy_constructor>
// READ: 函数定义（显式弃置）<https://zh.cppreference.com/w/cpp/language/function>

class DynFibonacci {
    size_t *cache;
    int cached;

public:
    // 动态设置容量的构造器
    DynFibonacci(int capacity) : cache(new size_t[capacity]), cached(2) {
        cache[0] = 0;
        cache[1] = 1;
    }

    // 复制构造器
    DynFibonacci(DynFibonacci const &fib) : cache(new size_t[fib.cached]), cached(fib.cached) {
        for (int i = 0; i < cached; ++i) {
            cache[i] = fib.cache[i];
        }
    }

    // 析构器，释放缓存空间
    ~DynFibonacci() {
        delete[] cache;
    }

    // 正确的缓存优化斐波那契计算
    size_t get(int i) {
        if (i < cached) {
            return cache[i];
        }
        for (int j = cached; j <= i; ++j) {
            cache[j] = cache[j - 1] + cache[j - 2];
        }
        cached = i + 1;
        return cache[i];
    }

    // const 修饰的方法
    size_t get(int i) const {
        if (i < cached) {
            return cache[i];
        }
        ASSERT(false, "i out of range");
        return 0; // 为了避免编译器警告，添加一个返回值
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    DynFibonacci const fib_ = fib;
    ASSERT(fib_.get(10) == fib.get(10), "Object cloned");
    return 0;
}
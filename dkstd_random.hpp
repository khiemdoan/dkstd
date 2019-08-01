// author:      Khiêm Đoàn Hoà (KhiemDH)
// github:      https://github.com/khiemdoan/dkstd
// created:     2018-12-18
// modified:    2019-08-01

#pragma once

#include <climits>
#include <random>
#include <vector>
#include <list>
#include <algorithm>

namespace dkstd {
    namespace random {

        double rand();
        double rand(double min, double max);

        int randint();
        int randint(int min, int max);
        
        template<typename T>
        T choice(const std::vector<T>& seq);
        
        template<typename T>
        T choice(const std::list<T>& seq);

        template<typename T>
        void shuffle(std::vector<T>& seq);

        template<typename T>
        void shuffle(std::list<T>& seq);
    }
}

// KhiemDH - 2019-07-31
double dkstd::random::rand()
{
    return dkstd::random::rand(0.0, 1.0);
}

// KhiemDH - 2019-08-01
double dkstd::random::rand(double min, double max)
{
    std::random_device device;
    std::default_random_engine engine{ device() };
    std::uniform_real_distribution dist(min, max);
    return dist(engine);
}

// KhiemDH - 2019-07-31
int dkstd::random::randint() {
    return dkstd::random::randint(INT_MIN, INT_MAX);
}

// KhiemDH - 2019-08-01
int dkstd::random::randint(int min, int max) {
    std::random_device device;
    std::default_random_engine engine{device()};
    std::uniform_int_distribution dist(min, max);
    return dist(engine);
}

// KhiemDH - 2019-07-31
template<typename T>
T dkstd::random::choice(const std::vector<T>& seq)
{
    auto index = randint(0, seq.size() - 1);
    auto li = seq.begin();
    std::advance(li, index);
    return *li;
}

// KhiemDH - 2019-07-31
template<typename T>
T dkstd::random::choice(const std::list<T>& seq)
{
    auto index = randint(0, seq.size() - 1);
    auto vi = seq.begin();
    std::advance(vi, index);
    return *vi;
}

// KhiemDH - 2019-07-31
template<typename T>
void dkstd::random::shuffle(std::vector<T>& seq)
{
    std::random_device device;
    std::default_random_engine engine{ device() };
    std::shuffle(seq.begin(), seq.end(), engine);
}

// KhiemDH - 2019-07-31
template<typename T>
void dkstd::random::shuffle(std::list<T>& seq)
{
    std::random_device device;
    std::default_random_engine engine{ device() };
    std::shuffle(seq.begin(), seq.end(), engine);
}

// author:      Khiêm Đoàn Hoà (KhiemDH)
// github:      https://github.com/khiemdoan/dkstd
// created:     2018-12-18
// modified:    2018-12-18

#pragma once

#include "limits"
#include "random"

namespace dkstd {
    namespace random {

        int randint();
        int randint(int min, int max);
    }
}

int dkstd::random::randint() {
    return dkstd::random::randint(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
}

int dkstd::random::randint(int min, int max) {
    std::random_device device;
    std::default_random_engine engine{device()};
    std::uniform_int_distribution<> dist(min, max);
    return dist(engine);
}
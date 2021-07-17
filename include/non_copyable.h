//
// Created by andyroiiid on 7/17/2021.
//

#ifndef TRACER_NON_COPYABLE_H
#define TRACER_NON_COPYABLE_H

class NonCopyable {
public:
    NonCopyable() = default;

    NonCopyable(const NonCopyable &) = delete;

    NonCopyable &operator=(const NonCopyable &) = delete;
};

#endif //TRACER_NON_COPYABLE_H

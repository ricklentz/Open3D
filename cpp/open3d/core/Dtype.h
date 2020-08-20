// ----------------------------------------------------------------------------
// -                        Open3D: www.open3d.org                            -
// ----------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2018 www.open3d.org
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// ----------------------------------------------------------------------------

#pragma once

#include <string>

#include "open3d/core/Dispatch.h"
#include "open3d/utility/Console.h"

static_assert(sizeof(float) == 4,
              "Unsupported platform: float must be 4 bytes.");
static_assert(sizeof(double) == 8,
              "Unsupported platform: double must be 8 bytes.");
static_assert(sizeof(int) == 4, "Unsupported platform: int must be 4 bytes.");
static_assert(sizeof(int32_t) == 4,
              "Unsupported platform: int32_t must be 4 bytes.");
static_assert(sizeof(int64_t) == 8,
              "Unsupported platform: int64_t must be 8 bytes.");
static_assert(sizeof(uint8_t) == 1,
              "Unsupported platform: uint8_t must be 1 byte.");
static_assert(sizeof(uint16_t) == 2,
              "Unsupported platform: uint16_t must be 2 bytes.");
static_assert(sizeof(bool) == 1, "Unsupported platform: bool must be 1 byte.");

namespace open3d {
namespace core {

class ObjDtype {
public:
    static const ObjDtype Undefined;
    static const ObjDtype Float32;
    static const ObjDtype Float64;
    static const ObjDtype Int32;
    static const ObjDtype Int64;
    static const ObjDtype UInt8;
    static const ObjDtype UInt16;
    static const ObjDtype Bool;

public:
    enum class DtypeCode {
        Undefined,
        Bool,  // Needed to distinguish bool from uint8_t.
        Int,
        UInt,
        Float,
        Object,
    };

    ObjDtype(DtypeCode dtype_code, int64_t byte_size, const std::string name)
        : dtype_code_(dtype_code), byte_size_(byte_size), name_(name) {
        (void)dtype_code_;
        (void)byte_size_;
        (void)name_;
    }

    /// Convert from C++ types to Dtype. Known types are explicitly specialized,
    /// e.g. DtypeUtil::FromType<float>(). Unsupported type will result in an
    /// exception.
    template <typename T>
    static inline ObjDtype FromType() {
        utility::LogError("Unsupported data type");
        return ObjDtype::Undefined;
    }

    int64_t ByteSize() const { return byte_size_; }

    std::string ToString() const { return name_; }

private:
    DtypeCode dtype_code_;
    int64_t byte_size_;
    std::string name_;
};

template <>
inline ObjDtype ObjDtype::FromType<float>() {
    return ObjDtype::Float32;
}

template <>
inline ObjDtype ObjDtype::FromType<double>() {
    return ObjDtype::Float64;
}

template <>
inline ObjDtype ObjDtype::FromType<int32_t>() {
    return ObjDtype::Int32;
}

template <>
inline ObjDtype ObjDtype::FromType<int64_t>() {
    return ObjDtype::Int64;
}

template <>
inline ObjDtype ObjDtype::FromType<uint8_t>() {
    return ObjDtype::UInt8;
}

template <>
inline ObjDtype ObjDtype::FromType<uint16_t>() {
    return ObjDtype::UInt16;
}

template <>
inline ObjDtype ObjDtype::FromType<bool>() {
    return ObjDtype::Bool;
}

enum class Dtype {
    Undefined,  // Dtype for uninitialized Tensor
    Float32,
    Float64,
    Int32,
    Int64,
    UInt8,
    UInt16,
    Bool,
};

class DtypeUtil {
public:
    static int64_t ByteSize(const Dtype &dtype) {
        int64_t byte_size = 0;
        switch (dtype) {
            case Dtype::Float32:
                byte_size = 4;
                break;
            case Dtype::Float64:
                byte_size = 8;
                break;
            case Dtype::Int32:
                byte_size = 4;
                break;
            case Dtype::Int64:
                byte_size = 8;
                break;
            case Dtype::UInt8:
                byte_size = 1;
                break;
            case Dtype::UInt16:
                byte_size = 2;
                break;
            case Dtype::Bool:
                byte_size = 1;
                break;
            default:
                utility::LogError("Unsupported data type");
        }
        return byte_size;
    }

    /// Convert from C++ types to Dtype. Known types are explicitly specialized,
    /// e.g. DtypeUtil::FromType<float>(). Unsupported type will result in an
    /// exception.
    template <typename T>
    static inline Dtype FromType() {
        utility::LogError("Unsupported data type");
        return Dtype::Undefined;
    }

    static std::string ToString(const Dtype &dtype) {
        std::string str = "";
        switch (dtype) {
            case Dtype::Undefined:
                str = "Undefined";
                break;
            case Dtype::Float32:
                str = "Float32";
                break;
            case Dtype::Float64:
                str = "Float64";
                break;
            case Dtype::Int32:
                str = "Int32";
                break;
            case Dtype::Int64:
                str = "Int64";
                break;
            case Dtype::UInt8:
                str = "UInt8";
                break;
            case Dtype::UInt16:
                str = "UInt16";
                break;
            case Dtype::Bool:
                str = "Bool";
                break;
            default:
                utility::LogError("Unsupported data type");
        }
        return str;
    }
};

template <>
inline Dtype DtypeUtil::FromType<float>() {
    return Dtype::Float32;
}

template <>
inline Dtype DtypeUtil::FromType<double>() {
    return Dtype::Float64;
}

template <>
inline Dtype DtypeUtil::FromType<int32_t>() {
    return Dtype::Int32;
}

template <>
inline Dtype DtypeUtil::FromType<int64_t>() {
    return Dtype::Int64;
}

template <>
inline Dtype DtypeUtil::FromType<uint8_t>() {
    return Dtype::UInt8;
}

template <>
inline Dtype DtypeUtil::FromType<uint16_t>() {
    return Dtype::UInt16;
}

template <>
inline Dtype DtypeUtil::FromType<bool>() {
    return Dtype::Bool;
}

}  // namespace core
}  // namespace open3d

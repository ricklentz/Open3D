
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

#include "open3d/core/Dtype.h"

namespace open3d {
namespace core {

const ObjDtype ObjDtype::Undefined =
        ObjDtype(ObjDtype::DtypeCode::Undefined, 1);
const ObjDtype ObjDtype::Float32 = ObjDtype(ObjDtype::DtypeCode::Float, 4);
const ObjDtype ObjDtype::Float64 = ObjDtype(ObjDtype::DtypeCode::Float, 8);
const ObjDtype ObjDtype::Int32 = ObjDtype(ObjDtype::DtypeCode::Int, 4);
const ObjDtype ObjDtype::Int64 = ObjDtype(ObjDtype::DtypeCode::Int, 8);
const ObjDtype ObjDtype::UInt8 = ObjDtype(ObjDtype::DtypeCode::UInt, 1);
const ObjDtype ObjDtype::UInt16 = ObjDtype(ObjDtype::DtypeCode::UInt, 2);
const ObjDtype ObjDtype::Bool = ObjDtype(ObjDtype::DtypeCode::Bool, 1);

}  // namespace core
}  // namespace open3d

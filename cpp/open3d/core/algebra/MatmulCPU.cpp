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

#include <mkl.h>
#include "Matmul.h"

namespace open3d {
namespace core {
namespace _detail {

// CPU converges to
// http://netlib.org/blas/#_level_3
// https://software.intel.com/content/www/us/en/develop/documentation/mkl-developer-reference-c/top/blas-and-sparse-blas-routines/blas-routines/blas-level-3-routines/cblas-gemm.html
// https://oneapi-src.github.io/oneDNN/group__dnnl__api__blas.html
Tensor MatmulCPU(const Tensor& A, const Tensor& B) {
    // Check dimensions
    SizeVector A_shape = A.GetShape();
    SizeVector B_shape = B.GetShape();

    if (A_shape.size() != 2) {
        utility::LogError("Tensor A must be 2D, but got {}D", A_shape.size());
    }
    if (B_shape.size() != 2) {
        utility::LogError("Tensor B must be 2D, but got {}D", B_shape.size());
    }
    if (A_shape[1] != B_shape[0]) {
        utility::LogError("Tensor A columns {} mismatch with Tensor B rows {}",
                          A_shape[1], B_shape[0]);
    }

    int64_t m = A_shape[0], k = A_shape[1], n = B_shape[1];

    // TODO: dtype and device check

    Tensor C = Tensor::Zeros({m, n}, A.GetDtype(), A.GetDevice());

    float alpha = 1.0f;
    float beta = 0.0f;

    void* A_data = A.Contiguous().GetDataPtr();
    void* B_data = B.Contiguous().GetDataPtr();
    void* C_data = C.GetDataPtr();

    // A: m x k
    // B: k x n
    // C: m x n
    // clang-format off
    cblas_sgemm(CblasColMajor,
                CblasNoTrans,
                CblasNoTrans,
                m, n, k, // dimensions
                alpha,
                static_cast<const float*>(A_data), m,
                static_cast<const float*>(B_data), k, // input and their leading dims
                beta,
                static_cast<float*>(C_data), m); // output and its leading dim
    // clang-format on

    return C;
}

}  // namespace _detail
}  // namespace core
}  // namespace open3d

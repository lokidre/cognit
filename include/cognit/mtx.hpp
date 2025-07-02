/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#include "complex.hpp"
#include "const.hpp"
#include "def.hpp"
#include "func.hpp"
#include "vec.hpp"

#include <apeal/buffer.hpp>
#include <apeal/hash.hpp>


//
// Core matrix operations
//
#include "./mtx/mtx_add_core.hpp"
#include "./mtx/mtx_copy_core.hpp"
#include "./mtx/mtx_eye_core.hpp"
#include "./mtx/mtx_transpose.hpp"


namespace cognit {

template <class Container, class T>
struct MtxElementAccessor {

    Container p;

    MtxElementAccessor(const Container& d) { p = d; }

    T& operator[](std::size_t index) { return p[index]; }

    const T& operator[](std::size_t index) const { return p[index]; }
};


//
// General matrix base class
//
template <class Var>
struct MtxBase {
    using Idx = int;
    using T = Var;
    using value_type = T;
    using iterator = T*;
    using const_iterator = const T*;
};

template <class A, class T, int tM, int tN>
struct FixedMtxBase: MtxBase<T> {
private:
    using Self = FixedMtxBase<A, T, tM, tN>;
    using Base = MtxBase<T>;

    using RetRef = A&;
    using RetPtr = A*;


public:
    using typename Base::Idx;

    using typename Base::value_type;
    using typename Base::iterator;
    using typename Base::const_iterator;

    constexpr static int M = tM;
    constexpr static int N = tN;
    //constexpr static Idx O = M * N;


    // Data
    T a[M][N];

    // Initialization

    // Information
    constexpr auto width() const noexcept { return M; }
    constexpr auto height() const noexcept { return N; }
    //constexpr auto dims() const noexcept { return apl::Size<Idx>{M, N}; }
    //constexpr auto size() const noexcept { return O; }
    constexpr bool isZero() const noexcept {
        for (auto it = begin(), itEnd = end(); it != itEnd; ++it)
            if (*it)
                return false;
        return true;
    }

    constexpr apl::Hash64 computeHash() const noexcept {
        static_assert(sizeof(*this) == sizeof(T) * M * N);

        apl::Hash64 seed = 0;

        for (auto it = begin(), itEnd = end(); it != itEnd; ++it) {
            apl::hashCombine(seed, *it);
        }

        return seed;
    }

    // Data Access
    // Fixed matrices are always allocated
    constexpr bool isValid() const noexcept { return true; }
    constexpr Idx dataSize() const noexcept { return M * N; }

    constexpr T* get() noexcept { return (T*)a; }

    // To access the data for modification purposes
    constexpr const T* get() const noexcept { return (T*)a; }  // To access the data for modification purposes

    constexpr auto data() noexcept { return (T*)a; }  // readonly access
    constexpr auto data() const noexcept { return (const T*)a; }  // readonly access

    constexpr auto begin() noexcept { return iterator(a); }
    constexpr auto end() noexcept { return begin() + M * N; }
    constexpr auto cbegin() const noexcept { return const_iterator(a); }
    constexpr auto cend() const noexcept { return begin() + M * N; }
    constexpr auto begin() const noexcept { return cbegin(); }
    constexpr auto end() const noexcept { return cend(); }


    //
    // Manipulations
    //
    constexpr auto zero() noexcept
    {
        std::memset(a, 0, dataSize() * sizeof(T));
        return static_cast<RetRef>(*this);
    }

    constexpr auto scale(const T& s) noexcept {
        for (auto p = begin(), pend = end(); p != pend; ++p)
            *p *= s;
        return static_cast<RetRef>(*this);
    }

    constexpr auto assignData(const T* ptr) noexcept {
        std::memcpy((T*)a, ptr, dataSize() * sizeof(T));
        return static_cast<RetRef>(*this);
    }

    constexpr auto assign(const A& m) noexcept { return assignData(m.data()); }


    constexpr bool cmp(const T* ptr) const noexcept {
        return std::memcmp(data(), ptr, dataSize() * sizeof(T)) == 0;
    }

    constexpr void setup(Idx, Idx) noexcept {}  // dummy
    //constexpr bool empty() const noexcept {  return false; }

    //
    // Matrix operations
    //

    //
    // Operator overloading
    //
    constexpr explicit operator bool() const noexcept { return !isZero(); }

    //RetRef operator
};


template <class T>
class Mtx2: public FixedMtxBase<Mtx2<T>, T, 2, 2> {
    using Self = Mtx2<T>;
    using Base = FixedMtxBase<Mtx2<T>, T, 2, 2>;

public:
    using Minor = T;

    using typename Base::Idx;
    using typename Base::iterator;
    using typename Base::const_iterator;

    using Base::begin;
    using Base::end;
    using Base::cbegin;
    using Base::cend;


    // converting constructor
    Mtx2() noexcept {}
    Mtx2(const Self& m) noexcept { *this = m; }

    // Converting constructor
    template <class M>
    Mtx2(const M& m)
    {
        mtx_convert(m, *this);
    }

    //Self& operator=(const Self& rhs) noexcept
    //{
    //    mtx_copy_it(rhs.begin(), rhs.end(), begin());
    //    return *this;
    //}

    //
    // Matrix operations
    //
    auto& eye() noexcept { return mtx2x2_eye(*this); }


    Self operator+=(const Self& rhs) noexcept
    {
        mtx2x2_add(*this, rhs, *this);
        return *this;
    }

    friend Self operator+(Self lhs, const Self& rhs) noexcept
    {
        lhs += rhs;
        return lhs;
    }

    Self operator-=(const Self& rhs) noexcept
    {
        mtx2x2_sub(*this, rhs, *this);
        return *this;
    }

    friend Self operator-(Self lhs, const Self& rhs) noexcept
    {
        lhs -= rhs;
        return lhs;
    }
};


template <class T>
class Mtx3: public FixedMtxBase<Mtx3<T>, T, 3, 3> {
    using Self = Mtx3<T>;
    using Base = FixedMtxBase<Mtx3<T>, T, 3, 3>;

public:
    using Minor = Mtx2<T>;

    // Construction
    Mtx3() noexcept {}
    Mtx3(const Self& m) noexcept { *this = m; }

    // Converting constructor
    template <class M>
    Mtx3(const M& m) {
        mtx_convert(m, *this);
    }


    //
    // Matrix operations
    //
    auto& eye() noexcept { return mtx3x3_eye(*this); }


    Self operator+=(const Self& rhs) noexcept {
        mtx3x3_add(*this, rhs, *this);
        return *this;
    }

    friend Self operator+(Self lhs, const Self& rhs) noexcept {
        lhs += rhs;
        return lhs;
    }

    Self operator-=(const Self& rhs) noexcept {
        mtx3x3_sub(*this, rhs, *this);
        return *this;
    }

    friend Self operator-(Self lhs, const Self& rhs) noexcept {
        lhs -= rhs;
        return lhs;
    }
};

template <class T>
class Mtx4: public FixedMtxBase<Mtx4<T>, T, 4, 4> {
    using Self = Mtx4;
    using Base = FixedMtxBase<Mtx4, T, 4, 4>;

public:
    using Minor = Mtx3<T>;

    Mtx4() noexcept {}
    Mtx4(const Self& m) noexcept { *this = m; }  // Copy constructor

    // Converting operator
    template <class B>
    explicit Mtx4(const B& b) noexcept {
        mtx_convert(b, *this);
    }

    //
    // Matrix operations
    //
    auto& eye() noexcept { return mtx4x4_eye(*this); }


    //constexpr Self& eye() {
    //    this->zero();
    //    this->a[0][0] = this->a[1][1] = this->a[2][2] = this->a[3][3] = T(1);
    //    return *this;
    //}

    Self& transpose() { return mtx4x4_t(*this); }
    Self transposed() const
    {
        Self b;
        return mtx4x4_t(*this, b);
    }

    // Remark! not efficient, extra copying
    Self& operator*=(const Self& U)
    {
        Self V;
        mtx_mul(*this, U, V);
        this->assign(V);
        return *this;
    }

    bool operator==(const Self& B) const { return this->cmp(B.data()); }
    bool operator!=(const Self& B) const { return !this->cmp(B.data()); }


    Self operator+=(const Self& rhs) noexcept
    {
        mtx4x4_add(*this, rhs, *this);
        return *this;
    }

    Self operator-=(const Self& rhs) noexcept
    {
        mtx4x4_sub(*this, rhs, *this);
        return *this;
    }

    friend Self operator+(Self lhs, const Self& rhs) noexcept
    {
        lhs += rhs;
        return lhs;
    }

    friend Self operator-(Self lhs, const Self& rhs) noexcept
    {
        lhs -= rhs;
        return lhs;
    }
};


//template <class T, int tN>
//class MtxN: public FixedMtxBase<MtxN<T, tN>, T, tN, tN> {
//    using Self = MtxN<T, tN>;
//    using Base = FixedMtxBase<MtxN<T, tN>, T, tN, tN>;
//
//public:
//    using Minor = MtxN<T, tN - 1>;
//};
//
//
//template <class T, int tM, int tN>
//struct MtxMN: public FixedMtxBase<MtxMN<T, tM, tN>, T, tM, tN> {
//};


//
// Variable dimension matrix
//


template <class _T>
struct Mtx: public MtxBase<_T> {
    using T = _T;
    //using value_type = T;

    using Self = Mtx<T>;
    using Base = MtxBase<T>;

    using typename Base::Idx;
    using typename Base::iterator;
    using typename Base::const_iterator;

    //using float_ttypedef T float_type;
    //typedef float_type value_type;

    //using

    using Minor = Mtx<T>;


    //T* p{};  // matrix data
    Idx M{}, N{};  // dimensions


    //typedef Mtx<T> minor_type;

    //typedef value_type* iterator;
    //typedef const value_type* const_iterator;

    // matrix types

    //enum sym_t {
    //    sym_none = 0,
    //    symm,        // symmetric
    //    skew         // skew symmetric
    //} sym;
    bool symmetric{}, skewSymmetric{};
    bool diagonal{};

    //enum dia_t {
    //    dia_none = 0,
    //    band = 0x01,         // band diagonal
    //    trid = 0x03,         // tri diagonal
    //    bidi = 0x07,         // bidiagonal
    //    diag = 0x80          // diagonal
    //} dia;

    Idx bandSize{};  // Band size for band diagonal matrix


    //enum tri_t {
    //    tri_none = 0,
    //    lo,               // lower triangular
    //    up,               // upper triangular
    //    up_l,             // left upper
    //    lo_r              // right lower
    //} tri;  // triangular type
    bool triangular{};  // Triangular matrix

    bool sparse{};  // Is sparce matrix

    // storage options
    enum Storage {
        Regular,
        Tridiagonal,  // stored as tridiagonal
        Triangular,  // stored as triangular
    };

    Storage storage{Storage::Regular};

    apl::Buffer<T> buffer_;


public:
    // access operator


    void setup(Idx im, Idx in)
    {
        //auto new_size = im * in;
        //if (new_size > allocated_size) {
        //    destroy();
        //    if ((buffer_ = new float_type[new_size]) == 0)
        //        throw 1;
        //    allocated_size = new_size;
        //    p = buffer_;
        //}

        buffer_.alloc(im * in);
        //p = buffer_.data();

        M = im, N = in;
    }

    void destroy() noexcept
    {
        //allocated_size = 0;
        M = N = 0;
        buffer_.clear();
        //if (buffer_) {
        //    delete[] buffer_;
        //    buffer_ = 0;
        //}
    }

    void resize(Idx im, Idx in) { setup(im, in); }
    void clear() noexcept { destroy(); }

    // default constructor
    Mtx() {}

    // constructor initializes nxn square matrix
    Mtx(Idx in) { resize(in, in); }

    // constructor inits mxn matrix
    Mtx(Idx im, Idx in) { resize(im, in); }

    // destructor
    ~Mtx() noexcept { clear(); }


    // element access
    //Mtx<type> &a(int i, int j) {  return p[j*m+i] ;  }

    //needed Mtx<type>

    MtxElementAccessor<T*, T> operator[](Idx i)
    {
        MtxElementAccessor<T*, T> t{&buffer_.data()[i * N]};
        return t;
    }

    //Mtx<float_type> &operator= (const Mtx<float_type> &b) {  copy(b) ;  return *this ;  }

    Mtx<T>& operator=(const Mtx<T>& b)
    {
        copy(b);
        return *this;
    }


    // matrix copying and "moving"
    void copy(const Mtx<T>& b)
    {
        resize(b.M, b.N);

        auto bIt = b.begin();
        auto aIt = begin(), aEnd = end();

        while (aIt != aEnd) {
            *aIt++ = *bIt++;
        }
    }

    template <class MT>
    MT convert() const
    {
        MT b;

        apl::verify(b.M == M && b.N == N, "Matrix dimentions don't match");

        mtx_copy_it(begin(), end(), b.data());
        return b;
    }

    /*
    void move(const Mtx<T>& b)
    {
        destroy();
        M = b.M, N = b.N;
        allocated_size = b.allocated_size;
        buffer_ = b.buffer_;
        b.M = b.N = 0;
        b.allocated_size = 0;
        b.buffer_ = 0;
    }
    */


    // iterators
    iterator begin() noexcept { return buffer_.begin(); }
    iterator end() noexcept { return buffer_.begin() + dataSize(); }

    const_iterator cbegin() const noexcept { return buffer_.cbegin(); }
    const_iterator cend() const noexcept { return buffer_.cbegin() + dataSize(); }

    const_iterator begin() const noexcept { return cbegin(); }
    const_iterator end() const noexcept { return cend(); }

    auto width() const noexcept { return M; }
    auto height() const noexcept { return N; }


    // Data access
    bool isValid() const noexcept { return M != 0 && N != 0; }
    constexpr Idx dataSize() const noexcept { return M * N; }

    T* data() noexcept { return buffer_.data(); }
    const T* data() const noexcept { return buffer_.data(); }
};

}  // namespace cognit

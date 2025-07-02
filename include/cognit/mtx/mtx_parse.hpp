/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#pragma once

#include "../mtx.hpp"

#include <apeal/assert.hpp>
#include <apeal/parse.hpp>
#include <apeal/parse/parse_input.hpp>
#include <apeal/parse/vector.hpp>

namespace cognit {

//
// Parsing matrix with known size
//
template <class It, class MT>
void mtx_parse(apl::ParseInput<It>& input, MT& m)
{
    //using namespace apl;

    using T = typename MT::T;
    using Idx = typename MT::Idx;

    using apl::verify;
    using apl::Char;
    using apl::parse;
    //using apl::parse_it;

    apl::ParserBase parser;



    Char beginSep{'['}, endSep{']'}, rowSep{';'};

    // Skip all the whitespaces
    input.ignoreEol = true;
    input.skipSpaces();

    verify(!input.end(), "Unexpected end of data");

    verify(input.peek() == beginSep, "Invalid character: %c", input.peek());

    input.skip();

    // Matrix values;
    Index numColumns{}, numRows{};

    // Using interators only, implement later
    //using Row = std::vector<apl::ParseInput<It>::IteratorPair>;

    using Row = std::vector<T>;
    std::vector<Row> values;

    String stemp;

    // Read matrix row
    auto readRow = [&]() -> Row& {
        auto& row = values.emplace_back();

        for (;;) {
            input.skipSpaces();

            verify(!input.end(), "Unexpected end");

            auto ch = input.peek();

            if (ch == rowSep) {
                input.skip();
                break;
            }

            if (ch == endSep)
                break;

            row.push_back(parse<T>(input.readNumber(parser, stemp)));
            //row.push_back(src.readNumber(parser));

            input.skipSpaces();

        }

        return row;
    };

    // Read the first row
    readRow();
    numColumns = std::ssize(values.back());

    verify(numColumns, "Empty matrix row");

    // Now read all the remaining rows
    for (;;) {
        verify(!input.end(), "Unexpected end");

        if (input.peek() == endSep) {
            input.skip();  // skip the end character
            break;
        }

        auto& row = readRow();

        // Check the row size
        verify(std::ssize(row) == numColumns, "Column numbers don't match");

        //if (src.peek() == rowSep)
        //    src.skip();
    }

    numRows = std::ssize(values);

    // 
    // Check the provided matrix size if any
    //
    if (m.isValid()) {
        verify(m.M == (Idx)numColumns, "Mtx:Invalid number of columns");
    } else {
        m.resize((Idx)numColumns, (Idx)numRows);
    }

    //
    // Now just assign the values
    //
    auto a = m.begin();
    for (auto& row: values) {
        for (auto& v: row) {
            *a++ = v;
            // Using iterators only
            //*a++ = parse_it<T>(v.first, v.second);
        }
    }


}


template <class T>
Mtx<T> mtx_parse(StrView text) {
    Mtx<T> m;
    apl::ParseInput input{text.begin(), text.end()};
    mtx_parse(input, m);
    return m;
}

template <class T, class It>
Mtx<T> mtx_parse_it(It begin, It end) {
    Mtx<T> m;
    apl::ParseInput input{begin, end};
    mtx_parse(input, m);
    return m;
}



}  // namespace cognit


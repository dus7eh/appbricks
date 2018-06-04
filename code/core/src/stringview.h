/*
 * variant.h
 *
 *  Created on: May 31, 2018
 *      Author: Dusteh
 */

#pragma once

#include <iterator>
#include <string>

namespace bricks {
    namespace core {
        class StringView {
        public:
            using Iterator = std::string::iterator;
            using RevIterator = std::string::reverse_iterator;
            using ConstIterator = std::string::const_iterator;
            using ConstRevIterator = std::string::const_reverse_iterator;
            using SingleChar = Iterator::value_type;

            explicit StringView(const std::string& text) : StringView(std::begin(text), std::end(text)) {}
            StringView(ConstIterator start, ConstIterator end) : start_{ start } {
                if (end < start)
                    throw std::range_error("End iterator should not point before begin iterator");
                size_ = std::distance(start, end);
            }

            StringView(ConstIterator start, size_t size) : StringView{ start, start + size } { }
            const char* c_str() const {
                return &(*start_);
            }

            std::string as_string() const {
                return {start_, std::next(start_, size_)};
            }

            ConstIterator begin() const noexcept {
                return start_;
            }

            ConstRevIterator rbegin() const noexcept {
                return ConstRevIterator{ end() };
            }

            ConstIterator end() const noexcept {
                return std::next(start_, size_);
            }

            ConstRevIterator rend() const noexcept {
                return ConstRevIterator{ begin() };
            }

            bool empty() const noexcept {
                return size_ == 0;
            }

            size_t size() const noexcept {
                return size_;
            }

            SingleChar operator[] (int idx) const {
                if (idx >= size_)
                    throw std::out_of_range("Index value exceeds view size");
                return *std::next(start_, idx);
            }

            friend std::ostream& operator<<(std::ostream& stream, const StringView& sv) {
                auto ptr = sv.start_;
                while (ptr != sv.end())
                    stream << *(ptr++);
                return stream;
            }
        private:
            ConstIterator start_;
            size_t size_ = 0;
        };
    }
}

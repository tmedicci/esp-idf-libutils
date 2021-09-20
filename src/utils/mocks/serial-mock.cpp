// Copyright 2021 Time Energy Industria e Comercio Ltda
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <algorithm>
#include "serial-mock.hpp"

using namespace std;
using namespace chrono;
using namespace mock;

Serial::Serial() : utils::Serial(), request(), response() {}

void Serial::write(const vector<uint8_t> &buffer)
{
    request.insert(request.end(), buffer.begin(), buffer.end());
}

void Serial::write(string msg)
{
    Serial::write(vector<uint8_t>(msg.cbegin(), msg.cend()));
}

size_t Serial::read(vector<uint8_t> &buffer, size_t nBytesToRead, nanoseconds timeout)
{
    std::vector<uint8_t> empty;
    return read(buffer, empty, nBytesToRead, timeout);
}

size_t Serial::read(std::vector<uint8_t> &buffer, std::vector<uint8_t> &pattern, size_t nBytesToRead,
                    std::chrono::nanoseconds timeout)
{
    bool patternFound = false;

    size_t totalRead = nBytesToRead < response.size() ? nBytesToRead : response.size();

    if (!pattern.empty()) {
        auto res = search(response.begin(), response.begin() + totalRead, pattern.begin(), pattern.end());
        if (res != response.begin() + totalRead) {
            totalRead = distance(begin(response), res + pattern.size());
            patternFound = true;
        }
    }

    buffer.reserve(buffer.size() + totalRead);

    copy(begin(response), begin(response) + totalRead, back_inserter(buffer));

    response.erase(begin(response), begin(response) + totalRead);

    return !pattern.empty() ? (patternFound ? totalRead : -totalRead) : totalRead;
}

size_t Serial::read(vector<uint8_t> &buffer, vector<uint8_t> &&pattern, size_t nBytesToRead, nanoseconds timeout)
{
    return read(buffer, pattern, nBytesToRead, timeout);
}

void Serial::setResponse(const vector<uint8_t> &response)
{
    Serial::response = response;
}

const vector<uint8_t> &Serial::getRequested() const
{
    return request;
}

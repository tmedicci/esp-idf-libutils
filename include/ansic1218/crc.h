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


#ifndef ANSIC1218_HOST_CRC_H
#define ANSIC1218_HOST_CRC_H

#include <cstdint>
#include <vector>

namespace ansic1218
{

    class CRC
    {

        static uint32_t table[256];

    public:
        static std::vector<uint8_t> &calculate(std::vector<uint8_t>::const_iterator first,
                                               std::vector<uint8_t>::const_iterator last,
                                               std::vector<uint8_t> &&buffer);

        static std::vector<uint8_t> &calculate(std::vector<uint8_t>::const_iterator first,
                                               std::vector<uint8_t>::const_iterator last,
                                               std::vector<uint8_t> &buffer);
    };
}

#endif //ANSIC1218_HOST_CRC_H
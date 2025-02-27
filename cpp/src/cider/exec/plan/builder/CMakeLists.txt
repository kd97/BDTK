# Copyright(c) 2022-2023 Intel Corporation.
#
# Licensed to the Apache Software Foundation (ASF) under one
# or more contributor license agreements.  See the NOTICE file
# distributed with this work for additional information
# regarding copyright ownership.  The ASF licenses this file
# to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance
# with the License.  You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied.  See the License for the
# specific language governing permissions and limitations
# under the License.

# Set up Proto
find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} -Wno-attributes -Wno-write-strings -Wno-unused-function -Wno-unused-label -Wno-sign-compare"
)

set(CIDER_PLAN_PARSER_SRCS SubstraitExprBuilder.cpp)
add_library(cider_expr_builder STATIC ${CIDER_PLAN_PARSER_SRCS})
target_link_libraries(cider_expr_builder substrait cider_util protobuf)

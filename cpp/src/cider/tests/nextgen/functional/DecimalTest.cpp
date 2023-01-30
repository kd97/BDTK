/*
 * Copyright(c) 2022-2023 Intel Corporation.
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include <gtest/gtest.h>
#include "exec/nextgen/Nextgen.h"
#include "tests/utils/CiderNextgenTestBase.h"

using namespace cider::test::util;
using namespace cider::exec::nextgen;

class ShortDecimalType : public CiderNextgenTestBase {
 public:
  ShortDecimalType() {
    table_name_ = "test";
    create_ddl_ =
        R"(CREATE TABLE test(col_1 DECIMAL(19,1), col_2 DECIMAL(19,1), col_3 INTEGER, col_4 INTEGER);)";
    QueryArrowDataGenerator::generateBatchByTypes(input_schema_,
                                                  input_array_,
                                                  100,
                                                  {"col_1", "col_2", "col_3", "col_4"},
                                                  {CREATE_SUBSTRAIT_DECIMAL_TYPE(19, 1),
                                                   CREATE_SUBSTRAIT_DECIMAL_TYPE(19, 1),
                                                   CREATE_SUBSTRAIT_TYPE(I32),
                                                   CREATE_SUBSTRAIT_TYPE(I32)},
                                                  {0, 0, 0, 0},
                                                  GeneratePattern::Random,
                                                  -10000,
                                                  10000);
  }
};

class LongDecimalType : public CiderNextgenTestBase {
 public:
  LongDecimalType() {
    table_name_ = "test";
    create_ddl_ = R"(CREATE TABLE test(col_1 DECIMAL(38,3), col_2 DECIMAL(38,4));)";
    QueryArrowDataGenerator::generateBatchByTypes(
        input_schema_,
        input_array_,
        30,
        {"col_1", "col_2"},
        {CREATE_SUBSTRAIT_DECIMAL_TYPE(38, 3), CREATE_SUBSTRAIT_DECIMAL_TYPE(38, 4)},
        {2, 2},
        Random,
        1'000'000'000'000'000'000 * (__int128_t)1'000'000,
        2'000'000'000'000'000'000 * (__int128_t)1'000'000);
  }
};

TEST_F(ShortDecimalType, decimalCompareTest) {
  // assertQuery("select col_1, col_2 from test where col_1 = col_2");
  // assertQuery("select * from test where col_1 <> col_2");
  // assertQuery("select col_2 from test where col_1 > 0");
  // assertQuery("select col_1 from test where col_2 <= 0");
  // assertQuery("select col_1 from test where col_2 IS NULL");
  // cider::exec::nextgen::context::CodegenOptions codegen_options{};
  // codegen_options.needs_error_check = true;
  // setCodegenOptions(codegen_options);
  assertQuery("select col_1 + col_2  + 1.0 from test");
  assertQuery("select col_1 * col_2 from test");
  // assertQuery("select col_3 * col_4 from test");
  // assertQuery("select 3 + col_1 - col_2 from test");
  // assertQuery("select col_1 * col_2 from test");
}

TEST_F(LongDecimalType, decimalMathTest) {
  // assertQuery("select col_1, col_2 from test where col_1 = col_2");
  // assertQuery("select * from test where col_1 <> col_2");
  // assertQuery("select col_2 from test where col_1 > 0");
  // assertQuery("select col_1 from test where col_2 <= 0");
  // assertQuery("select col_1 from test where col_2 IS NULL");
  // cider::exec::nextgen::context::CodegenOptions codegen_options{};
  // codegen_options.needs_error_check = true;
  // setCodegenOptions(codegen_options);
  assertQuery("select col_1 + col_2  + 1.0 from test");
  // assertQuery("select col_1 * col_2 from test");
  // assertQuery("select col_3 * col_4 from test");
  // assertQuery("select 3 + col_1 - col_2 from test");
  // assertQuery("select col_1 * col_2 from test");
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  return RUN_ALL_TESTS();
}

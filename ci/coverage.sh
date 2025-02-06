bazel coverage -s \
  --collect_code_coverage \
  --instrument_test_targets \
  --experimental_cc_coverage \
  --combined_report=lcov \
  --copt=-fprofile-arcs --copt=-ftest-coverage \
  --linkopt=-fprofile-arcs --linkopt=-ftest-coverage \
  --instrumentation_filter=//simulator:fx_simulator \
  --coverage_report_generator=@bazel_tools//tools/test/CoverageOutputGenerator/java/com/google/devtools/coverageoutputgenerator:Main \
  //simulator:simulator_tests
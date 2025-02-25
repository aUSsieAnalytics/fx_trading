test:
	bazel test //... --test_output=errors --test_verbose_timeout_warnings --cache_test_results=no

format:
	sh ./ci/format.sh

format-check:
	sh ./ci/check_formatting.sh

coverage:
	sh ./ci/coverage.sh

clean:
	bazel clean

build:
	bazel build //...
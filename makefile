test:
	bazel test //... --test_output=errors --test_verbose_timeout_warnings --cache_test_results=no

format:
	bash ./ci/format.sh

format-check:
	bash ./ci/check_formatting.sh

coverage:
	bash ./ci/coverage.sh

clean:
	bazel clean --expunge

build:
	bazel build //...
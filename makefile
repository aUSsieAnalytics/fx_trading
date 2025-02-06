test:
	bazel test //... --test_output=errors --test_verbose_timeout_warnings

format:
	sh ./ci/format.sh

format-check:
	sh ./ci/check_formatting.sh

coverage:
	sh ./ci/coverage.sh
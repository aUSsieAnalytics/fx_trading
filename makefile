test:
	bazel test //...

format:
	sh ./ci/format.sh

format-check:
	sh ./ci/check_formatting.sh
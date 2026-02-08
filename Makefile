.PHONY: all
all:
	@uv run main.py

.PHONY: build
build:
	@uv build

.PHONY: clean
clean:
	@rm -rf dist *.egg-info

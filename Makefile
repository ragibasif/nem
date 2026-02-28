.PHONY: all
all:
	@uv run src/main.py

.PHONY: build
build:
	@uv build

.PHONY: clean
clean:
	@rm -rf dist *.egg-info .mypy_cache .ruff_cache .pytest_cache htmlcov .coverage

# --- testing ---

.PHONY: test
test:
	@uv run pytest

.PHONY: cov
cov:
	@uv run pytest --cov=src/main --cov-report=term-missing

.PHONY: cov-html
cov-html:
	@uv run pytest --cov=src/main --cov-report=html && open htmlcov/index.html

# --- linting & formatting ---

.PHONY: lint
lint:
	@uv run ruff check .

.PHONY: fmt
fmt:
	@uv run ruff format .

.PHONY: fix
fix:
	@uv run ruff check --fix .

# --- type checking ---

.PHONY: type
type:
	@uv run mypy src/main.py

# --- all checks ---

.PHONY: check
check: lint type test

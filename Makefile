/// Apache License 2.0 

project_name := physics
project_version := $(shell git describe --tags --always)

docker_registry_path := openspacecollective
docker_image_repository := $(docker_registry_path)/open-space-toolkit-$(project_name)
docker_image_version := $(project_version)

docker_development_image_repository := $(docker_image_repository)-development
docker_release_image_cpp_repository := $(docker_image_repository)-cpp
docker_release_image_python_repository := $(docker_image_repository)-python
docker_release_image_jupyter_repository := $(docker_image_repository)-jupyter

jupyter_notebook_image_repository := jupyter/scipy-notebook:python-3.8.8
jupyter_notebook_port := 9004
jupyter_python_version := 3.8

project_name_camel_case := $(shell echo $(project_name) | sed -r 's/(^|-)([a-z])/\U\2/g')
jupyter_project_name_python_shared_object := $(shell echo "OpenSpaceToolkit${project_name_camel_case}.cpython-38-x86_64-linux-gnu")


################################################################################################################################################################

pull: ## Pull all images

	@ echo "Pulling images..."

	@ $(MAKE) pull-development-image
	@ $(MAKE) pull-release-images

pull-development-image: ## Pull development image

	@ echo "Pulling development image..."

	docker pull $(docker_development_image_repository):$(docker_image_version) || true
	docker pull $(docker_development_image_repository):latest || true

pull-release-images: ## Pull release images

	@ echo "Pull release images..."

	@ $(MAKE) pull-release-image-cpp

	@ $(MAKE) pull-release-image-python

	@ $(MAKE) pull-release-image-jupyter

pull-release-image-cpp:

	@ echo "Pull C++ release image..."

	docker pull $(docker_release_image_cpp_repository):$(docker_image_version) || true
	docker pull $(docker_release_image_cpp_repository):latest || true

pull-release-image-python:

	@ echo "Pulling Python release image..."

	docker pull $(docker_release_image_python_repository):$(docker_image_version) || true
	docker pull $(docker_release_image_python_repository):latest || true

pull-release-image-jupyter:

	@ echo "Pulling Jupyter Notebook release image..."

	docker pull $(docker_release_image_jupyter_repository):$(docker_image_version) || true
	docker pull $(docker_release_image_jupyter_repository):latest || true

################################################################################################################################################################

build: build-images ## Build all images

build-images: ## Build development and release images

	@ echo "Building images..."

	@ $(MAKE) build-development-image
	@ $(MAKE) build-release-images

build-development-image: pull-development-image ## Build development image

	@ echo "Building development image..."

	docker build \
		--file="$(CURDIR)/docker/development/Dockerfile" \
		--tag=$(docker_development_image_repository):$(docker_image_version) \
		--tag=$(docker_development_image_repository):latest \
		--build-arg="VERSION=$(docker_image_version)" \
		"$(CURDIR)"

build-release-images: ## Build release images

	@ echo "Building release images..."

	@ $(MAKE) build-release-image-cpp

	@ $(MAKE) build-release-image-python

	@ $(MAKE) build-release-image-jupyter

build-release-image-cpp: build-development-image pull-release-image-cpp

	@ echo "Building C++ release image..."

	docker build \
		--file="$(CURDIR)/docker/release/Dockerfile" \
		--tag=$(docker_release_image_cpp_repository):$(docker_image_version) \
		--tag=$(docker_release_image_cpp_repository):latest \
		--build-arg="VERSION=$(docker_image_version)" \
		--target=cpp-release \
		"$(CURDIR)"

build-release-image-python: build-development-image pull-release-image-python

	@ echo "Building Python release image..."

	docker build \
		--file="$(CURDIR)/docker/release/Dockerfile" \
		--tag=$(docker_release_image_python_repository):$(docker_image_version) \
		--tag=$(docker_release_image_python_repository):latest \
		--build-arg="VERSION=$(docker_image_version)" \
		--target=python-release \
		"$(CURDIR)"

build-release-image-jupyter: pull-release-image-jupyter

	@ echo "Building Jupyter Notebook release image..."

	docker build \
		--file="$(CURDIR)/docker/jupyter/Dockerfile" \
		--tag=$(docker_release_image_jupyter_repository):$(docker_image_version) \
		--tag=$(docker_release_image_jupyter_repository):latest \
		--build-arg="JUPYTER_NOTEBOOK_IMAGE_REPOSITORY=$(jupyter_notebook_image_repository)" \
		"$(CURDIR)/docker/jupyter"

build-documentation: build-development-image ## Build documentation

	@ $(MAKE) build-documentation-standalone

build-documentation-standalone: ## Build documentation (standalone)

	@ echo "Building documentation..."

	docker run \
		--rm \
		--volume="$(CURDIR):/app:delegated" \
		--volume="/app/build" \
		--workdir=/app/build \
		$(docker_development_image_repository):$(docker_image_version) \
		/bin/bash -c "cmake -DBUILD_UNIT_TESTS=OFF -DBUILD_PYTHON_BINDINGS=OFF -DBUILD_DOCUMENTATION=ON .. \
		&& $(MAKE) docs"

build-packages: ## Build packages

	@ echo "Building packages..."

	@ $(MAKE) build-packages-cpp
	@ $(MAKE) build-packages-python

build-packages-cpp: build-development-image ## Build C++ packages

	@ $(MAKE) build-packages-cpp-standalone

build-packages-cpp-standalone: ## Build C++ packages (standalone)

	@ echo "Building C++ packages..."

	docker run \
		--rm \
		--volume="$(CURDIR):/app:delegated" \
		--volume="/app/build" \
		--workdir=/app/build \
		$(docker_development_image_repository):$(docker_image_version) \
		/bin/bash -c "cmake -DBUILD_UNIT_TESTS=OFF -DBUILD_PYTHON_BINDINGS=OFF -DCPACK_GENERATOR=DEB .. \
		&& $(MAKE) package \
		&& mkdir -p /app/packages/cpp \
		&& mv /app/build/*.deb /app/packages/cpp"

build-packages-python: build-development-image ## Build Python packages
	
	@ $(MAKE) build-packages-python-standalone

build-packages-python-standalone: ## Build Python packages (standalone)

	@ echo "Building Python packages..."

	docker run \
		--rm \
		--volume="$(CURDIR):/app:delegated" \
		--volume="/app/build" \
		--workdir=/app/build \
		$(docker_development_image_repository):$(docker_image_version) \
		/bin/bash -c "cmake -DBUILD_UNIT_TESTS=OFF -DBUILD_PYTHON_BINDINGS=ON .. \
		&& $(MAKE) -j 4 \
		&& mkdir -p /app/packages/python \
		&& mv /app/build/bindings/python/dist/*.whl /app/packages/python"

################################################################################################################################################################

start-development-no-link: build-development-image ## Start development environment

	@ echo "Starting development environment..."

	docker run \
		-it \
		--rm \
		--privileged \
		--volume="$(CURDIR):/app:delegated" \
		--volume="$(CURDIR)/tools/development/helpers:/app/build/helpers:ro,delegated" \
		--workdir=/app/build \
		$(docker_development_image_repository):$(docker_image_version) \
		/bin/bash

start-development-link: ## Start linked development environment

	$(if $(links), , $(error "You need to provide the links to the C++ dependency repositories you want to link with, separated by white spaces. For example: make start-development-link links="/home/OSTk/open-space-toolkit-io /home/OSTk/open-space-toolkit-core"))

	@ echo "Starting development environment (linked)..."

	@ project_directory="$(CURDIR)" docker_development_image_repository=$(docker_development_image_repository) docker_image_version=$(docker_image_version) "$(CURDIR)/tools/development/start.sh" --link $(links)

ifndef link
start-development: start-development-no-link
else
start-development: start-development-link
endif

start-python: build-release-image-python ## Start Python runtime environment

	@ echo "Starting Python runtime environment..."

	docker run \
		-it \
		--rm \
		$(docker_release_image_python_repository):$(docker_image_version)

start-jupyter-notebook: build-release-image-jupyter ## Starting Jupyter Notebook environment

	@ echo "Starting Jupyter Notebook environment..."

	docker run \
		-it \
		--rm \
		--publish="$(jupyter_notebook_port):8888" \
		--volume="$(CURDIR)/bindings/python/docs:/home/jovyan/docs" \
		--workdir="/home/jovyan" \
		$(docker_release_image_jupyter_repository):$(docker_image_version) \
		bash -c "start-notebook.sh --ServerApp.token=''"

debug-jupyter-notebook: build-release-image-jupyter

	@ echo "Debugging Jupyter Notebook environment..."

	docker run \
		-it \
		--rm \
		--publish="$(jupyter_notebook_port):8888" \
		--volume="$(CURDIR)/bindings/python/docs:/home/jovyan/docs" \
		--volume="$(CURDIR)/tutorials/python/notebooks:/home/jovyan/tutorials" \
		--volume="$(CURDIR)/lib/libopen-space-toolkit-$(project_name).so.0:/opt/conda/lib/python$(jupyter_python_version)/site-packages/ostk/$(project_name)/libopen-space-toolkit-$(project_name).so.0:ro" \
		--volume="$(CURDIR)/lib/$(jupyter_project_name_python_shared_object).so:/opt/conda/lib/python$(jupyter_python_version)/site-packages/ostk/$(project_name)/$(jupyter_project_name_python_shared_object).so:ro" \
		--workdir="/home/jovyan" \
		$(docker_release_image_jupyter_repository):$(docker_image_version) \
		bash -c "start-notebook.sh --ServerApp.token=''"

################################################################################################################################################################

debug-development: build-development-image ## Debug development environment

	@ echo "Debugging development environment..."

	docker run \
		-it \
		--rm \
		$(docker_development_image_repository):$(docker_image_version) \
		/bin/bash

debug-cpp-release: build-release-image-cpp ## Debug C++ release environment

	@ echo "Debugging C++ release environment..."

	docker run \
		-it \
		--rm \
		--entrypoint=/bin/bash \
		$(docker_release_image_cpp_repository):$(docker_image_version)

debug-python-release: build-release-image-python ## Debug Python release environment

	@ echo "Debugging Python release environment..."

	docker run \
		-it \
		--rm \
		--entrypoint=/bin/bash \
		$(docker_release_image_python_repository):$(docker_image_version)

################################################################################################################################################################

test: ## Run tests

	@ echo "Running tests..."

	@ $(MAKE) test-unit
	@ $(MAKE) test-coverage

test-unit: ## Run unit tests

	@ echo "Running unit tests..."

	@ $(MAKE) test-unit-cpp
	@ $(MAKE) test-unit-python

test-unit-cpp: build-development-image ## Run C++ unit tests
	
	@ $(MAKE) test-unit-cpp-standalone

test-unit-cpp-standalone: ## Run C++ unit tests (standalone)

	@ echo "Running C++ unit tests..."

	docker run \
		--rm \
		--volume="$(CURDIR):/app:delegated" \
		--volume="$(CURDIR)/share/OpenSpaceToolkit:/usr/local/share/OpenSpaceToolkit:delegated" \
		--volume="/app/build" \
		--workdir=/app/build \
		$(docker_development_image_repository):$(docker_image_version) \
		/bin/bash -c "cmake -DBUILD_PYTHON_BINDINGS=OFF -DBUILD_UNIT_TESTS=ON .. \
		&& $(MAKE) -j 4 \
		&& $(MAKE) test"

test-unit-python: build-development-image ## Run Python unit tests

	@ $(MAKE) test-unit-python-standalone

test-unit-python-standalone: ## Run Python unit tests (standalone)

	@ echo "Running Python unit tests..."

	docker run \
		--rm \
		--volume="$(CURDIR):/app:delegated" \
		--volume="$(CURDIR)/share/OpenSpaceToolkit:/usr/local/share/OpenSpaceToolkit:delegated" \
		--volume="/app/build" \
		--workdir=/app/build \
		--entrypoint="" \
		$(docker_development_image_repository):$(docker_image_version) \
		/bin/bash -c "cmake -DBUILD_PYTHON_BINDINGS=ON -DBUILD_UNIT_TESTS=OFF .. \
		&& $(MAKE) -j 4 && pip install bindings/python/dist/*311*.whl \
		&& cd /usr/local/lib/python3.11/site-packages/ostk/$(project_name)/ \
		&& python3.11 -m pytest -sv ."

test-coverage: ## Run test coverage cpp

	@ echo "Running coverage tests..."

	@ $(MAKE) test-coverage-cpp

test-coverage-cpp: build-development-image ## Run C++ tests with coverage

	@ $(MAKE) test-coverage-cpp-standalone

test-coverage-cpp-standalone: ## Run C++ tests with coverage (standalone)

	@ echo "Running C++ coverage tests..."

	docker run \
		--rm \
		--volume="$(CURDIR):/app:delegated" \
		--volume="$(CURDIR)/share/OpenSpaceToolkit:/usr/local/share/OpenSpaceToolkit:delegated" \
		--volume="/app/build" \
		--workdir=/app/build \
		$(docker_development_image_repository):$(docker_image_version) \
		/bin/bash -c "cmake -DBUILD_UNIT_TESTS=ON -DBUILD_PYTHON_BINDINGS=OFF -DBUILD_CODE_COVERAGE=ON .. \
		&& $(MAKE) -j 4 \
		&& $(MAKE) coverage \
		&& (rm -rf /app/coverage || true) \
		&& mkdir /app/coverage \
		&& mv /app/build/coverage* /app/coverage"

################################################################################################################################################################

clean: ## Clean

	@ echo "Cleaning up..."

	rm -rf "$(CURDIR)/build"
	rm -rf "$(CURDIR)/bin/"*.test*
	rm -rf "$(CURDIR)/docs/html"
	rm -rf "$(CURDIR)/docs/latex"
	rm -rf "$(CURDIR)/lib/"*.so*
	rm -rf "$(CURDIR)/coverage"
	rm -rf "$(CURDIR)/packages"
	rm -rf "$(CURDIR)/.open-space-toolkit"

################################################################################################################################################################

.PHONY: pull pull-development-image \
		build build-images build-development-image \
		pull-release-images pull-release-image-cpp pull-release-image-python pull-release-image-jupyter \
		build-release-image-cpp build-release-image-python build-release-image-jupyter \
		build-documentation build-packages-cpp \
		start-development start-python start-jupyter-notebook debug-jupyter-notebook \
		debug-development debug-cpp-release debug-python-release \
		test test-unit test-unit-cpp test-unit-python test-coverage test-coverage-cpp \
		clean

################################################################################################################################################################

help:

	@grep -E '^[0-9a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

export DOCKER_BUILDKIT = 1

.DEFAULT_GOAL := help

################################################################################################################################################################

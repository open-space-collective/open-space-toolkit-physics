################################################################################################################################################################

# @project        Library ▸ Physics
# @file           Makefile
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

project_name := library-physics
project_version := $(shell git describe --tags --always)

docker_registry := openspacecollective
docker_image_repository = $(docker_registry)/$(project_name)

################################################################################################################################################################

build_development_image: ./tools/development/docker/Dockerfile

	docker build \
	--build-arg=VERSION=$(project_version) \
	--tag=$(docker_image_repository):$(project_version) \
	--file=./tools/development/docker/Dockerfile
	./tools/development/docker

push_development_image: build_development_image

	docker push $(docker_image_repository):$(project_version)

################################################################################################################################################################

.PHONY: build_development_image push_development_image

################################################################################################################################################################

SHELL := /bin/bash
RM    := rm -rf

all: ./build/Makefile
	@ $(MAKE) -C build

./build/Makefile:
	@ (mkdir -p build && cd build >/dev/null 2>&1 && cmake ..)

distclean:
	@- (mkdir -p build && cd build >/dev/null 2>&1 && cmake .. >/dev/null 2>&1)
	@- $(MAKE) --silent -C build clean || true
	@- $(RM) ./build/*
	@- $(RM) ./build
	@- $(RM) ./docs/*.html
	@- $(RM) ./docs/*.css
	@- $(RM) ./docs/*.png
	@- $(RM) ./docs/*.jpg
	@- $(RM) ./docs/*.gif
	@- $(RM) ./docs/*.tiff
	@- $(RM) ./docs/*.php
	@- $(RM) ./docs/search
	@- $(RM) ./docs/installdox


ifeq ($(findstring distclean,$(MAKECMDGOALS)),)

    $(MAKECMDGOALS): ./build/Makefile
	@ $(MAKE) -C build $(MAKECMDGOALS)

endif

################################################################################################################################################################

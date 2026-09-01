MainTest=phd-mpi

.PHONY: create-phd-mpi distclean-phd-mpi create distclean clean run run-bash run-bash-phd-mpi

volume_folder = not-set

ifeq ($(volume_folder), not-set)
	volume_folder = $(abspath $(dir $(lastword $(MAKEFILE_LIST)))/..)
endif

## Clean
clean:
	@docker container prune
	@docker rmi $$(docker images --filter "dangling=true" -q --no-trunc)

## Create
create:
	@make create-$(MainTest)

create-phd-mpi:
	@docker build --progress=plain -f Dockerfile --target phd-mpi . -t phd-mpi:1.0.0

## Run
run:
	@make run-$(MainTest)

run-phd-mpi:
	@docker run --rm -it -v ${volume_folder}:/shared -p 8080:8080 phd-mpi:1.0.0


run-bash:
	@make run-bash-$(MainTest)

run-bash-phd-mpi:
	@docker run --rm -it -v ${volume_folder}:/shared -p 8080:8080 phd-mpi:1.0.0 bash

## Distclean
distclean:
	@make distclean-$(MainTest)

distclean-phd-mpi:
	@docker container prune
	@docker rmi phd-mpi:1.0.0
	@docker rmi $$(docker images --filter "dangling=true" -q --no-trunc)
	@docker buildx prune -f

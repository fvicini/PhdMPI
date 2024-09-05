MainTest=phd-mpi

.PHONY: create-phd-mpi distclean-phd-mpi create distclean clean run run-bash run-bash-phd-mpi

## Clean
clean:
	@sudo docker container prune
	@sudo docker rmi $$(sudo docker images --filter "dangling=true" -q --no-trunc)

## Create
create:
	@make create-$(MainTest)

create-phd-mpi:
	sudo docker build -f Dockerfile --target phd-mpi . -t phd-mpi:1.0.0

## Run
run:
	@make run-$(MainTest)

run-phd-mpi:
	@sudo docker run --rm -it -p 8080:8080 phd-mpi:1.0.0


run-bash:
	@make run-bash-$(MainTest)

run-bash-phd-mpi:
	@sudo docker run --rm -it -p 8080:8080 phd-mpi:1.0.0 bash

## Distclean
distclean:
	@make distclean-$(MainTest)

distclean-phd-mpi:
	@sudo docker container prune
	@sudo docker rmi phd-mpi:1.0.0
	@sudo docker rmi $$(sudo docker images --filter "dangling=true" -q --no-trunc)
	@sudo docker buildx prune -f

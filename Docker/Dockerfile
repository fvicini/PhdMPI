## Set Stage
FROM ubuntu:20.04 AS phd-mpi

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
apt-utils \
ssh \
software-properties-common \
apt-transport-https ca-certificates gnupg software-properties-common wget \
bash-completion \
gcc-9 g++-9 gcc-9-base \
libopenmpi-dev \
&& update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-9 100 \
&& update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-9 100

RUN wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null && \
apt-add-repository 'deb https://apt.kitware.com/ubuntu/ bionic main' && \
add-apt-repository ppa:deadsnakes/ppa -y && \
apt-get update && \
apt-get install -y python3.10 && \
apt-get install -y python3.10-distutils && \
apt-get install -y python3.10-dev && \
update-alternatives --install /usr/bin/python3 python3 /usr/bin/python3.10 100 && \
update-alternatives --install /usr/bin/python python /usr/bin/python3.10 100 && \
wget https://bootstrap.pypa.io/get-pip.py && \
python3 get-pip.py && \
rm -rf get-pip.py

RUN apt-get update && \
apt-get install -y cmake && \
apt-get install -y git

RUN pip3 install jupyter --no-cache-dir && \
pip3 install RISE --no-cache-dir && \
pip3 install jupyter_nbextensions_configurator --no-cache-dir && \
pip3 install numpy --no-cache-dir && \
pip3 install scipy --no-cache-dir && \
pip3 install matplotlib --no-cache-dir && \
pip3 install tqdm --no-cache-dir && \
pip3 install mpi4py --no-cache-dir

WORKDIR /content/
RUN git clone https://github.com/fvicini/PhdMPI.git
WORKDIR /content/PhdMPI

RUN echo "source /usr/share/bash-completion/completions/git;cd /content/PhdMPI;git pull;" > /content/on_startup.sh
RUN chmod +x /content/on_startup.sh

ENV OMPI_ALLOW_RUN_AS_ROOT=1
ENV OMPI_ALLOW_RUN_AS_ROOT_CONFIRM=1

CMD cd /content/PhdMPI && git pull && \ 
jupyter notebook --ip 0.0.0.0 --port=8080 --no-browser --allow-root

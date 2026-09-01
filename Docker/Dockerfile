## Set Stage
FROM ubuntu:24.04 AS phd-mpi

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
    python3.12 \
    python3.12-dev \
    python3-pip \
    python3-full \
    gcc-13 \
    g++-13 \
    gfortran-13 \
    build-essential \
    ca-certificates \
    libblas3 \
    git \
    libopenmpi-dev \
    cmake \
 && rm -rf /var/lib/apt/lists/*

RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-13 100 \
 && update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-13 100 \
 && update-alternatives --install /usr/bin/gfortran gfortran /usr/bin/gfortran-13 100 \
 && update-alternatives --install /usr/bin/python3 python3 /usr/bin/python3.12 100

RUN python3 -m venv /opt/venv

ENV PATH="/opt/venv/bin:$PATH"

RUN pip3 install --upgrade pip && \
pip3 install jupyter --no-cache-dir && \
pip3 install RISE --no-cache-dir && \
pip3 install jupyter_nbextensions_configurator --no-cache-dir && \
pip3 install numpy --no-cache-dir && \
pip3 install scipy --no-cache-dir && \
pip3 install matplotlib --no-cache-dir && \
pip3 install tqdm --no-cache-dir && \
pip3 install mpi4py --no-cache-dir && \
pip3 install jupyterlab_rise --no-cache-dir

WORKDIR /shared

ENV OMPI_ALLOW_RUN_AS_ROOT=1
ENV OMPI_ALLOW_RUN_AS_ROOT_CONFIRM=1

CMD ["jupyter", "notebook", "--ip=0.0.0.0", "--port=8080", "--no-browser", "--allow-root"]

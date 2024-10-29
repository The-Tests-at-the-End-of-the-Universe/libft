FROM gcc:latest

WORKDIR /libft
COPY . .

RUN apt-get update
RUN apt-get install -y sudo
RUN apt-get install -y libbsd-dev
RUN cd libft_tester/null_checker/libbacktrace && mkdir build && cd build && ../configure && sudo make && sudo make install

SHELL ["/bin/bash", "-c"]

ENTRYPOINT cd libft_tester && bash tester.sh -nf -nn

FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive
ENV LANG C.UTF-8
ENV LC_ALL C.UTF-8

RUN apt-get -y update && \
    apt-get -y upgrade && \
    apt-get -y dist-upgrade && \
    apt-get -y autoremove && \
    apt-get install -y build-essential gdb wget git libssl-dev libcrypto++-dev libgtest-dev clang-format && \
    mkdir ~/temp && cd ~/temp && \
    apt-get install -y cmake && \
    cd ~/temp &&  wget -q https://sourceforge.net/projects/boost/files/boost/1.81.0/boost_1_81_0.tar.gz && \
    tar -zxf boost_1_81_0.tar.gz && cd ~/temp/boost_1_81_0 && ./bootstrap.sh && ./b2 cxxflags="-std=c++11" --reconfigure --with-fiber --with-context --with-atomic --with-date_time --with-filesystem --with-url install && \
    cd ~/temp && git clone -b v1.15 https://github.com/linux-test-project/lcov.git && cd lcov && make install && cd .. && \
    apt-get install -y libperlio-gzip-perl libjson-perl && \
    rm -rf ~/temp/* && \
    apt-get autoremove -y &&\
    apt-get clean -y &&\
    rm -rf /var/lib/apt/lists/*

RUN cd /usr/src/gtest && sudo cmake CMakeLists.txt && sudo make && cp *.a /usr/lib

RUN apt-get -y update && \
    apt-get install -y libpq-dev libsqlite3-dev unzip && \
    cd ~/temp && \
    git clone https://github.com/jtv/libpqxx.git && cd libpqxx && \
    git checkout 7.6.1 && \
    mkdir build && cd build && \
    cmake .. -DPostgreSQL_TYPE_INCLUDE_DIR=/usr/include/postgresql/libpq && \
    make -j6 && make install && \
    cd ~/temp && \
    wget -q https://github.com/SOCI/soci/archive/refs/tags/v4.0.3.zip && \
    unzip v4.0.3.zip && \
    cd soci-4.0.3 && \
    mkdir build && cd build && \
    cmake .. -DSOCI_WITH_BOOST=ON -DSOCI_WITH_POSTGRESQL=ON -DSOCI_WITH_SQLITE3=ON -DCMAKE_CXX_STANDARD=11 -DSOCI_CXX11=ON && \
    make -j6 && make install && \
    rm -rf ~/temp/* && \
    apt-get autoremove -y &&\   
    apt-get clean -y &&\
    rm -rf /var/lib/apt/lists/*

RUN apt-get -y update && \
    apt install libopencv-dev python3-opencv

RUN cd ~/temp && \
    git clone https://github.com/okyfirmansyah/libasyik.git && cd libasyik && \
    git submodule update --init --recursive && \
    cmake -Bbuild . &&  cd build && \
    make -j4 && make install && \
    rm -rf ~/temp/*

RUN apt-get install curl

COPY . .

RUN git submodule update --init --recursive && \
    cmake -Bbuild . && \
    cd build && make

ENV PORT 8080

EXPOSE 8080

CMD ["./build/image_resizer"]






# image-resizer

## Local

To Run it in local, install all dependencies, you can see all dependencies needed to be installed from Dockerfile

After that run

```
git submodule update --init --recursive && \
    cmake -Bbuild . && \
    cd build && make
```

## Run from docker

```
docker build -t <username>/<project_name> .
```

```
docker run --net=host <image_id>
```

for checking the request use

```
docker exec -it <container_id> bash
```

after you got into its terminal, POST request using wget

## Unit test

For unit test, put test.jpg into build file and then run
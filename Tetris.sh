xhost +local:docker

if [[ "$(docker images -q tetris 2> /dev/null)" == "" ]]; then
  docker build -t tetris .
fi

docker run -d --rm --env="DISPLAY" --net=host tetris


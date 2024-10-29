#https://stackoverflow.com/questions/70852648/remove-docker-image-if-it-exists

#TODO: add flags to run without remaking image
#TODO: add flags to run docker without immediately starting tester

check_image=$(docker images -af reference='libft_tester/tester' -q)
check_container=$(docker ps -a | grep 'libft_tester/tester' | awk '{print $1}')


if [ -z "$check_container" ];
then :
else docker rm $check_container
fi

if [ -z "$check_image" ];
then :
else docker rmi $check_image
fi

cd ..


docker build -f ./libft_tester/Dockerfile -t libft_tester/tester .

# docker exec -t -i libft_tester/tester /bin/bash
# exit 0

docker run -it libft_tester/tester

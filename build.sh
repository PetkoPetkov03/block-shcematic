if [ ! -d "./dist" ]
then mkdir ./dist
fi

clang++ -g -o "./dist/block_scheme" ./src/main.cpp -lraylib 

./dist/block_scheme

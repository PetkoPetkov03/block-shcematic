if [ ! -d "./dist" ]
then mkdir ./dist
fi

clang++ -g -o "./dist/block_scheme" ./src/main.cpp -lraylib 

if [ !$1 ]
then valgrind  --leak-check=yes -s ./dist/block_scheme
else 
  valgrind  $1 $2 -s ./dist/block_scheme
fi
  

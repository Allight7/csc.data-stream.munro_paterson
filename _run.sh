for suf in 1e8; do 
  g++ -O2 -Wall -std=c++11 test_$suf.cpp -o test_$suf && ./test_$suf
done


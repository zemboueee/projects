for i in $(find tests/pgn/*.pgn); do
    ./build/chessengine --pgn $i;
done

echo "============= PERFT TESTSUITE ==========="

for i in $(seq 1 9); do
    echo "===== TEST N°$i =====";
    echo $(cat tests/perft/$i.perft)
    echo "Intended result: $(cat tests/perft/$i.out)";
    echo -n "Result: "
    ./build/chessengine --perft "tests/perft/$i.perft"
done

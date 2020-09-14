echo "Building project!"
bash build.sh

echo "Executing Tests!"
cd build
./TestLexer


echo "queen O3"
cd C/single_thread
./queen_O3.sh $1

echo ""
echo "queen omp O3"
cd ../omp
./queen_omp_O3.sh $1

echo ""
echo "queen rs"
cd ../../Rust/single_thread
./queen_rs.sh $1

echo ""
echo "queen rs threaded"
cd ../threaded
./queen_rs_threaded.sh $1

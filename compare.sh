
echo "queen"
cd C/single_thread
./queen.sh $1

echo ""
echo "queen O3"
./queen_O3.sh $1

echo ""
echo "queen omp"
cd ../omp
./queen_omp.sh $1

echo ""
echo "queen omp O3"
./queen_omp_O3.sh $1

echo ""
echo "queen rs"
cd ../../Rust/single_thread
./queen_rs.sh $1

echo ""
echo "queen rs release"
./queen_rs_release.sh $1

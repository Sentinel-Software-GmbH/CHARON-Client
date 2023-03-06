cppcheck --enable=all --inline-suppr --suppress=portability include/ src/ port/windows/src port/demo/src -I port/windows/inc -I port/demo/inc  --inconclusive --xml --xml-version=2 --force 2> cppcheck.xml
py toolchain/htmlreport/cppcheck-htmlreport --file="cppcheck.xml" --report-dir=build/cppCheckReport

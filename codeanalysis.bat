cppcheck --enable=all --inline-suppr src/ Ports/Windows/src --suppress=variableScope --inconclusive --xml --xml-version=2 --force 2> cppcheck.xml
py toolchain/htmlreport/cppcheck-htmlreport --file="cppcheck.xml" --report-dir=build/cppCheckReport

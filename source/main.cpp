#include <iostream>
#include <iomanip>
#include <cmath>
#include <array>
#include <string>

// ISSUE DESCRIPTION:
//
// There is a change of behavior of the compiler generated code for release-x64 builds
// with floating point model = fast (/fp:fast) between Visual Studio 2013 and 2015/2017.
// This is considered be a bug, since it causes hidden unexpected result at runtime
// after compiler change.
//
// Compilers under test: VS 2013 (Version 12.0.40629.00 Update 5)
//                       VS 2015 (Version 14.0.25431.01 Update 3)
//                       VS 2017 (Version 15.4.1)

//-----------------------------------------------------------------------------
// NOTE: This test produce same results on all tested compilers!
//       The results are wrong for some values and correct for others!
void TestOne()
{
  std::cout << "TEST 1:" << std::endl;

  const int count = 32;
  for (int i = 1; i < count; ++i)
  {
    std::cout << "  Result for power of " << std::setw(2) << i << ": ";

    auto v = std::pow(2, i);
    auto r = std::log(v) / std::log(2);

    const int t = (r == i) ? 0 : 1;

    std::array<std::string, 2> tx = { "OK", "NOK!!!"};

    std::cout << std::fixed << std::setprecision(3) << "r: " << r
                                                    << "; ri: " << static_cast<int>(r)
                                                    << " - " << tx[t] << std::endl;
  }
}

//-----------------------------------------------------------------------------
// NOTE: This test produce different results for release-x64 builds!!!
//       VS2013-x64 generates different result then VS2015-x64 and VS2017-x64.
//       VS2013-x64 is correct!!!
//       VS2015-x64 and VS2017-x64 are wrong!!!
void TestTwo()
{
  std::cout << "TEST 2:" << std::endl;

  int v = 4096;  // = 2^12, PLEACE NOTE the difference between TestOne() and TestTwo() for VS2013-x64!
  auto r = std::log(v) / std::log(2);

  const int t = (r == static_cast<int>(r)) ? 0 : 1;
  std::array<std::string, 2> tx = { "OK", "NOK!!!" };

  std::cout << "  Result: ";
  std::cout << std::fixed << std::setprecision(3) << "r: " << r
                                                  << "; ri: " << static_cast<int>(r)
                                                  << " - " << tx[t] << std::endl;
}

//-----------------------------------------------------------------------------
// NOTE: This is just a test to check if the optimization causes this issue.
#pragma optimize("", off)
void TestThree()
{
  std::cout << "TEST 3:" << std::endl;

  int v = 4096;
  auto r = std::log(v) / std::log(2);

  const int t = (r == static_cast<int>(r)) ? 0 : 1;
  std::array<std::string, 2> tx = { "OK", "NOK!!!" };

  std::cout << "  Result: ";
  std::cout << std::fixed << std::setprecision(3) << "r: " << r
                                                  << "; ri: " << static_cast<int>(r)
                                                  << " - " << tx[t] << std::endl;
}
#pragma optimize("", on)

//-----------------------------------------------------------------------------
int main()
{
  TestOne();

  TestTwo();

  TestThree();

  getchar();

  return 0;
}

project('adventofcode2017', 'cpp',
        default_options : ['cpp_std=c++17', 'buildtype=debugoptimized'],
        )

gtest_dep = dependency('gtest')
boost_dep = dependency('boost')

days = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
	21, 22, 23, 24, 25]

foreach day : days
  day_with_num = 'day' + day.to_string()
  cpp_file = day_with_num + '.cpp'
  day_test = day_with_num + '-test'
  test_cpp_file = day_test + '.cpp'
  input_file = day_with_num + '.input'

  testcpp_file = day_with_num + '.cpp'
  executable(day_with_num, cpp_file, 'main.cpp', dependencies : [boost_dep])

  day_test_exe = executable(day_test, test_cpp_file, cpp_file, 'testmain.cpp',
                            dependencies : [gtest_dep, boost_dep])
  test(day_with_num, day_test_exe, timeout: 60)

  configure_file(input: input_file, output: input_file, copy: true)
endforeach




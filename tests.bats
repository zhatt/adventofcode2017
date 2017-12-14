#!/usr/bin/env bats

runcmd() {
    "$@" 2>/dev/null
}

run_stdin() {
	local stdin="$1"
	shift
	local prog="$1"
	shift
	echo "$stdin" | "$BATS_TEST_DIRNAME/$prog" "$@" 2>/dev/null
}

runtest.old() {
	local testname=$1
	local day=${testname%%.*}
	run runcmd $BATS_TEST_DIRNAME/$testname < "$day.input"
        [[ $status -eq 0 ]]
	[[ $output == "$(< $testname.output)" ]]
}

runtest() {
	local testname=$1
	local day=${testname%%.*}
	local part=${testname##*.}

	run runcmd $BATS_TEST_DIRNAME/$day -$part < "$day.input"
        [[ $status -eq 0 ]]
	[[ $output == "$(< $testname.output)" ]]
}

@test "day1.1" {
	runtest "${BATS_TEST_DESCRIPTION}"
}

@test "day1.1.1" {
	run run_stdin '1122' day1 -1
	[[ $status -eq 0 ]]
	[[ $output == '3' ]]
}

@test "day1.1.2" {
	run run_stdin '1111' day1 -1
	[[ $status -eq 0 ]]
	[[ $output == '4' ]]
}

@test "day1.1.3" {
	run run_stdin '1234' day1 -1
	[[ $status -eq 0 ]]
	[[ $output == '0' ]]
}

@test "day1.1.4" {
	run run_stdin '91212129' day1 -1
	[[ $status -eq 0 ]]
	[[ $output == '9' ]]
}

@test "day1.2" {
	runtest "${BATS_TEST_DESCRIPTION}"
}

@test "day1.2.1" {
	run run_stdin '1212' day1 -2
	[[ $status -eq 0 ]]
	[[ $output == '6' ]]
}

@test "day1.2.2" {
	run run_stdin '1221' day1 -2
	[[ $status -eq 0 ]]
	[[ $output == '0' ]]
}

@test "day1.2.3" {
	run run_stdin '123425' day1 -2
	[[ $status -eq 0 ]]
	[[ $output == '4' ]]
}

@test "day1.2.4" {
	run run_stdin '123123' day1 -2
	[[ $status -eq 0 ]]
	[[ $output == '12' ]]
}

@test "day1.2.5" {
	run run_stdin '12131415' day1 -2
	[[ $status -eq 0 ]]
	[[ $output == '4' ]]
}

@test "day2.1" {
	runtest.old "${BATS_TEST_DESCRIPTION}"
}

@test "day2.2" {
	runtest.old "${BATS_TEST_DESCRIPTION}"
}

@test "day3.1" {
	runtest.old "${BATS_TEST_DESCRIPTION}"
}

@test "day3.2" {
	runtest.old "${BATS_TEST_DESCRIPTION}"
}

@test "day4.1" {
	runtest.old "${BATS_TEST_DESCRIPTION}"
}

@test "day4.2" {
	runtest.old "${BATS_TEST_DESCRIPTION}"
}

@test "day5.1" {
	runtest.old "${BATS_TEST_DESCRIPTION}"
}

@test "day5.2" {
	runtest.old "${BATS_TEST_DESCRIPTION}"
}

@test "day6.1" {
	runtest.old "${BATS_TEST_DESCRIPTION}"
}

@test "day6.2" {
	runtest.old "${BATS_TEST_DESCRIPTION}"
}

@test "day7.1" {
	runtest.old "${BATS_TEST_DESCRIPTION}"
}

@test "day7.2" {
	runtest.old "${BATS_TEST_DESCRIPTION}"
}

@test "day8.1" {
	runtest.old "${BATS_TEST_DESCRIPTION}"
}

@test "day8.2" {
	runtest.old "${BATS_TEST_DESCRIPTION}"
}

@test "day9.1" {
	runtest.old "${BATS_TEST_DESCRIPTION}"
}

@test "day9.2" {
	runtest.old "${BATS_TEST_DESCRIPTION}"
}

@test "day10.1" {
	runtest.old "${BATS_TEST_DESCRIPTION}"
}

@test "day10.2" {
	runtest.old "${BATS_TEST_DESCRIPTION}"
}

@test "day10.2.1" {
	run run_stdin '' day10.2
	[[ $status -eq 0 ]]
	[[ $output == 'a2582a3a0e66e6e86e3812dcb672a272' ]]
}

@test "day10.2.2" {
	run run_stdin 'AoC 2017' day10.2
	[[ $status -eq 0 ]]
	[[ $output == '33efeb34ea91902bb2f59c9920caa6cd' ]]
}

@test "day10.2.3" {
	run run_stdin '1,2,3' day10.2
	[[ $status -eq 0 ]]
	[[ $output == '3efbe78a8d82f29979031a4aa0b16a9d' ]]
}

@test "day10.2.4" {
	run run_stdin '1,2,4' day10.2
	[[ $status -eq 0 ]]
	[[ $output == '63960835bcdc130f0b66d7ff4f6a5a8e' ]]
}

@test "day11.1" {
	runtest.old "${BATS_TEST_DESCRIPTION}"
}

@test "day11.2" {
	runtest.old "${BATS_TEST_DESCRIPTION}"
}

@test "day12.1" {
	runtest.old "${BATS_TEST_DESCRIPTION}"
}

@test "day12.2" {
	runtest.old "${BATS_TEST_DESCRIPTION}"
}


#!/usr/bin/env bats

runcmd() {
    "$@" 2>/dev/null
}

run_stdin() {
	local stdin="$1"
	shift
	local prog="$1"
	shift
	echo -ne "$stdin" | "$BATS_TEST_DIRNAME/$prog" "$@" 2>/dev/null
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
	local input='\n'
	run run_stdin "$input" day10.2
	[[ $status -eq 0 ]]
	[[ $output == 'a2582a3a0e66e6e86e3812dcb672a272' ]]
}

@test "day10.2.2" {
	local input='AoC 2017\n'
	run run_stdin "$input" day10.2
	[[ $status -eq 0 ]]
	[[ $output == '33efeb34ea91902bb2f59c9920caa6cd' ]]
}

@test "day10.2.3" {
	local input='1,2,3\n'
	run run_stdin "$input" day10.2
	[[ $status -eq 0 ]]
	[[ $output == '3efbe78a8d82f29979031a4aa0b16a9d' ]]
}

@test "day10.2.4" {
	input='1,2,4\n'
	run run_stdin "$input" day10.2
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

